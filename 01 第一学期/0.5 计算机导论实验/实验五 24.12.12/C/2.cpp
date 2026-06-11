#include <stdio.h>
int main()
{
	int n,i;
	printf("请输入n:\n");
	scanf("%d",&n);
	long long res=1;
	for(i=1;i<=n;i++) res=res*2;
	printf("2的%d次幂=%ld\n",n,res);
	return 0;
}
/*
10


请输入n:
10
2的10次幂=1024
*/
