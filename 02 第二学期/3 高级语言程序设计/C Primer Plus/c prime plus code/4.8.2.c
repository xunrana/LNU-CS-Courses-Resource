#include <stdio.h>
#include <string.h>
int main(void)
{
	char name[10];
	printf("Please enter your name:\n");
	scanf("%s",name);
	printf("\"%s\"\n",name);
	printf("\"%[[姓名已脱敏]已脱敏]s\"\n",name);
	printf("\"%-[[姓名已脱敏]已脱敏]s\"\n",name);
	int a=strlen(name);
	a=a+3;
	printf("\"   %s\"\n",name);
	return 0;
}
