#include<stdio.h>
int main()
{
	int a,b;
	float x,y;
	char c1,c2;
	scanf("a=%db=%d",&a,&b);
	scanf("%f%e",&x,&y);
	scanf("%c%c",&c1,&c2);
	printf("%d%d",a,b);// ‰»Îa=3b=7 8.5 7.182e+1Aa 
	printf("%d %d %f %f %c %c",a,b,x,y,c1,c2);
	return 0;
}
