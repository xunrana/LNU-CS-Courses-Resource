import java.util.Stack;

/**
 * @author Yitong Hong
 */

public class Input {
    public String expression;
    public int numOfVariables;

    public String getExpression() {
        return expression;
    }

    public void setExpression(String expression) {
        this.expression = expression;
    }

    public int getNumOfVariables() {
        return numOfVariables;
    }

    public void setNumOfVariables(int numOfVariables) {
        this.numOfVariables = numOfVariables;
    }

    public static int idxOfVariables(char c) {//输入'A' 返回1 根据变量找序号
        return c-'A'+1;
    }
    public static char variableByIdx(int x){//输入1 返回'A' 根据序号找变量
        return (char)(x-1+'A');
    }
    public Input(String expression) {//如果给定变量个数，则默认表达式中最大的大写字母对应的序号为变量个数
        this.expression = expression;
        obtainNumOfVariables();
    }

    public void obtainNumOfVariables(){
        int maxx = 0;
        for (int i = 0; i < expression.length(); i++) {
            char c = expression.charAt(i);
            if (Character.isUpperCase(c)) {
                if (maxx == 0) {
                    maxx = c;
                } else {
                    if (c > maxx) {
                        maxx = c;
                    }
                }
            }
        }
        this.numOfVariables = maxx+1-'A';

    }

    public Input(String expression, int numOfVariables) {
        this.expression = expression;
        this.numOfVariables = numOfVariables;
    }

    public Input() {
    }






}
