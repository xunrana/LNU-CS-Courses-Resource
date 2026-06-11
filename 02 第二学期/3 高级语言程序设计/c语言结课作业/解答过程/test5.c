#include <stdio.h>
void quick_sort(int a[],int low,int high)
{
    int i=low,j=high;
    int t,tmp=a[low];
    if(i>j) return ;
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
}
int main()
{
    int a[1001];
    int n,k,i=0;
    scanf("%d %d",&n,&k);
    while(n--) scanf("%d",&a[i++]);
    quick_sort(a,0,i-1);
    printf("%d",a[--k]);
}
