#include <stdio.h>
int main(void)
{
	double a[8],b[8];
	int i;
	for(i=0;i<8;i++) 
	{
		scanf("%lf",&a[i]);
		b[0]=a[0];
		if(i>0) b[i]=b[i-1]+a[i];
	}
	for(i=0;i<8;i++) printf("a[%d]=%-3.0f",i,a[i]);
    printf("\n");
    for(i=0;i<8;i++) printf("b[%d]=%-3.0f",i,b[i]);
    printf("\n");
    return 0;
}
