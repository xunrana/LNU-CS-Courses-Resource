<script setup lang="ts">
import { computed, ref } from 'vue';

interface CourseRow {
  id: number;
  name: string;
  credit: number;
  mode: 'numeric' | 'level';
  score: number;
  level: '优秀' | '良好' | '中等' | '及格' | '不及格';
}

const LEVEL_GPA: Record<CourseRow['level'], number> = {
  优秀: 4.0,
  良好: 3.0,
  中等: 2.0,
  及格: 1.0,
  不及格: 0.0
};

function calcLnuNumericGpa(score: number): number {
  if (Number.isNaN(score) || score < 60) return 0;
  const clamped = Math.min(100, score);
  const gpa = 4 - (3 * Math.pow(100 - clamped, 2)) / 1600;
  return Math.max(0, gpa);
}

const quickScore = ref(85);
const quickGpa = computed(() => calcLnuNumericGpa(quickScore.value));

const showSimulator = ref(false);
let uid = 100;

const PRESETS: Record<string, Array<{ name: string; credit: number; mode?: 'numeric' | 'level'; score?: number; level?: CourseRow['level'] }>> = {
  sem1: [
    { name: '高等数学A（一）', credit: 5, score: 88 },
    { name: '大学英语（一）', credit: 4, score: 85 },
    { name: '思想道德与法治', credit: 3, score: 82 },
    { name: '计算机导论', credit: 2, score: 85 },
    { name: '军事技能', credit: 2, mode: 'level', level: '优秀', score: 95 },
    { name: '体育（一）', credit: 1, score: 86 },
    { name: '计算机导论实验', credit: 0.5, score: 92 }
  ],
  sem2: [
    { name: '高等数学A（二）', credit: 6, score: 84 },
    { name: '普通物理A（上）', credit: 4, score: 85 },
    { name: '大学英语（二）', credit: 4, score: 86 },
    { name: '离散数学', credit: 3, score: 88 },
    { name: '高级语言程序设计（C）', credit: 3, score: 86 },
    { name: '计算理论', credit: 3, score: 85 },
    { name: '中国近现代史纲要', credit: 3, score: 80 },
    { name: '认知实验', credit: 1, score: 92 }
  ],
  core408: [
    { name: '数据结构', credit: 3, score: 88 },
    { name: '计算机组成原理', credit: 3, score: 86 },
    { name: '操作系统原理', credit: 3, score: 85 },
    { name: '计算机网络', credit: 3, score: 90 },
    { name: '数据库原理', credit: 3, score: 90 },
    { name: '算法设计与分析', credit: 3, score: 84 },
    { name: '编译原理', credit: 3, score: 82 }
  ]
};

const rows = ref<CourseRow[]>(
  PRESETS.sem1.map((p) => ({
    id: ++uid,
    name: p.name,
    credit: p.credit,
    mode: p.mode || 'numeric',
    score: p.score ?? 85,
    level: p.level || '优秀'
  }))
);

function loadPreset(key: string) {
  const list = PRESETS[key] || PRESETS.sem1;
  rows.value = list.map((p) => ({
    id: ++uid,
    name: p.name,
    credit: p.credit,
    mode: p.mode || 'numeric',
    score: p.score ?? 85,
    level: p.level || '优秀'
  }));
  showSimulator.value = true;
}

function addCourse() {
  rows.value.push({
    id: ++uid,
    name: `自定义课程 ${rows.value.length + 1}`,
    credit: 2,
    mode: 'numeric',
    score: 85,
    level: '良好'
  });
}

function removeCourse(id: number) {
  if (rows.value.length <= 1) return;
  rows.value = rows.value.filter((r) => r.id !== id);
}

function rowGpa(r: CourseRow): number {
  return r.mode === 'level' ? LEVEL_GPA[r.level] : calcLnuNumericGpa(r.score);
}

const summary = computed(() => {
  let totalCredits = 0;
  let weightedGpaSum = 0;
  for (const r of rows.value) {
    const c = Number(r.credit) || 0;
    if (c <= 0) continue;
    totalCredits += c;
    weightedGpaSum += c * rowGpa(r);
  }
  const avgGpa = totalCredits > 0 ? weightedGpaSum / totalCredits : 0;
  return {
    totalCredits: totalCredits.toFixed(1),
    avgGpa: avgGpa.toFixed(3)
  };
});
</script>

