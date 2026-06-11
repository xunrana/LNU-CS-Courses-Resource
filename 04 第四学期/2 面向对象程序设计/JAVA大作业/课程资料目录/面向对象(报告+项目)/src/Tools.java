import java.util.Stack;
import java.util.Vector;

import static java.lang.Math.pow;

/**
 * @author Yitong Hong
 */
public class Tools {
    public static boolean NoOtherChar(String s) {//判断是否都为合法字符
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c != '+' && (!Character.isUpperCase(c)) && c != '(' && c != ')' && c != '\'') {
                return false;
            }
        }
        return true;
    }

    public static boolean noEmptyBracket(String s) {//是否没有空括号
        int[] front = new int[2000];
        int[] back = new int[2000];
        Stack<Integer> sk = new Stack<>();
        Stack<Integer> pfront = new Stack<>();
        int id = 1;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '(') {
                sk.push(id);
                id++;
                pfront.push(i);
            } else if (s.charAt((i)) == ')') {

                int tsk = sk.peek();
                int tpf = pfront.peek();
                front[tsk] = tpf;
                back[tsk] = i;
                sk.pop();
                pfront.pop();
            }
        }
        for (int i = 1; i < id; i++)
            if (front[i] + 1 == back[i]) return false;

        return true;
    }


    public static boolean check(String s) {

        if (!NoOtherChar(s)) return false;
        Stack<Integer> sk = new Stack<>();
        boolean f = true;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '(') sk.push(1);
            else if (c == ')') {
                if (sk.empty()) {
                    return false;
                }
                sk.pop();
            }
        }
        if (!sk.empty()) return false;

        if (!noEmptyBracket(s)) return false;//不允许有空括号

        for (int i = 0; i < s.length(); i++)//非号的位置，只能是')'后或者字母或另一个非号后 ，不可以在开头
        {
            if (s.charAt(i) == '\'') {
                if (i == 0) return false;
                boolean letter = false;
                if (Character.isUpperCase(s.charAt(i - 1)) || s.charAt(i - 1) == '\'')
                    letter = true;//前面是字母或者非号都算作letter为true了
                if (s.charAt(i - 1) != ')' && (!letter)) return false;
            }
        }
        for (int i = 0; i < s.length(); i++)//加号的位置，不能在头尾，且前面要求是字母、非号、')'，后面要求是字母或者'('
        {
            char c = s.charAt(i);
            if (c == '+') {
                if (i == 0 || i == s.length() - 1) return false;
                char b = s.charAt(i - 1);
                char d = s.charAt(i + 1);
                boolean blt = false;
                boolean dlt = false;
//                if (b >= 'A' && b <= 'Z') blt = true;
                if (Character.isUpperCase(b)) blt = true;
                if (Character.isUpperCase(d)) dlt = true;
                if (b != '\'' && b != ')' && (!blt)) return false;
                if (d != '(' && (!dlt)) return false;
            }
        }
        return true;

    }


    //输入合法基础上，删除双重非号
    public static String delDoubleInv(String s) {
        boolean[] h = new boolean[2000];//1 0
        Vector<Character> v = new Vector<Character>();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (i == 0) v.add(c);
            else {
                if (c == '\'' && v.lastElement() == '\'') {
                    v.remove(v.size() - 1);
                    h[i] = true;
                    h[i - 1] = true;
                } else {
                    v.add(s.charAt(i));
                }
            }
        }
        StringBuilder buf = new StringBuilder();
        for (int i = 0; i < s.length(); i++) if (!h[i]) buf.append(s.charAt(i));
        return buf.toString();
    }


    //输入合法的基础上 （此函数作用是加乘号，为了求后缀表达式）
    public static String addMul(String s) {
        String r;
        boolean[] h = new boolean[2000];
        for (int i = 0; i < s.length() - 1; i++) {
            if ((Character.isUpperCase(s.charAt(i)) || s.charAt(i) == ')' ||
                    s.charAt(i) == '\'') && (Character.isUpperCase(s.charAt(i + 1))
                    || s.charAt(i + 1) == '(')) {
                h[i] = true;
            }
        }
        StringBuilder buf = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            buf.append(s.charAt(i));
            if (h[i]) buf.append('*');
        }
        return buf.toString();
    }

    public static boolean cmp(char x, char y) {//前面的优先级不低于后面
        if (x == '\'') return true;
        if (x == '*' && (y == '*' || y == '+')) return true;
        if (x == '+' && y == '+') return true;
        return false;
    }


    //format之后吧
    public static String obtainSuffix(String s) {
        addMul(s);//先加乘号
        StringBuilder buf = new StringBuilder();
        Stack<Character> sk = new Stack<>();
        for (int i = 0; i < s.length(); i++) {
            if (Character.isUpperCase(s.charAt(i))) {
                buf.append(s.charAt(i));
            } else if (s.charAt(i) == '(') {
                sk.push(s.charAt(i));
            } else if (s.charAt(i) == ')') {
                while (sk.peek() != '(') {
                    buf.append(sk.peek());
                    sk.pop();
                }
                sk.pop();//弹出(
            } else {
                while ((!sk.empty()) && cmp(sk.peek(), s.charAt(i))) {
                    buf.append(sk.peek());
                    sk.pop();
                }
                sk.push(s.charAt(i));

            }

        }
        while (!sk.empty()) {
            buf.append(sk.peek());
            sk.pop();
        }
        return buf.toString();
    }


    //输入合法基础上
    public static String delInnerBracket(String s) {
        int len = s.length();
        boolean[] h = new boolean[2000];

        int[] front = new int[2000];
        int[] back = new int[2000];
        Stack<Integer> sk = new Stack<>();
        Stack<Integer> pfront = new Stack<>();
        int id = 1;
        for (int i = 0; i < len; i++) {
            if (s.charAt(i) == '(') {
                sk.push(id);
                id++;
                pfront.push(i);
            } else if (s.charAt(i) == ')')//存括号位置
            {
                int tsk = sk.peek();
                int tpf = pfront.peek();
                front[tsk] = tpf;
                back[tsk] = i;
                sk.pop();
                pfront.pop();
            }
        }
        //除去(((xxx)))内层括号
        for (int i = id - 2; i >= 1; i--) {
            if (front[i + 1] == front[i] + 1 && back[i + 1] == back[i] - 1) {
                h[front[i]] = true;
                h[back[i]] = true;
            }
        }


        StringBuilder ns = new StringBuilder();
        for (int i = 0; i < len; i++) {
            if (!h[i]) ns.append(s.charAt(i));
        }
        return ns.toString();
    }

    public static String delUselessBracket(String s) {//删除不影响优先级的括号（但不包括嵌套）
        int len = s.length();
        boolean[] h = new boolean[2000];
        int[] front = new int[2000];
        int[] back = new int[2000];
        Stack<Integer> sk = new Stack<>();
        Stack<Integer> pfront = new Stack<>();
        int id = 1;
        for (int i = 0; i < len; i++) {
            if (s.charAt(i) == '(') {
                sk.push(id);
                id++;
                pfront.push(i);
            } else if (s.charAt(i) == ')')//存括号位置
            {
                int tsk = sk.peek();
                int tpf = pfront.peek();
                front[tsk] = tpf;
                back[tsk] = i;
                sk.pop();
                pfront.pop();
            }
        }
        for (int i = 1; i < id; i++) {
            int l = front[i];
            int r = back[i];
            int leftBracket = 0;
            boolean add = false;
            boolean MulorAdd = false;
            int cnt = 0;

            for (int j = l + 1; j <= r - 1; j++) {

                if (s.charAt(j) == '(') leftBracket++;
                if (s.charAt(j) == ')') leftBracket--;
                if (leftBracket == 0)//当积累的左侧小括号为0时，说明此时不再受小括号保护)
                {
                    if (s.charAt(j) == '+') add = true;
                }
                if (Character.isUpperCase(s.charAt(j))) cnt++;//只要存在两个字母(这个无所谓中间的括号)，一定存在乘法或加法运算
            }
            if (cnt >= 2) MulorAdd = true;//至少两个字母一定存在加或者乘的关系（因为不存在嵌套多余括号）
            // 无论是加的关系还是乘的关系，我们都认为是外面的不能优先于乘
            boolean omul = false;
            boolean backN = false;
            if (r < len - 1 && s.charAt(r + 1) == '\'') backN = true;
            if (l >= 1) {
                if (s.charAt(l - 1) == '\'' || Character.isUpperCase(s.charAt(l - 1))
                        || s.charAt(l - 1) == ')')//左括号前是：1.非号 2.字母 3.')' 都相当于乘
                {
                    omul = true;
                }
            }
            if (r < len - 1) {
                if (Character.isUpperCase(s.charAt(r + 1)) || s.charAt(r + 1) == '(')
                    omul = true;//右括号后是：1.字母 2.'(' 都相当于乘
            }

            if (!(add && omul || MulorAdd && backN))//里面未被保护的加 外面乘；里面加或乘（即不止一个变量）外面后面非 这两种情况括号有用 否则无用
            {
                h[l] = true;
                h[r] = true;
            }

        }


        StringBuilder r = new StringBuilder();
        for (int i = 0; i < len; i++) {
            if (!h[i]) r.append(s.charAt(i));
        }
        return r.toString();
    }

    public static String Formatted(String s) {
        s = delDoubleInv(s);
        s = delInnerBracket(s);
        s = delUselessBracket(s);//此步在delInnerBracket之后
        s = delDoubleInv(s);
        return s;
    }

    public static String obtainInversion(String s) {
        if (s.equals("0")) return "1";
        if (s.equals("1")) return "0";
        s = Formatted(s);

        String des;
        int len = s.length();
        s += '+';//此函数独有的，但是由于板子部分用的是len，故不影响

        int[] front = new int[2000];
        int[] back = new int[2000];

        Stack<Integer> sk = new Stack<>();//存id（括号编号） 一对括号一个编号，按照左括号出现次序从1开始
        Stack<Integer> pfront = new Stack<>();//存字符串中的下标号
        int id = 1;
        for (int i = 0; i < len; i++) {
            if (s.charAt(i) == '(') {
                sk.push(id);
                id++;
                pfront.push(i);
            } else if (s.charAt(i) == ')')//存括号位置
            {
                int tsk = sk.peek();
                int tpf = pfront.peek();
                front[tsk] = tpf;//之前左括号是第tpf个
                back[tsk] = i;//当前到第i个（字符串中的序号）

                sk.pop();
                pfront.pop();
            }
        }

        int[] addLeft = new int[2000];
        int[] addRight = new int[2000];
        for (int i = 0; i < s.length() - 1; i++)//先把所有连续的变量都给括起来（中间末尾可以有非号，不可以有括号）
        {
            if (Character.isUpperCase(s.charAt(i)))//变量连乘
            {
                int start = i;
                while (Character.isUpperCase(s.charAt(i)) || s.charAt(i) == '\'')//s我们额外加了一个'+'，故这样不会越界
                {
                    i++;
                }
                i--; //i的值为该与项的最后一个变量(字母或非号)
                int end = i;
                addLeft[start]++;
                addRight[end]++;
            }
        }


        StringBuilder r = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            while (addLeft[i]-- > 0) {
                r.append('(');
            }
            if (Character.isUpperCase(s.charAt(i))) {
                r.append(s.charAt(i));
                if (i + 1 < s.length() && s.charAt(i + 1) == '\'') r.append('\'');
            } else r.append(s.charAt(i));
            while (addRight[i]-- > 0) {
                r.append(')');
            }
        }
        s = r.substring(0, r.length() - 1);
        des = s;


        //现在s一连串的变量已经被括号包起来了 只需考虑括号间的乘法 注意()'()情况  不仅仅是()()
        len = s.length();

        Stack<Integer> sk1 = new Stack<>();//存id（括号编号） 一对括号一个编号，按照左括号出现次序从1开始
        Stack<Integer> pfront1 = new Stack<>();//存字符串中的下标号
        id = 1;
        for (int i = 0; i < len; i++) {
            if (s.charAt(i) == '(') {
                sk1.push(id);
                id++;
                pfront1.push(i);

            } else if (s.charAt(i) == ')')//存括号位置
            {
                int tsk = sk1.peek();
                int tpf = pfront1.peek();
                front[tsk] = tpf;//之前左括号是第tpf个
                back[tsk] = i;//当前到第i个（字符串中的序号）

                sk1.pop();
                pfront1.pop();
            }
        }


        int[] reFront = new int[2000];//与front数组相反的映射 通过左半括号的位置找序号
        int[] reBack = new int[2000];//与back数组相反的映射 通过右半括号的位置找序号 （然后可以通过序号找另一边括号的位置)
        int[] addAdd = new int[2000];

        for (int i = 1; i < id; i++) {
            reFront[front[i]] = i;
            reBack[back[i]] = i;
        }
        for (int i = 0; i < 2000; i++) {
            addLeft[i] = 0;
            addRight[i] = 0;
        }
        r.delete(0, r.length());//

        for (int i = 0; i < s.length() - 1; i++) {
            if (s.charAt(i) == ')' && s.charAt(i + 1) == '(') {

                addLeft[front[reBack[i]]]++;
                addRight[back[reFront[i + 1]]]++;
                addAdd[i]++;
            } else if (s.charAt(i) == '\'' && s.charAt(i + 1) == '(') {

                addLeft[front[reBack[i - 1]]]++;
                addRight[back[reFront[i + 1]]]++;
                addAdd[i]++;
            } else if (Character.isUpperCase(s.charAt(i)) && Character.isUpperCase(s.charAt(i + 1))
                    || s.charAt(i) == '\'' && Character.isUpperCase(s.charAt(i + 1))) {

                addAdd[i]++;
            }
        }


        for (int i = 0; i < s.length(); i++)//先加左括号，加号直接去掉，变量改成反变量，如果需要加法则加一下，最后加右括号
        {
            while (addLeft[i]-- > 0) {

                r.append('(');
            }


            if (Character.isUpperCase(s.charAt(i)))//如果是变量，(变成反变量）连同非号一起加
            {

                r.append(s.charAt(i));
                if (!(i + 1 < s.length() && s.charAt(i + 1) == '\'')) r.append('\'');
            } else if (s.charAt(i) != '+') r.append(s.charAt(i));
            while (addRight[i]-- > 0) {

                r.append(')');
            }
            if (addAdd[i] > 0) r.append('+');

        }
        return Formatted(r.toString());
    }

    public static String obtainDual(String s) {
        StringBuilder r = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            if (Character.isUpperCase(s.charAt(i))) {
                if (i + 1 < s.length() && s.charAt(i + 1) == '\'') {//A'
                    r.append(s.charAt(i));
                    i++;//下一个是非号，可直接跳过，但还有其他
                    //出现非号的地方，比如括号后面
                } else {//A
                    r.append(s.charAt(i));
                    r.append('\'');
                }
            } else {
                r.append(s.charAt(i));
            }
        }
        return r.toString();
    }

    public static String obtainInvForAnd(String s) {
        StringBuilder r = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            if (Character.isUpperCase(s.charAt(i))) {
                if (i + 1 < s.length() && s.charAt(i + 1) == '\'') {
                    r.append(s.charAt(i));
                } else {
                    r.append(s.charAt(i));
                    r.append('\'');
                }
                r.append('+');

            }
        }
        return r.substring(0, r.length() - 1);
    }

    public static int idx = 0;
    public static int[] h = new int[2000];

    public static void dfs(int u, int n, int[] ans) {
        if (u == n + 1) {
            ans[idx]++;
            return;
        }
        int ha = h['A' + u - 1];
        if (ha == 0) {
            dfs(u + 1, n, ans);
            int t = (int) pow(2, n - u);
            idx += t;
            dfs(u + 1, n, ans);
            idx -= t;
        } else if (ha == 1) {
            int t = (int) pow(2, n - u);
            idx += t;
            dfs(u + 1, n, ans);
            idx -= t;
        } else if (ha == 2) {
            dfs(u + 1, n, ans);
        }
    }


    public static void DataFromAndor(String s, int n, int[] ans) {
        idx = 0;
        int ceiling = (int) (Math.pow(2, n) - 1);
        s += '+';
        boolean f = true;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '+') {
                if (f) {
                    idx = 0;
                    dfs(1, n, ans);
                } else f = true;
                for (int j = 0; j < 2000; j++) h[j] = 0;
            } else if (s.charAt(i + 1) == '\'') {
                if (h[c] == 0 || h[c] == 2) h[c] = 2;
                else {
                    h[c] = 3;
                    f = false;
                }
                i++;
            } else {
                if (h[c] == 0 || h[c] == 1) h[c] = 1;
                else {
                    h[c] = 3;
                    f = false;
                }
            }
        }
    }


    //最小项之和
    public static String SumFromAndor(String s, int n) {
        StringBuilder r = new StringBuilder();
        int[] ans = new int[2000];
        DataFromAndor(s, n, ans);
        int ceiling = (int) (pow(2, n) - 1);
        r.append("m(");
        int t = 0;
        for (int i = 0; i <= ceiling; i++) {
            if (ans[i] > 0) {
                if (t != 0) r.append(',');
                r.append(String.valueOf(i));
                t++;
            }
        }
        r.append(')');
        return r.toString();
    }

    public static String MultiFromAndor(String s, int n) {
        StringBuilder r = new StringBuilder();
        int[] ans = new int[2000];
        DataFromAndor(s, n, ans);
        int ceiling = (int) (pow(2, n) - 1);
        r.append("M(");
        int t = 0;
        for (int i = 0; i <= ceiling; i++) {
            if (ans[i] == 0) {
                if (t != 0) r.append(',');
                r.append(String.valueOf(i));
                t++;
            }
        }
        r.append(')');
        return r.toString();
    }


    public static String AndFromIdx(int x, int n) {
        StringBuilder r = new StringBuilder();
        boolean[] ha = new boolean[2000];
        for (int i = n - 1; i >= 0; i--) {
            if (x % 2 > 0) ha[i] = true;
            else ha[i] = false;
            x /= 2;
        }
        for (int i = 0; i < n; i++) {
            r.append((char) ('A' + i));
            if (!ha[i]) r.append('\'');
        }
        return r.toString();
    }

    public static void DetailFromIdx(int x, int[] a, int n) {
        for (int i = n; i >= 1; i--) {
            a[i] = x % 2;
            x /= 2;
        }
    }

    public static int ValueFromSuffix(String suf, int x, int n) {

        int[] a = new int[2000];
        DetailFromIdx(x, a, n);
        Stack<Integer> sk = new Stack<>();
        for (int i = 0; i < suf.length(); i++) {
            if (Character.isUpperCase(suf.charAt(i))) {
                sk.push(a[suf.charAt(i) - 'A' + 1]);
            } else {
                if (suf.charAt(i) == '\'') {
                    int tp = sk.peek();
                    sk.pop();
                    tp = 1 - tp;
                    sk.add(tp);
                } else if (suf.charAt(i) == '*') {
                    int later = sk.peek();
                    sk.pop();
                    int former = sk.peek();
                    sk.pop();
                    sk.push(later & former);//
                } else if (suf.charAt(i) == '+') {
                    int later = sk.peek();
                    sk.pop();
                    int former = sk.peek();
                    sk.pop();
                    sk.push(later | former);
                }
            }
        }
        return sk.peek();
    }

    public static void TruthTable(String s, int n, int[] table) {

        String r;

        r = addMul(s);

        String suf = obtainSuffix(r);

        int ceiling = (int) (pow(2, n) - 1);
        for (int i = 0; i <= ceiling; i++) {

            table[i] = ValueFromSuffix(suf, i, n);

        }
    }

    public static String showTruthTable(int[] table, int n) {
        StringBuilder r = new StringBuilder();
        for (int i = 0; i < n; i++) {

            r.append((char) ('A' + i));
        }
        r.append("\t" + 'F');
        r.append('\n');
        int ceiling = (int) (pow(2, n) - 1);
        for (int i = 0; i <= ceiling; i++) {
            int ii = i;
            StringBuilder b = new StringBuilder();
            while (ii > 0) {
                b.append(String.valueOf(ii % 2));
                ii /= 2;
            }

            while (b.length() < n) b.append('0');

            b.reverse();
            r.append(b).append("\t");
            r.append(table[i]);
            r.append('\n');
        }
        return r.toString();
    }
    public static String AnyToStandardAndOr(String s,int n){
        s=getSimplestAndor(s,n);
        if(s.equals("0")) return "0";
        if(s.equals("1")) return "1";
        return AndOrtoStandardAndOr(s,n);
    }


    //与或变为标准与或
    public static String AndOrtoStandardAndOr(String s, int n) {
        int[] ans = new int[2000];
        DataFromAndor(s, n, ans);
        StringBuilder r = new StringBuilder();
        int ceiling = (int) (Math.pow(2, n) - 1);
        int t = 0;
        for (int i = 0; i <= ceiling; i++) {
            if (ans[i] > 0) {
                if (t != 0) {
                    r.append('+');
                }
                r.append(AndFromIdx(i, n));
                t++;
            }
        }
        return r.toString();
    }


    //任何表达式变为标准或与
    public static String AnyToStandardOrAnd(String s, int n) {
        String rs = obtainInversion(s);
        String andor = AndOrtoStandardAndOr(rs, n);
        String randor = obtainInversion(andor);
        return randor;
    }

    public static String getSimplestAndor(String s) {

        ValidInput validInput = new ValidInput(s);

        Simplest simplest = new Simplest(validInput);
        return simplest.obtainSimplest();
    }
    public static String getSimplestAndor(String s,int n) {
        ValidInput validInput = new ValidInput(s,n);

        Simplest simplest = new Simplest(validInput);
        return simplest.obtainSimplest();
    }

    //与非与非
    public static String obtainAnAnFromexp(String ex) {

        String s = getSimplestAndor(ex);
        if (s.equals("0")) return "0";
        if (s.equals("1")) return "1";
        StringBuilder r = new StringBuilder();
        r.append('(');
        s += '+';//方便处理
        StringBuilder p = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) != '+') {
                p.append(s.charAt(i));
            } else {
                r.append('(');
                r.append(p);
                r.append(')');
                r.append('\'');
                p.delete(0, p.length());
            }
        }
        r.append(')');
        r.append('\'');
        return r.toString();
    }

    //或与非
    public static String obtainOrAndNotFromexp(String ex) {

        String s = getSimplestAndor(ex);
        if (s.equals("0")) return "0";
        if (s.equals("1")) return "1";
        StringBuilder r = new StringBuilder();
        r.append('(');
        r.append(Tools.obtainInversion(s));
        r.append(')');
        r.append('\'');
        return r.toString();
    }

    public static String obtainOrAndFromexp(String ex) {

        String ns = obtainInversion(ex);

        return obtainInversion(getSimplestAndor(ns));
    }


    public static String obtainAndOrNot(String ex) {
        String s = obtainOrAndFromexp(ex);
        if (s.equals("0")) return "0";
        if (s.equals("1")) return "1";
        StringBuilder r = new StringBuilder();
        r.append('(');
        r.append(obtainInversion(s));
        r.append(')');
        r.append('\'');
        return r.toString();
    }


}
