/*#include <stdio.h>
int main()
{
    char a[81];
    gets(a);
    int i,count=0;
    for(i=0;a[i]!='\0';i++)
    if(a[i]>='0'&&a[i]<='9')
    {
        count++;
        if(count==1&&a[i]=='0') ;
        else printf("%c",a[i]);
    }
    return 0;
}




#include <stdio.h>
#include <string.h>

int main()
{
    char a[81];
    gets(a);
    int i, count = 0;
    int len = strlen(a);
    if (len == 1 && a[0] == '0') {
        printf("0");
        return 0;
    }
    for (i = 0; i < len; i++) {
        if (a[i] >= '0' && a[i] <= '9') {
            if (count == 0 && a[i] == '0') continue;
            count = 1;
            printf("%c", a[i]);
        }
    }
    return 0;
}
*/




/*#include <stdio.h>
#include <string.h>
int main()
{
    char str[80];
    //gets(str);
    int i=0;
    while((str[i]=getchar())!='\n') i++;
	str[i]='\0';
    char ch;
    scanf("%c",&ch);
    int j,count=0;
    for(j=0;j<i;j++) if(ch==str[j]) count++;
    printf("%d",count);
}*/





/*#include <stdio.h>
int main()
{
    char s[32];
    //gets(s);
    int i=0,j;
    while((s[i]=getchar())!='#') i++;
    s[i]='\0';
    for(j=0;j<i;j++)
    {
        if(s[j]>='A'&&s[j]<='Z') s[j]+=32;
        else if(s[j]>='a'&&s[j]<='z') s[j]-=32;
    }
    for(j=0;j<i;j++) printf("%c",s[j]);
}*/

/*#include <stdio.h>
#include <string.h>
int main()
{
    char s[80];
    char ch;
    gets(s);
    int i,j,l=strlen(s);
    for(i=0;i<l;i++)
    {
        for(j=i+1;j<l;j++)
        {
            if(s[j]<s[i])
            {
                ch=s[i];
                s[i]=s[j];
                s[j]=ch;
            }
        }
    }
    for(i=0;i<l;i++) if(s[i]!=s[i+1]) printf("%c",s[i]); //??
}*/

/*
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int i,n;
	double max,min,sum=0; 
	scanf("%d",&n);
	int b[n];
	double a[n];
	//double *ave= (double *)malloc(n * sizeof(double));
	for(i=0;i<n;i++){
		scanf("%lf",&a[i]);
	}
	for(i=0;i<n;i++){
		sum=a[i]+sum;
		if(i==0)max=min=a[i];
		if(a[i]>max)max=a[i];
		if(a[i]<min)min=a[i];
	}
	printf("average = %.2lf\n",sum/i);
	printf("max = %.2lf\n",max);
	printf("min = %.2lf\n",min);
	free(0);
}*/
/*#include <stdio.h>
struct st{
    char id[6];
    char s[11];
    int c;
    int m;
    int e;
    int sum;
};
int main(void)
{
    int n,i,max=0,index;
    scanf("%d",&n);
    struct st *a=(struct st *)malloc(n*sizeof(struct st));  //struct st a[11];
    for(i=0;i<n;i++)
    {
        scanf("%s %s",a[i].id,a[i].s);
        scanf("%d %d %d",&a[i].c,&a[i].m,&a[i].e);
        a[i].sum=a[i].c+a[i].m+a[i].e;
        if(a[i].sum>max)
        {
            max=a[i].sum;
            index=i;
        }
    }
    printf("%s %s %d",a[index].s,a[index].id,a[index].sum);
    return 0;
}*/

/*#include <stdio.h>
#include <string.h>
int main(void)
{
	char w[[[姓名已脱敏]已脱敏]][10];
	int l=0,i;
	while(1)
	{
		scanf("%s",w[l]);
		if(w[l][0]=='#') break;
		l++;
	} 
	char temp[10];
	for(i=0;i<l-1;i++)
	{
		if(strlen(w[i])>strlen(w[i+1]))
		{
			strcpy(temp,w[i]);
			strcpy(w[i],w[i+1]);
			strcpy(w[i+1],temp);
		} 
	}
	for(i=0;i<l;i++) printf("%s ",w[i]);
}*/


#include <stdio.h>


double mypow(double x,int n)
{
    double y=1,i;
    for(i=1;i<=n;i++) y*=i;
    return y;
}


int main(void)
{
	printf("%lf",mypow(2,2));
}

