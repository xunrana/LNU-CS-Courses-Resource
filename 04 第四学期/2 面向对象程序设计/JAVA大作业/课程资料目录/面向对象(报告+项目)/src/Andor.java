/**
 * @author Yitong Hong
 */
public class Andor extends ValidInput {
    public Andor(String expression) {
        super(expression);
    }

    public Andor(String expression, int numOfVariables) {
        super(expression, numOfVariables);
    }

    public Andor() {
    }

    @Override
    public void obtainInversion() {
        String s = expression;
        s += '+';
        StringBuilder r = new StringBuilder();
        StringBuilder p = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '+') {
                r.append('(');
                r.append(Tools.obtainInvForAnd(p.toString()));
                p.delete(0, p.length());
                r.append(')');
            } else {
                p.append(s.charAt(i));
            }
        }
        Inversion = r.toString();
        Inversion = Tools.Formatted(Inversion);//去掉多余括号
    }

    //效率更高
    @Override
    public void obtainStandardAndOr() {
        standardAndOr = Tools.AndOrtoStandardAndOr(expression, numOfVariables);
    }

    @Override
    public void obtainSum() {
        sum = Tools.SumFromAndor(expression, numOfVariables);//与或即可，不必标准与或
    }

    @Override
    public void obtainMulti() {
        multi = Tools.MultiFromAndor(expression, numOfVariables);//与或即可，不必标准与或
    }
}
