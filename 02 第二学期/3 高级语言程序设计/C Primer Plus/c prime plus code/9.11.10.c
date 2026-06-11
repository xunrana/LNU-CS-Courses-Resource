#include <stdio.h>
void to_base_n(int a,int b)
{
	int r;
	r=a%b;
	if(a>=b) to_base_n(a/b,b);
	printf("%d",r);
}
int main(void)
{
	int a,b;
	scanf("%d %d",&a,&b);
	to_base_n(a,b);
	return 0;
}
