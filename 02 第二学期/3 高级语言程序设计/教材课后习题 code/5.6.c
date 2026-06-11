#include <stdio.h>
double f(int n)
{
	int i;
	double j=1;
	for(i=1;i<=n;i++) j*=i;
	return j;
}
int main()
{
	int i,n;
	scanf("%d",&n);
	double s=0;
	for(i=1;i<=n;i++)
	{
	    s+=f(i);
	    printf("%f\n",f(i));
	}
	printf("%f",s);
}
