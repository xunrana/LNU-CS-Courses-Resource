#include <stdio.h>
#include <string.h>
int main()
{
	char strings[7]="China";
	putchar(strings[6]);
	int i;
	for(i=0;strings[i]!='\0';i++) putchar(strings[i]+4);
	putchar('\n');
	printf("%s\n",strings);
	printf("%d",strlen(strings));
}
