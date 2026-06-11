#include <stdio.h>
void show_arr(double a[],int n)
{
	int i;
	for(i=0;i<n;i++) 
	printf("%g\n",a[i]);
}
/*void reverse(double a[],int n)
{
	int i;
	double temp;
	for(i=0;i<n/2;i++)
	{
		temp=a[i];
		a[i]=a[n-1-i];
		a[n-1-i]=temp;
	}
}*/
void reverse(double *a,int n)
{
	int i;
	double temp;
	for(i=0;i<n/2;i++)
	{
		temp=*(a+i);
		*(a+i)=*(a+n-1-i);
		*(a+n-1-i)=temp;
	}
}
int main(void)
{
	double a[]={1.1,5.5,2.2,4.4,3.2};
	int l=sizeof a/sizeof a[0];
	printf("Array:\n");
	show_arr(a,l);
	reverse(a,l);
	printf("After reversing:\n");
	show_arr(a,l);
}
