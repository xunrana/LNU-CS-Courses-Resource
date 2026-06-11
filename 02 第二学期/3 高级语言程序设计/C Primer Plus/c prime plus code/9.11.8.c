#include <stdio.h>
double power(double n,int p)
{
	if(p==0) {if(n==0) printf("No defined\n");return 1;
	}
	else if(n==0) return 0;
	if(p>0)
	{
		int i;
		double sum=1;
		for(i=1;i<=p;i++) sum*=n;
		return sum;
	}
	else if(p<0)
	{
		int i;
		double sum=1;
		for(i=1;i<=-p;i++) sum*=n;
		sum=1/sum;
		return sum;
	}
}
int main(void)
{
	double n;
	int p;
    scanf("%lf %d",&n,&p);
	printf("%f",power(n,p));
	return 0;
} 
