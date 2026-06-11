#include <bits/stdc++.h>
using namespace std;
#define N 100010// 定义常量 N，表示数组的最大大小
struct node// 定义活动的结构体
{
	int s,e;// 活动的开始时间和结束时间
}p[N];// 定义结构体数组 p，存储每个活动的信息
bool cmp(node p1,node p2)// 活动比较函数，用于排序
{
	if(p1.e==p2.e) return p1.s<p2.s;// 如果结束时间相同，则按照开始时间升序排列,便于尽早安排会场 
	return p1.e<p2.e;// 按照结束时间升序排列
}
int n; // 活动的数量
int main()
{
	cin>>n;// 输入活动的数量
	for(int i=1;i<=n;i++) cin>>p[i].s>>p[i].e;// 循环读入每个活动的开始时间和结束时间
	sort(p+1,p+1+n,cmp); // 对活动数组 p 按照结束时间进行排序，使用自定义的比较函数 cmp
	priority_queue<int,vector<int>,greater<int>> pq; // 小顶堆，存储会场的结束时间
	pq.push(p[1].e);// 将第一个活动的结束时间放入堆中作为第一个会场
	for(int i=2;i<=n;i++)// 遍历排序后的活动列表，从第二个活动开始处理
	{
		if(!pq.empty()&&pq.top()<=p[i].s)// 如果堆不为空且堆顶会场(最早结束的会场）的结束时间早于当前活动的开始时间
		{
			pq.pop();// 移除堆顶的会场（因为当前活动可以复用该会场）
			pq.push(p[i].e); // 将当前活动的结束时间放入堆中
		}
		else pq.push(p[i].e);// 否则，最早结束的会场都不可复用，需要新增一个会场
	}
	cout<<pq.size()<<"\n";// 输出最终所需的最少会场数，即堆的大小即为所需的会场数
}
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


/*
5:3 5 6 8
//前缀和 差分 
#include <bits/stdc++.h>
using namespace std;
#define N 100010
int n,a[N],s[N],e[N],mx,ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i]>>e[i],ans=max(ans,e[i]);
	for(int i=1;i<=n;i++) a[s[i]]++,a[e[i]]--;
	for(int i=0;i<=ans;i++) a[i]+=a[i-1],cout<<a[i]<<" ",mx=max(mx,a[i]);
	cout<<"\n";
	cout<<mx<<"\n";
}
*/

