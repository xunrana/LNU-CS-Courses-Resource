#include <stdio.h> 
int main()
{
	int sum=0;
	int a[11]; 
	for(int i=1;i<=10;i++) scanf("%d",&a[i]),sum+=a[i];
	double avg=1.0*sum/10;
	printf("平均值为%.10f\n",avg);
	printf("比平均值大的数有：\n");
	for(int i=1;i<=10;i++) 
	if(a[i]>avg) printf("%d ",a[i]);
	return 0;
}
/*
1 7 5 3 2 8 9 10 6 4


1 7 5 3 2 8 9 10 6 4
平均值为5.5000000000
比平均值小的数有：
1 5 3 2 4
*/
