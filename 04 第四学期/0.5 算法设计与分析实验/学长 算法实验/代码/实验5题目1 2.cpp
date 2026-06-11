#include <iostream>

using namespace std;
// 采用递归回溯法设计一个算法，求从1~n的n个整数中取出m个元素的排列，要求每个数据元素只能取一次。例如：n=3、m=2的输出结果是（1,2）（1,3）（2,1）（2,3）（3,1）（3,2）
#define N 4
#define M 3
int a[N];

void dfs(int cur) {
    // cur表示当前已经决策好了前cur个元素
    if (cur == M) {
        // 已经决策好了前M个元素
        for (int i = 0; i < M; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
        return;
    }
    for (int i = cur; i < N; i++) {
        swap(a[cur], a[i]);
        dfs(cur + 1);
        swap(a[cur], a[i]);
    }
}

int main() {
    for(int i = 0; i < N; i++) a[i] = i + 1;
    dfs(0);
    return 0;
}