#include <stdio.h>
void chline(char ch,int i,int j)
{
	int i1,j1;
	for(i1=0;i1<j;i1++)
	{
		for(j1=0;j1<i;j1++) putchar(ch);
		putchar('\n');
	}
}
int main(void)
{
	char ch;
	ch=getchar();
	int i,j;
	scanf("%d %d",&i,&j);
	chline(ch,i,j);
}
