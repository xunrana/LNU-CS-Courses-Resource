/**
 * @author Yitong Hong
 */
public class OrAnd extends ValidInput {
    String orAnd;

    public OrAnd(String expression) {
        super(expression);
    }
    public void obtainOrAnd(){
        orAnd=Tools.obtainOrAndFromexp(expression);
    }
}
