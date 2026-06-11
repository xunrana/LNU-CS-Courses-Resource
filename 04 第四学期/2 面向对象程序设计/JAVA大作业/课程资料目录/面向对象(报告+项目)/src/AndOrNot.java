/**
 * @author Yitong Hong
 */
public class AndOrNot extends ValidInput{
    String andOrNot;

    public AndOrNot(String andOrNot) {
        this.andOrNot = andOrNot;
        obtainAndOrnot();
    }

    public AndOrNot(String expression, int numOfVariables) {
        super(expression, numOfVariables);
        obtainAndOrnot();
    }

    public void obtainAndOrnot(){
        andOrNot=Tools.obtainAndOrNot(expression);
    }
}
