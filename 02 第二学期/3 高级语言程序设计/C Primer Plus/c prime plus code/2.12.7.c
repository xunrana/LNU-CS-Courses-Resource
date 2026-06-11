#include <stdio.h>
void s(void);
int main(void)
{
	s();
	s();
	s();
	printf("\n");
	s();
	s();
	printf("\n");
	s();
	return 0;
}
void s(void)
{
	printf("Smile!");
}
