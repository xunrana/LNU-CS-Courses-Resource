#include <iostream>

using namespace std;
#define N 4

char g[N][N];   // 用来存路径
bool col[N]; // 列，用来判断下一个位置是否可以放置皇后
bool dg[N * 2], udg[N * 2];  // 主对角线，副对角线

void dfs(int u) {
    // u 表示当前行-1
    if (u == N) {
        // 已经决策完毕
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << g[i][j] << " ";
            cout << endl;
        }
        cout << "-----------------\n";
        return;
    }
    // 枚举第u行的所有列，判断是否可以放置皇后
    for (int i = 0; i < N; i++) {
        // 不满足约束条件的，不再继续
        if (!col[i] && !dg[u - i + N] && !udg[u + i]) {
            // 即同一主对角线上的点，行-列的值相等，同一副对角线上的点，行+列的值相等
            g[u][i] = 'Q';
            col[i] = dg[u - i + N] = udg[u + i] = true;
            dfs(u + 1);
            // 回溯
            col[i] = dg[u - i + N] = udg[u + i] = false;
            g[u][i] = '.';
        }
    }
}

void queen_solve() {
    // 使用回溯法求解N皇后问题
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            g[i][j] = '.';
    dfs(0);
}

int main() {
    queen_solve();
    return 0;
}