#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;
#define M 4
int a[M][M]{
        {0, 8, 5, 36},
        {6, 0, 8, 5},
        {8, 9, 0, 5},
        {7, 7, 8, 0}
};  // 地图的邻接矩阵

void vio_solve() {
    int min = 1000000;
    int path[M] = {0};
    // 路径 i -> j -> k -> l -> i
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < M; k++) {
                for (int l = 0; l < M; l++) {
                    if(i == j || i == k || i == l || j == k || j == l || k == l) continue; // 保证每个城市只经过一次
                    int sum = a[i][j] + a[j][k] + a[k][l] + a[l][i];
                    if (sum < min) {
                        min = sum;
                        path[0] = i;
                        path[1] = j;
                        path[2] = k;
                        path[3] = l;
                    }
                }
            }
        }
    }
    cout << "暴力法：\n\t最短长度：" << min << endl;
    cout << "\t最短路径：";
    for (int i = 0; i < M; i++) cout << path[i] << " ";
    cout << endl;
}

// 第二种方法：回溯算法
void recall_solve() {
    int min = 1000000;
    int path[M] = {0};
    // 路径 i -> j -> k -> l -> i
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (i == j) continue;   // 不满足约束条件
            for (int k = 0; k < M; k++) {
                if (i == k || j == k) continue; // 不满足约束条件
                for (int l = 0; l < M; l++) {
                    if (i == l || j == l || k == l) continue; // 不满足约束条件
                    int sum = a[i][j] + a[j][k] + a[k][l] + a[l][i];
                    if (sum < min) {
                        min = sum;
                        path[0] = i;
                        path[1] = j;
                        path[2] = k;
                        path[3] = l;
                    }
                }
            }
        }
    }
    cout << "回溯法：\n\t最短长度：" << min << endl;
    cout << "\t最短路径：";
    for (int i = 0; i < M; i++) cout << path[i] << " ";
    cout << endl;
}

void solve() {
    clock_t start, end;
    start = clock();
    vio_solve();
    end = clock();
    cout << "暴力算法耗时：" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    start = clock();
    recall_solve();
    end = clock();
    cout << "回溯算法耗时：" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
}

int main() {
    // 货郎问题：有m个城市，从某个城市出发，要求经过每个城市一次且仅一次，最后回到出发的城市，求最短的路线。
    solve();
}