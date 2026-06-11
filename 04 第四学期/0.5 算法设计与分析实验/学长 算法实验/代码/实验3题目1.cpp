#include <iostream>
#include <algorithm>

using namespace std;

struct Meeting {
    int start;      // 开始时间
    int end;        // 结束时间
    int duration;   // 持续时间
};

void sove(struct Meeting meetings[], int n) {
    bool exist[12] = { false }; // 标记会议是否已经安排
    // 此处使用贪心算法，每次选择结束时间最早的会议
    sort(meetings + 1, meetings + 12, [](Meeting a, Meeting b) {
        return a.end < b.end;
        });
    int count = 0;  // 会场个数
    int end = 0;    // 当前会场的结束时间
    for (int i = 1; i <= 11; i++) {
        if (!exist[i]) {
            count++;
            exist[i] = true;
            end = meetings[i].end;
            cout << endl << "会场" << count << "：会议" << i << " ";
            for (int j = i + 1; j <= 11; j++) {
                if (!exist[j] && meetings[j].start >= end) {
                    exist[j] = true;
                    end = meetings[j].end;  // 更新会场的结束时间
                    cout << "会议" << j << " ";
                }
            }
        }
    }
    cout << endl << "最少的会场个数为：" << count << endl;
}

int main() {
    // 只有一个会议室，下面是11个会议的开始时间和结束时间，求最少的会场个数
    struct Meeting meetings[12] = { {0, 0, 0},
        {1, 4, 3}, {3, 5, 2}, {0, 6, 6}, {5, 7, 2}, {3, 8, 5}, {5, 9, 4},
        {6, 10, 4}, {8, 11, 3}, {8, 12, 4}, {2, 13, 11}, {12, 15, 3}
    };
    sove(meetings, 11);
}