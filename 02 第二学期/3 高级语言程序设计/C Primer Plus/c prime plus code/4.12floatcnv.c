#include <stdio.h>
int main(void)
{
	float n1=3.0;
	double n2=3.0;
	long n3=[[姓名已脱敏]已脱敏]00000000;
	long n4=1234567890;
	printf("%.le %.le %.le %.le",n1,n2,n3,n4);
	printf("%ld %ld\n",n3,n4);
	printf("%ld %ld %ld %ld\n",n1,n2,n3,n4);
	return 0;
}
