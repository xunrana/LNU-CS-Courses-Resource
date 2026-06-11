#include <stdio.h>
#include <float.h>
int main(void)
{
	double a=1.0/3.0;
	float b=1.0/3.0;
	printf("%.6f %.12f %.16f\n",a,a,a);
	printf("%.6f %.12f %.16f\n",b,b,b);
	printf("FLT_DIG=%d DBL_DIG=%d\n",FLT_DIG,DBL_DIG);
	return 0;
}
