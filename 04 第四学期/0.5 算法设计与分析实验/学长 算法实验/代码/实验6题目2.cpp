#include<iostream>
#include<queue>
using namespace std;
const int N = 7, M = 7;//地图大小
int dx[4] = { 0,0,-1,1 };//上下左右四个方向
int dy[4] = { -1,1,0,0 };
int map[N][M] = {
    { 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0 },
    { 1, 0, 0, 0, 1, 0, 0 },
    { 1, 1, 1, 0, 0, 0, 0 },
    { 1, 1, 1, 0, 0, 0, 0 },
};
bool visit[N][M];//标记是否被走过
struct Node {//状态结构体
    int x, y;
    int dis;//起点到当前状态需要的步数
    int h;//当前状态到目标状态的估价函数值（曼哈顿距离）
    bool operator<(const Node& t)const {//重载小于号，用于排序
        return dis + h > t.dis + t.h;
    }
};
int h(int x1, int y1, int x2, int y2) {//曼哈顿距离
    return abs(x1 - x2) + abs(y1 - y2);
}
bool check(int x, int y) {//检查当前状态是否越界或被封锁
    if (x >= 0 && x < N && y >= 0 && y < M && map[x][y] == 0 && !visit[x][y]) return true;
    return false;
}
void bfs(int sx, int sy, int ex, int ey) {
    priority_queue<Node> q;
    q.push({ sx,sy,0,h(sx,sy,ex,ey) });//将起点加入队列
    while (!q.empty()) {
        auto t = q.top();
        q.pop();
        if (t.x == ex && t.y == ey) {//当前状态为目标状态
            cout << "最短布线为：" << t.dis << endl;
            return;
        }
        visit[t.x][t.y] = true;//标记当前状态已走过
        for (int i = 0;i < 4;i++) {//拓展当前状态的所有合法后继状态
            int x = t.x + dx[i], y = t.y + dy[i];
            if (check(x, y)) q.push({ x,y,t.dis + 1,h(x,y,ex,ey) });
        }
    }
    cout << "无可行解" << endl;//经搜索无法到达终点
}
int main() {
    bfs(2, 1, 3, 5);//起点为（2，1），终点为（3，5）
    return 0;
}