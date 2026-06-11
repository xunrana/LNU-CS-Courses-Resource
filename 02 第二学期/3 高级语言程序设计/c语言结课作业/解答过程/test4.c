#include <stdio.h>
void quicksort(char a[],int low,int high)
{
	int i=low,j=high;
	char temp,tmp=a[low];
	if(i>j) return ;
	while(i!=j)
	{
		while(a[j]>=tmp&&j>i) j--;
		while(a[i]<=tmp&&j>i) i++;
		if(j>i)
		{
			temp=a[j];
			a[j]=a[i];
			a[i]=temp;
		}
	}
	a[low]=a[i];
	a[i]=tmp;
	quicksort(a,low,i-1);
	quicksort(a,i+1,high);
}
int main()
{
	char a[10],i;
	for(i=0;i<10;i++) scanf("%c",&a[i]);
	quicksort(a,0,i-1);
	for(i=0;i<10;i++) printf("%c",a[i]);
}
