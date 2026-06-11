#include <stdio.h>
int main(void)
{
	char ch;
	while((ch=getchar())!=EOF)
	{
		if(ch<32) printf("^%c",ch+64);
		else if(ch=='\n') printf("\\n");
		else if(ch=='\t') printf("\\t");
		else printf("%c %d\n",ch,ch);
	}
}
