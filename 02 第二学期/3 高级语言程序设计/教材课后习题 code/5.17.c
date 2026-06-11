#include <stdio.h>

int main()
{
	int A_battle, B_battle, C_battle;
	//如果A对战的对象从“X”到“Z”
	for (A_battle = 'X'; A_battle <= 'Z'; A_battle++)
	{
		//如果B对战的对象从“X”到“Z”
		for (B_battle = 'X'; B_battle <= 'Z'; B_battle++)
		{
			//如果C对战的对象从“X”到“Z”
			for (C_battle = 'X'; C_battle <= 'Z'; C_battle++)
			{
				//去除限制条件
				if (A_battle == 'X' || C_battle == 'X' || C_battle == 'Z' || B_battle == A_battle || B_battle == C_battle || A_battle == C_battle)
				{
					continue;
				}
				printf("A对%c,B对%c,C对%c", A_battle, B_battle, C_battle);
			}
		}
	}
	return 0;
}

