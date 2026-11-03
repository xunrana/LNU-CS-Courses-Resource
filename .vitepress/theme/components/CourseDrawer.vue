<script setup lang="ts">
import { computed, onBeforeUnmount, onMounted, ref, watch } from 'vue';
import { withBase, useRouter } from 'vitepress';
import {
  closeResourceDrawer,
  drawerState,
  FIFTY_MB,
  formatBytes,
  getDownloadUrl,
  getFileTypeMeta,
  getGithubUrl,
  REPO_URL,
  useManifest
} from '../store';

const { manifest, loading, error, loadManifest } = useManifest();
const router = useRouter();

const filterQuery = ref('');
const activeCat = ref<'all' | 'pdf' | 'doc' | 'ppt' | 'code'>('all');
const scopeToSubdir = ref(true);
const sparseMode = ref<'init' | 'add'>('init');
const copied = ref(false);

watch(
  () => drawerState.targetPath,
  () => {
    filterQuery.value = '';
    activeCat.value = 'all';
    scopeToSubdir.value = true;
    copied.value = false;
  }
);

watch(
  () => drawerState.open,
  (isOpen) => {
    if (typeof document !== 'undefined') {
      document.body.style.overflow = isOpen ? 'hidden' : '';
    }
  }
);

function onKeydown(e: KeyboardEvent) {
  if (e.key === 'Escape' && drawerState.open) {
    closeResourceDrawer();
  }
}

onMounted(() => {
  window.addEventListener('keydown', onKeydown);
});

onBeforeUnmount(() => {
  window.removeEventListener('keydown', onKeydown);
  if (typeof document !== 'undefined') {
    document.body.style.overflow = '';
  }
});

const parsedTarget = computed(() => {
  const raw = drawerState.targetPath;
  const parts = raw.split('/').filter(Boolean);
  const isRootItem = parts.length <= 1;
  const dirKey = parts.length >= 2 ? `${parts[0]}/${parts[1]}` : raw;
  const subRel = parts.length > 2 ? parts.slice(2).join('/') : '';
  return { raw, parts, isRootItem, dirKey, subRel };
});

const rootFileInfo = computed(() => {
  if (!manifest.value || !parsedTarget.value.isRootItem) return null;
  return manifest.value.rootFiles.find((f) => f.path === parsedTarget.value.raw) || null;
});

const currentDirectory = computed(() => {
  if (!manifest.value || parsedTarget.value.isRootItem) return null;
  return manifest.value.directories[parsedTarget.value.dirKey] || null;
});

const sparseFolderTarget = computed(() => {
  if (drawerState.targetKind === 'dir' && parsedTarget.value.raw) {
    return parsedTarget.value.raw;
  }
  return parsedTarget.value.dirKey || parsedTarget.value.raw;
});

const sparseCommand = computed(() => {
  const folder = sparseFolderTarget.value;
  if (sparseMode.value === 'add') {
    return `git sparse-checkout add "${folder}"`;
  }
  return [
    `git clone --filter=blob:none --sparse ${REPO_URL}.git`,
    'cd LNU-CS-Courses-Resource',
    `git sparse-checkout set "${folder}"`
  ].join('\n');
});

async function copySparseCommand() {
  try {
    await navigator.clipboard.writeText(sparseCommand.value);
    copied.value = true;
    setTimeout(() => {
      copied.value = false;
    }, 2000);
  } catch {
    // Fallback
  }
}

interface EnrichedFile {
  relPath: string;
  fullPath: string;
  fileName: string;
  folderHint: string;
  size: number;
  sizeLabel: string;
  isLarge: boolean;
  isTarget: boolean;
  icon: string;
  cat: 'doc' | 'ppt' | 'pdf' | 'code' | 'sheet' | 'other';
  ghUrl: string;
  dl: { url: string; label: string; isCdn: boolean };
}

