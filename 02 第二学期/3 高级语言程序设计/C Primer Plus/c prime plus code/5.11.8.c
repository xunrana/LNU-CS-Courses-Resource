#include <stdio.h>
int main(void)
{
	printf("This program computes moduli.\n");
	printf("Enter an integer to serve as the second operand: ");
	int a,b;
	scanf("%d",&a);
	printf("Now enter the first operand: ");
	scanf("%d",&b);
	int c;
	c=b%a;
	printf("%d %% %d is %d\n",b,a,c);
	while(b>0)
	{
		printf("Enter next number for first operand (<= 0 to quit): ");
		scanf("%d",&b);
		if(b<=0) break;
		//c=b%a;
		printf("%d %% %d is %d\n",b,a,b%a);
	}
	if(b<=0)printf("Done!");
	return 0;
}
