#include <stdio.h>
int main(void)
{
	double pint,cup,ounce,da,cha;
	printf("please enter your cups:");
	scanf("%lf",&cup);
	printf("pint is %.0f\n",cup/2);
	printf("ounce is %.0f\n",cup*8);
	printf("da is %.0f\n",cup*8*2);
	printf("cha is %.0f\n",cup*8*2*3);
	return 0;
}
