#include <bits/stdc++.h>
using namespace std;

// 定义Token的类型（标记类型），用于表示词法分析中的不同符号类型
enum Type {  
    ID,// 标识符
    PLUS,// 加号
    TIMES,// 乘号
    LPAREN,// 左括号
    RPAREN,// 右括号
    END,// 结束符号
    E,// 非终结符 E
    T,// 非终结符 T
    F // 非终结符 F
};
// Token结构体，用于表示一个Token（词法单元），包含类型和词素
struct Token {
    Type type;  // Token的类型
    string lexeme;  // Token的词素
};

// 用来打印Token类型的映射表
map<Type, string> TokenType = {
    {ID, "ID"},
    {PLUS, "PLUS"},
    {TIMES, "TIMES"},
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {END, "END"},
    {E, "E"},
    {T, "T"},
    {F, "F"}
};

// Lexer类：负责扫描输入字符串并生成Token
class Lexer {
public:
	// 构造函数，接收一个字符串并对其进行词法分析
    Lexer(string s) {
        string lx;
        for (auto i : s) {// 遍历输入字符串中的每个字符
            if (isalpha(i)) {// 如果是字母（标识符）
                lx += i;// 将字符加入到当前词素
            } else if (i == '+') {// 如果是加号
                if (lx != "") tokens.push_back({ID, lx}), lx = ""; // 如果之前有标识符，则生成Token
                tokens.push_back({PLUS, "+"});// 生成加号Token
            } else if (i == '*') {// 如果是乘号
                if (lx != "") tokens.push_back({ID, lx}), lx = "";// 如果之前有标识符，则生成Token
                tokens.push_back({TIMES, "*"});// 生成乘号Token
            } else if (i == '(') {// 如果是左括号
                if (lx != "") tokens.push_back({ID, lx}), lx = ""; // 如果之前有标识符，则生成Token
                tokens.push_back({LPAREN, "("});// 生成左括号Token
            } else if (i == ')') {// 如果是右括号
                if (lx != "") tokens.push_back({ID, lx}), lx = ""; // 如果之前有标识符，则生成Token
                tokens.push_back({RPAREN, ")"});// 生成右括号Token
            } else if (i == '\n' || i == ' ') {// 如果是换行或空格
                // 空格或换行
                if (lx != "") tokens.push_back({ID, lx});// 如果有标识符，将其加入Token列表
                lx = "";// 重置临时变量
            } else {
                // ERROR
                throw runtime_error("Invalid character");// 抛出异常，表示非法字符
            }
        }
        if (lx != "") {// 如果最后还有未处理的标识符
            tokens.push_back({ID, lx}); // 将标识符加入Token列表
        }
        tokens.push_back({END, "$"});// 在Token列表末尾加入结束符Token
    }

    queue<Type> getTokens() {// 获取所有的Token，并返回一个队列
        queue<Type> res;
        for (auto i : tokens) { // 遍历Token列表
            res.push(i.type);// 将Token类型加入队列
        }
        return res;// 返回Token队列
    }

private:
    vector<Token> tokens;  // 存储Token列表
};

