#include <iostream>
#include <string>

using namespace std;
int main() {
    int count = 7;     // 关键字个数
    int length = 9;    // 哈希表长度
    int s[count] = { 2, 10, 19, 7, 35, 28, 23 };
    // 设散列函数为：h(x) = k mod 9
    // 生成哈希表
    int hash[length] = { 0 };
    for (int i = 0; i < count; i++) {
        // 采用线性探查法解决冲突
        int j = s[i] % length;
        while (hash[j] != 0) {
            j = (j + 1) % length;
        }
        hash[j] = i + 1;
    }
    // 输出哈希表
    for (int i = 0; i < length; i++) {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < length; i++) {
        if (hash[i] != 0)
            cout << s[hash[i]-1] << "\t";
        else
            cout << "   \t";
    }

    // 求出在概率相等的情况下的查找成功的平均查找长度
    double sum = 0;
    for (int i = 0; i < count; i++) {
        int j = s[i] % length;
        int k = 1;
        while (hash[j] != i + 1) {
            j = (j + 1) % length;
            k++;
        }
        sum += k;
        cout << endl << "第" << i + 1 << "个关键字的查找长度为：" << k;
    }
    cout << endl << "平均查找长度为：" << sum << "/" << count << endl;

    // 求出装填因子
    cout << "装填因子为：" << count << "/" << length << endl;
}