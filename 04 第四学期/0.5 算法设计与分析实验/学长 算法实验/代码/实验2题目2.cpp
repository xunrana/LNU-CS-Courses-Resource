#include <iostream>

using namespace std;

void solve(double income[4][8]) {
    double dp[4][8];   // dp[i][j]表示前i个项目，投资j万元时的最大收益
    double s[4][8] = { 0 };  // sum[i][j]表示前i个项目，投资j万元时，对第i个项目的投资，用于追溯解路径 
    
    // 边界处理：没有项目时，或者投资额度为0时，最大收益都为0
    for (int i = 0; i <= 3; i++)
        dp[i][0] = 0;
    for (int j = 0; j <= 7; j++)
        dp[0][j] = 0;
    // 状态转移方程（不投、投1...投j万元）：dp[i][j] = max(dp[i - 1][j - k] + income[i][k]) (0 <= k <= j)
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 7; j++) {
            double max = 0;
            for (int k = 0; k <= j; k++) {
                if (dp[i - 1][j - k] + income[i][k] > max) {
                    max = dp[i - 1][j - k] + income[i][k];
                    s[i][j] = k;
                }
            }
            dp[i][j] = max;
        }
    }
    // 输出一下dp数组，竖着输出
    cout << "\t";
    for (int i = 0; i <= 3; i++) {
        cout << "i=" << i << "\t";
    }
    for (int j = 0; j <= 7; j++) {
        cout << endl << "j=" << j << "\t";
        for (int i = 0; i <= 3; i++) {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }

    // 追溯解路径
    int i = 3, j = 7;
    while (i > 0) {
        cout << "第" << i << "个项目投资" << s[i][j] << "万元" << endl;
        j -= s[i][j];
        i--;
    }
}

int main() {
    double income[4][8] = {
        {},
        {0, 0.11, 0.13, 0.15, 0.21, 0.24, 0.30, 0.35},
        {0, 0.12, 0.16, 0.21, 0.23, 0.25, 0.24, 0.34},
        {0, 0.08, 0.12, 0.[[姓名已脱敏]已脱敏], 0.24, 0.26, 0.30, 0.35}
    };  //  income[i][j]表示第i个项目，投资j万元时的收益
    solve(income);
}