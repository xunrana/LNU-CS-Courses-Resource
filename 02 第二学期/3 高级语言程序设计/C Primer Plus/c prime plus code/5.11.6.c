#include <stdio.h>
int main(void)
{
	int days;
	scanf("%d",&days);
	int sum=0,a=0;
	while(a++<days)
	{
		sum+=a*a;
	}
	printf("%d",sum);
	return 0;
}
