import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import { defineConfig } from 'vitepress';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const ROOT = path.resolve(__dirname, '..');
const REPO_URL = 'https://github.com/XUNRANA/LNU-CS-Courses-Resource';

const PAGE_REWRITES: Record<string, string> = {
  'README.md': 'index.md',
  'CONTRIBUTING.md': 'contributing.md',
  '01 第一学期/README.md': 'semester/01.md',
  '02 第二学期/README.md': 'semester/02.md',
  '03 第三学期/README.md': 'semester/03.md',
  '04 第四学期/README.md': 'semester/04.md',
  '05 第五学期/README.md': 'semester/05.md',
  '06 第六学期/README.md': 'semester/06.md',
  '07 第七学期/README.md': 'semester/07.md',
  '08 第八学期/README.md': 'semester/08.md',
  '09 通识选修课/README.md': 'electives.md',
  '10 往年课程试卷/README.md': 'exams.md'
};

// Reverse map: rewritten relative path -> original source directory in repo
const REWRITE_TO_SRCDIR: Record<string, string> = {};
const SOURCE_TO_ROUTE: Record<string, string> = {};
for (const [src, dest] of Object.entries(PAGE_REWRITES)) {
  const dir = path.posix.dirname(src);
  REWRITE_TO_SRCDIR[dest] = dir === '.' ? '' : dir;
  const route = '/' + dest.replace(/index\.md$/, '').replace(/\.md$/, '');
  SOURCE_TO_ROUTE[src.toLowerCase()] = route;
  if (src.toLowerCase().endsWith('/readme.md')) {
    SOURCE_TO_ROUTE[src.slice(0, -10).toLowerCase()] = route;
  }
}

// Load pre-generated manifest paths to distinguish files vs directories accurately (even in sparse checkouts)
function loadKnownFilesAndDirs() {
  const files = new Set<string>(['LICENSE', '21版计算机科学与技术专业培养方案.pdf', '辽宁大学本科生成绩管理方法.pdf']);
  const dirs = new Set<string>();
  const manifestPath = path.join(__dirname, 'public', 'manifest.json');
  if (fs.existsSync(manifestPath)) {
    try {
      const data = JSON.parse(fs.readFileSync(manifestPath, 'utf8'));
      for (const rf of data.rootFiles || []) files.add(rf.path);
      for (const [dirKey, info] of Object.entries<any>(data.directories || {})) {
        dirs.add(dirKey);
        const top = dirKey.split('/')[0];
        if (top) dirs.add(top);
        for (const [relFile] of info.files || []) {
          const fullRel = `${dirKey}/${relFile}`;
          files.add(fullRel);
          const segs = fullRel.split('/');
          for (let i = 1; i < segs.length - 1; i++) {
            dirs.add(segs.slice(0, i + 1).join('/'));
          }
        }
      }
    } catch {
      // Ignore parse errors
    }
  }
  return { files, dirs };
}

const KNOWN = loadKnownFilesAndDirs();

function safeDecode(str: string): string {
  try {
    return decodeURIComponent(str);
  } catch {
    return str;
  }
}

function encodeGithubPath(p: string): string {
  return p
    .split('/')
    .map((seg) => encodeURIComponent(seg))
    .join('/');
}

function isRepoFile(repoRelPath: string): boolean {
  if (KNOWN.files.has(repoRelPath)) return true;
  if (KNOWN.dirs.has(repoRelPath)) return false;
  const full = path.join(ROOT, repoRelPath);
  if (fs.existsSync(full)) {
    return fs.statSync(full).isFile();
  }
  const leaf = repoRelPath.split('/').pop() || '';
  return /\.[a-z0-9]{1,8}$/i.test(leaf);
}

function normalizeAnchorKey(s: string): string {
  return s
    .trim()
    .toLowerCase()
    .replace(/[^\p{L}\p{N}]+/gu, '');
}

function escapeHtml(s: string): string {
  return s
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;');
}

