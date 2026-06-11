#include <stdio.h>
int main(void)
{
	char ch;
	int cnt=0;
	while((ch=getchar())!='#')
	{
		cnt++;
		printf("%c %3d   ",ch,ch);
		if(cnt%8==0) printf("\n");
	}
	return 0;
}