const allCourseFiles = computed<EnrichedFile[]>(() => {
  const dir = currentDirectory.value;
  if (!dir) return [];
  const dirKey = parsedTarget.value.dirKey;
  const targetSub = drawerState.targetKind === 'file' ? parsedTarget.value.subRel : '';

  return dir.files.map(([relPath, size]) => {
    const segs = relPath.split('/');
    const fileName = segs[segs.length - 1];
    const folderHint = segs.length > 1 ? segs.slice(0, -1).join(' / ') : '';
    const fullPath = `${dirKey}/${relPath}`;
    const meta = getFileTypeMeta(fileName);
    return {
      relPath,
      fullPath,
      fileName,
      folderHint,
      size,
      sizeLabel: formatBytes(size),
      isLarge: size > FIFTY_MB,
      isTarget: Boolean(targetSub && relPath === targetSub),
      icon: meta.icon,
      cat: meta.cat,
      ghUrl: getGithubUrl(fullPath, 'file'),
      dl: getDownloadUrl(fullPath, size)
    };
  });
});

const pinnedFile = computed(() => allCourseFiles.value.find((f) => f.isTarget) || null);

const filteredFiles = computed(() => {
  let list = allCourseFiles.value;

  if (
    drawerState.targetKind === 'dir' &&
    parsedTarget.value.subRel &&
    scopeToSubdir.value
  ) {
    const prefix = `${parsedTarget.value.subRel}/`;
    list = list.filter((f) => f.relPath === parsedTarget.value.subRel || f.relPath.startsWith(prefix));
  }

  if (activeCat.value !== 'all') {
    list = list.filter((f) => f.cat === activeCat.value);
  }

  const q = filterQuery.value.trim().toLowerCase();
  if (q) {
    list = list.filter((f) => f.relPath.toLowerCase().includes(q));
  }

  return list;
});

function goToContributing() {
  closeResourceDrawer();
  router.go(withBase('/contributing'));
}
</script>

