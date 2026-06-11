#include <stdio.h>
/*int max(int *x,int n)
{
	int i;
	for(i=0;i<n;i++) if(*x<*(x+i)) *x=*(x+i);
	return *x;
}*/
int max(int x[],int n)
{
	int i;
	for(i=0;i<n;i++) if(x[0]<x[i]) x[0]=x[i];
	return x[0];
}
int main(void)
{
	int x[5]={1,5,10,13,9};
	printf("%d",max(x,5));
}

