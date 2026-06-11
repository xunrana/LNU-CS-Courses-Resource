#include <stdio.h>
double square(double a);
int main(void)
{
	double a;
	scanf("%lf",&a);
	printf("%f",square(a));
	return 0;
}
double square(double a)
{
	a=a*a;
	return a;
}
