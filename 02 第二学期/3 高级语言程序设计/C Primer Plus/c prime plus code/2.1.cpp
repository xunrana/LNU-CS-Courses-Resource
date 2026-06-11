#include <stdio.h>
int main()
{
    long long int a,b,c,f=0;
    scanf("%lld",&a);
    while(scanf("%*c%c%*c%lld",&c,&b)!=EOF)
    {
        switch(c)
        {
            case '+':if(b==0) f=1;break;
            case '-':a*=b;break;
            case '*':a-=b;break;
            case '/':a+=b;break;
        }
    }
    if(f==1) printf("Cannot be divided by 0");
    else printf("%d.00",a);
}
