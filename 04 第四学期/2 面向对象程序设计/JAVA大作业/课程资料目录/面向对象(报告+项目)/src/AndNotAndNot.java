/**
 * @author Yitong Hong
 */
public class AndNotAndNot extends ValidInput {
    String AnAn;

    public AndNotAndNot(String expression) {
        super(expression);
        obtainAnAn();
    }

    public AndNotAndNot(String expression, int numOfVariables) {
        super(expression, numOfVariables);
        obtainAnAn();
    }

    public void obtainAnAn() {//外面加非号，加号变乘号 与项外面加括号 非
        AnAn= Tools.obtainAnAnFromexp(expression);
    }


}
