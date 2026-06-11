#include <bits/stdc++.h>
using namespace std;
#define N 100010
int n,c,w[N],cnt;
int main()
{
	cin>>n>>c; // 输入总人数n和船的最大载重量c
	for(int i=1;i<=n;i++) cin>>w[i];// 输入每个人的体重
	sort(w+1,w+1+n); // 将所有人的体重按照从小到大排序
	int j=n,i=1; // 初始化两个指针，分别指向最重和最轻的人
	while(j>=i)
	{
		if(w[j]+w[i]<=c) // 如果最重和最轻的人可以一起乘船
		cnt++,j--,i++;  // 计数器加一,最重的人已经乘船，指针左移,最轻的人已经乘船，指针右移
		else cnt++,j--;// 只能最重的人单独乘船，计数器加一,最重的人已经乘船，指针左移
	}
	cout<<cnt<<"\n";// 输出最少使用船的次数
} 
/*
6 10
5 3 7 2 8 4
*/
