#include <stdio.h>
/*double min(double x,double y)
{
	if(x<y) return x;
	else return y;
}*/
/*double min(double *x,double *y)
{
	if(*x<*y) return *x;
	else return *y;
}*/
double *min(double *x,double *y)
{
	if(*x<*y) return x;
	else return y;
}
int main(void)
{
	double x,y;
	scanf("%lf %lf",&x,&y);
	printf("%f",*min(&x,&y));
}
