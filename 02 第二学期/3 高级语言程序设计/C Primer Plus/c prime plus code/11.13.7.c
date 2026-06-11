#include <stdio.h>
#include <string.h>
#define LEN 10
char *mystrncpy(char *s1,char *s2,int n)
{
	int c=0;
	while(*s2!='\0'&&c<n) *(s1+c++)=*s2++;
	*(s1+c)='\0';
	return s1;
}

char *s_gets(char *st,int n)
{
	char *ret_val;
	char *find;
	ret_val=fgets(st,n,stdin);
	if(ret_val!=NULL)
	{
		find=strchr(st,'\n');
		if(find!=NULL) *find='\0';
		else eatline();
	}
	return ret_val;
}
void eatline(void)
{
	while(getchar()!='\n') continue;
	return 0;
}
int main(void)
{
	int len;
	char t[LEN];
	char s[LEN];
	puts("Please enter a string (EOF to quit):");
	while(s_gets(s,LEN)!=NULL)
	{
		puts("Please enter a number for copy (>0):");
		while(scanf("%d",&len)!=1||len<=0)
		{
			eatline();
			printf("Please enter again: ");
		}
		eatline();
		printf("s string:%s\n",s);
		printf("t string:%s\n",mystrncpy(t,s,len));
		printf("You can enter a string again (EOF to quit):\n");
	}
	printf("Done.\n");
	return 0;
}
