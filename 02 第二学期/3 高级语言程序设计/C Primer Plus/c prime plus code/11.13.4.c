#include <stdio.h>
#include <ctype.h>
#define LEN 10
char *getword(char *str,int len)
{
	int n=0;
	char ch;
	char *pt=str;
	while((ch=getchar())!=EOF&&isspace(ch))
	continue;
	if(ch==EOF) return NULL;
	else {n++;*str++=ch;
	}
	while((ch=getchar())!=EOF&&!isspace(ch)&&(n<len-1))
	{
		*str++=ch;
		n++;
	}
	*str='\0';
	if(ch==EOF) return NULL;
	else 
	{
		while(getchar()!='\n') continue;
		return pt;
	}
}
int main(void)
{
	char input[LEN];
	puts("Please enter a word (EOF to quit):");
	while(getword(input,LEN))
	{
		puts("Result:");
		puts(input);
		puts("You can enter a word again(EOF to quit):");
	}
	puts("Done.");
	return 0;
}
