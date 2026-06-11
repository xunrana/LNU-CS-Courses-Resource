#include <stdio.h>
float getf(float a)
{
	while(scanf("%f",&a)!=1)
	{
		char ch;
		while((ch=getchar())!='\n') putchar(ch);
		printf(" is not a number.\nPlease enter a number, such as 25, -178, or 3: ");
	}
	return (float)a;
}
float start(float a)
{
	printf("Enter first number: ");
	return getf(a);
}
float start1(float a)
{
	printf("Enter second number: ");
	return getf(a);
}
void add(void)
{
	float a,b;
    a=start(a);
    b=start1(b);
    printf("%f+%f=%f\n",a,b,a+b);
}
void sub(void)
{
	float a,b;
    a=start(a);
    b=start1(b);
    printf("%f-%f=%f\n",a,b,a-b);
}
void mul(void)
{
	float a,b;
    a=start(a);
    b=start1(b);
    printf("%f*%f=%f\n",a,b,a*b);
}
void div(void)
{
	float a,b;
    a=start(a);
    b=start1(b);
    printf("%f/%f=%f\n",a,b,a/b);
}
void char1(void)
{
	printf("Enter the operation of your choice:\n");
	printf("a. add          s. subtract\n");
	printf("m. multiply     d. divide\n");
	printf("q. quit\n");
}
int main(void)
{
	char1();
	char ch;
    scanf("%c",&ch);
	switch(ch)
	{
		case 'a':add();break;
		case 's':sub();break;
		case 'm':mul();break;
		case 'd':div();break;
		case 'q':printf("Bye!");break;
	}
}

