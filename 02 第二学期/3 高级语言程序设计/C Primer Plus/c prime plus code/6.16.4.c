#include <stdio.h>
int main(void)
{
	int i,j;
	char ch='A';
	for(i=0;i<6;i++)
	{
		for(j=0;j<=i;j++) printf("%c",ch++);
		printf("\n");
	}
    return 0; 
}
