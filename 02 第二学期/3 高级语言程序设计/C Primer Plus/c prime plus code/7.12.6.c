#include <stdio.h>
int main(void)
{
	char ch,ch1;
	int cnt=0;
	while((ch=getchar())!='#')
	{
		if(ch1=='e'&&ch=='i') cnt++;
		ch1=ch;
	}
	printf("%d",cnt);
}
