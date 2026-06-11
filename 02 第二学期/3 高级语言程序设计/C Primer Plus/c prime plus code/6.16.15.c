#include <stdio.h>
int main(void)
{
	char a[256];
	//scanf("%s",a);
	gets(a);
	int i;
	for(i=strlen(a);i>=0;i--) printf("%c",a[i]);
}
