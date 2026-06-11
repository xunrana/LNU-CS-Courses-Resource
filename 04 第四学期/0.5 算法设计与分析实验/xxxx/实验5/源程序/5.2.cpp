#include <bits/stdc++.h>
using namespace std;
#define N 100
int n,m,a[N]; 
vector<int>path,vt(N);//path用于存储当前的排列路径，vt用于标记整数元素的使用情况。
void dfs()// 定义递归函数dfs，用于生成排列
{
	if(path.size()==m) // 如果当前路径中元素个数达到要求m，则输出路径中的元素
	{
		for(auto i:path) cout<<i<<" ";// 输出当前排列
		cout<<"\n";
		return ; 
	}
	
	for(int i=1;i<=n;i++)  // 遍历1到n，尝试将每个未使用过的元素加入排列中
	{
		if(!vt[i]) // 如果元素i未被使用过
		{
			vt[i]=1;// 标记元素i为已使用
			path.push_back(i);// 将元素i加入当前排列路径中
			dfs();// 递归调用dfs，继续生成排列
			vt[i]=0;// 回溯，标记元素i为未使用
			path.pop_back(); // 移除元素i，尝试下一个元素
		}
	}
}
int main()
{
	cin>>n>>m;// 输入整数n和m
	dfs();// 调用dfs函数，生成所有从1到n中取m个元素的排列
} 