<template>
  <div class="lnu-gpa-box">
    <div class="gpa-quick-row">
      <div class="gpa-quick-left">
        <span class="gpa-badge">🧮 辽大单科绩点速查</span>
        <label class="gpa-slider-wrap">
          <span>百分制分数：</span>
          <input
            v-model.number="quickScore"
            type="range"
            min="55"
            max="100"
            step="1"
            aria-label="拖动调整百分制分数"
          />
          <input
            v-model.number="quickScore"
            type="number"
            min="0"
            max="100"
            class="gpa-num-input"
            aria-label="输入百分制分数"
          />
        </label>
      </div>

      <div class="gpa-quick-result">
        <div class="gpa-res-item">
          <span class="lbl">折算绩点</span>
          <strong class="val">{{ quickGpa.toFixed(2) }}</strong>
          <small>({{ quickGpa.toFixed(4) }})</small>
        </div>
        <button
          type="button"
          class="lnu-mini-btn primary"
          @click="showSimulator = !showSimulator"
        >
          {{ showSimulator ? '收起多科加权模拟器' : '📊 展开学期加权 GPA 模拟器' }}
        </button>
      </div>
    </div>

    <div v-if="showSimulator" class="gpa-sim-panel">
      <div class="sim-toolbar">
        <span class="sim-label">快速载入真实课表模板：</span>
        <div class="chip-wrap">
          <button type="button" class="chip" @click="loadPreset('sem1')">🌱 大一秋必修</button>
          <button type="button" class="chip" @click="loadPreset('sem2')">🔥 大一春高压课表</button>
          <button type="button" class="chip" @click="loadPreset('core408')">💎 408 与专业主干课</button>
          <button type="button" class="chip" @click="addCourse">＋ 添加课程</button>
        </div>
      </div>

      <div class="sim-table-wrap">
        <table class="sim-table">
          <thead>
            <tr>
              <th>课程名称</th>
              <th>学分</th>
              <th>计分制</th>
              <th>成绩</th>
              <th>单科绩点</th>
              <th></th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="row in rows" :key="row.id">
              <td>
                <input v-model="row.name" type="text" class="sim-text-in" aria-label="课程名称" />
              </td>
              <td>
                <input
                  v-model.number="row.credit"
                  type="number"
                  min="0.5"
                  max="20"
                  step="0.5"
                  class="sim-num-in"
                  aria-label="课程学分"
                />
              </td>
              <td>
                <select v-model="row.mode" class="sim-sel" aria-label="计分方式">
                  <option value="numeric">百分制</option>
                  <option value="level">等级制</option>
                </select>
              </td>
              <td>
                <input
                  v-if="row.mode === 'numeric'"
                  v-model.number="row.score"
                  type="number"
                  min="0"
                  max="100"
                  class="sim-num-in"
                  aria-label="百分制成绩"
                />
                <select v-else v-model="row.level" class="sim-sel" aria-label="等级制成绩">
                  <option value="优秀">优秀 (4.0)</option>
                  <option value="良好">良好 (3.0)</option>
                  <option value="中等">中等 (2.0)</option>
                  <option value="及格">及格 (1.0)</option>
                  <option value="不及格">不及格 (0)</option>
                </select>
              </td>
              <td class="sim-gpa-cell">{{ rowGpa(row).toFixed(2) }}</td>
              <td>
                <button
                  type="button"
                  class="sim-del-btn"
                  aria-label="移除该课程"
                  title="移除"
                  @click="removeCourse(row.id)"
                >
                  ✕
                </button>
              </td>
            </tr>
          </tbody>
        </table>
      </div>

      <div class="sim-summary">
        <span>累计计算学分：<strong>{{ summary.totalCredits }}</strong> 学分</span>
        <span>加权平均绩点（GPA）：<strong class="highlight-gpa">{{ summary.avgGpa }}</strong> / 4.000</span>
      </div>
    </div>
  </div>
</template>
