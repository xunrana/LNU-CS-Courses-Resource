#include <bits/stdc++.h>
using namespace std;
class Node // 定义节点类
{
    public:
    int totalWeight;// 当前节点的总重量
    int totalItems;// 当前节点包含的物品数量
    int level;// 当前处理到的物品索引
    vector<int> path;// 当前节点的路径（装载方案）
    Node(int totalWeight, int totalItems, int level, vector<int> path)// 构造函数
        : totalWeight(totalWeight), totalItems(totalItems), level(level), path(path) {}
    // 优先队列需要根据 totalWeight 进行比较，另外在同等重量时比较 totalItems
    bool operator<(const Node& other) const // 重载 < 运算符，用于在优先队列中比较节点
	{
        if(totalWeight==other.totalWeight) return totalItems>other.totalItems; // 较少的物品数量优先
        return totalWeight<other.totalWeight; // 较大的重量优先
    }
};

// 优先队列式分枝限界法求解最优装载问题
pair<int, vector<int>> knapsackBranchBound(const vector<int>& weights, int W) 
{
    priority_queue<Node> pq;// 定义优先队列
    pq.push(Node(0, 0, 0, vector<int>(weights.size(), 0)));// 初始化根节点并压入队列
  
    vector<int> bestPath(weights.size(), 0);// 用于记录最佳路径的向量
    int bestWeight = 0;// 记录最佳总重量
    int minItems = INT_MAX;// 记录最佳方案中的最小物品数量

    while(!pq.empty()) // 优先队列不为空时循环
	{
        Node current=pq.top();// 取出优先队列顶部的节点
        pq.pop();// 移除顶部节点
        if(current.level==weights.size()) // 如果所有物品都处理完毕，检查是否是最佳方案
		{
            if(current.totalWeight>bestWeight||(current.totalWeight==bestWeight&&current.totalItems<minItems)) 
			{
                bestWeight=current.totalWeight;// 更新最佳重量
                minItems=current.totalItems;// 更新最少物品数量
                bestPath=current.path;// 更新最佳路径
            }
            continue;// 继续处理其他节点
        }
        // 不装载当前物品，生成子节点并压入队列
        pq.push(Node(current.totalWeight,current.totalItems,current.level+1,current.path));
        // 装载当前物品，生成子节点并压入队列
		int nextWeight=current.totalWeight+weights[current.level];// 计算新的总重量
        if (nextWeight<=W) // 如果新的总重量不超过限重
		{
            vector<int> nextPath=current.path;// 复制当前路径
            nextPath[current.level]=1;// 标记当前物品被装载
            pq.push(Node(nextWeight,current.totalItems+1,current.level+1,nextPath));// 压入新节点
        }
    }
    return {bestWeight, bestPath}; // 返回最佳重量和最佳路径
}

int main() 
{
    vector<int>weights={5,2,6,4,3}; // 定义物品重量
    int W=10;// 定义最大承重
    pair<int,vector<int>> result=knapsackBranchBound(weights,W); // 调用算法获取结果
    int bestWeight=result.first;// 获取最佳总重量
    vector<int>bestPath=result.second;// 获取最佳路径
    cout<<"最优装载总重量: "<<bestWeight<<"\n";// 输出最佳总重量
    cout<<"答案解向量: ";
    for(int i=0;i<bestPath.size();++i) cout<<bestPath[i]<<" ";// 输出最佳路径向量
    cout<<"\n";
    cout<<"选中的集装箱索引: ";
    for(int i=0;i<bestPath.size();++i) if(bestPath[i]==1) cout<<i<<" ";// 输出被选中的物品索引
    cout<<"\n";
    return 0;
}

