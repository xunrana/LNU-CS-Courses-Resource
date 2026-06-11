#include <stdio.h>
int main(void)
{
	double a,b,res;
	printf("Enter a pair of number:\n");
	while(scanf("%lf %lf",&a,&b)==2)
	{
		res=(a-b)/(a*b);
		printf("(%.3g-%.3g)/(%.3g*%.3g)=%.5g\n",a,b,a,b,res);
	}
	return 0;
}
