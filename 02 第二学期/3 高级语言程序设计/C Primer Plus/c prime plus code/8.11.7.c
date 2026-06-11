#include <stdio.h>
void put(int i);
int main(void)
{
	put(65);
	printf("Enter the char corresponding to the desired pay rate or action:\n");
	char a;
	scanf("%c",&a);
	switch(a)
	{
		case 'a':printf("1)  $8.75/hr\n");break;
		case 'b':printf("2)  $9.33/hr\n");break;
		case 'c':printf("3)  $10.00/hr\n");break;
		case 'd':printf("4)  $11.[[姓名已脱敏]已脱敏]/hr\n");break;
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
