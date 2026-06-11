#include <stdio.h>
int main()
{
	double h=100;
	int i;
	double s=100;
	for(i=1;i<10;i++)
	{
		h/=2;
		s+=h*2;
	}
	printf("%f  %f",s,h/2);
}
