#include <stdio.h>
void show_arr(int n,int m,int a[n][m])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++) printf("%-5d",a[i][j]);
		putchar('\n');
	}
}
void double_arr(int n,int m,int a[n][m])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			a[i][j]*=2;
			printf("%-5d",a[i][j]);
		}
		putchar('\n');
	}
}
int main(void)
{
	int a[3][5]={1,6,8,7,6,7,7,5};
	show_arr(3,5,a);
	putchar('\n');
	double_arr(3,5,a);
	//show_arr(3,5,a);
}
