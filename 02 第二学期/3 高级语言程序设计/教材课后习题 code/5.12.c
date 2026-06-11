#include <stdio.h>
int main()
{
	int day=9;
	int prev_day_count;
	int cur_day_count=1;
	while(day>0)
	{
		prev_day_count=(cur_day_count+1)*2;
		cur_day_count=prev_day_count;
		day--;
	}
	printf("total count : %d\n",cur_day_count);
	return 0;
}

