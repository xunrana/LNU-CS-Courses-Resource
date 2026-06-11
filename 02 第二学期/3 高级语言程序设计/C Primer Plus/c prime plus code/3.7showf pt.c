#include <stdio.h>
int main(void)
{
	float aboat = 3[[姓名已脱敏]已脱敏]00.0;
	double abet = 2.14e9;
	long double dip = 5.32e-5;
	printf("%f can be written %e\n",aboat,aboat);
	printf("And it is %a in henxadecimal, powers of 2 notation\n",aboat);
	printf("%f can be written %e\n",abet,abet);
	printf("%Lf can be written %Le\n",dip,dip);
	return 0;
}
