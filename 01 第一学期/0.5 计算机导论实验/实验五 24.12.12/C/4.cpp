#include <stdio.h>
int main()
{
	for(int i=1;i<=9;i++)
	{ 
		for(int j=1;j<=i;j++) 
		printf("%d+%d=%d ",i,j,i+j);
		putchar('\n');
	} 
	return 0;
}
/*
10


ÇëÊäÈën:
10
10!=3628800
*/
