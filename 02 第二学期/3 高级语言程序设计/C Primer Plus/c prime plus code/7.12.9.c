#include <stdio.h>
int ISPRIME(int a);
int main(void)
{
	int a;
	scanf("%d",&a);
	int i;
	for(i=2;i<a;i++)
	if(ISPRIME(i)) printf("%d\n",i);
	return 0; 
}
int ISPRIME(int a)
{
	int b;
	for(b=2;b*b<=a;b++)
	{
		if(a%b==0) return 0;
	}
	return 1;
}
