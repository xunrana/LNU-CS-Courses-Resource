#include <stdio.h>
int main(void)
{
	char ch,ch1,ch2;
	scanf("%c",&ch);
	int i1=ch-'A'+1,i,j,m,n;
	for(i=0;i<i1;i++)
	{
		ch1='A';
		//ch2=ch;
		for(j=0;j<i1-1-i;j++) printf(" ");
		for(m=0;m<=i;m++) printf("%c",ch1++);
		for(n=m-1,ch1=ch1-2;n>0;n--) printf("%c",ch1--);
		//for(n;n>=0;n--) printf(" ");
		printf("\n");
	}
	return 0;
}      

/*#include <stdio.h>
int main(void)
{
	char c,k,m,i,j;
	printf("please enter a big char:\n");
	scanf("%c",&c);
	for(i='A';i<=c;i++)
	{
		for(j=c-1;j>=i;j--) printf(" ");
		for(k='A';k<=i;k++) printf("%c",k);
		for(m='A',k=k-2;m<i;m++,k--) printf("%c",k);
		printf("\n");
	}
	return 0;
}*/

