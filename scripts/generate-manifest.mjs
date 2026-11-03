import { execFileSync } from 'node:child_process';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const ROOT = path.resolve(__dirname, '..');

const KNOWN_MAJORS = ['计科', '软件工程', '信息管理', '电子信息', '通信工程'];
const KNOWN_TEACHERS = [
  '岳承君', '薛军', '王青松', '李晓光', '郭凯红', '张昕', '冯东晖', '刘建',
  '王龙', '王玉梅', '徐皓', '曲大鹏', '吕红', '马技', '张颖', '冯勇',
  '朱珠', '宋丽丽', '王嵘冰', '吴莹', '宫元九', '赵雪英', '王军', '王涛',
  '马利', '邰滢滢', '宣伟宏', '宋宝燕', '臧洁', '徐红艳', '王妍', '张利',
  '李响', '朱红宁', '任秀丽', '陈廷伟', '窦春轶', '李晓莉', '邴红艳', '张大波',
  '康鹏', '段苛苛', '宋琪', '刘砚秋', '孙鼎成', '孙鼎城', '尹凤杰', '杨晖',
  '时书丽', '历风满', '丁琳琳'
];

async function getTrackedEntries() {
  // 1. In GitHub Actions (blobless clone), avoid `git ls-tree -l` which lazily fetches 3.8GB of blobs.
  //    Instead, query GitHub Git Trees API which returns all paths + exact byte sizes in ~200ms.
  if (process.env.GITHUB_ACTIONS === 'true') {
    try {
      const repo = process.env.GITHUB_REPOSITORY || 'xunrana/LNU-CS-Courses-Resource';
      const sha = process.env.GITHUB_SHA || 'HEAD';
      const headers = {
        Accept: 'application/vnd.github+json',
        'User-Agent': 'LNU-CS-Courses-Resource-Builder'
      };
      if (process.env.GITHUB_TOKEN) {
        headers.Authorization = `Bearer ${process.env.GITHUB_TOKEN}`;
      }
      const res = await fetch(`https://api.github.com/repos/${repo}/git/trees/${sha}?recursive=1`, { headers });
      if (res.ok) {
        const data = await res.json();
        if (Array.isArray(data.tree) && data.tree.length > 0) {
          return data.tree
            .filter((item) => item.type === 'blob')
            .map((item) => ({ path: item.path, size: item.size || 0 }));
        }
      }
    } catch (err) {
      console.warn('[manifest] GitHub Trees API fallback:', err.message);
    }

    // Fallback in blobless CI without `-l` so git never lazy-fetches blobs
    try {
      const safeRoot = ROOT.replace(/\\/g, '/');
      const out = execFileSync(
        'git',
        ['-c', `safe.directory=${safeRoot}`, '-c', 'core.quotepath=false', 'ls-tree', '-r', 'HEAD'],
        { cwd: ROOT, encoding: 'utf8', maxBuffer: 32 * 1024 * 1024 }
      );
      const entries = [];
      for (const line of out.split(/\r?\n/)) {
        if (!line.trim()) continue;
        const tabIdx = line.indexOf('\t');
        if (tabIdx === -1) continue;
        const filePath = line.slice(tabIdx + 1).trim();
        entries.push({ path: filePath, size: 0 });
      }
      if (entries.length > 0) return entries;
    } catch {
      // ignore
    }
  }

  // 2. Local full clone: `git ls-tree -r -l HEAD` reads local objects in <150ms
  try {
    const safeRoot = ROOT.replace(/\\/g, '/');
    const out = execFileSync(
      'git',
      ['-c', `safe.directory=${safeRoot}`, '-c', 'core.quotepath=false', 'ls-tree', '-r', '-l', 'HEAD'],
      { cwd: ROOT, encoding: 'utf8', maxBuffer: 32 * 1024 * 1024 }
    );
    const entries = [];
    for (const line of out.split(/\r?\n/)) {
      if (!line.trim()) continue;
      const tabIdx = line.indexOf('\t');
      if (tabIdx === -1) continue;
      const meta = line.slice(0, tabIdx).trim().split(/\s+/);
      const filePath = line.slice(tabIdx + 1).trim();
      const size = Number.parseInt(meta[3], 10) || 0;
      entries.push({ path: filePath, size });
    }
    if (entries.length > 0) return entries;
  } catch {
    // Fallback to filesystem walk if git is unavailable
  }

  const entries = [];
  function walk(dir) {
    for (const ent of fs.readdirSync(dir, { withFileTypes: true })) {
      if (['.git', 'node_modules', '.vitepress', '.omc', '.claude'].includes(ent.name)) continue;
      const full = path.join(dir, ent.name);
      if (ent.isDirectory()) {
        walk(full);
      } else if (ent.isFile()) {
        const rel = path.relative(ROOT, full).replace(/\\/g, '/');
        entries.push({ path: rel, size: fs.statSync(full).size });
      }
    }
  }
  walk(ROOT);
  return entries;
}

