#include <stdio.h>
int main(void)
{
	printf("Enter a floating-point value: ");
	double a;
	scanf("%lf",&a);
	printf("fixed-point notation: %f\n",a);
	printf("exponential notation: %e\n",a);
	printf("p notation: %.2a\n",a);
}
