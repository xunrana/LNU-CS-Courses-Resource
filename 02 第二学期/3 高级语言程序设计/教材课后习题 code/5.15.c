#include<stdio.h>
#include<math.h>

int main()
{
	double left = -10, right = 10, mid;
	double temp = 10;
	while (fabs(temp) > 1e-5)
	{
		mid = (left + right) / 2;
		//((2x - 4)*x + 3) * x - 6 ==> 2x^3 - 4x^2 + 3x -6
		temp = ((2 * mid - 4) * mid + 3) * mid - 6;

		if (temp > 0)
		{
			right = mid;
		}
		else if (temp < 0)
		{
			left = mid;
		}
	}
	printf("在(-10,10)的根为：%lf", mid);
	return 0;
}

