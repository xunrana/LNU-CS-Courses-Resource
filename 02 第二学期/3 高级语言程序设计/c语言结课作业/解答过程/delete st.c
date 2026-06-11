#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s
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
	int order_major;
	int order_class; 
    struct s*next;//下一个同学 
}St;
void show_st(St *head)
{
	St *p;
	puts("   [姓名已脱敏]     [姓名已脱敏]     专业     C语言  计算物理学   大学物理  原子物理   光学    总成绩   班级名次  年级名次");
	for(p=head;p!=NULL;p=p->next)
	printf("%s %-8s %-5s %3d %3d %3d %3d %3d %3d\n",p->num,p->name,p->major,p->c,p->p1,p->p2,p->p3,p->o,p->sum);
}

void delete_st(St **head,char *num) 
{
	St *i=*head,*j=(*head)->next;
	if(strcmp(i->num,num)==0)
	{
		*head=(*head)->next;
		free(i);
	}
	else
	{
		while(j)
		{
			if(strcmp(j->num,num)==0)
			{
				i->next=j->next;
				free(j);
				break;
			}
			else i=j;
			j=j->next;
		}
	}
}


int main()
{
	St *p,*head=NULL,*tail=NULL;
	FILE *fp;
	if((fp=fopen("[姓名已脱敏]单","r"))==NULL)
	{
		puts("cannot open file.");
		exit(0);
	}
    fscanf(fp,"%*[^\n]"); // 读取并丢弃第一行的内容
    fscanf(fp,"%*c");     // 读取并丢弃换行符
	while(!feof(fp))
	{
		p=(St *)malloc(sizeof(St));
		fscanf(fp,"%s %s %s %d %d %d %d %d",p->num,p->name,p->major,&p->c,&p->p1,&p->p2,&p->p3,&p->o);
		p->sum=p->o+p->p1+p->p2+p->p3+p->c;
		if(head==NULL) head=tail=p;
		else tail->next=p;
		tail=p;
    }
	fclose(fp);
	char num[12];
	puts("输入[姓名已脱敏]:");
	gets(num);
	delete_st(&head,num);
	show_st(head);
}
