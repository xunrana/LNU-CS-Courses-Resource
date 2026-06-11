#include <stdio.h>
#define TIMES 10000000
int main(void)
{
	double a=1,b=1,sum=0,sum1=0,a1=1,b1=1;
    /*do
    {
    	sum=sum+a/b;
    	b++;
	}while(b<TIMES);
	printf("%f",sum);*/
	int flag=1;
	/*do
	{
		sum1=sum1+a1/b1*flag;
		b1++;
		flag=-flag;
	}while(b1<TIMES);
	printf("%f",sum1);*/
	do
	{
		sum=sum+a/b;
		b++;
		sum1=sum1+a1/b1*flag;
		b1++;
		flag=-flag;
	}while(b<TIMES);
	printf("%f",sum+sum1);
	return 0;
}
//fuck the regulations!!!!!!!
