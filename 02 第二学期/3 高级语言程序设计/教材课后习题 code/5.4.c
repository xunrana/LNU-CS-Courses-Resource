#include <stdio.h>
int main()
{
	char ch;
	int d,l,b,o;
	d=l=b=o=0;
	while((ch=getchar())!='\n')
	{
		if(ch>='0'&&ch<='9') d++;
		else if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') l++;
		else if(ch==' ') b++;
		else o++; //º¬tab¼ü 
	}
	printf("%d\n%d\n%d\n%d",l,b,d,o);
}
