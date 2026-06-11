#include <stdio.h>
int main(void)
{
	char ch;
	int b,n,o;
	b=n=o=0;
	while((ch=getchar())!='#')
	{
		if(ch==' ') b++;
		else if(ch=='\n') n++;
		else o++;
	}
	printf("%d %d %d",b,n,o);
	return 0;
}
