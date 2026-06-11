#include <stdio.h>
#include <string.h>
#define LEN [[姓名已脱敏]已脱敏]
char *s_gets(char *st,int n);
int is_within(char ch,const char *str);
int main(void)
{
	char ch,str[LEN];
	puts("Please enter a string (EOF to quit):");
	while(s_gets(str,LEN))
	{
		printf("Please enter a character: ");
		ch=getchar();
		while(getchar()!='\n') continue;
		puts("String:");
		puts(str);
		if(is_within(ch,str))
		printf("Exist %c in the string.\n",ch);
		else printf("Not exist %c in the string.\n",ch);
		puts("You can enter a string again (EOF to quit):");
	}
	puts("Done.");
	return 0;
}
char *s_gets(char *st,int n)
{
	char *ret_val;
	char *find;
	ret_val=fgets(st,n,stdin);
	if(ret_val)
	{
		find=strchr(st,'\n');
		if(find) *find='\0';
		else while(getchar()!='\n') continue;
	}
	return ret_val;
}
int is_within(char ch,const char *str)
{
	while(*str)
	{
		if(*str==ch) return 1;
		str++;
	}
	return 0;
}
