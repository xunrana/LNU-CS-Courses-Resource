#include <stdio.h>
double res(double a,double b);
int main(void)
{
	double a,b;
	scanf("%lf %lf",&a,&b);
	printf("(%.3g - %.3g)/(%.3g*%.3g) = %.5g\n", a, b, a, b, res(a,b));
	return 0;
}
double res(double a,double b)
{
	double r;
	r=(a-b)/(a*b);
	return r;
}
