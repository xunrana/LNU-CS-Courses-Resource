#include <iostream>
#include <queue> // 引入优先队列

using namespace std;

#define MAXN 105
int w[MAXN] = {5, 2, 6, 4, 3}; // 集装箱重量
int n = 5, W = 10; // 集装箱数量和限重

// 定义状态类
class State {
public:
    int cur; // 当前集装箱编号
    int sum; // 当前装载重量
    int cnt; // 当前已经装载的集装箱个数
    State(int c = 0, int s = 0, int t = 0) : cur(c), sum(s), cnt(t) {} // 构造函数
    bool operator<(const State &other) const { // 重载 < 运算符
        return cnt > other.cnt; // 用于优先队列的排序
    }
};

int ans = 0;

void bfs() {
    priority_queue<State> q; // 定义优先队列

    // 将起点加入优先队列
    q.push(State(0, 0, 0));

    while (!q.empty()) {
        State curState = q.top(); // 取出队首状态
        q.pop(); // 弹出队首状态

        // 如果已经装满且当前方案比之前的更优，则更新答案
        if (curState.sum == W && (ans == 0 || curState.cnt < ans)) {
            ans = curState.cnt;
        }

        // 如果当前方案已经不可能是最优方案，则剪枝
        if (ans != 0 && curState.cnt >= ans) {
            continue;
        }

        // 扩展当前状态的子状态
        if (curState.cur < n) {
            // 不选当前集装箱
            q.push(State(curState.cur + 1, curState.sum, curState.cnt));
            // 选当前集装箱
            if (curState.sum + w[curState.cur] <= W) { // 如果能装下当前集装箱
                q.push(State(curState.cur + 1, curState.sum + w[curState.cur], curState.cnt + 1));
            }
        }
    }
}

int main() {
    bfs();
    cout << "最少装载集装箱数为：" << ans << endl;
    return 0;
}