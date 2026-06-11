#include <stdio.h>
void one_three(void);
void two(void);
int main(void)
{
	printf("starting now:\n");n
	one_three();
	printf("done!");
}
void two(void)
{
	printf("two\n");
}
void one_three(void)
{
	printf("one\n");
	two();
	printf("three\n");
}
