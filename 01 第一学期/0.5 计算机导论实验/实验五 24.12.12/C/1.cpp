#include <stdio.h>
int main()
{
	int n,i;
	printf("«Î ‰»În:\n");
	scanf("%d",&n);
	long long res=1;
	for(i=1;i<=n;i++) res=res*i;
	printf("%d!=%ld\n",n,res);
	return 0;
}
/*
10


«Î ‰»În:
10
10!=3628800
*/
