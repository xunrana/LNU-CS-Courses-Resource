#include <iostream>

using namespace std;
// 给定若干个正整数a0,a2,……,an-1，从中选择若干个数，使它们的和正好等于k。
#define N 10
int a[N] = { 1,2,3,4,5,6,7,8,9,10 };
int k = 10;
int x[N] = { 0 };   // 用于记录是否被选中
int sum = 0;        // 用于记录当前选中的数的和
int count = 0;      // 用于记录当前选中的数的个数

void dfs(int i) {
    // 决策第i个数是否选中
    if (i >= N) return;
    if (sum == k) {
        count++;
        int j;
        for (j = 0; j < N; j++) {
            if (x[j] == 1) {
                cout << a[j];
                break;
            }
        }
        for (j = j + 1; j < N; j++) {
            if (x[j] == 1) cout << " + " << a[j];
        }
        cout << " = " << k << endl;
        return;
    }
    // 选中第i个数
    x[i] = 1;
    sum += a[i];
    dfs(i + 1);
    // 不选中第i个数
    x[i] = 0;
    sum -= a[i];
    dfs(i + 1);
}

int main() {
    dfs(0);
    cout << "共有" << count << "种方案" << endl;
    return 0;
}