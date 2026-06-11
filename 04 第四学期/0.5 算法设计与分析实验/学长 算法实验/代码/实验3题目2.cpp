#include <iostream>
#include <algorithm>

using namespace std;

void solve(int n, int w[], int C) {
    // n个人，第i个人的体重为w[i]，船的最大载重量为C
    sort(w + 1, w + n + 1); // 从小到大排序
    int i = 1, j = n;       // i指向最轻的人，j指向最重的人
    int count = 0;          // 船的数量
    while (i <= j) {
        if (w[i] + w[j] <= C) {
            // 最轻的人和最重的人可以坐在一艘船上
            cout << "第" << ++count << "艘船：" << w[i] << " " << w[j] << endl;
            i++;
            j--;
        }
        else {
            // 最重的人只能单独坐一艘船
            cout << "第" << ++count << "艘船：" << w[j] << endl;
            j--;
        }
    }
    cout << "最少的船的数量为：" << count << endl;
}

int main() {
    // 求解乘船问题。有n个人，第i个人的体重为wi。每艘船的最大载重量均为C，且最多能乘坐2人。试用最少的船装载所有人。
    int n = 11;
    int w[12] = { 0, 150, 176, 183, 138, 160, 170, 180, 165, 185, 190, [[姓名已脱敏]已脱敏]0 };  // 人的体重
    int C = 340;        // 船的最大载重量
    solve(n, w, C);
}