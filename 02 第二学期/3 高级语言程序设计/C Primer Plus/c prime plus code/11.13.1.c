#include <stdio.h>
#define LEN 10
void getnchar(char str[],int n)
{
	int i=0;
	for(i=0;i<n-1;i++) str[i]=getchar();
	str[n-1]='\0';
}
int main(void)
{
	char str[LEN];
	printf("Please enter %d characters:\n",LEN-1);
	getnchar(str,LEN);
	printf("Result:\n");
	puts(str);
	puts("Done.");
	return 0;
}
