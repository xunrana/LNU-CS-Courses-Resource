#include <iostream>

using namespace std;

void solve(int N, int C, int p[], int v[]) {
    // N件物品，背包容量为C，第i件物品的重量为p[i]，价值为v[i]
    int dp[N + 1][C + 1];   // dp[i][j]表示前i种菜，报销额度为j时的最大评分
    int s[N + 1][C + 1];    // s[i][j]表示前i种菜，报销额度为j时，是否点了第i种菜
    // 边界处理：没有菜时，或者报销额度为0时，最大评分都为0
    for (int i = 0; i <= N; i++)
        dp[i][0] = 0;
    for (int j = 0; j <= C; j++)
        dp[0][j] = 0;
    // 状态转移方程：dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - p[i]] + v[i])
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= C; j++) {
            if (j < p[i]) {
                // 报销额度不够，只能不点这道菜
                dp[i][j] = dp[i - 1][j];
                s[i][j] = 0;
            }
            else {
                if(dp[i - 1][j] > dp[i - 1][j - p[i]] + v[i]) {
                    // 不点这道菜
                    dp[i][j] = dp[i - 1][j];
                    s[i][j] = 0;
                }
                else {
                    // 点这道菜
                    dp[i][j] = dp[i - 1][j - p[i]] + v[i];
                    s[i][j] = 1;
                }
            }
        }
    }
    // // 输出一下dp数组，竖着输出
    // cout << "\t";
    // for (int i = 0; i <= N; i++) {
    //     cout << "i=" << i << "\t";
    // }
    // for (int j = 0; j <= C; j++) {
    //     cout << endl << "j=" << j << "\t";
    //     for (int i = 0; i <= N; i++) {
    //         cout << dp[i][j] << "\t";
    //     }
    //     cout << endl;
    // }
    // 追溯解路径，从dp[N][C]开始
    int i = N, j = C;
    int sum = 0;
    while (i > 0 && j > 0) {
        if (s[i][j] == 1) {
            cout << "第" << i << "道菜、";
            sum += p[i];
            j -= p[i];
        }
        i--;
    }
    cout << endl << "总共花了" << sum << "元" << endl;
    cout << "总共得了" << dp[N][C] << "分" << endl;
}

int main() {
    // 某实验室经常有活动需要叫外卖，但是每次叫外卖报销的经费总额最大为C元，有N种菜可以点，经过长时间的点菜，实验室对每种菜i都有一个量化的评分Vi，这种菜的价格为Pi，问如何选择各种菜（每种菜只能点一次），才能在报销额度范围内使点到菜的总评价分数最高。
    int N = 10, C = [[姓名已脱敏]已脱敏];    // 10种菜，[[姓名已脱敏]已脱敏]元
    int p[11] = { 0, 8, 2, 5, 8, 10, 9, 10, 7, 2, 6 };  // 价格
    int v[11] = { 0, 10, 3, 4, 1, 2, 7, 2, 4, 8, 6 };   // 评分
    solve(N, C, p, v);
}