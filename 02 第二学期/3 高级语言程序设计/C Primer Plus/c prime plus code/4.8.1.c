#include <stdio.h>
int main()
{
	printf("Please enter your first name:\n");
	char a[10],b[10];
	scanf("%s",a);
	printf("Please enter your last name:\n");
	scanf("%s",b);
	printf("%s,%s",b,a);
	return 0;
} 
