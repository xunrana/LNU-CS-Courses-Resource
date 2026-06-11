#include <bits/stdc++.h>
using namespace std;
int n,m,d[10],dp[10];
int main()
{
	/*
6 3
1 3 4
	*/
	cin>>n>>m;// 读取找零金额 n 和硬币种类数 m
	for(int i=1;i<=m;i++) cin>>d[i];// 读取每种硬币的面值
	for(int i=1;i<=n;i++)
	{
		dp[i]=i; // 初始化 dp[i] 为 i，因为用 i 个 1 元硬币可以组成金额 i
		for(int j=1;j<=m;j++) if(i>=d[j]) dp[i]=min(dp[i],dp[i-d[j]]+1);// 更新 dp[i] 为使用 d[j] 硬币时的最小硬币数
	}
	for(int i=1;i<=n;i++) cout<<dp[i]<<" ";// 输出从 1 到 n 每个金额的最少硬币数
} 
