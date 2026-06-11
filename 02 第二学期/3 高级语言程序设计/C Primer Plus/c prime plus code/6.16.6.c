#include <stdio.h>
int main(void)
{
	int lower,upper,index;
	int square,cube;
	printf("Enter starting integer: ");
	scanf("%d",&lower);
	printf("Enter ending integer: ");
	scanf("%d",&upper);
	printf("%5s %10s %15s\n","num","square","cube");
	int i;
	for(i=lower;i<=upper;i++)
	{
		square=i*i;
		cube=square*i;
		printf("%5d %10d %15d\n",i,square,cube);
	}
	return 0;
}
