#include <stdio.h>
#include <string.h>
#define LEN 10
char *string_in(char *s1,char *s2)
{
	int i=0,j=0;
	int a=strlen(s1),b=strlen(s2);
	while(i<a&&j<b)
	{
		if(s1[i]==s2[j])
		{
			i++;
			j++;
		}
		else 
		{
			i=i-j+1;
			j=0;
		}
	}
	return j==b? s1+i-j:NULL;
	//return strchr(s1,s2);
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
	char s1[LEN];
	char s2[LEN];
	puts("Please enter the first string (EOF to quit):");
	while(s_gets(s1,LEN)!=NULL)
	{
		puts("Please enter the second string:");
		if(s_gets(s2,LEN)!=NULL)
		{
			const char *temp=string_in(s1,s2);
			if(temp) printf("String %s exists in string %s\n",s2,s1);
			else printf("String %s doesn't exist in string %s\n",s2,s1);
		}
		puts("You can enter again (EOF to quit):");
	}
	puts("Done");
	return 0;
}
