#include <bits/stdc++.h>
using namespace std;
#define N 1010
int n,s[N],e[N];// n为会议数量，s存放开始时间，e存放结束时间
int dp[N];//表示考虑前 i 个会议的安排方案的最大兼容时间。
vector<int>ans[N];//考虑前 i 个会议时，达到 dp[i] 所对应的最大兼容时间时，具体选取的会议序列。
int main() 
{
	cin>>n;// 输入会议数量
	for(int i=1;i<=n;i++) cin>>s[i]>>e[i]; // 输入每个会议的开始时间和结束时间
	
	for(int i=1;i<=n;i++)  // 动态规划求解
	{
		dp[i]=dp[i-1];// 初始化为上一个会议的最大兼容时间
		ans[i]=ans[i-1];// 初始化选取会议序列为上一个会议的选取序列
		for(int j=0;j<i;j++) // 遍历之前的每一个会议，寻找可以兼容当前会议的最大兼容时间
		if(s[i]>=e[j])// 当前会议的开始时间必须晚于等于前一个会议的结束时间
		{
			if(dp[j]+e[i]-s[i]>dp[i])
			{
				dp[i]=dp[j]+e[i]-s[i];// 更新最大兼容时间
				ans[i]=ans[j];// 更新选取会议序列
				ans[i].push_back(i);// 将当前会议加入选取序列
			}
		}
	}
	cout<<"最大兼容时间: "<<dp[n]<<"\n";// 更新最大兼容时间
	cout<<"选取的会议为：";
	for(auto i:ans[n]) cout<<i<<" ";
	cout<<"\n";
}
/*
11
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
12 15
*/
