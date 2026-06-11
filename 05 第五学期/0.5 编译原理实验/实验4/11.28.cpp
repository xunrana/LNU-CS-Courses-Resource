#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>

using namespace std;

// 定义符号类型
enum TokenType { NUM, PLUS, MINUS, MULTIPLY, DIVIDE, LPAREN, RPAREN, END, ERROR, ID };

// 文法的产生式编号
enum Production { 
    E_PLUS_T = 1, E_MINUS_T, E_T, 
    T_TIMES_F, T_DIVIDE_F, T_F, 
    F_LPAREN_E_RPAREN, F_ID
};

// 词法分析器，读取并返回下一个符号
TokenType getNextToken(const string &expr, int &index) {
    while (index < expr.length() && (expr[index] == ' ' || expr[index] == '\t')) {
        index++;  // 跳过空格或制表符
    }

    if (index >= expr.length()) return END;  // 到达表达式的末尾

    char current = expr[index];
    index++;

    if (isdigit(current)) return NUM;  // 如果是数字，返回 NUM
    if (current == '+') return PLUS;
    if (current == '-') return MINUS;
    if (current == '*') return MULTIPLY;
    if (current == '/') return DIVIDE;
    if (current == '(') return LPAREN;
    if (current == ')') return RPAREN;
    if (isalpha(current)) return ID;  // 假设字母是一个变量id

    return ERROR;  // 无效字符
}

// 打印栈状态
void printStack(stack<int> &stk) {
    stack<int> temp = stk;  // 创建一个临时栈，避免破坏原栈
    cout << "当前栈状态: ";
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
}

// LR分析表
map<pair<int, TokenType>, string> actionTable;
map<pair<int, TokenType>, int> gotoTable;

// 初始化分析表
void initTables() {
    // 初始化Action表 (移进、规约、接受、报错)
    actionTable[{0, NUM}] = "s5";   // 状态0遇到数字移进到状态5
    actionTable[{0, LPAREN}] = "s4";  // 状态0遇到左括号移进到状态4
    actionTable[{1, PLUS}] = "s6";   // 状态1遇到加号移进到状态6
    actionTable[{1, MINUS}] = "s7";  // 状态1遇到减号移进到状态7
    actionTable[{2, NUM}] = "s5";   // 状态2遇到数字移进到状态5
    actionTable[{2, LPAREN}] = "s4";  // 状态2遇到左括号移进到状态4
    actionTable[{3, PLUS}] = "r1";   // 状态3遇到加号进行规约：E -> E + T
    actionTable[{3, MINUS}] = "r1";  // 状态3遇到减号进行规约：E -> E + T
    actionTable[{3, RPAREN}] = "r1"; // 状态3遇到右括号进行规约：E -> E + T
    actionTable[{4, NUM}] = "s5";   // 状态4遇到数字移进到状态5
    actionTable[{4, LPAREN}] = "s4";  // 状态4遇到左括号移进到状态4
    actionTable[{5, PLUS}] = "r2";   // 状态5遇到加号进行规约：T -> T * F
    actionTable[{5, MINUS}] = "r2";  // 状态5遇到减号进行规约：T -> T * F
    actionTable[{5, RPAREN}] = "r2"; // 状态5遇到右括号进行规约：T -> T * F
    // ... (继续为更多状态初始化表)

    // 初始化Goto表 (跳转)
    gotoTable[{0, E}] = 1;
    gotoTable[{1, T}] = 2;
    gotoTable[{2, F}] = 3;
    // ... (继续初始化更多的Goto表)
}

// 执行LR分析
void parse(const string &expr) {
    stack<int> stateStack;  // 状态栈
    stack<TokenType> symbolStack;  // 符号栈

    stateStack.push(0);  // 初始状态为0
    TokenType token;
    int index = 0;
    token = getNextToken(expr, index);

    while (true) {
        int currentState = stateStack.top();
        
        if (actionTable[{currentState, token}] == "ERROR") {
            cout << "遇到错误：非法输入!" << endl;
            break;
        }

        string action = actionTable[{currentState, token}];
        
        if (action[0] == 's') {  // 移进操作
            int nextState = action[1] - '0';  // 移进到下一个状态
            stateStack.push(nextState);
            symbolStack.push(token);
            token = getNextToken(expr, index);
            cout << "移进，栈状态：";
        }
        else if (action[0] == 'r') {  // 规约操作
            int production = action[1] - '0';  // 根据产生式编号进行规约
            cout << "规约：根据产生式" << production << endl;
            for (int i = 0; i < 2; i++) {  // 假设每个产生式右边有2个符号
                stateStack.pop();
                symbolStack.pop();
            }
            stateStack.push(gotoTable[{stateStack.top(), E}]);  // 跳转到新的状态
            symbolStack.push(E);  // 推入非终结符
        }
        else if (action == "ACC") {  // 接受
            cout << "分析完成，接受!" << endl;
            break;
        }

        printStack(stateStack);  // 打印栈状态
    }
}

// 主函数
int main() {
    string expr;
    cout << "请输入算术表达式: ";
    getline(cin, expr);  // 读取一行输入的算术表达式
    
    initTables();  // 初始化分析表
    parse(expr);  // 解析输入的表达式
    return 0;
}

