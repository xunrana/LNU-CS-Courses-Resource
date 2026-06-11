#include <stdio.h>//   0.0 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 11.0 12.0 13.0 14.0 
void a(double ar[],int n)
{
	int i;
	for(i=0;i<n;i++) scanf("%lf",&ar[i]);
}
double b(double ar[],int n)
{
	int i;
	double sum=0;
	for(i=0;i<n;i++) sum+=ar[i];
	return sum/n;
}
double b1(double ar[][5],int n)
{
	int i,j;
	double sum=0;
	for(i=0;i<n;i++)
	for(j=0;j<5;j++) sum+=ar[i][j];
	return sum/(5*n);
}
double max(double ar[][5],int n)
{
	int i,j;
	double max=ar[0][0];
	for(i=0;i<n;i++)
	for(j=0;j<5;j++)
	if(max<ar[i][j]) max=ar[i][j];
	return max;
}
void show_arr(double ar[][5],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<5;j++)
		printf("%-3g",ar[i][j]);
		putchar('\n');
	}
}
int main(void)
{
	double c[3][5];
	int i;
	for(i=0;i<3;i++)
	a(c[i],5);
	show_arr(c,3);
	putchar('\n');
	for(i=0;i<3;i++)
	printf("%-3g",b(c[i],5));
	putchar('\n');
	printf("%-3g\n",b1(c,3));
	printf("%g",max(c,3)); 
}
