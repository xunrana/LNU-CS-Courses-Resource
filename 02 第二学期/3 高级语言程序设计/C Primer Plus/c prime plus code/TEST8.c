#include <stdio.h>
void show(void)
{
	puts("     主菜单");
	puts("====================");
	puts("1.录入学生信息");
	puts("2.查询学生信息");
	puts("3.修改学生信息");
	puts("4.显示学生信息");
	puts("0.退出");
	puts("====================");
	puts("请输入选择：0~4");
}
int main(void)
{
	int n;
	show();
	char q;
	while(scanf("%d",&n)!=1||n<0||n>4)
	{
		getchar();
		puts("Invalid input");
		show();
		continue;
	}
	do{
    switch(n)
	{
		case 1:puts("录入学生信息");break; 
		case 2:puts("查询学生信息");break;
		case 3:puts("修改学生信息");break; 
		case 4:puts("显示学生信息");break;
		case 0:puts("是否确认退出(q to quit)");q=getchar();if(q!='y') {
			scanf("%d",&n);
			continue;
		}
		default:break;
	}
    }while(q!='y');
}
