#include <stdio.h>
int main(void)
{
	printf("please enter a number:");
	int number;
	scanf("%d",&number);
	printf("%llf",950*number/(3.0e-23));
	return 0;
}
