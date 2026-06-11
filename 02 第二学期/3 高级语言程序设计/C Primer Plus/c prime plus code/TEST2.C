#include <stdio.h>
int main()
{
	int n,i,j;
	char a[10][10];
	scanf("%d",&n);
	for(i=0;i<2*n;i++) for(j=0;j<2*n;j++) scanf(" %c",&a[i][j]); 
	int i1,k,count=0,c=0,x1,y1,x2,y2;
	scanf("%d",&k);
	for(i1=0;i1<k;i1++)
	{
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		if(a[x1-1][y1-1]==a[x2-1][y2-1]&&a[x1-1][y1-1]!='*')
		{
			c++;
			a[x1-1][y1-1]='*';
			c++;
			a[x2-1][y2-1]='*';
			if(c==4*n*n) {printf("Congratulations!");return 0;}
			else for(i=0;i<2*n;i++)
			{
				printf("%c",a[i][0]);
				for(j=1;j<2*n;j++) printf(" %c",a[i][j]);
				putchar('\n');
			}
		}
		else 
		{
			count++;
			puts("Uh-oh");
			if(count==3) {printf("Game Over");return 0;}
		}
	}
}