export default defineConfig({
  lang: 'zh-CN',
  title: 'LNU CS 资源库',
  titleTemplate: ':title · 辽宁大学计科课程资源库',
  description:
    '辽宁大学计算机科学与技术专业课程资源库：82 门课程、320 份历年真题、2700+ 份课件 / 笔记 / 实验 / 代码与逐课备考攻略一站式整理。',
  base: '/LNU-CS-Courses-Resource/',
  cleanUrls: true,
  lastUpdated: false,
  ignoreDeadLinks: false,

  srcExclude: [
    '0*/*/**',
    '10*/*/**',
    'scripts/**',
    'assets/**',
    'node_modules/**',
    '.claude/**',
    '.omc/**'
  ],

  rewrites: PAGE_REWRITES,

  head: [
    ['link', { rel: 'icon', type: 'image/svg+xml', href: '/LNU-CS-Courses-Resource/logo.svg' }],
    ['meta', { name: 'theme-color', content: '#4f46e5' }],
    ['meta', { name: 'author', content: 'XUNRANA' }],
    [
      'meta',
      {
        name: 'keywords',
        content: '辽宁大学,辽大,计算机科学与技术,计科,课程资料,历年真题,期末复习,课件,笔记,实验报告,LNU,408'
      }
    ],
    ['meta', { property: 'og:type', content: 'website' }],
    ['meta', { property: 'og:site_name', content: 'LNU CS 资源库' }],
    ['meta', { property: 'og:locale', content: 'zh_CN' }]
  ],

  vite: {
    publicDir: path.resolve(__dirname, 'public'),
    server: {
      watch: {
        ignored: ['**/0*/*/**', '**/10*/*/**', '**/.git/**', '**/.omc/**', '**/.claude/**']
      }
    }
  },

  markdown: {
    math: true,
    theme: {
      light: 'github-light',
      dark: 'github-dark'
    },
    container: {
      tipLabel: '提示',
      warningLabel: '注意',
      dangerLabel: '警告',
      infoLabel: '说明',
      detailsLabel: '详细信息'
    },
    config(md) {
      // 1. Pre-process raw Markdown source for page-specific enhancements (zero disk mutation!)
      const origParse = md.parse.bind(md);
      md.parse = (src, env) => {
        const rel = (env?.relativePath || '').replace(/\\/g, '/');

        // Homepage: replace GitHub-only centered badge header & self-referential tip with custom <HomeHero /> + <GpaCalculator />
        if (rel === 'index.md' || rel === 'README.md') {
          src = src.replace(/^<div align="center">[\s\S]*?<\/div>\s*---\s*/m, '<HomeHero />\n\n');
          src = src.replace(
            /> \[!TIP\]\r?\n> \*\*在线文档站\*\*[^\r\n]*\r?\n?/m,
            ''
          );
          src = src.replace(
            /(- \*\*等级制\*\*：[^\r\n]+\r?\n)/,
            '$1\n<GpaCalculator />\n'
          );
        }

        // Exam Archive page: mount interactive multi-dimensional <ExamExplorer /> right before the 57-course catalog
        if (rel === 'exams.md' || rel === '10 往年课程试卷/README.md') {
          src = src.replace(
            /(## 🗂️ 课程索引（57 门）)/,
            '## ⚡ 交互式试卷检索器\n\n<ExamExplorer />\n\n---\n\n$1'
          );
        }

        // Clean duplicate leading ⚠️ inside [!WARNING] blocks across semester pages
        src = src.replace(
          /(> \[!WARNING\]\r?\n>\s*\*\*)⚠️\s*/g,
          '$1'
        );

        return origParse(src, env);
      };

      // 2. Upgrade ASCII effort/difficulty bar blocks (`████` + `⭐`) into responsive visual cards
      const defaultFence =
        md.renderer.rules.fence ||
        function (tokens, idx, options, _env, self) {
          return self.renderToken(tokens, idx, options);
        };

      md.renderer.rules.fence = (tokens, idx, options, env, self) => {
        const token = tokens[idx];
        const info = (token.info || '').trim();
        const raw = token.content || '';

        if (!info && raw.includes('████') && raw.includes('⭐')) {
          const lines = raw
            .split(/\r?\n/)
            .map((l) => l.trim())
            .filter(Boolean);
          const items = lines
            .map((line) => {
              const m = line.match(/^(.+?)\s+(█+)\s+(⭐+)\s*(?:[（(](.+)[)）])?$/);
              if (!m) return null;
              return {
                name: m[1].trim(),
                bars: m[2].length,
                stars: [...m[3]].length,
                note: (m[4] || '').trim()
              };
            })
            .filter(Boolean) as Array<{ name: string; bars: number; stars: number; note: string }>;

          if (items.length > 0) {
            const maxBars = Math.max(...items.map((i) => i.bars), 24);
            const cardsHtml = items
              .map((item) => {
                const pct = Math.min(100, Math.round((item.bars / maxBars) * 100));
                const levelClass =
                  item.stars >= 5 ? 'is-critical' : item.stars >= 4 ? 'is-high' : item.stars >= 3 ? 'is-medium' : 'is-normal';
                const starsText = '★'.repeat(item.stars) + '☆'.repeat(Math.max(0, 5 - item.stars));
                return `<div class="lnu-effort-row ${levelClass}">
  <div class="lnu-effort-head">
    <span class="lnu-effort-name">${escapeHtml(item.name)}</span>
    <span class="lnu-effort-stars" aria-label="难度 ${item.stars} 星">${starsText}</span>
  </div>
  <div class="lnu-effort-track"><span class="lnu-effort-fill" style="width:${pct}%"></span></div>
  ${item.note ? `<div class="lnu-effort-note">${escapeHtml(item.note)}</div>` : ''}
</div>`;
              })
              .join('\n');
            return `<div class="lnu-effort-card">${cardsHtml}</div>`;
          }
        }

        return defaultFence(tokens, idx, options, env, self);
      };

      // 3. Transform Markdown links & GitHub-style anchors at compile time
      md.core.ruler.after('inline', 'lnu_link_transformer', (state) => {
        const rel = (state.env?.relativePath || '').replace(/\\/g, '/');
        const srcDir =
          rel in REWRITE_TO_SRCDIR
            ? REWRITE_TO_SRCDIR[rel]
            : path.posix.dirname(rel) === '.'
              ? ''
              : path.posix.dirname(rel);

        // Collect heading ids in current page to reconcile GitHub's `#-heading` anchors with VitePress heading ids
        const headingMap = new Map<string, string>();
        for (let i = 0; i < state.tokens.length; i++) {
          const tok = state.tokens[i];
          if (tok.type === 'heading_open') {
            const idAttr = tok.attrGet('id');
            const inlineTok = state.tokens[i + 1];
            if (idAttr && inlineTok && inlineTok.type === 'inline') {
              headingMap.set(normalizeAnchorKey(inlineTok.content), idAttr);
              headingMap.set(normalizeAnchorKey(idAttr), idAttr);
            }
          }
        }

        function processTokens(tokens: any[]) {
          for (const tok of tokens) {
            if (tok.children) processTokens(tok.children);
            if (tok.type !== 'link_open') continue;

            const rawHref = tok.attrGet('href');
            if (!rawHref) continue;
            if (/^(https?:|mailto:|javascript:|data:)/i.test(rawHref)) continue;

            // Pure in-page anchor (`#-全课程总目录`)
            if (rawHref.startsWith('#')) {
              const rawHash = safeDecode(rawHref.slice(1));
              const matched = headingMap.get(normalizeAnchorKey(rawHash));
              if (matched) {
                tok.attrSet('href', `#${matched}`);
              } else if (rawHash.startsWith('-')) {
                tok.attrSet('href', `#${rawHash.replace(/^-+/, '')}`);
              }
              continue;
            }

            const [pathPart, hashPart] = rawHref.split('#');
            const decodedPath = safeDecode(pathPart).replace(/\/$/, '');
            if (!decodedPath) continue;

            const repoRelPath = path.posix
              .normalize(srcDir ? `${srcDir}/${decodedPath}` : decodedPath)
              .replace(/^\.\//, '');

            // Case A: Internal Markdown page link (e.g., `01%20第一学期/README.md`, `../README.md`, `CONTRIBUTING.md`)
            const targetRoute = SOURCE_TO_ROUTE[repoRelPath.toLowerCase()];
            if (targetRoute && (/readme\.md$/i.test(repoRelPath) || /\.md$/i.test(repoRelPath))) {
              const suffix = hashPart ? `#${safeDecode(hashPart).replace(/^-+/, '')}` : '';
              tok.attrSet('href', `${targetRoute}${suffix}`);
              continue;
            }

            // Case B: Course folder or binary resource file -> bind to in-site <CourseDrawer /> + GitHub fallback href
            const fileFlag = isRepoFile(repoRelPath);
            const ghHref = `${REPO_URL}/${fileFlag ? 'blob' : 'tree'}/main/${encodeGithubPath(repoRelPath)}`;
            tok.attrSet('href', ghHref);
            tok.attrSet('target', '_blank');
            tok.attrSet('rel', 'noopener');
            tok.attrSet('data-lnu-path', repoRelPath);
            tok.attrSet('data-lnu-kind', fileFlag ? 'file' : 'dir');
            tok.attrJoin('class', fileFlag ? 'lnu-res-link is-file' : 'lnu-res-link is-dir');
          }
        }

        processTokens(state.tokens);
      });
    }
  },

  themeConfig: {
    logo: '/logo.svg',
    siteTitle: 'LNU CS 资源库',

    nav: [
      { text: '🏠 首页', link: '/' },
      {
        text: '📚 学期指南',
        items: [
          {
            text: '🌱 大一学年',
            items: [
              { text: '第一学期 · 大一秋（10 门）', link: '/semester/01' },
              { text: '第二学期 · 大一春（14 门）', link: '/semester/02' }
            ]
          },
          {
            text: '🌿 大二学年',
            items: [
              { text: '第三学期 · 大二秋（11 门）', link: '/semester/03' },
              { text: '第四学期 · 大二春（13 门）', link: '/semester/04' }
            ]
          },
          {
            text: '🌳 大三学年',
            items: [
              { text: '第五学期 · 大三秋（8 门）', link: '/semester/05' },
              { text: '第六学期 · 大三春（9 门）', link: '/semester/06' }
            ]
          },
          {
            text: '🎓 大四学年',
            items: [
              { text: '第七学期 · 大四秋（2 门）', link: '/semester/07' },
              { text: '第八学期 · 大四春（2 门）', link: '/semester/08' }
            ]
          }
        ]
      },
      { text: '🎨 通识选修', link: '/electives' },
      { text: '📝 历年试卷库', link: '/exams' },
      { text: '🧮 绩点速算', link: '/#绩点与官方文档' },
      { text: '🤝 贡献指南', link: '/contributing' }
    ],

    sidebar: [
      {
        text: '🧭 导览与总览',
        items: [
          { text: '🏠 资源库首页', link: '/' },
          { text: '📝 往年课程试卷库（320 份）', link: '/exams' },
          { text: '🎨 通识选修课指南（13 门）', link: '/electives' }
        ]
      },
      {
        text: '🌱 大一 · 基础筑基',
        collapsed: false,
        items: [
          { text: '🍂 第一学期 · 大一秋', link: '/semester/01' },
          { text: '🌸 第二学期 · 大一春', link: '/semester/02' }
        ]
      },
      {
        text: '🌿 大二 · 核心进阶',
        collapsed: false,
        items: [
          { text: '🍁 第三学期 · 大二秋', link: '/semester/03' },
          { text: '🌷 第四学期 · 大二春', link: '/semester/04' }
        ]
      },
      {
        text: '🌳 大三 · 系统与前沿',
        collapsed: false,
        items: [
          { text: '🍂 第五学期 · 大三秋', link: '/semester/05' },
          { text: '🌼 第六学期 · 大三春', link: '/semester/06' }
        ]
      },
      {
        text: '🎓 大四 · 收官与毕设',
        collapsed: false,
        items: [
          { text: '🍂 第七学期 · 大四秋', link: '/semester/07' },
          { text: '🎓 第八学期 · 大四春', link: '/semester/08' }
        ]
      },
      {
        text: '🤝 社区与共建',
        collapsed: false,
        items: [{ text: '🤝 贡献指南与规范', link: '/contributing' }]
      }
    ],

    outline: {
      level: [2, 3],
      label: '📑 本页目录'
    },

    search: {
      provider: 'local',
      options: {
        detailedView: true,
        miniSearch: {
          searchOptions: {
            fuzzy: 0.2,
            prefix: true,
            boost: { title: 4, text: 2, titles: 1 }
          }
        },
        translations: {
          button: {
            buttonText: '搜索课程 / 真题 / 攻略…',
            buttonAriaLabel: '搜索课程、真题与备考攻略'
          },
          modal: {
            displayDetails: '切换摘要详情',
            resetButtonTitle: '清空搜索关键词',
            backButtonTitle: '关闭搜索',
            noResultsText: '没有找到匹配内容，试试课程简称或教师姓名',
            footer: {
              selectText: '跳转',
              selectKeyAriaLabel: '回车确认',
              navigateText: '上下切换',
              navigateUpKeyAriaLabel: '向上箭头',
              navigateDownKeyAriaLabel: '向下箭头',
              closeText: '关闭',
              closeKeyAriaLabel: 'Esc 键'
            }
          }
        }
      }
    },

    socialLinks: [
      { icon: 'github', link: REPO_URL, ariaLabel: '访问 GitHub 仓库' }
    ],

    docFooter: {
      prev: '上一篇',
      next: '下一篇'
    },

    darkModeSwitchLabel: '外观主题',
    lightModeSwitchTitle: '切换到浅色模式',
    darkModeSwitchTitle: '切换到深色模式',
    sidebarMenuLabel: '学期导航菜单',
    returnToTopLabel: '回到顶部',

    footer: {
      message:
        '由 <a href="https://github.com/XUNRANA" target="_blank" rel="noopener">XUNRANA</a> 独立整理与维护 · 采用 CC BY-NC-SA 4.0 许可 · 与辽宁大学官方无关',
      copyright: '© 2022–2026 LNU CS Courses Resource · 学长走过的弯路，后来人不必再走'
    }
  }
});
