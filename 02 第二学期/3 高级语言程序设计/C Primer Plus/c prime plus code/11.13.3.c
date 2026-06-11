#include <stdio.h>
#include <ctype.h>
#define LEN 10
char *getword(char *str)
{
	int ch,n=0;
	char *pt=str;
	while((ch=getchar())!=EOF&&isspace(ch))
	continue;
	if(ch==EOF) return NULL;
	else 
	{
		n++;
		*str++=ch;
	}
	while((ch=getchar())!=EOF&&!isspace(ch)&&(n<LEN-1))
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
	printf("Please enter a word (EOF to quit):\n");
	while(getword(input)!=NULL)
	{
		puts("Result:");
		puts(input);
		puts("You can enter a word again(EOF to quit):");
	}
	puts("Done.");
	return 0;
} 

