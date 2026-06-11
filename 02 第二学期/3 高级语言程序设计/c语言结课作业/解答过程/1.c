#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct s
{
    char num[12];//[姓名已脱敏]
    char name[9];//学生[姓名已脱敏] 
    char major[6];//学生专业 
    int c;//c语言 
    int p1;//计算物理
    int p2;//大学物理
    int p3;//原子物理
    int o;//optics 光学
    int sum;//总成绩
    int order_major;//专业名次 
    int order_class; //年级名次 
    struct s*next;//下一个同学 
}a[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬0];
int main()
{
	FILE *fp;
	fp=fopen("[姓名已脱敏]单","r");
	if(fp==NULL)
	{
		puts("cannot open file.");
		exit(0);
	}
	char ch[100];
	fgets(ch,100,fp);
	int i=0,j;
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %d %d %d %d %d",a[i].num,a[i].name,a[i].major,&a[i].c,&a[i].p1,&a[i].p2,&a[i].p3,&a[i].o);
		i++;
	}
	fclose(fp);
	j=i; 
	for(i=0;i<j;i++)
	{
		printf("%s %s %s %d %d %d %d %d\n",a[i].num,a[i].name,a[i].major,a[i].c,a[i].p1,a[i].p2,a[i].p3,a[i].o);
	}
}







