#include <stdio.h>
#define SIZE 4
int main(void)
{
	short dates[SIZE];
	double bills[SIZE];
	int *pti=dates;
	double *ptf=bills;
	int index;
	printf("%23s %15s\n","short","double");
	for(index=0;index<SIZE;index++)
	{
		printf("pointers + %d: %10p %10p\n",index,index+pti,index+ptf);
	}
	return 0;
}
