#include <bits/stdc++.h>
using namespace std;

// 定义一个字符串数组，存储各类标识符的中文描述
string res[] = 
{
    "Invalid input(无效输入)",  // 错误输入 0
    "Identifier(标识符)",        // 标识符 1
    "Decimal(十进制)",          // 十进制 2
    "Octal(八进制)",            // 八进制 3
    "Hexadecimal(十六进制)",    // 十六进制 4
    "Operator/Separator(运算符和分隔符)", // 运算符和分隔符 5
    "Keyword(关键字)"           // 关键字 6
}; 

// 判断是否是一个有效的标识符，支持后缀如 "_" 或 "."
// 标识符必须以字母开头，后面可以包含字母、数字，并且支持后缀
bool ck1(string s) {
    // 标识符必须以字母开头
    if (!(isupper(s[0]) || islower(s[0]))) return false;
    
    bool hasSuffix = false; // 标识符是否带后缀
    for (int i = 1; i < s.size(); i++) {
        // 后缀字符可以是 "_" 或 "."
        if (s[i] == '_' || s[i] == '.') {
            hasSuffix = true;
        } else if (!(isupper(s[i]) || islower(s[i]) || isdigit(s[i]))) {
            return false; // 后缀后的字符必须是字母或数字
        }
    }

    // 如果有后缀，最后一个字符必须是字母或数字
    if (hasSuffix && !(isupper(s[s.size() - 1]) || islower(s[s.size() - 1]) || isdigit(s[s.size() - 1]))) {
        return false;
    }

    return true;
}

// 判断是否是十进制数
bool ck2(string s) {
    if(s=="0") return true;  // 特殊情况：直接判断 "0" 为有效十进制数
    if(!(s[0]>='1'&&s[0]<='9')) return false;  // 十进制数第一位不能为零，且必须是 1-9 之间的数字
    
    int n = s.size();
    bool point = false;
    
    // 如果数字包含正负号，去除符号部分
    if (s[0] == '+' || s[0] == '-') s = s.substr(1); 
    n = s.size();

    // 遍历字符串，处理小数点和数字部分
    bool hasDigit = false;
    for (int i = 0; i < n; i++) {
        if (s[i] == '.') {
            if (point) return false; // 小数点只能出现一次
            point = true;
        } else if (!(s[i] >= '0' && s[i] <= '9')) {
            return false; // 其他字符必须是数字
        } else {
            hasDigit = true;
        }
    }

    if (!hasDigit) return false; // 必须至少有一个数字

    return true;
}

// 判断是否是八进制数
bool ck3(string s) {
    int n = s.size();
    bool point = false;
    
    // 八进制数必须以 "0" 开头
    if (s[0] != '0') return false;
   
    // 八进制数的第二位必须是 1-7 的数字
    if (!(s[1] >= '1' && s[1] <= '7')) return false;

    // 遍历字符串，处理小数点和数字部分
    for (int i = 0; i < n; i++) {
        if (s[i] == '.') {
            if (point) return false;  // 小数点只能出现一次
            point = true;
        } else if (!(s[i] >= '0' && s[i] <= '7')) {
            return false; // 其他字符必须是 0-7 之间的数字
        }
    }

    return true;
}

// 判断是否是十六进制数
bool ck4(string s) 
{
    int n = s.size();
    bool point = false;

    // 十六进制数必须以 "0x" 开头
    if (s[0] != '0' || s[1] != 'x') return false;

    // "0x" 后必须有至少一个有效的十六进制字符
    if ((s.size() < 3) || !((s[2] >= '1' && s[2] <= '9') || (s[2] >= 'a' && s[2] <= 'f'))) return false;

    s = s.substr(2); // 去掉 "0x" 前缀
    n = s.size();

    // 遍历字符串，处理小数点和数字部分
    for (int i = 0; i < n; i++) {
        if (s[i] == '.') {
            if (point) return false;  // 小数点只能出现一次
            point = true;
        } else if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f'))) {
            return false;  // 只能是十六进制的字符（0-9, a-f）
        }
    }

    return true;
}

// 判断是否是运算符或分隔符
bool ck5(string s) {
    // 判断是否是常见的运算符或分隔符
    if (s == "+" || s == "-" || s == "*" || s == "/" || s == ">" || s == "<" || s == "=" || s == "(" || s == ")" || s == ";") 
        return true;
    return false;
}

// 判断是否是关键字
bool ck6(string s) {
    // 判断是否是预定义的关键字
    if (s == "if" || s == "then" || s == "else" || s == "while" || s == "do") return true;
    return false;
}

// 判断输入字符串的类型并返回对应的编号
int ck(string s) {
    if (ck6(s)) return 6;  // 关键字
    else if (ck1(s)) return 1;  // 标识符
    else if (ck2(s)) return 2;  // 十进制
    else if (ck3(s)) return 3;  // 八进制
    else if (ck4(s)) return 4;  // 十六进制
    else if (ck5(s)) return 5;  // 运算符和分隔符
    else return 0;  // 错误输入
}

// 主函数，处理输入和输出
void solve() {
    while (1) {
        // 提示用户输入一个单词
        cout << "请输入您要查询的单词?(输入-1退出)\n";
        string s;
        cin >> s;
        
        // 如果用户输入 "-1"，则退出程序
        if (s == "-1") break;
        
        // 输出单词的类型和对应的中文描述
        cout << ck(s) << " " << res[ck(s)] << "\n";
    }
}
/*
var_name
12345
075
0xA1B2
+
if
while
else
do
then
-
0x1F
+3.14
-123
3.14
_underscore
example_
.123
0xabc
a1b2c3
null
ifelse
+-
;
-1
*/
int main() {
    int T = 1;
    while (T--) solve();  // 调用 solve 函数进行处理
}

