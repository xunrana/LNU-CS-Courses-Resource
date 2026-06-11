#include <stdio.h>
void show_arr(int n,int m,double a[n][m])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++) printf("%-4.2f ",a[i][j]);
		putchar('\n');
	}
}
void copy_arr(int n,int m,double a[n][m],double b[n][m])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++) a[i][j]=b[i][j];
	}
}
int main(void)
{
	double a[][4]={2.2,6.4,4.9,5.4,4.6,4.5,4.7,7.9};
	double b[2][4];
	show_arr(2,4,a);
	copy_arr(2,4,b,a);
	putchar('\n');
	show_arr(2,4,b);
}
