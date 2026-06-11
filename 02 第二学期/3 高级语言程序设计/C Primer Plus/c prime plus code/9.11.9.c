#include <stdio.h>
double power(double n,int p)
{
	if(p==0) {if(n==0) printf("No defined\n");return 1;
	}
	else if(n==0) return 0;
	if(p>0) return n*power(n,p-1);
	else if(p<0) return 1/(n*power(n,-p-1));
}
int main(void)
{
	double n;
	int p;
    scanf("%lf %d",&n,&p);
	printf("%f",power(n,p));
	return 0;
} 
