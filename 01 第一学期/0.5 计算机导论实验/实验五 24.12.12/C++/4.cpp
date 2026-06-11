#include <bits/stdc++.h>
using namespace std;
void solve()
{
	for(int i=1;i<=9;i++)
	{ 
		for(int j=1;j<=i;j++) cout<<i<<"+"<<j<<"="<<i+j<<" ";
		cout<<"\n";
	} 
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	while(T--) solve();
} 
