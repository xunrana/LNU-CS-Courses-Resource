#include <stdio.h>
int main(void)
{
	char name[10];
	//float a;
	int a;
	printf("Please enter your name:\n");
	scanf("%s",name);
	printf("Please enter your height(cm):\n");
	//scanf("%f",&a);
	//printf("%s, you are %.3f feet tall.\n",name,a);
	scanf("%d",&a);
	double b=a/100.0;
	printf("%s, you are %.2f m.\n",name,b);
	return 0;
}
