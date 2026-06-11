/**
 * @author Yitong Hong
 */
public class OrAndNot extends ValidInput{
    String orAndNot;

    public OrAndNot(String expression) {
        super(expression);
       orAndNot= Tools.obtainOrAndNotFromexp(expression);
    }

}
