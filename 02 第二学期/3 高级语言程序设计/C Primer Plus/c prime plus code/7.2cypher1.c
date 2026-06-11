#include <stdio.h>
int main(void)
{
	const char SPACE=' ';
	char ch;
	//ch=getchar();
	while((ch=getchar())!='\n')
	{
		if(ch==SPACE) putchar(ch);
		else putchar(ch+1);
		//ch=getchar();
	}
	putchar(ch);
	return 0;
}
