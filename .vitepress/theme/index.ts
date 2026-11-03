import DefaultTheme from 'vitepress/theme';
import type { Theme } from 'vitepress';
import Layout from './Layout.vue';
import HomeHero from './components/HomeHero.vue';
import ExamExplorer from './components/ExamExplorer.vue';
import GpaCalculator from './components/GpaCalculator.vue';
import CourseDrawer from './components/CourseDrawer.vue';
import './custom.css';

export default {
  extends: DefaultTheme,
  Layout,
  enhanceApp({ app }) {
    app.component('HomeHero', HomeHero);
    app.component('ExamExplorer', ExamExplorer);
    app.component('GpaCalculator', GpaCalculator);
    app.component('CourseDrawer', CourseDrawer);
  }
} satisfies Theme;
