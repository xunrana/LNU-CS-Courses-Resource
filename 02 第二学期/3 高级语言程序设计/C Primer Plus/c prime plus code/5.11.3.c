#include <stdio.h>
#define week 7
int main(void)
{
	int days;
	scanf("%d",&days);
	printf("%d ",days);
	int weeks=days/week;
	days=days%week;
	printf("days are %d weeks, %d days.\n",weeks,days);
	return 0;
}
