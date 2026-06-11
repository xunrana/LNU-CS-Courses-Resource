#include <stdio.h>
int main(void)
{
	float mbs,mb,t;
	printf("Please enter the mbs and the mb:\n");
	scanf("%f %f",&mbs,&mb);
	t=mb*8/mbs;
	printf("At %.2f megabits per second, a file od %.2f megabytes\n",mbs,mb);
	printf("downloads in %.2f seconds.\n",t);
	return 0;
}
