#include <stdio.h>
int main(void)
{
	int a[3][3],min[3],r1[3]={0},r2[3]={0};
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			scanf("%d",&a[i][j]);
			if(j==0) min[i]=a[i][j];
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=1;j<3;j++)
		{
			if(min[i]>a[i][j])
			{
				min[i]=a[i][j];
			    r1[i]=i;
			    r2[i]=j;
		    }
		}
	}
	for(i=1;i<3;i++)
	{
		if(min[0]>min[i])
		{
			min[0]=min[i];
			r1[0]=i;
			r2[0]=r2[i];
		}
	}
	printf("%d %d %d\n",min[0],r1[0]+1,r2[0]+1);
}
