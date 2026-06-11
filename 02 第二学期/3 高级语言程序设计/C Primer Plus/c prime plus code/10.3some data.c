#include <stdio.h>
#define SIZE 4
int main(void)
{
	int no_date[SIZE]={1492,1066};
	int i;
	printf("%2s%14s\n","i","no_date[i]");
	for(i=0;i<SIZE;i++)
	printf("%2d%14d\n",i,no_date[i]);
	return 0;
}
