#include <stdio.h>
/*void sort(double *a,double *b,double *c)
{
	double min,max,med;
	min= (*a>*b? *b:*a)>*c? *c:(*a>*b? *b:*a);
	max= (*a<*b? *b:*a)<*c? *c:(*a<*b? *b:*a);
	med= *a+*b+*c-min-max;
	*a=min;
	*b=med;
	*c=max;
}*/
void sort(double *a,double *b,double *c)
{
	if(*a>*b) swap(a,b);
	if(*a>*c) swap(a,c);
	if(*b>*c) swap(b,c);
} 
void swap(double *a,double *b)
{
	double temp;
	temp=*b;
	*b=*a;
	*a=temp;
}

int main(void)
{
	double a,b,c;
	scanf("%lf %lf %lf",&a,&b,&c);
	sort(&a,&b,&c);
	printf("%lf %lf %lf",a,b,c);
	return 0;
}
