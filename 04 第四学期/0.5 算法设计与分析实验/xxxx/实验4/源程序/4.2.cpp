#include <bits/stdc++.h>
using namespace std;
const int N=4;// 定义城市数量
int dis[N][N]={
	{0,8,5,36},
    {6,0,8,5},
    {8,9,0,5},
    {7,7,8,0}
}; // 距离矩阵，dis[i][j] 表示城市 i 到城市 j 的距离
int dp[1<<N][N];// 动态规划数组，dp[s][j] 表示当前状态为 s，且以城市 j 结尾的最短路径
vector<int>path[1<<N][N],path_ans;  // 路径数组，用于存储每个状态对应的路径
int main() 
{
	// 初始化动态规划数组，所有状态的初始值设为一个大数（表示无限大）
	for(int s=0;s<(1<<N);s++) for(int j=0;j<N;j++) dp[s][j]=1e9;
	// 初始化起点到其他城市的距离，起点为城市 0
	for(int i=1;i<N;i++) // 从城市 1 到城市 N-1
	{
		dp[(1<<i)+1][i]=dis[0][i];// 设置从城市 0 到城市 i 的初始距离
		path[(1<<i)+1][i].push_back(0);// 路径初始化，添加起点 0
		path[(1<<i)+1][i].push_back(i);// 路径初始化，添加目标城市 i
	}
	// 枚举所有状态 s
	for(int s=0;s<(1<<N);s++)
	{
		if(!(s&1)) continue;// 如果状态 s 中没有包含城市 0，则跳过
		for(int i=1;i<N;i++)
		{
			if(!(s>>i&1)) continue;// 如果状态 s 中没有包含城市 i，则跳过
			for(int k=1;k<N;k++)// 遍历所有城市 i
			{
				if(k==i||!(s>>k&1)) continue; // 如果 k 和 i 相同或者状态 s 中没有包含城市 k，则跳过
				// 以 k 结尾的状态转移到以 i 结尾的状态
				if(dp[s-(1<<i)][k]+dis[k][i]<dp[s][i])// 如果从 k 转移到 i 的新路径更短
				{
					dp[s][i]=dp[s-(1<<i)][k]+dis[k][i];// 更新 dp 数组的最短路径值
					path[s][i]=path[s-(1<<i)][k];// 更新路径
					path[s][i].push_back(i);// 在路径中添加城市 i
				}
			}
		}
	}
	int ans=dp[15][1]+dis[1][0]; // 初始结果设为从状态 15 到城市 1 再回到起点 0 的路径长度
	path_ans=path[15][1];// 初始路径设为从状态 15 到城市 1 的路径
	for(int i=2;i<N;i++) // 遍历所有以 i 结束的状态
	if(dp[15][i]+dis[i][0]<ans) // 如果新的路径更短
	{
		ans=dp[15][i]+dis[i][0]; // 更新最短路径长度
		path_ans=path[15][i];// 更新最短路径
	}
	cout<<ans<<"\n";// 输出最终结果
	for(auto i:path_ans) cout<<i<<" ";// 输出最短路径的每个城市
	cout<<"\n";
}

