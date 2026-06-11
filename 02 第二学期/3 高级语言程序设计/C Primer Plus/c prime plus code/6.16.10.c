#include <stdio.h>
int main(void)
{
	int a,b,c;
	printf("please enter lower and upper limits: ");
	scanf("%d %d",&a,&b);
	while(a<b)
	{
		int i,k=0;
		for(i=a;i<=b;i++) k+=i*i;
		printf("The sum of the suqares from %d to %d is %d\n",a*a,b*b,k);
		printf("Enter next set of limits: ");
		scanf("%d %d",&a,&b);
	}
	printf("Done!\n");
	return 0;
}
