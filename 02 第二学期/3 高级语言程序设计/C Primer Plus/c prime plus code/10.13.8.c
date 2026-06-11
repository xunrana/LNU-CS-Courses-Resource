#include <stdio.h>
/*void copy_arr(double a[],double b[],int n)
{
	int i;
	for(i=0;i<n;i++) a[i]=b[i];
}*/
void copy_arr(double *a,double *b,int n)
{
	int i;
	for(i=0;i<n;i++) *(a+i)=*(b+i);
}
void show_arr(double a[],int n)
{
	int i;
	for(i=0;i<n;i++) printf("%-5.0f",a[i]);
	putchar('\n');
}
int main(void)
{
	double a[7]={0.0,1.0,2.0,3.0,4.0,5.0,6.0};
	double b[3];
	copy_arr(b,&a[2],3);
	show_arr(b,3);
}
