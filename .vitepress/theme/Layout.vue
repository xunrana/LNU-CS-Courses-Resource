<script setup lang="ts">
import { nextTick, onBeforeUnmount, onMounted, ref, watch } from 'vue';
import DefaultTheme from 'vitepress/theme';
import { useRoute, useRouter, withBase } from 'vitepress';
import CourseDrawer from './components/CourseDrawer.vue';
import { openResourceDrawer, REPO_URL } from './store';

const { Layout } = DefaultTheme;
const route = useRoute();
const router = useRouter();

const scrollProgress = ref(0);

function updateProgress() {
  if (typeof window === 'undefined') return;
  const max = document.documentElement.scrollHeight - window.innerHeight;
  const y = window.scrollY || document.documentElement.scrollTop;
  scrollProgress.value = max > 0 ? Math.min(100, (y / max) * 100) : 0;
}

const LEGACY_HASH_MAP: Record<string, string> = {
  'readme.md': '/',
  'contributing.md': '/contributing',
  '01 第一学期/readme.md': '/semester/01',
  '02 第二学期/readme.md': '/semester/02',
  '03 第三学期/readme.md': '/semester/03',
  '04 第四学期/readme.md': '/semester/04',
  '05 第五学期/readme.md': '/semester/05',
  '06 第六学期/readme.md': '/semester/06',
  '07 第七学期/readme.md': '/semester/07',
  '08 第八学期/readme.md': '/semester/08',
  '09 通识选修课/readme.md': '/electives',
  '10 往年课程试卷/readme.md': '/exams'
};

function handleLegacyDocsifyHash() {
  if (typeof window === 'undefined') return;
  const h = window.location.hash;
  if (!h || !h.startsWith('#/')) return;

  let rawPath = h.slice(2).split('?')[0].replace(/\/+$/, '');
  try {
    rawPath = decodeURIComponent(rawPath);
  } catch {
    // ignore malformed URI
  }

  if (!rawPath) {
    history.replaceState(null, '', window.location.pathname);
    return;
  }

  const normalized = rawPath.toLowerCase();
  const mapped =
    LEGACY_HASH_MAP[normalized] ||
    LEGACY_HASH_MAP[`${normalized}/readme.md`];

  if (mapped) {
    router.go(withBase(mapped));
    return;
  }

  // Legacy hash pointed directly to a course folder or binary file -> open drawer in-site!
  history.replaceState(null, '', window.location.pathname);
  const leaf = rawPath.split('/').pop() || '';
  openResourceDrawer(rawPath, /\.[a-z0-9]{1,8}$/i.test(leaf) ? 'file' : 'dir');
}

function enhancePageDom() {
  if (typeof document === 'undefined') return;
  const docEl = document.querySelector('.vp-doc');
  if (!docEl) return;

  // 1) Wrap Markdown tables in `.lnu-table-scroll` for mobile sticky first column & horizontal scroll hints
  docEl.querySelectorAll('table').forEach((table) => {
    if (table.classList.contains('sim-table')) return;
    const parent = table.parentElement;
    if (parent && parent.classList.contains('lnu-table-scroll')) return;
    const wrap = document.createElement('div');
    wrap.className = 'lnu-table-scroll';
    table.parentNode?.insertBefore(wrap, table);
    wrap.appendChild(table);
  });

  // 2) Mount "展开全部学期 / 收起全部学期" button next to `## 📚 全课程总目录`
  docEl.querySelectorAll('h2').forEach((h2) => {
    if (!h2.textContent?.includes('全课程总目录')) return;
    if (h2.querySelector('.lnu-details-toggle')) return;

    const detailsList: HTMLDetailsElement[] = [];
    let cur = h2.nextElementSibling;
    while (cur && cur.tagName !== 'H2') {
      if (cur.tagName === 'DETAILS') detailsList.push(cur as HTMLDetailsElement);
      cur = cur.nextElementSibling;
    }
    if (!detailsList.length) return;

    const btn = document.createElement('button');
    btn.type = 'button';
    btn.className = 'lnu-details-toggle';

    const syncLabel = () => {
      const allOpen = detailsList.every((d) => d.open);
      btn.textContent = allOpen ? '收起全部学期' : '展开全部学期';
    };

    btn.addEventListener('click', () => {
      const nextState = !detailsList.every((d) => d.open);
      detailsList.forEach((d) => {
        d.open = nextState;
      });
      syncLabel();
    });

    detailsList.forEach((d) => d.addEventListener('toggle', syncLabel));
    syncLabel();
    h2.appendChild(btn);
  });
}

function onGlobalClick(e: MouseEvent) {
  if (e.defaultPrevented || e.button !== 0 || e.metaKey || e.ctrlKey || e.shiftKey || e.altKey) {
    return;
  }
  const target = e.target as HTMLElement | null;
  const anchor = target?.closest?.('a[data-lnu-path]') as HTMLAnchorElement | null;
  if (!anchor) return;

  const repoPath = anchor.getAttribute('data-lnu-path');
  const kind = (anchor.getAttribute('data-lnu-kind') as 'dir' | 'file') || 'dir';
  if (!repoPath) return;

  e.preventDefault();
  openResourceDrawer(repoPath, kind);
}

onMounted(() => {
  window.addEventListener('scroll', updateProgress, { passive: true });
  window.addEventListener('resize', updateProgress);
  window.addEventListener('hashchange', handleLegacyDocsifyHash);
  document.addEventListener('click', onGlobalClick);

  handleLegacyDocsifyHash();
  updateProgress();
  nextTick(enhancePageDom);
});

watch(
  () => route.path,
  () => {
    nextTick(() => {
      updateProgress();
      enhancePageDom();
    });
  }
);

onBeforeUnmount(() => {
  window.removeEventListener('scroll', updateProgress);
  window.removeEventListener('resize', updateProgress);
  window.removeEventListener('hashchange', handleLegacyDocsifyHash);
  document.removeEventListener('click', onGlobalClick);
});
</script>

<template>
  <div class="lnu-progress-bar" aria-hidden="true">
    <span :style="{ width: `${scrollProgress}%` }"></span>
  </div>

  <Layout>
    <template #not-found>
      <div class="lnu-notfound">
        <div class="nf-code">404</div>
        <h1 class="nf-title">这里没有可直接阅读的文档页面</h1>
        <p class="nf-desc">
          如果你访问的是某个<strong>课程资料文件夹</strong>或<strong>原始文档路径</strong>（PDF / Word / PPT / 源码），可在站内首页或学期页点击课程名打开文件预览抽屉，或直接前往 GitHub 仓库浏览。
        </p>
        <div class="nf-actions">
          <a class="lnu-action-btn primary" :href="withBase('/')">🏠 返回资源库首页</a>
          <a class="lnu-action-btn secondary" :href="withBase('/exams')">📝 浏览往年试卷库</a>
          <a class="lnu-action-btn ghost" :href="REPO_URL" target="_blank" rel="noopener">📦 打开 GitHub 仓库 ↗</a>
        </div>
      </div>
    </template>
  </Layout>

  <CourseDrawer />
</template>
