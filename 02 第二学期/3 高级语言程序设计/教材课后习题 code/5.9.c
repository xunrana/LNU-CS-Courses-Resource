#include <stdio.h>
int main()
{
	int i,j,k;
	for(i=1;i<1000;i++)
	{
		k=0;
		for(j=1;j<=i/2;j++) if(i%j==0) k+=j;
		if(k==i)
		{ 
		    printf("%d its factors are 1",k);
		    for(j=2;j<=i/2;j++) if(i%j==0) printf(",%d",j);
		    putchar('\n');
		}
	}
}
