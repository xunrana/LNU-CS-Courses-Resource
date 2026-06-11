#include <stdio.h>
int main(void)
{
	char ch;
	int cnt=0;
	while((ch=getchar())!='#')
	{
		if(ch=='!') {putchar('!');putchar('!');cnt++;
		}
		else if(ch=='.') {putchar('!');cnt++;
		}
		else putchar(ch);
	}
	printf("%d",cnt);
	return 0;
}
