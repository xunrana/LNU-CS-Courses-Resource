#include <stdio.h>
double f1(int k)
{
	int i;
	double s=0;
	for(i=1;i<=k;i++) s+=i;
	return s;
}
double f2(int k)
{
	int i;
	double s=0;
	for(i=1;i<=k;i++) s+=i*i;
	return s;
}
double f3(int k)
{
	int i;
	double s=0;
	for(i=1;i<=k;i++) s+=1.0/i;
	return s;
}
int main()
{
	int k1,k2,k3;
	scanf("%d %d %d",&k1,&k2,&k3);
	printf("%f\n",f1(k1));
	printf("%f\n",f2(k2));
	printf("%f\n",f3(k3));
	printf("%f",f1(k1)+f2(k2)+f3(k3));
}
