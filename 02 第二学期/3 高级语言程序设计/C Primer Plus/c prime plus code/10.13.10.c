#include <stdio.h>
void add_arr(int n,int m,double a[n][m],double b[n][m],double c[n][m])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++) c[i][j]=a[i][j]+b[i][j];
	}
}
void show_arr(int n,int m,double a[n][m])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++) printf("%-4.2f ",a[i][j]);
		putchar('\n');
	}
}
int main(void)
{
	double a[2][2]={2,4,5,8};
	double b[2][2]={1,0,4,6};
	double c[2][2];
	show_arr(2,2,a);
	putchar('\n');
	show_arr(2,2,b);
	putchar('\n');
	add_arr(2,2,a,b,c);
	show_arr(2,2,c);
	putchar('\n');
}
