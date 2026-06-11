#include <stdio.h>
void larger_of(double *x,double *y)
{
	if(*x<*y) *x=*y;
	else *y=*x;
}
int main(void)
{
	double a,b;
	scanf("%lf %lf",&a,&b);
	larger_of(&a,&b);
	printf("%f\n%f\n",a,b);
	return 0;
}
