#include <iostream>
#include <queue> // 引入优先队列

using namespace std;

#define N 10
int graph[N][N] = {
    {0,   2,   4,   70,  99,  30,  78,  3,   41,  69},
    {14,  0,   22,  29,  47,  27,  56,  6,   79,  46},
    {85,  84,  0,   12,  88,  85,  100, 71,  36,  10},
    {95,  95,  57,  0,   [[姓名已脱敏]已脱敏],  44,  33,  24,  36,  34},
    {90,  16,  99,  71,  0,   5,   62,  80,  13,  48},
    {43,  33,  96,  77,  49,  0,   77,  29,  99,  76},
    {69,  88,  55,  7,   96,  73,  0,   30,  70,  17},
    {44,  10,  77,  4,   85,  81,  11,  0,   45,  59},
    {38,  81,  73,  14,  75,  4,   40,  79,  0,   84},
    {88,  82,  31,  98,  1,   72,  90,  90,  37,  0}
};
int s = 0, t = 9;

// 定义状态类
class State {
public:
    int cur; // 当前节点编号
    int sum; // 当前路径长度
    int cnt; // 经过的路径条数
    State(int c = 0, int s = 0, int t = 0) : cur(c), sum(s), cnt(t) {} // 构造函数
    bool operator<(const State &other) const { // 重载 < 运算符
        return sum > other.sum; // 用于优先队列的排序
    }
};

int path[N];
int cnt = 0;
int minSum = 1000000000;

void bfs() {
    priority_queue<State> q; // 定义优先队列

    // 将起点加入优先队列
    q.push(State(s, 0, 1));

    while (!q.empty()) {
        State curState = q.top(); // 取出队首状态
        q.pop(); // 弹出队首状态

        // 如果当前路径长度已经大于之前的最短路径，剪枝
        if (curState.sum >= minSum) {
            continue;
        }

        path[curState.cnt-1] = curState.cur; // 将当前节点加入路径

        // 如果已经到达终点，更新最短路径长度及经过的路径条数
        if (curState.cur == t) {
            if (curState.sum < minSum) {
                minSum = curState.sum;
                cnt = curState.cnt;
            } else if (curState.sum == minSum) {
                cnt += curState.cnt;
            }
            continue; // 注意要跳过后面的扩展操作
        }

        // 扩展当前状态的子状态
        for (int i = 0; i < N; i++) {
            if (graph[curState.cur][i] != 0) { // 如果当前节点能到达节点 i
                State nextState(i, curState.sum + graph[curState.cur][i], curState.cnt+1); // 构造子状态
                q.push(nextState); // 加入优先队列，自动按照路径长度排序
            }
        }
    }
}

int main() {
    bfs();
    cout << "最短路径长度为：" << minSum << endl;
    cout << "经过的路径条数为：" << cnt << endl;
    cout << "路径为：";
    for (int i = 0; i < cnt; i++) {
        cout << path[i] << " ";
    }
    cout << endl;
    return 0;
}