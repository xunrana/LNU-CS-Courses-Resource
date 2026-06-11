/*
#include <stdio.h>
int main()
{
	double a=1,b=2,c,d=2,e=3,f;
	int i;
	double s=d/a+e/b;
	for(i=2;i<[[姓名已脱敏]已脱敏];i++)
	{
		c=a+b;
		f=d+e;
		s+=f/c;
		a=b;
		b=c;
		d=e;
		e=f;
	}
	printf("%f",s);
}*/

#include <stdio.h> 
#define COUNT [[姓名已脱敏]已脱敏]
int main()
{
	double a=2,b=1,sum=0;
	double temp;
	int i;
	for(i=0;i<COUNT;i++)
	{
		sum+=a/b;
		temp=a;
		a+=b;
		b=temp;
	}
	printf("%f",sum);
}

