#include <stdio.h>
int main(void)
{
	const int SIZE=26;
	char a=0;
	for(a=a+'a';a<SIZE+'a';a++)
	printf("%c ",a);
	printf("\n");
	return 0;
}
