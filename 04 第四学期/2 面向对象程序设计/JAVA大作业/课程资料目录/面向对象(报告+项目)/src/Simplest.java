/**
 * @author Yitong Hong
 */
public class Simplest {

    static int[] table = new int[500];
    static int n;
    static int ceiling;
    static int l;
    static String[][] a = new String[500][500];//由几个变量组成(from1)  依次往后(from0)
    static boolean[][] has = new boolean[500][500];
    static int[] e = new int[500];
    static String[] pr = new String[3000];
    static int[] np = new int[3000];
    static StringBuilder t = new StringBuilder();
    static StringBuilder r = new StringBuilder();
    static int idx;//from 1
    static int minl = 0x3f3f3f;//字母总个数 第二关键字
    static int minOr = 0x3f3f3f;//或项最少 第一关键字
    static int cntl;
    static int cntOr;
    static String best;
    static StringBuilder s = new StringBuilder();


    ValidInput validInput;

    public Simplest(ValidInput validInput) {
        this.validInput = validInput;
    }

    public Simplest() {
    }

    public static void updateData(ValidInput validInput) {
        table = validInput.table;
        n = validInput.numOfVariables;
        ceiling = (int) (Math.pow(2, n) - 1);
    }

    public static void dfsTF(int u, String t) {

        if (u == t.length()) {
            a[t.length()][l++] = r.toString();
            return;
        }

        r.append(t.charAt(u));
        dfsTF(u + 1, t);

        r.append('\'');
        dfsTF(u + 1, t);
        r.setLength(r.length() - 2);
    }

    public static int Cnk2k(int k) {
        int ret;
        ret = (int) (Math.pow(2, k));
        int up, down;
        up = n - k + 1;
        down = 1;
        for (int i = 1; i <= k; i++) {
            ret *= up;
            ret /= down;
            up++;
            down++;
        }
        return ret;
    }

    public static void eUpdate() {
        for (int i = 1; i <= n; i++) {
            e[i] = Cnk2k(i);
        }
    }

    public static void dfsCom(int u, int num)//现在考虑了多少个字母，由多少个变量组成 比如AB BC AC，后者为2
    {
        if (t.length() > num) {
            return;
        }

        if (u == n) {
            if (t.length() == num) {
                dfsTF(0, t.toString());
            }
            return;
        }

        dfsCom(u + 1, num);
        t.append((char) (u + 'A'));
        dfsCom(u + 1, num);
        t.setLength(t.length() - 1);
    }

    public static boolean Contains(int[] cp) {
        for (int i = 0; i <= ceiling; i++) {
            if (cp[i] > 0 && table[i] == 0)
                return false;
        }
        return true;
    }

    public static boolean cover(String cv) {
        int[] tb = new int[500];
        Tools.TruthTable(cv, n, tb);
        for (int i = 0; i <= ceiling; i++) {
            if (table[i] > 0 && tb[i] == 0)
                return false;
        }
        return true;
    }

    public static boolean StringContains(String s1, String s2) {//字符串包含，逻辑上不包含  这里说的是逻辑
        //true:s1逻辑包含s2,s2字符串上包含s1，比如 s1:A'B s2:A'BC' 比如S1:A S2:A
        boolean[] ha = new boolean[500];
        for (int i = 0; i < s1.length(); i++) {
            if (i < s1.length() - 1 && s1.charAt(i + 1) == '\'') {
                ha[(int) (2 * s1.charAt(i))] = true;
                i++;//跳过非号
            } else {
                ha[(int) (s1.charAt(i))] = true;
            }
        }
        for (int i = 0; i < s2.length(); i++) {
            if (i < s2.length() - 1 && s2.charAt(i + 1) == '\'') {
                ha[(int) (2 * s2.charAt(i))] = false;
                i++;//跳过非号
            } else {
                ha[(int) (s2.charAt(i))] = false;
            }
        }
        for (int i = 'A'; i <= 2 * 'Z'; i++) {
            if (ha[i]) return false;//s2字符串不能包含s1 s1逻辑上不能包含s2
        }
        return true;
    }

    public static void updateHas() {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < e[i]; j++) {
                int[] tb = new int[500];
                Tools.TruthTable(a[i][j], n, tb);
                if (Contains(tb)) {
                    has[i][j] = true;
                }
            }
        }
    }


    public static void deleteContains() {//删除非质蕴含项
        for (int i = 1; i < n; i++) {//遍历除去最后一行的所有行
            for (int j = 0; j < e[i]; j++) {
                if (has[i][j]) {
                    String s1 = a[i][j];
                    for (int k = i + 1; k <= n; k++) {
                        for (int p = 0; p < e[k]; p++) {
                            if (has[k][p]) {//确认都是蕴含项
                                String s2 = a[k][p];
                                if (StringContains(s1, s2)) {
                                    has[k][p] = false;//被包含，不是质蕴含项
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    public static void updatePrime() {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < e[i]; j++) {
                if (has[i][j]) {
                    pr[++idx] = a[i][j];
                    np[idx] = i;
                }
            }
        }
    }

    public static void dfsChoose(int u) {//from 0
        if (cntOr > minOr) return;//剪枝

        if (u == idx) {
            if (s.length() == 0) return;

            String res = s.substring(0, s.length() - 1);//去掉最后一个加号
            if (cover(res)) {
                if (cntOr < minOr) {
                    minl = cntl;
                    minOr = cntOr;
                    best = res;
                } else {
                    if (cntl < minl) {
                        minl = cntl;
                        best = res;
                    }
                }
            }
            return;
        }
        dfsChoose(u + 1);//不选

        cntOr++;//选
        cntl += np[u + 1];
        String past = s.toString();
        s.append(pr[u + 1]);
        s.append('+');//最后末尾的'+'最后处理
        dfsChoose(u + 1);
        s = new StringBuilder(past);
        cntOr--;
        cntl -= np[u + 1];
    }

    public static int check01() {
        boolean one = true;
        boolean zero = true;
        for (int i = 0; i <= ceiling; i++) {
            if (table[i] == 0) one = false;
            else zero = false;
        }
        if (one) return 1;
        else if (zero) return 0;
        else return 2;
    }

    public void cleanup() {
        for (int i = 0; i <= 499; i++) {
            table[i] = 0;
        }
        l = 0;
        for (int i = 0; i < 499; i++) {
            for (int j = 0; j < 499; j++) {
                has[i][j] = false;
            }
        }
        minl = 0x3f3f3f;
        minOr = 0x3f3f3f;
        cntl = 0;
        cntOr = 0;
        t.delete(0, t.length());
        r.delete(0, r.length());
        idx = 0;
    }

    public String obtainSimplest() {

        cleanup();
        updateData(validInput);
        int ck = check01();
        if (ck == 0) return "0";
        else if (ck == 1) return "1";

        for (int i = 1; i <= n; i++) {
            dfsCom(0, i);
            l = 0;
        }

        eUpdate();
        updateHas();
        deleteContains();
        updatePrime();
        dfsChoose(0);
        return best;
    }


}

