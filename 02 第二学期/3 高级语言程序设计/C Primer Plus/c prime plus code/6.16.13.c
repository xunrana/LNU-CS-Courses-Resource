#include <stdio.h>
int power(int a,int b);
int main(void)
{
	int a[8],i;
	for(i=0;i<8;i++) a[i]=power(2,i+1);
	i--;
	do
	{
		printf("a[%d]=%d\n",i,a[i]);
		i--;
	}while(i!=-1);
	return 0;
}
int power(int a,int b)
{
	int i,j=1;
	for(i=0;i<b;i++) j=j*a;
	return j;
}
