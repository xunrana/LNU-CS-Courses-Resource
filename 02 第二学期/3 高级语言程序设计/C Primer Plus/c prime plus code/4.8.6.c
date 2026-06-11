#include <stdio.h>
int main(void)
{
	char fname[10],lname[10];
	printf("Please enter your first name:\n");
	scanf("%s",fname);
	printf("Please enter your last name:\n");
	scanf("%s",lname);
	printf("%s %s\n",fname,lname);
	int a=strlen(fname);
	int b=strlen(lname);
	printf("%*d %*d\n",a,a,b,b);
	printf("%-*d %-*d\n",a,a,b,b);
	return 0;
}
