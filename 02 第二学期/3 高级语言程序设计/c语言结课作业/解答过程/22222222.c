#include<stdio.h>
#include<string.h>
int main()
{
    int i,la,lb,j=0;
    char aa[10001],aayi[10001],bb[10001],bbyi[10001];
    la=strlen(gets(aa));       //gets()获得键盘输入的字符串，以换行符结束；strlen()求字符串长度
    for(i=1;i<la;i++)
    {
        if((aa[i]-'0')%2==(aa[i-1]-'0')%2)            //减 ‘0’是为了把ASCII码转换成对应数字
            aayi[j++]= aa[i]>aa[i-1]? aa[i]:aa[i-1];   //三目运算，取二者中大的那个
    }
    lb=strlen(gets(bb));
    j=0;
    for(i=1;i<lb;i++)
    {
        if((bb[i]-'0')%2==(bb[i-1]-'0')%2)            //同上
            bbyi[j++]= bb[i]>bb[i-1]?bb[i]:bb[i-1];   //同上
    }
    if(strcmp(aayi,bbyi)==0)        //strcmp()函数是比较两个字符串是否相等
        printf("%s\n",aayi);
    else
        printf("%s\n%s\n",aayi,bbyi);
}
