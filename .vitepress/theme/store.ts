import { reactive, ref } from 'vue';
import { withBase } from 'vitepress';

export interface RootFileEntry {
  name: string;
  path: string;
  size: number;
}

export interface DirectoryEntry {
  title: string;
  group: string;
  empty: boolean;
  totalBytes: number;
  fileCount: number;
  files: [string, number][];
}

export interface ExamEntry {
  dir: string;
  code: string;
  course: string;
  name: string;
  path: string;
  size: number;
  majors: string[];
  grade: string;
  year: string;
  teachers: string[];
  types: string[];
}

export interface ManifestData {
  generatedAt: string;
  repo: string;
  branch: string;
  totals: {
    courses: number;
    examCourses: number;
    examFiles: number;
    resourceFiles: number;
    totalBytes: number;
  };
  rootFiles: RootFileEntry[];
  directories: Record<string, DirectoryEntry>;
  exams: ExamEntry[];
}

export const REPO_URL = 'https://github.com/XUNRANA/LNU-CS-Courses-Resource';
export const RAW_BASE = 'https://raw.githubusercontent.com/XUNRANA/LNU-CS-Courses-Resource/main';
export const JSDELIVR_BASE = 'https://cdn.jsdelivr.net/gh/XUNRANA/LNU-CS-Courses-Resource@main';
export const TWENTY_MB = 20 * 1024 * 1024;
export const FIFTY_MB = 50 * 1024 * 1024;

export const drawerState = reactive({
  open: false,
  targetPath: '',
  targetKind: 'dir' as 'dir' | 'file'
});

const manifestRef = ref<ManifestData | null>(null);
const loadingRef = ref(false);
const errorRef = ref<string | null>(null);
let fetchPromise: Promise<ManifestData | null> | null = null;

export function loadManifest(): Promise<ManifestData | null> {
  if (manifestRef.value) return Promise.resolve(manifestRef.value);
  if (fetchPromise) return fetchPromise;

  loadingRef.value = true;
  errorRef.value = null;

  fetchPromise = fetch(withBase('/manifest.json'))
    .then((res) => {
      if (!res.ok) throw new Error(`HTTP ${res.status}`);
      return res.json() as Promise<ManifestData>;
    })
    .then((data) => {
      manifestRef.value = data;
      return data;
    })
    .catch((err) => {
      errorRef.value = err?.message || '无法加载文件索引';
      fetchPromise = null;
      return null;
    })
    .finally(() => {
      loadingRef.value = false;
    });

  return fetchPromise;
}

export function useManifest() {
  return {
    manifest: manifestRef,
    loading: loadingRef,
    error: errorRef,
    loadManifest
  };
}

export function openResourceDrawer(repoRelPath: string, kind: 'dir' | 'file' = 'dir') {
  drawerState.targetPath = repoRelPath.replace(/^\/+|\/+$/g, '');
  drawerState.targetKind = kind;
  drawerState.open = true;
  loadManifest();
}

export function closeResourceDrawer() {
  drawerState.open = false;
}

export function encodePathSegments(p: string): string {
  return p
    .split('/')
    .map((s) => encodeURIComponent(s))
    .join('/');
}

export function getGithubUrl(repoRelPath: string, kind: 'dir' | 'file' = 'file'): string {
  return `${REPO_URL}/${kind === 'file' ? 'blob' : 'tree'}/main/${encodePathSegments(repoRelPath)}`;
}

export function getDownloadUrl(repoRelPath: string, byteSize: number): { url: string; label: string; isCdn: boolean } {
  const encoded = encodePathSegments(repoRelPath);
  if (byteSize > 0 && byteSize < TWENTY_MB) {
    return {
      url: `${JSDELIVR_BASE}/${encoded}`,
      label: 'CDN 直链',
      isCdn: true
    };
  }
  return {
    url: `${RAW_BASE}/${encoded}`,
    label: 'Raw 下载',
    isCdn: false
  };
}

export function formatBytes(bytes: number): string {
  if (!bytes || bytes <= 0) return '0 B';
  const units = ['B', 'KB', 'MB', 'GB'];
  let idx = 0;
  let val = bytes;
  while (val >= 1024 && idx < units.length - 1) {
    val /= 1024;
    idx += 1;
  }
  return `${val >= 100 || idx === 0 ? Math.round(val) : val.toFixed(1)} ${units[idx]}`;
}

export function getFileTypeMeta(fileName: string): { icon: string; cat: 'doc' | 'ppt' | 'pdf' | 'code' | 'sheet' | 'other' } {
  const ext = (fileName.split('.').pop() || '').toLowerCase();
  if (ext === 'pdf') return { icon: '📕', cat: 'pdf' };
  if (['doc', 'docx', 'rtf', 'txt', 'md'].includes(ext)) return { icon: '📘', cat: 'doc' };
  if (['ppt', 'pptx'].includes(ext)) return { icon: '📙', cat: 'ppt' };
  if (['xls', 'xlsx', 'csv'].includes(ext)) return { icon: '📊', cat: 'sheet' };
  if (['c', 'cpp', 'h', 'hpp', 'java', 'py', 'sql', 'js', 'ts', 'html', 'css', 'v', 'asm'].includes(ext)) {
    return { icon: '💻', cat: 'code' };
  }
  if (['png', 'jpg', 'jpeg', 'svg', 'webp', 'bmp'].includes(ext)) return { icon: '🖼️', cat: 'other' };
  return { icon: '📄', cat: 'other' };
}
