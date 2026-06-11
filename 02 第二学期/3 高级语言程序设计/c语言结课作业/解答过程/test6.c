#include <stdio.h>
#include <string.h>
void swap(char *a,char *b)
{
    char temp[9];
    memcpy(temp,a,9);
    memcpy(a,b,9);
    memcpy(b,temp,9);
} 
void quick_sort(char a[][9],int low,int high)
{
	if(low>=high) return ;
	int i=low;
	int j=high;
	char *pivot=a[low];
	while(i<j)
	{
		while(strcmp(a[j],pivot)>=0&&j>i) j--;
		while(strcmp(a[i],pivot)<=0&&j>i) i++;
		if(j>i)
		{
			swap(a[i],a[j]);
		}
	}
	swap(a[low],a[i]);
	quick_sort(a,low,i-1);
	quick_sort(a,i+1,high);
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
