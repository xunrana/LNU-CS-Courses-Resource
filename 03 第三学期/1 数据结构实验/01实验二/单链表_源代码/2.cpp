#include <bits/stdc++.h>
using namespace std;
long long t,n,f[35],u,v,f1;
string s;
int fx(int i)
{
	if(s[f[i]]==s[i]&&s[f[f[i]]]==s[i]) return 1;
	return 0;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		s="0"+s;
		f1=0;
		for(int i=1;i<n;i++)
		{
			cin>>u>>v;
			if(u>v) swap(u,v);
			f[v]=u;
		}
		for(int i=1;i<s.size();i++) if(fx(i)) f1=1;
		if(f1==1) cout<<"NO\n";
		else cout<<"YES\n";
	}
}
