#include <bits/stdc++.h>
using namespace std;
void solve()
{
	int n;
	cout<<"请输入n:\n";
	cin>>n;
	long long res=1;
	for(int i=1;i<=n;i++) res=res*2;
	cout<<"2的"<<n<<"次幂="<<res<<"\n"; 
}
/*
10


请输入n:
10
2的10次幂=1024
*/ 
int main()
{
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	int T=1;
	while(T--) solve();
} 
