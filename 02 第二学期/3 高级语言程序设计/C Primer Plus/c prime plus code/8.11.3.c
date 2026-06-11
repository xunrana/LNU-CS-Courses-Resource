/*#include <stdio.h>
//#include <ctype.h>
int main(void)
{
	char ch;
	int cnta=0,cntA=0;
	while((ch=getchar())!=EOF)
	{
		if(ch<='z'&&ch>='a') cnta++;
		else if(ch<='Z'&&ch>='A') cntA++;
	}
	printf("%d %d",cnta,cntA);
	return 0;
}*/
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	char ch;
	int ca=0,cA=0;
	while((ch=getchar())!=EOF)
	{
		if(islower(ch)) ca++;
		else if(isupper(ch)) cA++;
	}
	printf("%d %d",ca,cA);
	return 0;
}
