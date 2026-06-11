#include <stdio.h>
int find_doublemax_index(double a[],int n)
{
	int i,index=0;
	double max=a[0];
	for(i=1;i<n;i++) if(max<a[i]){max=a[i];index++;} 
	return index;
}
int main(void)
{
	double a[5]={1.1,2.2,52.1,4.4,5.5};
	int b=find_doublemax_index(a,5);
	printf("%d",b);
}
