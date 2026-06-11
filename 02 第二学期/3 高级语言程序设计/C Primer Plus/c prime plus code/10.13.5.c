#include <stdio.h>
/*double find_double_dif_max_min(double a[],int n)
{
	int i,j;
	double temp;
	for(i=0;i<n;i++)
	for(j=i+1;j<n;j++)
	if(a[i]>a[j])
	{
		temp=a[i];
		a[i]=a[j];
		a[j]=temp;
	}
	return a[n-1]-a[0];
}*/
double find_double_dif_max_min(double *a,int n)
{
	int i;
	double max=a[0],min=a[0];
	for(i=1;i<n;i++)
	{
		max=max>a[i]?max:a[i];
		min=min<a[i]?min:a[i];
	}
	return max-min;
}
int main(void)
{
	double a[5]={1.0,0.5,2.0,3.0,4.0};
	double dif=find_double_dif_max_min(a,5);
	printf("%g",dif);
}
