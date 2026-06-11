#include <stdio.h>
void reverse(char *s)
{
	int i,l=strlen(s);
	for(i=0;i<l/2;i++)
	{
		char temp=s[i];
		s[i]=s[l-1-i];
		s[l-1-i]=temp;
	}
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
int main(void)
{
	char s[10];
	puts("Please enter a string (EOF to quit):");
	while(s_gets(s,10)!=NULL)
	{
		puts("String:");
		puts(s);
		reverse(s);
		puts("After reversing:");
		puts(s);
		puts("Your can enter a string again (EOF to quit):");
	}
	return 0;
}
