#include <bits/stdc++.h>
using namespace std;
#define N 100010
int n,k,a[N]; // 定义数组大小、目标和及数组a
vector<int>ans;// 当前组合
vector<vector<int>> res;// 保存所有符合条件的组合
void dfs(int i,int s)// 深度优先搜索函数，i表示当前处理到数组的哪个位置，s表示当前组合的和
{
	if(s==k) // 如果当前组合的和等于目标值k，保存当前组合
	{
		res.push_back(ans);
		return ;
	}
	if(s>k) return ; // 如果当前组合的和超过目标值k，停止搜索
	for(int j=i+1;j<=n;j++) // 从下一个位置开始继续搜索
	{
		ans.push_back(a[j]);// 将a[j]加入当前组合
		dfs(j,s+a[j]);// 继续搜索
		ans.pop_back();// 回溯，移除刚才加入的元素
	}
	
}

int main()
{
	cin>>n>>k;// 读取n和k的值
	for(int i=1;i<=n;i++) cin>>a[i]; // 读取数组a的值
	sort(a+1,a+1+n);// 将数组a排序
	dfs(0,0); // 开始深度优先搜索
	for(auto i:res)// 输出所有符合条件的组合
	{
		for(auto j:i) cout<<j<<" ";
		cout<<"\n";
	}
} 

/*
5 11
1 3 7 8 10
1 3 7
1 10
3 8
*/
