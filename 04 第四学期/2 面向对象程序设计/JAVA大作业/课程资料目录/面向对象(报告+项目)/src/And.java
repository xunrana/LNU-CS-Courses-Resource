import com.sun.glass.ui.monocle.AndroidInputDeviceRegistry;

/**
 * @author Yitong Hong
 */
public class And extends Andor {
    public And(String expression) {
        super(expression);
    }

    public And(String expression, int numOfVariables) {
        super(expression, numOfVariables);
    }

    public And() {
    }

    @Override
    public void obtainInversion() {//重写求反演的方法，由于是单个与项，可以用更高效的方式直接求，不必那么复杂
        Inversion=Tools.obtainInvForAnd(expression);
    }
}
