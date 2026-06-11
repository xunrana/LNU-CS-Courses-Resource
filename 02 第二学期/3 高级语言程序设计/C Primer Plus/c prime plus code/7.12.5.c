#include <stdio.h>
int main(void)
{
	char ch;
	int cnt=0;
	while((ch=getchar())!='#')
	{
		switch(ch)
		{
			case '!':putchar('!');putchar('!');cnt++;break;
			case '.':putchar('!');cnt++;break;
			default:putchar(ch);break;
		}
	}
	printf("%d",cnt);
	return 0;
}
