#include <bits/stdc++.h>// 引入所有标准C++库
using namespace std;
int n,fa,index,a[100010],ans;// 声明必要的变量
vector<int>g[100010];// 声明一个用于邻接表的向量数组
void dfs(int u,int fa,int sum)// 深度优先搜索(DFS)函数
{
	if(g[u].size()==1) ans=max(ans,sum);// 如果是叶子节点，更新答案
	for(auto v:g[u])// 遍历当前节点u的所有邻接节点v
	{
		if(v==fa) continue;// 跳过父节点
		dfs(v,u,sum+a[v]);// 递归调用子节点
	}
}
int main()
{
/*
第一行输入结点个数n
第二行输入n个数的a1，a2，a3，......an，ai代表结点i的节点值 
第三行输入n个数的b1，b2，b3，......bn，结点i的父亲为bi，保证b1=0，表示结点1的没有父亲 
6
5 2 4 3 1 6
0 1 1 2 3 3
*/
	cin>>n;// 输入节点个数n
	for(int i=1;i<=n;i++) cin>>a[i];// 输入每个节点的值
	for(int i=1;i<=n;i++)
	{
		cin>>fa;// 输入每个节点的父节点
		if(fa==0)
		{
			index=i;// 根节点的父节点为0，记录根节点
			continue;
		}
		g[i].push_back(fa); // 添加边到邻接表
		g[fa].push_back(i);// 添加边到邻接表
	}
	dfs(index,0,a[index]);// 从根节点开始进行DFS
	cout<<ans<<"\n";// 输出答案
} 
