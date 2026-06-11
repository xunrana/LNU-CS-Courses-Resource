#include <iostream>
#include <string>

using namespace std;
typedef struct {
    unsigned int weight;
    unsigned int parent, lchild, rchild;
} HTNode, * HuffmanTree;        // 动态分配数组存储赫夫曼树
typedef string* HuffmanCode;    // 动态分配数组存储赫夫曼编码表

string to_string_my(int n) {
    string s;
    while (n) {
        s = (char)(n % 10 + '0') + s;
        n /= 10;
    }
    return s;
}

void readFile(string& str, string filename) { // 根据文件名，读取文件内容，以 str 返回
    FILE* fp = fopen(filename.c_str(), "r");
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        str += ch;
    }
    fclose(fp);
}
void writeFile(string str, string filename) { // 根据文件名，将 str 写入文件
    FILE* fp = fopen(filename.c_str(), "w");
    for (int i = 0; i < str.length(); i++) {
        fputc(str[i], fp);
    }
    fclose(fp);
}
void countWeight(string str, int*& weight, char*& ch, int& n) { // 统计字符出现次数
    int* w = new int[256]();
    for (int i = 0; i < str.length(); i++)
        w[str[i]]++;
    // 新整理一个数组，只存放出现过的字符
    n = 0;
    for (int i = 0; i < 256; i++)
        if (w[i] != 0) n++;
    weight = new int[n];
    ch = new char[n];
    int j = 0;
    for (int i = 0; i < 256; i++)
        if (w[i] != 0) {
            weight[j] = w[i];
            ch[j++] = i;
        }
}
void HuffmanGenerate(HuffmanTree& HT, int* weight, int n) { // 构造赫夫曼树 HT
    if (n <= 1) return;
    int m = 2 * n - 1;              // 赫夫曼树总结点数
    HT = new HTNode[m + 1];         // 0号单元未用
    for (int i = 1; i <= m; i++) {  // 初始化
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for (int i = 1; i <= n; i++)    // 建立n个叶子结点
        HT[i].weight = weight[i - 1];
    for (int i = n + 1; i <= m; i++) { // 建立n-1个非叶子结点
        int min1 = 0, min2 = 0;
        for (int j = 1; j <= i - 1; j++) { // 在HT[1..i-1]中选择parent为0且weight最小的两个结点，其序号分别为min1和min2
            if (HT[j].parent == 0) {
                if (min1 == 0) min1 = j;
                else if (min2 == 0) min2 = j;
                else if (HT[j].weight < HT[min1].weight) min1 = j;
                else if (HT[j].weight < HT[min2].weight) min2 = j;
            }
        }
        HT[min1].parent = i;
        HT[min2].parent = i;
        HT[i].lchild = min1;
        HT[i].rchild = min2;
        HT[i].weight = HT[min1].weight + HT[min2].weight;
    }
}
void HuffmanCoding(HuffmanCode& HC, HuffmanTree HT, int n) { // 从赫夫曼树 HT 中得到赫夫曼编码 HC
    HC = new string[n + 1];
    for (int i = 1; i <= n; i++) { // 逐个字符求赫夫曼编码
        HC[i] = "";
        int c = i, f = HT[i].parent;
        while (f != 0) { // 从叶子到根逆向求编码
            if (HT[f].lchild == c) HC[i] = '0' + HC[i];
            else HC[i] = '1' + HC[i];
            c = f;
            f = HT[f].parent;
        }
    }
}
void HuffmanDecode(string code, string& result, HuffmanTree HT, char* ch, int n) { // 解码
    int m = 2 * n - 1;
    int p = m;
    for (int i = 0; i < code.length(); i++) {
        if (code[i] == '0') p = HT[p].lchild;
        else p = HT[p].rchild;
        if (HT[p].lchild == 0 && HT[p].rchild == 0) {
            result += string(1, ch[p - 1]);
            p = m;
        }
    }
}

void printHuffmanTree(HuffmanTree HT, int n) {
    int m = 2 * n - 1;
    for (int i = 1; i <= m; i++) {
        cout << "结点 " << i << "：\t";
        cout << "w " << HT[i].weight << "\t";
        cout << "p " << HT[i].parent << "\t";
        cout << "l " << HT[i].lchild << "\t";
        cout << "r " << HT[i].rchild << endl;
    }
}

int calcWPL(HuffmanTree HT, int n) { // 计算WPL
    // 遍历数组，如果是 l 或 r 等于 0，就是叶子结点，计算 WPL，输出计算过程
    int m = 2 * n - 1;
    int wpl = 0;
    for (int i = 1; i <= m; i++) {
        if (HT[i].lchild == 0 && HT[i].rchild == 0) {
            int p = HT[i].parent;
            int w = 0;
            int x = 0;
            while (p != 0) {
                w += HT[i].weight;
                p = HT[p].parent;
                x ++;
            }
            wpl += w;
            cout << HT[i].weight << " * " << x << " = " << w << endl;
        }
    }
    return wpl;
}

int main() {
    if (fopen("D:/原始数据.txt", "r") == NULL)
        writeFile("There is no royal road to science, and only those who do not dread the fatiguing climb of gaining its numinous summits.",
            "D:/原始数据.txt");
    string str = "";                // 原始字符串
    int* weight = NULL;             // 存储n个字符的权值(均>0)
    char* ch = NULL;                // 存储字符
    int n = 0;                      // 叶子结点个数

    readFile(str, "D:/原始数据.txt");       // 读取文件内容
    countWeight(str, weight, ch, n);    // 统计字符出现次数

    HuffmanTree HT = NULL;              // 赫夫曼树
    HuffmanGenerate(HT, weight, n);     // 构造赫夫曼树 HT
    string str_tree = to_string_my(2 * n - 1); // 数据第一行为赫夫曼树结点个数
    // 将赫夫曼树写入 HuffmanTree.dat 文件
    for (int i = 1; i <= 2 * n - 1; i++)
        str_tree += "\n" + to_string_my(HT[i].weight) + " " + to_string_my(HT[i].parent)
        + " " + to_string_my(HT[i].lchild) + " " + to_string_my(HT[i].rchild);
    writeFile(str_tree, "D:/HuffmanTree.dat");

    HuffmanCode HC = NULL;              // 赫夫曼编码表
    HuffmanCoding(HC, HT, n);           // 从赫夫曼树 HT 中得到赫夫曼编码 HC
    string str_code = to_string_my(n);     // 数据第一行为字符个数
    // 将赫夫曼编码写入 HuffmanCode.txt 文件
    for (int i = 1; i <= n; i++)
        // 将 ch[i-1] 转换为字符串
        str_code += "\n" + string(1, ch[i - 1]) + " " + HC[i];
    writeFile(str_code, "D:/HuffmanCode.txt");

    // 将原始字符串编码写入 CodeFile.dat 文件
    string str_codeFile = "";
    for (int i = 0; i < str.length(); i++)
        for (int j = 1; j <= n; j++)
            if (str[i] == ch[j - 1]) {
                str_codeFile += HC[j];
                break;
            }
    writeFile(str_codeFile, "D:/CodeFile.dat");

    // 将编码后的字符串解码输出
    string str_decode = "";
    HuffmanDecode(str_codeFile, str_decode, HT, ch, n);
    cout << str_decode << endl;

    // 用括号表示法输出赫夫曼树
    cout << "Huffman Tree:" << endl;
    printHuffmanTree(HT, n);
    cout << calcWPL(HT, n) << endl;

    return 0;
}