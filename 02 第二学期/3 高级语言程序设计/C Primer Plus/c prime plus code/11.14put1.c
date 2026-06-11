#include <stdio.h>
void put1(const char*string)
{
	while(*string!='\0')
	putchar(*string++);
}
int main(void)
{
	char a[]="i am longing for you!";
	put1(a);
	return 0;
}
