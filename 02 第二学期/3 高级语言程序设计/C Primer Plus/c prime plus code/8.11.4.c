#include <stdio.h>
#include <ctype.h>
int main(void)
{
	int cnt=0,a=0;
	char ch,ch1=' ';
	while((ch=getchar())!=EOF)
	{
		if(islower(ch)||isupper(ch)) {cnt++;if(!islower(ch1)&&!isupper(ch1)) a++;
		}
		ch1=ch;
	}
	printf("%d %f",a,(double)cnt/a);
}
