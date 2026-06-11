#include <stdio.h>
void jolly(void);
void deny(void);
int main()
{
	jolly();
	jolly();
	deny();
	return 0;
}
void jolly(void)
{
	printf("For he is a jolly good fellow!\n");
}
void deny(void)
{
	printf("Which nobody can deny!");
}
