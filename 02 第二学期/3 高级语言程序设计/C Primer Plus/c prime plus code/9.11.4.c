#include <stdio.h>
double average(double a,double b)
{
	a=1/a;
	b=1/b;
	double aver=1/((a+b)/2);
	return aver;
}
int main(void)
{
	double a,b;
	scanf("%lf %lf",&a,&b);
	printf("%f",average(a,b));
	return 0;
}
