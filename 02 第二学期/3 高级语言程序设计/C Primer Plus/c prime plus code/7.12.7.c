#include <stdio.h>
int main(void)
{
	printf("Please enter your working hours: ");
	double h;
	scanf("%lf",&h);
	double s,t;
	if(h<=40) s=h*10;
	else s=h*1.5*10;
	if(s<300) t=s*0.15;
	else if(s<450) t=45+(s-300)*0.2;
	else t=45+30+(s-450)*0.25;
	printf("%f %f %f",s,t,s-t);
	return 0;
}
