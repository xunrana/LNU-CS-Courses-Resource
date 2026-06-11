#include <bits/stdc++.h>
using namespace std;
#define N 100010// 定义常量 N，表示数组的最大大小
struct node// 定义活动的结构体
{
	int s,e;// 活动的开始时间和结束时间
}p[N];// 定义结构体数组 p，存储每个活动的信息
int ans=1e9,vt[N];
bool cmp(node p1,node p2)// 活动比较函数，用于排序
{
	if(p1.e==p2.e) return p1.s<p2.s;// 如果结束时间相同，则按照开始时间升序排列,便于尽早安排会场 
	return p1.e<p2.e;// 按照结束时间升序排列
}
int n; // 活动的数量
void dfs(int i,int res)
{
	if(i>n) // 如果已经处理完所有活动
	{
		ans=min(ans,res);// 更新最小会场数量
		return ;
	}
	
	for(int j=1;j<i;j++) 
	if(vt[j]&&vt[j]<=p[i].s) // 如果第 j 个会场可以安排当前活动
	{
		int t=vt[i]; // 保存原来的会场结束时间
		vt[i]=p[i].e;// 更新会场 j 的结束时间为当前活动的结束时间
		dfs(i+1,res);// 递归处理下一个活动
		vt[i]=t; // 恢复会场 j 的结束时间
	}
	
	vt[i]=p[i].e;// 新开一个会场，安排当前活动
	dfs(i+1,res+1);// 递归处理下一个活动
}
int main()
{
	/*
	10
	1 4
	3 5
	0 6
	5 7
	3 8
	5 9
	6 10
	8 11
	8 12
	2 13
	*/ 
	cin>>n;// 输入活动的数量
	for(int i=1;i<=n;i++) cin>>p[i].s>>p[i].e;// 循环读入每个活动的开始时间和结束时间
	sort(p+1,p+1+n,cmp); // 对活动数组 p 按照结束时间进行排序，使用自定义的比较函数 cmp
	
	vt[1]=p[1].e; // 第一个活动安排第一个会场
	dfs(2,1);// 从第二个活动开始调用深度优先搜索函数，当前已使用一个会场
	cout<<ans<<"\n";
}
