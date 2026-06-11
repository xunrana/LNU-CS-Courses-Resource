#include <stdio.h>
int main(void)
{
	char a[50];
	scanf("%s",a); //空格就结束 
	//gets(a);    '\0' 结束 
	int length=strlen(a);
	for(;length>=0;length--) printf("%c",a[length]);
}
