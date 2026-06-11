#include <bits/stdc++.h>
using namespace std;
void solve()
{
	int n;
	cout<<"ÇëÊäÈën:\n";
	cin>>n;
	long long res=1;
	for(int i=1;i<=n;i++) res=res*i;
	cout<<n<<"!="<<res<<"\n";
}
/*
10


ÇëÊäÈën:
10
10!=3628800
*/ 
int main()
{
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	int T=1;
	while(T--) solve();
} 
