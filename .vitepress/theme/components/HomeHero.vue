<script setup lang="ts">
import { withBase, useRouter } from 'vitepress';
import { REPO_URL } from '../store';

const router = useRouter();

interface SemesterCard {
  id: string;
  badge: string;
  title: string;
  meta: string;
  highlights: string;
  link: string;
}

const semesters: SemesterCard[] = [
  {
    id: '01',
    badge: '大一秋',
    title: '第一学期',
    meta: '10 门 · 22 学分',
    highlights: '高数一 · 大英一 · 计算机导论',
    link: '/semester/01'
  },
  {
    id: '02',
    badge: '大一春',
    title: '第二学期',
    meta: '14 门 · 35 学分',
    highlights: '高数二 · C语言 · 离散 · 计算理论',
    link: '/semester/02'
  },
  {
    id: '03',
    badge: '大二秋',
    title: '第三学期',
    meta: '11 门 · 25 学分',
    highlights: '数据结构 · 数据库 · 线代 · 普物下',
    link: '/semester/03'
  },
  {
    id: '04',
    badge: '大二春',
    title: '第四学期',
    meta: '13 门 · 26 学分',
    highlights: '计组 · 算法设计 · 数字逻辑 · Java',
    link: '/semester/04'
  },
  {
    id: '05',
    badge: '大三秋',
    title: '第五学期',
    meta: '8 门 · 16 学分',
    highlights: '操作系统 · 编译原理 · 最优化 · AI',
    link: '/semester/05'
  },
  {
    id: '06',
    badge: '大三春',
    title: '第六学期',
    meta: '9 门 · 14 学分',
    highlights: '计算机网络 · 机器学习 · 大数据',
    link: '/semester/06'
  },
  {
    id: '07',
    badge: '大四秋',
    title: '第七学期',
    meta: '2 门 · 5 学分',
    highlights: '计算机系统结构 · 双创学分转换',
    link: '/semester/07'
  },
  {
    id: '08',
    badge: '大四春',
    title: '第八学期',
    meta: '2 门 · 18 学分',
    highlights: '毕业论文全流程 · 查重与盲审红线',
    link: '/semester/08'
  }
];

function triggerGlobalSearch() {
  const btn = document.querySelector<HTMLButtonElement>('#local-search button, .VPNavBarSearch button');
  if (btn) {
    btn.click();
    return;
  }
  window.dispatchEvent(new KeyboardEvent('keydown', { key: 'k', ctrlKey: true, bubbles: true }));
}

function go(path: string) {
  router.go(withBase(path));
}
</script>

<template>
  <section class="lnu-hero" aria-label="站点总览与快速入口">
    <div class="lnu-hero-bg" aria-hidden="true"></div>
    <div class="lnu-hero-inner">
      <img class="lnu-hero-logo" :src="withBase('/logo.svg')" alt="LNU CS 资源库 Logo" width="84" height="84" />

      <div class="lnu-hero-badge">
        <span class="dot" aria-hidden="true"></span>
        辽宁大学 · 计算机科学与技术专业（2022–2026 全学程归档）
      </div>

      <h1 class="lnu-hero-title">
        LNU CS <span class="grad">课程资源库</span>
      </h1>

      <p class="lnu-hero-sub">
        本科四年全部 82 门课程的课件、笔记、实验源码、历年真题与逐课备考攻略，按学期结构化编排，站内即查即用。
      </p>
      <p class="lnu-hero-quote">“学长走过的弯路，后来人不必再走。”</p>

      <!-- 快捷全局搜索触发栏 -->
      <button
        type="button"
        class="lnu-hero-search"
        aria-label="打开全局搜索弹窗"
        @click="triggerGlobalSearch"
      >
        <svg class="search-ico" viewBox="0 0 24 24" aria-hidden="true">
          <circle cx="11" cy="11" r="7" fill="none" stroke="currentColor" stroke-width="2.2" />
          <path d="M20 20l-3.8-3.8" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" />
        </svg>
        <span class="search-placeholder">搜索课程名、任课教师、408 真题或备考考点…</span>
        <span class="search-kbd" aria-hidden="true"><kbd>Ctrl</kbd><kbd>K</kbd></span>
      </button>

      <!-- 核心统计矩阵 -->
      <div class="lnu-hero-stats">
        <a class="lnu-stat-card" href="#全课程总目录">
          <b>82</b>
          <span>门本科课程全覆盖</span>
        </a>
        <a class="lnu-stat-card" :href="withBase('/exams')" @click.prevent="go('/exams')">
          <b>320</b>
          <span>份历年期末真题 ↗</span>
        </a>
        <a class="lnu-stat-card" :href="withBase('/electives')" @click.prevent="go('/electives')">
          <b>8 + 1</b>
          <span>学期 + 通识选修指南</span>
        </a>
        <a class="lnu-stat-card" href="#重点课程导览">
          <b>3000+</b>
          <span>份课件 / 笔记 / 源码</span>
        </a>
      </div>

      <!-- 主操作按钮组 -->
      <div class="lnu-hero-actions">
        <a class="lnu-action-btn primary" href="#全课程总目录">
          📚 浏览全课程目录
        </a>
        <a class="lnu-action-btn secondary" :href="withBase('/exams')" @click.prevent="go('/exams')">
          📝 检索 320 份往年试卷
        </a>
        <a class="lnu-action-btn secondary" href="#绩点与官方文档">
          🧮 辽大 GPA 速算器
        </a>
        <a class="lnu-action-btn ghost" :href="REPO_URL" target="_blank" rel="noopener">
          <svg viewBox="0 0 16 16" aria-hidden="true">
            <path
              fill="currentColor"
              d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0016 8c0-4.42-3.58-8-8-8z"
            />
          </svg>
          GitHub 仓库
        </a>
      </div>

      <!-- 八大学期一键直达矩阵 -->
      <div class="lnu-sem-grid" aria-label="按学期快速直达">
        <a
          v-for="sem in semesters"
          :key="sem.id"
          class="lnu-sem-card"
          :href="withBase(sem.link)"
          @click.prevent="go(sem.link)"
        >
          <div class="sem-top">
            <span class="sem-num">{{ sem.id }}</span>
            <span class="sem-title">{{ sem.title }}</span>
            <span class="sem-badge">{{ sem.badge }}</span>
          </div>
          <div class="sem-highlights">{{ sem.highlights }}</div>
          <div class="sem-meta">
            <span>{{ sem.meta }}</span>
            <span class="sem-arrow" aria-hidden="true">→</span>
          </div>
        </a>
      </div>

      <p class="lnu-hero-footnote">
        💡 提示：点击站内任意<strong>课程名称</strong>或<strong>资料链接</strong>即可直接在侧边抽屉预览真实文件清单、查看文件大小并一键复制按需下载命令（按住 <kbd>Ctrl</kbd> 点击可直接打开 GitHub）。
      </p>
    </div>
  </section>
</template>
