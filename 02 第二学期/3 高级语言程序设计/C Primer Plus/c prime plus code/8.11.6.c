#include <stdio.h>
char get_first(void)
{
	int ch;
	ch=getchar();
	while(ch==' ') ch=getchar();
	while(getchar()!='\n') continue;
	return ch;
}
int main(void)
{
	putchar(get_first());
	return 0;
}
