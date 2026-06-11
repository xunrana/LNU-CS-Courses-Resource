#include <stdio.h>//   0.0 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 11.0 12.0 13.0 14.0 
void a(int n,double ar[n])
{
	int i;
	for(i=0;i<n;i++) scanf("%lf",&ar[i]);
}
double b(int n,double ar[n])
{
	int i;
	double sum=0;
	for(i=0;i<n;i++) sum+=ar[i];
	return sum/n;
}
double b1(int n,int m,double ar[n][m])
{
	int i,j;
	double sum=0;
	for(i=0;i<n;i++)
	for(j=0;j<m;j++) sum+=ar[i][j];
	return sum/(m*n);
}
double max(int n,int m,double ar[n][m])
{
	int i,j;
	double max=ar[0][0];
	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	if(max<ar[i][j]) max=ar[i][j];
	return max;
}
void show_arr(int n,int m,double ar[n][m])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		printf("%-3g",ar[i][j]);
		putchar('\n');
	}
}
int main(void)
{
	double c[3][5];
	int i;
	for(i=0;i<3;i++)
	a(5,c[i]);
	show_arr(3,5,c);
	putchar('\n');
	for(i=0;i<3;i++)
	printf("%-3g",b(5,c[i]));
	putchar('\n');
	printf("%-3g\n",b1(3,5,c));
	printf("%g",max(3,5,c)); 
}
