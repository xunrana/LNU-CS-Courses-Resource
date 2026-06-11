#include <stdio.h>
void interchange(int x,int y)
{
	int temp;
	printf("Originally x = %d and y = %d.\n",x,y);
	temp=x;
	x=y;
	y=temp;
	printf("Originally x = %d and y = %d.\n",x,y);
}
int main(void)
{
	int x=5,y=10;
	printf("Originally x = %d and y = %d.\n",x,y);
	interchange(x,y);
	printf("Now x = %d and y = %d.\n",x,y);
	return 0;
}
