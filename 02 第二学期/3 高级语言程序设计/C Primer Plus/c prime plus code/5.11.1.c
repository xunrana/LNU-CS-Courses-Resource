#include <stdio.h>
int main(void)
{
	const int a=60;
	int b,c,d;
	printf("Please enter a number:\n");
	scanf("%d",&b);
	while(b>0)
	{
		c=b/60;
		d=b%60;
		printf("%d hour(s) and %d minutes\n",c,d);
		scanf("%d",&b);
	}
	return 0;
}
