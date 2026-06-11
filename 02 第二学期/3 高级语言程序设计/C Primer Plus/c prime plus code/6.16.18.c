#include <stdio.h>
int main(void)
{
	int a=5,i;
	for(i=1;i<=73;i++)
	{
		a=a-i;
		a*=2;
		//if(a==150) break;
	}
	printf("%d\n%d",a,i);
}
