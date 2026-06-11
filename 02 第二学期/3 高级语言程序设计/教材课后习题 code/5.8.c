#include <stdio.h>
#include <math.h>
int main()
{
	int i,j,k;
	for(i=100;i<1000;i++)
	{
		k=pow(i%10,3)+pow(i/10%10,3)+pow(i/100,3);
		if(k==i) printf("%d\n",i);
	}
}
