#include <stdio.h>
#include <string.h>
char *s_gets(char *st,int n);
#define MAXTITL 41
#define MAXAUTL 31
struct book{
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
}library;
int main(void)
{
	//struct book library;
	puts("Please enter the book title.");
	s_gets(library.title,MAXTITL);
	puts("Now enter the author.");
	s_gets(library.author,MAXAUTL);
	puts("Now enter the value.");
	scanf("%f",&library.value);
	printf("%s by %s: $.2f\n",library.title,library.author,library.value);
	printf("%s: \"%s\" ($.2f)\n",library.title,library.author,library.value);
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
