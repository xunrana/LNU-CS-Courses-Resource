#include <bits/stdc++.h>
using namespace std;
#define N 100010 // 定义常量 N，表示数组的最大长度
int n,a[N],ans,ans_cnt,cnt;
// 声明变量 n（序列长度）、a（存放序列元素的数组）、ans（出现次数最多的数）、ans_cnt（出现次数最多的次数）、cnt（当前元素出现的次数）
int main()
{
	cin>>n;// 输入序列长度
	for(int i=1;i<=n;i++) cin>>a[i];// 输入序列元素
	sort(a+1,a+1+n);  // 对序列进行排序
	for(int i=1;i<=n;i++)// 遍历排序后的序列
	{
		int now=a[i];
		cnt=1; // 统计当前元素出现的次数
		while(i+1<=n&&a[i+1]==now) i++,cnt++;// 如果下一个元素与当前元素相同,i++,增加当前元素的出现次数统计
		if(cnt>ans_cnt) // 更新出现次数最多的元素及其次数
		{
			ans=now;// 更新出现次数最多的元素为当前元素
			ans_cnt=cnt; // 更新出现次数最多的次数为当前元素的出现次数
		}
	}
	cout<<"出现次数最多的元素是："<<ans<<"，出现次数为："<<ans_cnt<<"\n"; // 输出出现次数最多的元素及其出现次数 
}
/*
6
1 2 2 3 4 5
*/
