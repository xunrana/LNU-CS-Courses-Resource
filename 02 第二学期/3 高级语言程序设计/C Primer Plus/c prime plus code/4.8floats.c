#include <stdio.h>
int main(void)
{
	const double PENT=3852.99;
	printf("*%f*\n",PENT);
	printf("*%e*\n",PENT);
	printf("*%4.2f*\n",PENT);
	printf("*%2.1f*\n",PENT);
	printf("*%10.3f*\n",PENT);
	printf("*%10.3E*\n",PENT);
	printf("*%+4.2f*\n",PENT);
	printf("*%010.2f*\n",PENT);
	return 0;
}
