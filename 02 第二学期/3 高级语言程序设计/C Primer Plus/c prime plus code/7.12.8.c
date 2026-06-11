#include <stdio.h>
void put(int i);
int main(void)
{
	put(65);
	printf("Enter the number corresponding to the desired pay rate or action:\n");
	int a;
	scanf("%d",&a);
	switch(a)
	{
		case 1:printf("1)  $8.75/hr\n");break;
		case 2:printf("2)  $9.33/hr\n");break;
		case 3:printf("3)  $10.00/hr\n");break;
		case 4:printf("4)  $11.[[姓名已脱敏]已脱敏]/hr\n");break;
	    default:printf("5)  quit\n");break;
	}
	put(65);
}
void put(int i)
{
	int j;
	for(j=0;j<i;j++) printf("*");
	printf("\n");
}
