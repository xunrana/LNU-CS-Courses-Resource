#include <stdio.h>
void copy_arr(double a[],double b[],int n)
{
	int i;
	for(i=0;i<n;i++)
	b[i]=a[i];
}
void show_arr(double x[][5],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<5;j++) printf("%.1f ",x[i][j]);
		putchar('\n');
	}
} 
int main(void)
{
	double a[5][5]={{1.1,2.2},{3.3,4.4},{5.5,6.6},{7.7,8.8},{9.9}};
	//int l=sizeof a/sizeof a[0];
	//printf("%d",l);
	show_arr(a,5);
	double b[5][5];
	int i;
	for(i=0;i<5;i++)
	copy_arr(a[i],b[i],5);
	putchar('\n');
	show_arr(b,5);
}
