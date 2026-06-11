#include <stdio.h>

int main()
{
	int cur_row, space_count, start_count;
	//输出前4行内容
	for (cur_row = 0; cur_row < 4; cur_row++)
	{
		//计算当前行空格数量，并且进行打印
		for (space_count = 3 - cur_row; space_count > 0; space_count--)
		{
			printf(" ");
		}
		//计算当前行*数量，并且进行打印
		for (start_count = 2 * cur_row + 1; start_count > 0; start_count--)
		{
			printf("*");
		}
		printf("\n") ;
	}
	//输出后三行
	for (cur_row = 0; cur_row < 3; cur_row++)
	{
		for (space_count = cur_row + 1; space_count > 0; space_count--)
		{
			printf(" ");
		}

		for (start_count = 7 - 2 * (cur_row + 1); start_count > 0; start_count--)
		{
			printf("*");
		}
		printf("\n");
	}
	return 0;
}