function parseExamMeta(dirName, fileName) {
  const dirMatch = dirName.match(/^(\d+)\s+(.+)$/);
  const code = dirMatch ? dirMatch[1] : '';
  const course = dirMatch ? dirMatch[2].trim() : dirName.trim();

  const majors = KNOWN_MAJORS.filter((m) => fileName.includes(m));
  const teachers = KNOWN_TEACHERS.filter((t) => fileName.includes(t));

  const gradeMatch = fileName.match(/(\d{2}级)/);
  const grade = gradeMatch ? gradeMatch[1] : '';

  let year = '';
  const yearMatch = fileName.match(/(?:^|\s)(\d{2})\s+(\d{2})\s+([12])(?:\s|$)/);
  if (yearMatch) {
    const y1 = Number.parseInt(yearMatch[1], 10);
    const y2 = Number.parseInt(yearMatch[2], 10);
    const term = yearMatch[3];
    if (y2 === y1 + 1) {
      year = `20${yearMatch[1]}-20${yearMatch[2]}-${term}`;
    } else {
      year = `20${yearMatch[1]}-20${yearMatch[2]}-${term}`;
    }
  }

  const types = [];
  if (/试卷分析/.test(fileName)) {
    types.push('试卷分析');
  }
  if (/答案|评分标准/.test(fileName)) {
    types.push('含答案');
  }
  if (/(?:试卷|\s|_|（|\()[AaＡ](?:卷|\s|\.|（|\)|）|$)|[AaＡ](?:卷|试卷)/.test(fileName)) {
    types.push('A卷');
  }
  if (/(?:试卷|\s|_|（|\()[BbＢ](?:卷|\s|\.|（|\)|）|$)|[BbＢ](?:卷|试卷)/.test(fileName)) {
    types.push('B卷');
  }
  if (types.length === 0) {
    types.push('试卷');
  }

  return { code, course, majors, grade, year, teachers, types };
}

async function buildManifest() {
  const entries = await getTrackedEntries();

  const directories = {};
  const rootFiles = [];
  const exams = [];

  let resourceFiles = 0;
  let totalBytes = 0;
  const courseSet = new Set();
  const examDirSet = new Set();

  for (const item of entries) {
    const p = item.path;
    const parts = p.split('/');

    // Root-level reference files (PDFs / LICENSE)
    if (parts.length === 1) {
      if (/\.(pdf)$/i.test(p) || p === 'LICENSE') {
        rootFiles.push({ name: p, path: p, size: item.size });
      }
      continue;
    }

    const topDir = parts[0];
    const isCourseGroup = /^0[1-9]\s/.test(topDir);
    const isExamGroup = /^10\s/.test(topDir);
    if (!isCourseGroup && !isExamGroup) continue;

    // Ignore semester-level README.md
    if (parts.length === 2 && /^README\.md$/i.test(parts[1])) continue;
    if (parts.length < 2) continue;

    const subDir = parts[1];
    const dirKey = `${topDir}/${subDir}`;
    if (isCourseGroup) courseSet.add(dirKey);
    if (isExamGroup) examDirSet.add(dirKey);

    if (!directories[dirKey]) {
      directories[dirKey] = {
        title: subDir,
        group: topDir,
        empty: true,
        totalBytes: 0,
        fileCount: 0,
        files: []
      };
    }

    const leaf = parts[parts.length - 1];
    if (leaf === '.gitkeep') continue;

    const relInsideCourse = parts.slice(2).join('/');
    if (!relInsideCourse) continue;

    directories[dirKey].empty = false;
    directories[dirKey].totalBytes += item.size;
    directories[dirKey].fileCount += 1;
    directories[dirKey].files.push([relInsideCourse, item.size]);

    resourceFiles += 1;
    totalBytes += item.size;

    if (isExamGroup && /\.docx?$/i.test(leaf)) {
      const meta = parseExamMeta(subDir, leaf);
      exams.push({
        dir: subDir,
        code: meta.code,
        course: meta.course,
        name: leaf,
        path: p,
        size: item.size,
        majors: meta.majors,
        grade: meta.grade,
        year: meta.year,
        teachers: meta.teachers,
        types: meta.types
      });
    }
  }

  // Sort files in each directory naturally
  for (const dir of Object.values(directories)) {
    dir.files.sort((a, b) => a[0].localeCompare(b[0], 'zh-CN', { numeric: true }));
  }

  exams.sort((a, b) => a.dir.localeCompare(b.dir, 'zh-CN', { numeric: true }) || a.name.localeCompare(b.name, 'zh-CN', { numeric: true }));

  const manifest = {
    generatedAt: new Date().toISOString(),
    repo: 'XUNRANA/LNU-CS-Courses-Resource',
    branch: 'main',
    totals: {
      courses: courseSet.size,
      examCourses: examDirSet.size,
      examFiles: exams.length,
      resourceFiles,
      totalBytes
    },
    rootFiles,
    directories,
    exams
  };

  const publicDir = path.join(ROOT, '.vitepress', 'public');
  fs.mkdirSync(publicDir, { recursive: true });
  fs.writeFileSync(path.join(publicDir, 'manifest.json'), JSON.stringify(manifest));

  // Ensure brand logo is available in VitePress public assets while keeping assets/logo.svg for GitHub README
  const srcLogo = path.join(ROOT, 'assets', 'logo.svg');
  if (fs.existsSync(srcLogo)) {
    fs.copyFileSync(srcLogo, path.join(publicDir, 'logo.svg'));
  }

  console.log(
    `[manifest] Generated: ${manifest.totals.courses} courses, ${manifest.totals.examCourses} exam dirs, ${manifest.totals.examFiles} exam docs, ${manifest.totals.resourceFiles} total resource files.`
  );
}

buildManifest();
