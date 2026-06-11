#include <stdio.h>
#include <string.h>
void delete(char *s)
{
    int i,j=0,k=strlen(s);
    for(i=0;i<k;i++) if(s[i]!=' ') s[j++]=s[i];
    s[j]='\0';
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
	puts("Please enter a string (EOF to quit):");
	char s[[[姓名已脱敏]已脱敏]];
	while(s_gets(s,[[姓名已脱敏]已脱敏])!=NULL)
	{
		puts(s);
		puts("After deleting:");
	    delete(s);
	    puts(s);
		puts("You can enter a string again (EOF to quit):");
	}
	return 0;
} 
