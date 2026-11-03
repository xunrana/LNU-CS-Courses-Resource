<script setup lang="ts">
import { computed, onMounted, ref } from 'vue';
import {
  formatBytes,
  getDownloadUrl,
  getGithubUrl,
  openResourceDrawer,
  useManifest
} from '../store';

const { manifest, loading, loadManifest } = useManifest();

const query = ref('');
const selectedMajor = ref('全部');
const selectedType = ref('全部');
const visibleLimit = ref(24);

const majors = ['全部', '计科', '软件工程', '信息管理', '电子信息', '通信工程'];
const docTypes = [
  { key: '全部', label: '全部类型' },
  { key: '试卷卷面', label: '📝 A/B 试题卷' },
  { key: '含答案', label: '✅ 含答案/评分标准' },
  { key: '试卷分析', label: '📊 试卷分析报告' }
];

onMounted(() => {
  loadManifest();
});

const filteredExams = computed(() => {
  const list = manifest.value?.exams || [];
  const q = query.value.trim().toLowerCase();

  return list.filter((item) => {
    if (selectedMajor.value !== '全部' && !item.majors.includes(selectedMajor.value)) {
      return false;
    }
    if (selectedType.value === '含答案' && !item.types.includes('含答案')) {
      return false;
    }
    if (selectedType.value === '试卷分析' && !item.types.includes('试卷分析')) {
      return false;
    }
    if (
      selectedType.value === '试卷卷面' &&
      !item.types.includes('A卷') &&
      !item.types.includes('B卷') &&
      !item.types.includes('试卷')
    ) {
      return false;
    }
    if (q) {
      const hay = `${item.course} ${item.name} ${item.teachers.join(' ')} ${item.grade} ${item.year} ${item.majors.join(' ')}`.toLowerCase();
      if (!hay.includes(q)) return false;
    }
    return true;
  });
});

const displayedExams = computed(() => filteredExams.value.slice(0, visibleLimit.value));

function resetFilters() {
  query.value = '';
  selectedMajor.value = '全部';
  selectedType.value = '全部';
  visibleLimit.value = 24;
}

function openCourseFolder(dir: string) {
  openResourceDrawer(`10 往年课程试卷/${dir}`, 'dir');
}
</script>

<template>
  <div class="lnu-exam-explorer">
    <div class="explorer-controls">
      <div class="explorer-search-row">
        <input
          v-model="query"
          type="search"
          class="explorer-input"
          placeholder="输入课程名、出题教师（如：张昕 / 王青松 / 岳承君）、年级（如：15级）实时过滤…"
          aria-label="搜索往年试卷"
          @input="visibleLimit = 24"
        />
        <button
          v-if="query || selectedMajor !== '全部' || selectedType !== '全部'"
          type="button"
          class="lnu-mini-btn"
          @click="resetFilters"
        >
          重置条件
        </button>
      </div>

      <div class="explorer-filter-group">
        <span class="filter-label">适用专业：</span>
        <div class="chip-wrap">
          <button
            v-for="m in majors"
            :key="m"
            type="button"
            :class="['chip', { active: selectedMajor === m }]"
            @click="
              selectedMajor = m;
              visibleLimit = 24;
            "
          >
            {{ m }}
          </button>
        </div>
      </div>

      <div class="explorer-filter-group">
        <span class="filter-label">文档类型：</span>
        <div class="chip-wrap">
          <button
            v-for="t in docTypes"
            :key="t.key"
            type="button"
            :class="['chip', { active: selectedType === t.key }]"
            @click="
              selectedType = t.key;
              visibleLimit = 24;
            "
          >
            {{ t.label }}
          </button>
        </div>
      </div>
    </div>

    <div class="explorer-summary">
      <span v-if="loading">正在载入 320 份试卷索引…</span>
      <span v-else>
        共匹配到 <strong>{{ filteredExams.length }}</strong> 份试卷文档（显示前 {{ displayedExams.length }} 份）
      </span>
    </div>

    <div v-if="!loading && displayedExams.length" class="explorer-grid">
      <div v-for="exam in displayedExams" :key="exam.path" class="exam-card">
        <div class="exam-card-top">
          <button
            type="button"
            class="exam-course-tag"
            title="打开该课程全部试卷抽屉"
            @click="openCourseFolder(exam.dir)"
          >
            📁 {{ exam.dir }}
          </button>
          <div class="exam-badges">
            <span
              v-for="tp in exam.types"
              :key="tp"
              :class="['exam-type-pill', { ans: tp === '含答案', ana: tp === '试卷分析' }]"
            >
              {{ tp }}
            </span>
          </div>
        </div>

        <div class="exam-filename" :title="exam.name">{{ exam.name }}</div>

        <div class="exam-meta-row">
          <span v-if="exam.majors.length">🎓 {{ exam.majors.join(' / ') }}</span>
          <span v-if="exam.teachers.length">👨‍🏫 {{ exam.teachers.join('、') }}</span>
          <span v-if="exam.grade">📅 {{ exam.grade }}</span>
          <span>📦 {{ formatBytes(exam.size) }}</span>
        </div>

        <div class="exam-actions">
          <a
            class="file-act-btn dl"
            :href="getDownloadUrl(exam.path, exam.size).url"
            target="_blank"
            rel="noopener"
          >
            ⬇️ {{ getDownloadUrl(exam.path, exam.size).label }}下载
          </a>
          <a
            class="file-act-btn gh"
            :href="getGithubUrl(exam.path, 'file')"
            target="_blank"
            rel="noopener"
          >
            GitHub 查看 ↗
          </a>
        </div>
      </div>
    </div>

    <div v-else-if="!loading" class="lnu-no-match">
      没有找到符合当前筛选组合的考卷，请尝试放宽专业或关键词筛选条件。
    </div>

    <div v-if="filteredExams.length > visibleLimit" class="explorer-more">
      <button
        type="button"
        class="lnu-mini-btn primary"
        @click="visibleLimit += 36"
      >
        加载更多试卷（剩余 {{ filteredExams.length - visibleLimit }} 份）
      </button>
      <button
        type="button"
        class="lnu-mini-btn"
        @click="visibleLimit = filteredExams.length"
      >
        展开全部 {{ filteredExams.length }} 份
      </button>
    </div>
  </div>
</template>
