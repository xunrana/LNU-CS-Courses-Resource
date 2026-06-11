#include <stdio.h>
//#include <stdbool.h> 
int main(void)
{
	long num;
	long sum=0L;
	_Bool input_is_good;
	//int input_is_good;
	printf("Please enter an integer to be summed ");
	printf("(q to quit): ");
	input_is_good=(scanf("%ld",&num)==1);
	while(input_is_good)
	{
		sum+=num;
		printf("Please enter next integer (q to quit): ");
		input_is_good=(scanf("%ld",&num)==1);
	}
	printf("Those integers sum to %ld.\n",sum);
	return 0;
}
