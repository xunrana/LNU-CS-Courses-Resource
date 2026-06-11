#include <stdio.h>
int main()
{
	int a,n,i,s=0;
	scanf("%d %d",&a,&n);
	int b=a;
	for(i=0;i<n;i++)
	{
		s+=b;
		b=b*10+a;
	}
	printf("%d",s);
}
