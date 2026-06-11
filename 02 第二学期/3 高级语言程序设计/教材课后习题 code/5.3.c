#include <stdio.h>
int gcd(int a,int b)
{
    return b==0? a:gcd(b,a%b); 
}
int f(int a,int b)
{
	return a*b/gcd(a,b);
}
int main()
{
	int a,b;
	scanf("%d %d",&a,&b);
	printf("%d\n",gcd(a,b));
	printf("%d",f(a,b));
}
