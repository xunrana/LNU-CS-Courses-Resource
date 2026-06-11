/*#include <stdio.h>
int main(void)
{
	char ch;
	int j,o,sj=0,so=0;
	j=o=0;
	while((ch=getchar())!='0')
	{
		ch=ch-48;
		if(ch%2==0) {o++;so=so+ch;}
		else {j++;sj=sj+ch;} 
	}
	double aj,ao;
	aj=(double)sj/j;
	ao=(double)so/o;
	printf("%d %f %d %f",o,ao,j,aj);
	return 0;
}*/
#include <stdio.h>
int main(void)
{
	int a;
	int j=0,o=0,sj=0,so=0;
	while(scanf("%d",&a)&&a!=0)
	{
		if(a%2==0){o++;so+=a;
		} 
		else {j++;sj+=a;
		}
	}
	double aj=(double)sj/j;
	double ao=(double)so/o;
	printf("%d %f %d %f",o,ao,j,aj);
	return 0;
}
