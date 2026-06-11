#include <stdio.h>
#include <string.h>
void quick_sort(char t[][9],int low,int high)
{
	int i=low,j=high;
	char temp[9];
	char *p=t[low];
	if(i>=j) return ;
	while(i!=j)
	{
		while(strcmp(t[j],p)>=0&&j>i) j--;
		while(strcmp(t[i],p)<=0&&j>i) i++;
		if(j>i)
		{
			strcpy(temp,t[j]);
			strcpy(t[j],t[i]);
			strcpy(t[i],temp);
		}
	}
	strcpy(temp,t[low]);
	strcpy(t[low],t[i]);
	strcpy(t[i],temp);
	quick_sort(t,low,i-1);
	quick_sort(t,i+1,high);
}
int main()
{
	int n,i,j,k;
	scanf("%d",&n);
	char t[2*n][9];
	while(n--) scanf("%s %*c %s",t[i++],t[i++]);
	quick_sort(t,0,i-1);
    if(strcmp("00:00:00",t[0])!=0) printf("00:00:00 - %s\n",t[0]);
    for(j=1;j<i-1;j+=2)
    if(strcmp(t[j],t[j+1])!=0) printf("%s - %s\n",t[j],t[j+1]);
    if(strcmp(t[i-1],"23:59:59")!=0) printf("%s - 23:59:59\n",t[i-1]);
}























/*          ÕûÊýÉýÐò 
void sort_quick(int a[],int low,int high)
{
	int i=low,j=high,t;
	int tmp=a[low];
	if(i>j) return ;
	while(i!=j)
	{                                               //ÕûÊý½µÐò 
		while(a[j]>=tmp&&j>i) j--;                  // >= change <= 
		while(a[i]<=tmp&&j>i) i++;                  // >= change <= 
		if(j>i)
		{
			t=a[j];
			a[j]=a[i];
			a[i]=t;
		}
	}
	a[low]=a[i];
	a[i]=tmp;
	sort_quick(a,low,i-1);
	sort_quick(a,i+1,high);
}
*/

/*        ×Ö·ûÉýÐò 
void quick_sort(char a[],int low,int high)
{
	int i=low,j=high;
	char t,tmp=a[low];
	if(i>=j) return ;
	while(i!=j)
	{
		while(a[j]>=tmp&&j>i) j--;
		while(a[i]<=tmp&&j>i) i++;
		if(j>i)
		{
			t=a[j];
			a[j]=a[i];
			a[i]=t;
		}
	}
	a[low]=a[i];
	a[i]=tmp;
	quick_sort(a,low,i-1);
	quick_sort(a,i+1,high);
}*/
