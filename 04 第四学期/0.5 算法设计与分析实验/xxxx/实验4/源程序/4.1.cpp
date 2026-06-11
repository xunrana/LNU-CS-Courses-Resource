#include <bits/stdc++.h>
using namespace std;
map<pair<int,int>,int>dis; // 用于存储节点之间的距离
vector<int>path,ans_path;// 当前路径
vector<int>vt(4,0);// 用于标记节点是否已访问
int res=1e9;// 存储结果，初始为一个很大的数 
void dfs()// 深度优先搜索函数
{
	if(path.size()==4)// 如果当前路径包含4个节点
	{
		int sum=0;// 计算路径距离和
		sum+=dis[{path[path.size()-1],path[0]}]; // 添加最后一个节点到第一个节点的距离
		for(int i=0;i<path.size()-1;i++) sum+=dis[{path[i],path[i+1]}];// 添加相邻节点之间的距离
		if(sum<res) res=sum,ans_path=path;// 更新最小距离和和最佳路径
	}
	
	for(int i=0;i<=3;i++) // 遍历所有节点
	{
		if(!vt[i]) // 如果节点未访问
		{
			vt[i]=1;// 标记节点已访问
			path.push_back(i);// 将节点添加到当前路径
			dfs();// 递归调用
			vt[i]=0;// 恢复节点未访问状态
			path.pop_back(); // 从当前路径中移除节点
		}
	}
}
int main()
{
	 // 初始化节点之间的距离
	dis[{0,1}]=8;
	dis[{1,0}]=6;
	dis[{0,2}]=5;
	dis[{2,0}]=8;
	dis[{0,3}]=36;
	dis[{3,0}]=7;
	dis[{1,2}]=8;
	dis[{2,1}]=9;
	dis[{1,3}]=5;
	dis[{3,1}]=7;
	dis[{2,3}]=5;
	dis[{3,2}]=8;
	dfs();// 调用深度优先搜索函数
	cout<<"最短路径为："<<res<<"\n";
	cout<<"最佳路径：\n";
	for(auto i:ans_path) cout<<i<<" ";
	cout<<"\n"; 
}
