import javax.tools.Tool;
import java.util.Stack;
import java.util.Vector;

/**
 * @author Yitong Hong
 */
public class ValidInput extends Input {
    public String suffix;//后缀表达式（用于求值）
    public String Inversion;//反演（用反演规则得到的）
    public String withMul;//有乘号的版本，求后缀
    public String dual;//对偶式，可根据反演式求
    public String standardAndOr; //标准与或
    public String standardOrAnd;//标准或与
    public int[] table=new int[2000];//真值表
    public String sum;//最小项之和
    public String multi;//最大项之积


    public void obtainInversion(){
        Inversion=Tools.obtainInversion(expression);
    }
    public void obtainTruthTable(){
        Tools.TruthTable(expression,numOfVariables,table);
    }
    public void obtainDual(){
        dual=Tools.obtainDual(Inversion);
    }
    public void obtainStandardAndOr(){
        standardAndOr=Tools.AnyToStandardAndOr(expression,numOfVariables);
    }
    public void obtainStandardOrAnd(){
        standardOrAnd=Tools.AnyToStandardOrAnd(expression,numOfVariables);
    }
    public void obtainSum(){
        sum=Tools.SumFromAndor(standardAndOr,numOfVariables);
    }
    public void obtainMulti(){
        multi=Tools.MultiFromAndor(standardAndOr,numOfVariables);
    }


    public ValidInput(String expression) {
        super(expression);
        this.suffix = Tools.obtainSuffix(expression);
        this.withMul=Tools.addMul(expression);
        obtainInversion();
        obtainDual();

        obtainTruthTable();
    }

    public ValidInput(String expression, int numOfVariables) {
        super(expression, numOfVariables);
        this.suffix = Tools.obtainSuffix(expression);
        this.withMul=Tools.addMul(expression);
        obtainInversion();
        obtainDual();
        obtainTruthTable();

    }


    public ValidInput() {
    }


    public String showTruthTable(){
            return Tools.showTruthTable(table,numOfVariables);
    }

}