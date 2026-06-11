#include <stdio.h>
#include <ctype.h>
#define LEN 10
void getnchar(char str[],int n)
{
	int i=0;
	while(i<n-1)
	{
		str[i]=getchar();
		if(isspace(str[i])) break;
		++i;
	}
	
	str[i]='\0';
}
int main(void)
{
	char str[LEN];
	printf("Please enter %d character:\n");
	getnchar(str,LEN);
	puts("Result:");
	puts(str);
	puts("Done.");
	return 0;
}
