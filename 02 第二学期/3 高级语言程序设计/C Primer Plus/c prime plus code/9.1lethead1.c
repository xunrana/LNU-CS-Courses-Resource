#include <stdio.h>
#define NAME "GIGATHINK, INC."
#define ADDRESS "101 Megabuck Plaza" 
#define PLACE "Megapolis, CA 94004"
#define WIDTH 40
void starbar(void)
{
	int count;
	for(count=1;count<=WIDTH;count++) putchar('*');
	putchar('\n');
}
int main(void)
{
	starbar();
	printf("%s\n%s\n%s\n",NAME,ADDRESS,PLACE);
	starbar();
	return 0;
}