<template>
  <Teleport to="body">
    <Transition name="lnu-drawer-fade">
      <div
        v-if="drawerState.open"
        class="lnu-drawer-backdrop"
        role="dialog"
        aria-modal="true"
        aria-label="课程资料文件浏览器"
        @click.self="closeResourceDrawer"
      >
        <aside class="lnu-drawer-panel">
          <!-- 顶部标题栏 -->
          <header class="lnu-drawer-header">
            <div class="drawer-title-wrap">
              <div class="drawer-breadcrumb">
                <span v-for="(seg, idx) in parsedTarget.parts" :key="idx" class="crumb">
                  <template v-if="idx > 0"><i class="sep">/</i></template>
                  {{ seg }}
                </span>
              </div>
              <div v-if="currentDirectory" class="drawer-submeta">
                <span>📦 共 {{ currentDirectory.fileCount }} 份归档文件</span>
                <span>·</span>
                <span>总大小 {{ formatBytes(currentDirectory.totalBytes) }}</span>
              </div>
            </div>
            <button
              type="button"
              class="lnu-drawer-close"
              aria-label="关闭文件预览抽屉"
              title="关闭 (Esc)"
              @click="closeResourceDrawer"
            >
              ✕
            </button>
          </header>

          <!-- 加载 / 错误态 -->
          <div v-if="loading" class="lnu-drawer-state">
            <div class="spinner" aria-hidden="true"></div>
            <p>正在读取全库文件索引…</p>
          </div>

          <div v-else-if="error" class="lnu-drawer-state">
            <p>⚠️ 索引读取失败（{{ error }}）</p>
            <div class="state-actions">
              <button type="button" class="lnu-mini-btn primary" @click="loadManifest">重试加载</button>
              <a
                class="lnu-mini-btn"
                :href="getGithubUrl(parsedTarget.raw, drawerState.targetKind)"
                target="_blank"
                rel="noopener"
              >
                直接在 GitHub 查看 ↗
              </a>
            </div>
          </div>

          <!-- 根目录单文件（如培养方案 PDF / 成绩管理方法 PDF / LICENSE） -->
          <div v-else-if="rootFileInfo" class="lnu-drawer-body">
            <div class="lnu-pinned-card">
              <div class="pinned-tag">📄 仓库根目录官方文档</div>
              <div class="file-row-main">
                <span class="file-ico">{{ getFileTypeMeta(rootFileInfo.name).icon }}</span>
                <div class="file-info">
                  <div class="file-name">{{ rootFileInfo.name }}</div>
                  <div class="file-meta">{{ formatBytes(rootFileInfo.size) }}</div>
                </div>
              </div>
              <div class="pinned-actions">
                <a
                  class="lnu-mini-btn primary"
                  :href="getDownloadUrl(rootFileInfo.path, rootFileInfo.size).url"
                  target="_blank"
                  rel="noopener"
                >
                  ⚡ {{ getDownloadUrl(rootFileInfo.path, rootFileInfo.size).label }}预览 / 下载
                </a>
                <a
                  class="lnu-mini-btn"
                  :href="getGithubUrl(rootFileInfo.path, 'file')"
                  target="_blank"
                  rel="noopener"
                >
                  📦 在 GitHub 查看 ↗
                </a>
              </div>
            </div>
          </div>

          <!-- 课程或试卷目录详情 -->
          <div v-else-if="currentDirectory" class="lnu-drawer-body">
            <!-- 定向单文件高亮卡 -->
            <div v-if="pinnedFile" class="lnu-pinned-card">
              <div class="pinned-tag">🎯 当前选中的目标资料</div>
              <div class="file-row-main">
                <span class="file-ico">{{ pinnedFile.icon }}</span>
                <div class="file-info">
                  <div class="file-name">{{ pinnedFile.fileName }}</div>
                  <div class="file-meta">
                    <span v-if="pinnedFile.folderHint">{{ pinnedFile.folderHint }} · </span>
                    <span>{{ pinnedFile.sizeLabel }}</span>
                    <span v-if="pinnedFile.isLarge" class="warn-pill">⚠️ 超 50MB 大文件</span>
                  </div>
                </div>
              </div>
              <div class="pinned-actions">
                <a class="lnu-mini-btn primary" :href="pinnedFile.dl.url" target="_blank" rel="noopener">
                  ⚡ {{ pinnedFile.dl.label }}
                </a>
                <a class="lnu-mini-btn" :href="pinnedFile.ghUrl" target="_blank" rel="noopener">
                  📦 GitHub 查看 ↗
                </a>
              </div>
            </div>

            <!-- 一键复制 Git Sparse Checkout 命令面板 -->
            <div v-if="!currentDirectory.empty" class="lnu-sparse-box">
              <div class="sparse-head">
                <span class="sparse-title">📥 按需下载本目录（Git Sparse Checkout）</span>
                <div class="sparse-tabs" role="tablist">
                  <button
                    type="button"
                    :class="['tab-pill', { active: sparseMode === 'init' }]"
                    @click="sparseMode = 'init'"
                  >
                    首次克隆
                  </button>
                  <button
                    type="button"
                    :class="['tab-pill', { active: sparseMode === 'add' }]"
                    @click="sparseMode = 'add'"
                  >
                    追加目录
                  </button>
                </div>
              </div>
              <pre class="sparse-pre"><code>{{ sparseCommand }}</code></pre>
              <div class="sparse-foot">
                <button type="button" class="lnu-mini-btn primary" @click="copySparseCommand">
                  {{ copied ? '✓ 已复制到剪贴板' : '📋 一键复制命令' }}
                </button>
                <a
                  class="lnu-mini-btn"
                  :href="getGithubUrl(sparseFolderTarget, 'dir')"
                  target="_blank"
                  rel="noopener"
                >
                  📦 在 GitHub 打开此目录 ↗
                </a>
              </div>
            </div>

            <!-- 空壳文件夹提示 -->
            <div v-if="currentDirectory.empty" class="lnu-empty-folder">
              <div class="empty-emoji" aria-hidden="true">📭</div>
              <h3>该课程目录当前暂无归档资料</h3>
              <p>目前仅含 <code>.gitkeep</code> 占位。如果你手头有该课程的笔记、课件、实验或往年考卷，非常欢迎分享给学弟学妹！</p>
              <div class="empty-actions">
                <button type="button" class="lnu-mini-btn primary" @click="goToContributing">
                  🤝 查看贡献指南
                </button>
                <a
                  class="lnu-mini-btn"
                  :href="`${REPO_URL}/issues/new`"
                  target="_blank"
                  rel="noopener"
                >
                  💬 通过 Issue 投稿资料 ↗
                </a>
              </div>
            </div>

            <!-- 文件筛选与列表 -->
            <template v-else>
              <div class="lnu-file-toolbar">
                <input
                  v-model="filterQuery"
                  type="search"
                  class="lnu-file-search"
                  placeholder="在当前课程目录内搜索文件名…"
                  aria-label="在当前课程目录内搜索文件名"
                />
                <div class="lnu-cat-chips">
                  <button
                    type="button"
                    :class="['chip', { active: activeCat === 'all' }]"
                    @click="activeCat = 'all'"
                  >
                    全部 ({{ allCourseFiles.length }})
                  </button>
                  <button
                    type="button"
                    :class="['chip', { active: activeCat === 'pdf' }]"
                    @click="activeCat = 'pdf'"
                  >
                    📕 PDF
                  </button>
                  <button
                    type="button"
                    :class="['chip', { active: activeCat === 'doc' }]"
                    @click="activeCat = 'doc'"
                  >
                    📘 文档/试卷
                  </button>
                  <button
                    type="button"
                    :class="['chip', { active: activeCat === 'ppt' }]"
                    @click="activeCat = 'ppt'"
                  >
                    📙 课件
                  </button>
                  <button
                    type="button"
                    :class="['chip', { active: activeCat === 'code' }]"
                    @click="activeCat = 'code'"
                  >
                    💻 源码
                  </button>
                </div>

                <!-- 子目录范围提示 -->
                <div
                  v-if="drawerState.targetKind === 'dir' && parsedTarget.subRel"
                  class="lnu-scope-banner"
                >
                  <span v-if="scopeToSubdir">
                    📂 当前仅显示子目录 <strong>{{ parsedTarget.subRel }}</strong>（{{ filteredFiles.length }} 份）
                  </span>
                  <span v-else>
                    📂 当前显示本课程全部文件（{{ filteredFiles.length }} 份）
                  </span>
                  <button type="button" class="link-btn" @click="scopeToSubdir = !scopeToSubdir">
                    {{ scopeToSubdir ? '查看整门课全部文件' : '仅看该子目录' }}
                  </button>
                </div>
              </div>

              <ul v-if="filteredFiles.length" class="lnu-file-list">
                <li
                  v-for="file in filteredFiles"
                  :key="file.relPath"
                  :class="['lnu-file-item', { highlighted: file.isTarget }]"
                >
                  <div class="file-row-main">
                    <span class="file-ico" aria-hidden="true">{{ file.icon }}</span>
                    <div class="file-info">
                      <div class="file-name" :title="file.fileName">{{ file.fileName }}</div>
                      <div class="file-meta">
                        <span v-if="file.folderHint" class="folder-tag">{{ file.folderHint }}</span>
                        <span class="size-tag">{{ file.sizeLabel }}</span>
                        <span v-if="file.isLarge" class="warn-pill" title="大于 50MB，建议使用上方 Git Sparse Checkout 下载">
                          ⚠️ 大文件
                        </span>
                      </div>
                    </div>
                  </div>
                  <div class="file-actions">
                    <a
                      class="file-act-btn dl"
                      :href="file.dl.url"
                      target="_blank"
                      rel="noopener"
                      :title="file.dl.isCdn ? '通过 CDN 直链预览或下载（<20MB）' : '通过 GitHub Raw 下载原始文件'"
                    >
                      {{ file.dl.label }}
                    </a>
                    <a
                      class="file-act-btn gh"
                      :href="file.ghUrl"
                      target="_blank"
                      rel="noopener"
                      title="在 GitHub 查看文件"
                    >
                      GitHub ↗
                    </a>
                  </div>
                </li>
              </ul>

              <div v-else class="lnu-no-match">
                没有匹配当前筛选条件的文件，可尝试清空关键词或切换分类。
              </div>
            </template>
          </div>

          <!-- 兜底：未匹配到索引的自定义路径 -->
          <div v-else class="lnu-drawer-state">
            <p>该路径未在课程索引中单独归档，可直接前往 GitHub 查看。</p>
            <a
              class="lnu-mini-btn primary"
              :href="getGithubUrl(parsedTarget.raw, drawerState.targetKind)"
              target="_blank"
              rel="noopener"
            >
              📦 在 GitHub 打开 ↗
            </a>
          </div>
        </aside>
      </div>
    </Transition>
  </Teleport>
</template>
