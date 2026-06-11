#include <stdio.h>
int main(void)
{
	int count,sum;
	count=0;
	sum=0;
	printf("Please enter the days:\n");
	int days;
	scanf("%d",&days);
	while(count++<days)
	sum+=count;
	printf("sum=%d\n",sum);
	return 0;
}
