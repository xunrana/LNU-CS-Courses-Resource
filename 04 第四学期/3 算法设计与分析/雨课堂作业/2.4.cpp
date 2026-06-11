#include <bits/stdc++.h>
using namespace std;
int n,m,k,x,y;// 定义网格的行数n、列数m、硬币数k及坐标x、y
int a[10][10],dp[10][10];// a数组表示硬币位置，dp数组用于动态规划计算
vector<pair<int,int> >p[10][10];// 用于记录路径
int main()
{
	cin>>n>>m>>k; // 输入网格大小和硬币数
	while(k--) // 输入硬币的坐标，并标记在数组a中
	{
		cin>>x>>y;
		a[x][y]=1;
	}
	for(int i=2;i<=n;i++) p[i][1].push_back({1,1});// 初始化第0列的路径，表示从第1行开始，没有从上方来的路径
	for(int i=2;i<=m;i++) p[1][i].push_back({1,1});// 初始化第0行的路径，表示从第1列开始，没有从左方来的路径
	
	for(int i=2;i<=n;i++)// 遍历网格，计算每个格子能收集到的最大硬币数并记录路径
	for(int j=2;j<=m;j++)
	{
		if(dp[i-1][j]>dp[i][j-1])// 如果上方的dp值大于左方的dp值
		{
			p[i][j]=p[i-1][j];// 路径继承自上方
			p[i][j].push_back({i,j});// 添加当前格子到路径中
		}
		else
		{
			p[i][j]=p[i][j-1];// 路径继承自左方
			p[i][j].push_back({i,j});// 添加当前格子到路径中
		}
		dp[i][j]=max(dp[i-1][j],dp[i][j-1])+a[i][j];// 计算当前格子的dp值，取上方和左方的最大值加上当前格子的硬币值
	}
	cout<<"最大硬币数："<<dp[n][m]<<"\n";// 输出从左上角到右下角能收集的最大硬币数
	cout<<"路径：\n"; 
	for(auto i:p[n][m]) cout<<i.first<<" "<<i.second<<"\n";// 输出路径

} 

/*
5 6 9
1 5
2 2
2 4
3 4
3 6
4 3 
4 6
5 1
5 5
*/
