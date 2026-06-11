#include <stdio.h>
#include <stdlib.h>
struct s{
    char num[11];
    char name[8];
    char major[5];
    int c;
    int p1;//计算物理
    int p2;//大学物理
    int p3;//原子物理
    int o;//optics 光学
    //St *next;
}b;
int main()
{
    FILE *fp;
    if((fp=fopen("[姓名已脱敏]单","r"))==NULL)
    {
        puts("cannot open file.");
        exit(0);
    }
    char a[100];
    fgets(a,100,fp);
    fscanf(fp,"%s %s %s %d %d %d %d %d",b.num,b.name,b.major,&b.c,&b.p1,&b.p2,&b.p3,&b.o);
    fclose(fp);
    printf("%s %s %s %d %d %d %d %d\n",b.num,b.name,b.major,b.c,b.p1,b.p2,b.p3,b.o);
}

