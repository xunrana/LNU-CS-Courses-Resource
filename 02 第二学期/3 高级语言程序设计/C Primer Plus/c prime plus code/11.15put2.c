#include <stdio.h>
int puts(const char*string)
{
	int count=0;
	while(*string)
	{
		putchar(*string++);
		count++;
	}
	putchar('\n');
	return count;
} 
int main(void)
{
	char a[]="i am definately love you!";
	printf("%d",puts(a));
}
