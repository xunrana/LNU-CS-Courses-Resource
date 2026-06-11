#include <bits/stdc++.h>
using namespace std;
int a[11];
void solve()
{
	int sum=0;
	for(int i=1;i<=10;i++) cin>>a[i],sum+=a[i];
	double avg=1.0*sum/10;
	cout<<"平均值为"<<avg<<"\n";
	cout<<"比平均值大的数有：\n";
	for(int i=1;i<=10;i++) if(a[i]>avg) cout<<a[i]<<" ";
	cout<<"\n"; 
}
/*
1 7 5 3 2 8 9 10 6 4


1 7 5 3 2 8 9 10 6 4
平均值为5.5
比平均值小的数有：
1 5 3 2 4
*/ 
int main()
{
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	int T=1;
	while(T--) solve();
} 
