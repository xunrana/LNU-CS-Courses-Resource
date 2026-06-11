#include <bits/stdc++.h>
using namespace std;
#define N 101
int n;// 定义变量 n，表示棋盘大小
int a[N][N];// 定义二维数组 a，表示棋盘，a[i][j] 表示在第 i 行第 j 列是否放置皇后
int l[N];// 数组 l 用于标记左对角线上是否已经有皇后
int r[N]; // 数组 r 用于标记右对角线上是否已经有皇后
int z[N]; // 数组 z 用于标记每列是否已经有皇后
int f[N];// 数组 f 用于标记每行是否已经有皇后
void dfs(int i)// 定义深度优先搜索函数 dfs，参数 i 表示当前处理的行数
{
	if(i>n)// 如果 i 超过了棋盘大小 n，则说明找到了一组解，打印出当前的棋盘布局
	{
		for(int i=1;i<=n;i++,cout<<"\n") for(int j=1;j<=n;j++) cout<<a[i][j]<<" ";
		cout<<"\n";
		return ;
	} 
	// 遍历当前行 i 的每一列 j，尝试放置皇后
	for(int j=1;j<=n;j++)
	{ // 检查当前位置 (i, j) 是否满足放置皇后的条件：不在同一列、左右对角线没有其他皇后
		if(!l[i-j+n]&&!r[i+j]&&!z[j]&&!f[i])
		{
			a[i][j]=1;// 放置皇后
			l[i-j+n]=r[i+j]=z[j]=f[i]=1;// 更新左右对角线和列的标记数组
			dfs(i+1);// 递归处理下一行
			a[i][j]=0; // 回溯，撤销当前行的操作
			l[i-j+n]=r[i+j]=z[j]=f[i]=0; // 回溯，撤销当前行的操作
		}
	} 
}
int main()
{
	cin>>n;
	dfs(1);
} 
