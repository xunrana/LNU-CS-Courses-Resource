#include <stdio.h>
int main()
{
    int a[1001]={0};
    int i,n,j;
    scanf("%d",&n);
    int b[n];
    for(i=0;i<n;i++) scanf("%d",&b[i]);
    j=0;
    while(j<n)
    {
        i=0;
        if(b[j]+a[i]<=100)
        {
            a[i]+=b[j];
            
        }
    }
}
