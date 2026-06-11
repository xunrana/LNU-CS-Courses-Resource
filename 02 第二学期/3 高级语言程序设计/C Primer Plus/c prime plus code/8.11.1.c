#include <stdio.h>
int main()
{
	int cnt=0;
	char ch;
	while((ch=getchar())!=EOF) cnt++;
	printf("%d",cnt);
	return 0;
}
