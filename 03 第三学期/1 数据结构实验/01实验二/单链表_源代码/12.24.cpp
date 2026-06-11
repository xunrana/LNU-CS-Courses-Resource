#include <iostream>
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
  long long t,a,n,res,pre;
  cin>>t;
  while(t--)
  {
    cin>>a>>n;
    res=1;
    for(long long i=2;i<=a;i++) 
	{
		pre=res;
		res=lcm(res,i);
	}
    cout<<n/pre-n/res<<"\n";
  }
}
