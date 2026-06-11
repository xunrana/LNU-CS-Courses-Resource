#include <stdio.h>
int fab(int a)
{
	int an=1,an1=1,an2,i;
	if(a==1||a==2) return an;
	else for(i=2;i<a;i++) 
	{
		an2=an+an1;
		an=an1;
		an1=an2;
	}
	return an2;
} 
int main(void)
{
	int i;
	scanf("%d",&i);
	printf("%d",fab(i));
	return 0;
}



/*
int fab(int a)
{
	if(a==1||a==2) return 1;
	else return fab(a-1)+fab(a-2);
}
*/
