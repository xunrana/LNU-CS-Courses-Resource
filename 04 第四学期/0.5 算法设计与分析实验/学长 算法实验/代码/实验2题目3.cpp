#include <iostream>

using namespace std;

struct Meeting {
    int start;      // 开始时间
    int end;        // 结束时间
    int duration;   // 持续时间
};


void solve(struct Meeting meetings[]) {
    // 每个会议有两种选择：开或者不开
    int dp[12][25];     // 前i个会议，会议室使用时间为0~j时的最大持续时间
    int s[12][25] = { 0 };  // sum[i][j]表示前i个会议，会议室使用时间为j时，对第i个会议的选择，0不开，1开
    // 边界处理：没有会议时，或者会议室使用时间为0时，最大持续时间都为0
    for (int i = 0; i < 12; i++)
        dp[i][0] = 0;
    for (int j = 0; j < 25; j++)
        dp[0][j] = 0;
    // 状态转移方程：dp[i][j] = max(dp[i - 1][j], dp[i - 1][meetings[i].start] + meetings[i].duration)
    for (int i = 1; i < 12; i++) {
        for (int j = 1; j < 25; j++) {
            if (j < meetings[i].end)
                dp[i][j] = dp[i - 1][j];
            else {
                if (dp[i - 1][j] > dp[i - 1][meetings[i].start] + meetings[i].duration) {
                    dp[i][j] = dp[i - 1][j];
                    s[i][j] = 0;
                } else {
                    dp[i][j] = dp[i - 1][meetings[i].start] + meetings[i].duration;
                    s[i][j] = 1;
                }
            }
        }
    }

    // 追溯解路径
    int i = 11, j = 24;
    while (i > 0) {
        if (s[i][j] == 1) {
            cout << "第" << i << "个会议开" << endl;
            j = meetings[i].start;
            cout << "会议室使用时间：" << j << "~" << meetings[i].end << endl;
        }
        i--;
    }
}

int main() {
    // 只有一个会议室，下面是11个会议的开始时间和结束时间，求会议室使用时间最长的方案
    struct Meeting meetings[12] = { {0, 0, 0},
        {1, 4, 3}, {3, 5, 2}, {0, 6, 6}, {5, 7, 2}, {3, 8, 5}, {5, 9, 4},
        {6, 10, 4}, {8, 11, 3}, {8, 12, 4}, {2, 13, 11}, {12, 15, 3}
    };
    solve(meetings);
}