#include <stdio.h>
int main(void)
{
	int i,j;
	char f;
	for(i=0;i<6;i++)
	{
		f='F';
		for(j=0;j<=i;j++) printf("%c",f--);
		printf("\n");
	}
	return 0;
}
