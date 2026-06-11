/*#include <stdio.h>
#include <limits.h>
int main(void)
{
	printf(" charmin=%d\n charmax=%d\n charbit=%d\n",CHAR_MIN,CHAR_MAX,CHAR_BIT);
	printf(" signedcharmin=%d\n signedcharmax=%d\n",CHAR_MIN,SCHAR_MAX);
	printf(" shortmin=%d\n shortmax=%d\n",SHRT_MIN,SHRT_MAX);
	printf(" unsignedcharmax=%d\n unsignedshortmax=%d\n",UCHAR_MAX,USHRT_MAX);
	printf(" intmin=%d\n intmax=%d\n",INT_MIN,INT_MAX);
	printf(" unsignedintmax=%d\n unsignedshortmax=%d\n",UINT_MAX,USHRT_MAX);
	printf(" longmin=%d\n longmax=%d\n",LONG_MIN,LONG_MAX);
	printf(" longlongmin=%d\n longlongmax=%d\n",LLONG_MIN,LLONG_MAX);
	printf(" unsignedlonglongmax=%d\n",ULLONG_MAX);
    return 0;
}*/

#include <stdio.h>
int main(void)
{
	double a[7],b[7],sum2;
	int i;
	for(i=0;i<7;i++) scanf("%lf",&a[i]);
	puts("end");
	for(i=0;i<7;i++)
	{
		scanf("%lf",&b[i]);
		sum2+=b[i];		
	} 
	double sum=0;
	for(i=0;i<7;i++) sum+=a[i]*b[i];
	printf("%f\n",sum/sum2);
}