// LRParser类：实现LR语法分析
class LRParser {
public:
	 // 构造函数，接收一个Token队列
    LRParser(queue<Type> tokens){
        this->tokens=tokens;// 将传入的Token队列赋值给成员变量
    }
    // 开始解析过程
    void parse(){
        stateStack.push(0);// 初始状态压入状态栈
        int nowState;// 当前状态
        Type nowToken; // 当前Token
        while(true){
            nowState = stateStack.top();// 获取栈顶状态
            nowToken = tokens.front();// 获取队列中的第一个Token
            auto nowAction = action[{nowState, nowToken}];// 根据当前状态和Token查找对应的动作
            if(nowAction.first==0){    // 如果动作是SHIFT（移入）
                stateStack.push(nowAction.second);// 将新的状态压入状态栈
                symbolStack.push(nowToken);// 将当前Token压入符号栈
                tokens.pop();// 移除已经处理的Token
                cout<<"Shift \t"<<TokenType[nowToken]<<endl;// 输出当前的SHIFT动作
            }else if(nowAction.first==1){  // 如果动作是REDUCE（归约）
                int num = Grammar[nowAction.second].second;// 获取归约所需的符号数量
                reduce(num);// 执行归约
				reduceStates(num);// 归约时，移除状态栈中的元素
                stateStack.push(gotoTable[{stateStack.top(), Grammar[nowAction.second].first}]);// 根据新的非终结符转移到新的状态
                symbolStack.push(Grammar[nowAction.second].first); // 将新的非终结符压入符号栈
                cout<<"Reduce \t"<<GrammarStr[nowAction.second]<<endl;// 输出当前的REDUCE动作
            }else if(nowAction.first==2){  // 如果动作是ACC（接受）
                cout<<"Accept"<<endl;// 输出接受消息
                break;// 解析完成，跳出循环
            }else{
            	// 如果遇到错误动作
                cout<<"Error"<<endl;// 输出错误信息
                break;// 跳出循环
            }
        }
    }
private:
	 // 语法规则表，表示文法的产生式
    vector<pair<int, int>> Grammar={
        {},// 第0条规则是空的，占位
        {E,3},// E -> E + T
        {E,1},// E -> T
        {T,3},// T -> T * F
        {T,1},// T -> F
        {F,3},// F -> ( E )
        {F,1}// F -> id
    };
    // 产生式的字符串表示
    string GrammarStr[7]={
        "",// 第0条规则为空，占位
        "E->E+T",// 规则1
        "E->T",// 规则2
        "T->T*F",// 规则3
        "T->F",// 规则4
        "F->(E)",// 规则5
        "F->id"// 规则6
    };
     // Action表，定义每个状态和每个Token的动作
    map<pair<int, int>, pair<int, int>> action={
        {{0,ID},{0,5}},     {{0,LPAREN},{0,4}},
        {{1,PLUS},{0,6}},   {{1,END},{2,2}},
        {{2,PLUS},{1,2}},   {{2,TIMES},{0,7}},  {{2,RPAREN},{1,2}}, {{2,END},{1,2}},
        {{3,PLUS},{1,4}},   {{3,TIMES},{1,4}},  {{3,RPAREN},{1,4}}, {{3,END},{1,4}},
        {{4,ID},{0,5}},     {{4,LPAREN},{0,4}},
        {{5,PLUS},{1,6}},   {{5,TIMES},{1,6}},  {{5,RPAREN},{1,6}}, {{5,END},{1,6}},
        {{6,ID},{0,5}},     {{6,LPAREN},{0,4}},
        {{7,ID},{0,5}},     {{7,LPAREN},{0,4}},
        {{8,PLUS},{0,6}},   {{8,RPAREN},{0,11}},
        {{9,PLUS},{1,1}},   {{9,TIMES},{0,7}},  {{9,RPAREN},{1,1}}, {{9,END},{1,1}},
        {{10,PLUS},{1,3}},  {{10,TIMES},{1,3}}, {{10,RPAREN},{1,3}},{{10,END},{1,3}},
        {{11,PLUS},{1,5}},  {{11,TIMES},{1,5}}, {{11,RPAREN},{1,5}},{{11,END},{1,5}}
    };
    // GOTO表，定义每个状态和每个非终结符的转移
    map<pair<int, int>, int> gotoTable={
        {{0,E},1},  {{0,T},2},  {{0,F},3},
        {{4,E},8},  {{4,T},2},  {{4,F},3},
        {{6,T},9},  {{6,F},3},
        {{7,F},10},
    };
    queue<Type> tokens;// 存储输入的Token队列
    stack<int> stateStack;// 状态栈
    stack<int> symbolStack;// 符号栈
    // 执行归约操作，移除符号栈中的元素
    void reduce(int num){
        for(int i = 0; i<num ;i++)  symbolStack.pop();
        return ;
    }
    // 执行状态归约，移除状态栈中的元素
    void reduceStates(int num){
        for(int i = 0; i<num ;i++)  stateStack.pop();
        return ;
    }
};

// 主函数
int main() 
{
    string lexerIn="id*id+id";
    string readIn;
    Lexer lexer(lexerIn);  // 创建Lexer实例
    auto tokens = lexer.getTokens();  // 获取tokens
    LRParser parser(tokens);  // 创建LRParser实例
    parser.parse();  // 开始解析
}

