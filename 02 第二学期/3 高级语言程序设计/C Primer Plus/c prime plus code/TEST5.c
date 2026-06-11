#include<stdio.h>
struct STU
{
    char name[11];
    int bir;
    char tel[18];
};
int main()
{
    int n,i,j;
    scanf("%d",&n);
    struct STU a[n],t;
    for(i=0;i<n;i++)
    {
        scanf("%s%d%s",a[i].name,&a[i].bir,a[i].tel);
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(a[j].bir>a[j+1].bir)
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        printf("%s %d %s\n",a[i].name,a[i].bir,a[i].tel);
    }
    return 0;
}
