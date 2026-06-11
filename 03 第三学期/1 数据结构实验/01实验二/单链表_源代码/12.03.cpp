#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a,long long b)
{
    return b==0? a:gcd(b,a%b);
}
long long lcm(long long a,long long b)
{
    return a*b/(gcd(a,b));
}
int main()
{	
  int t,a,n,res,pre,ans[1000010];
  res=1;
  ans[1]=1;
  cout<<"safdsf\n";
  for(long long i=2;i<=1000000;i++) ans[i]=lcm(ans[i-1],i);
  cin>>t;
  while(t--)
  {
    cin>>a>>n;
    cout<<n/ans[a-1]-n/ans[a]<<"\n";
  }
}
