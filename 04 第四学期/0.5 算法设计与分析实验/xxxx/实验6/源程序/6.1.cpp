#include <bits/stdc++.h>
using namespace std;
#define N 100// 假设最多100个顶点
int n; // 顶点个数
int adjMatrix[N][N]; // 邻接矩阵
struct Node // 定义节点结构体，用于优先队列中的元素
{
    int vertex,cost;// 当前节点和从起点到该节点的花费
    vector<int>path;// 从起点到当前节点的路径
    bool operator>(const Node &other) const  // 定义优先队列的比较规则，根据cost排序
	{
        return cost>other.cost;
    }
};
int branchAndBound(int s,int t,vector<vector<int>> &allPaths) // 分枝限界法求最短路径
{
    priority_queue<Node,vector<Node>,greater<Node>>pq;// 使用优先队列实现分枝限界
    vector<int>dist(n,INT_MAX);// 记录从起点到各点的最短距离
    vector<int>pathCount(n,0); // 记录从起点到各点的路径条数
    dist[s]=0;// 起点到起点的距离为0
    pathCount[s]=1;// 起点到起点的路径条数为1
    pq.push({s,0,{s}});// 将起点加入优先队列
    while(!pq.empty())
	{
        Node curr=pq.top();// 取出队列中最小cost的节点
        pq.pop();
        int u=curr.vertex;// 当前节点
        int currentCost=curr.cost;// 当前花费
        if(u==t) // 如果到达目标节点，则记录路径
		{
            allPaths.push_back(curr.path);
            continue;
        }
        if(currentCost>dist[u]) continue;// 如果当前花费大于记录的最短距离，则跳过
        for(int v=0;v<n;++v)// 遍历邻接矩阵中的所有节点
		{
            if(adjMatrix[u][v]!=INT_MAX&&u!=v)  // 如果存在从u到v的边，并且u不等于v
			{
                int newCost=currentCost+adjMatrix[u][v]; // 计算新花费
                if(newCost<dist[v]) // 如果新花费小于记录的到v的最短距离，则更新
				{
                    dist[v]=newCost;// 更新最短距离
                    pathCount[v]=pathCount[u];// 更新路径条数
                    vector<int>newPath=curr.path;// 生成新路径
                    newPath.push_back(v);// 将节点v加入新路径
                    pq.push({v,newCost,newPath});// 将新节点加入队列
                } 
				else if(newCost==dist[v]) // 如果新花费等于记录的最短距离
				{
                    pathCount[v]+=pathCount[u]; // 增加路径条数
                    vector<int>newPath=curr.path;// 生成新路径
                    newPath.push_back(v);// 将节点v加入新路径
                    pq.push({v,newCost,newPath});// 将新节点加入队列
                }
            }
        }
    }
    return dist[t];// 返回起点到目标节点的最短距离
}

int main() 
{
    int s,t;
    cin>>n;// 输入顶点个数
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) cin>>adjMatrix[i][j];// 输入邻接矩阵的值
    cin>>s>>t;// 输入起点和目标点
    vector<vector<int>>allPaths;// 用于存储所有最短路径
    int shortestPathLength=branchAndBound(s,t,allPaths);// 调用分枝限界法计算最短路径长度
    cout<<"从"<<s<<"到"<<t<<"的最短路径长度: "<<shortestPathLength<<"\n";// 输出最短路径长度
    cout<<"最短路径条数: "<<allPaths.size()<<"\n"; // 输出最短路径条数
    cout<<"所有最短路径: \n";
    for(const auto&path:allPaths) // 遍历所有路径
	{
        for(int vertex:path) cout<<vertex<<" ";// 遍历路径中的每个顶点
        cout<<"\n";
    }
    return 0;
}
/*
5
0 10 3 2147483647 2147483647
2147483647 0 1 2 2147483647
2147483647 4 0 8 2
2147483647 2147483647 2147483647 0 7
2147483647 2147483647 2147483647 9 0
0 4
*/

