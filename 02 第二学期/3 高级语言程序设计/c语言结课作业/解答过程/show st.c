#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s
{
	char num[12];//[姓名已脱敏] 
	int n; //=atoi(num) 
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
	puts("   [姓名已脱敏]     [姓名已脱敏]     专业     C语言  计算物理学   大学物理  原子物理   光学    总成绩   专业名次  年级名次");
	for(p=head;p!=NULL;p=p->next)
	printf("%s %-8s %-5s %3d %3d %3d %3d %3d %3d %3d %3d\n",p->num,p->name,p->major,p->c,p->p1,p->p2,p->p3,p->o,p->sum,p->order_major,p->order_class);
}


void show_1_3(St *head)
{
	St *p;
	for(p=head;p!=NULL;p=p->next) p->n=atoll(p->num)%100000000;
	//for(p=head;p!=NULL;p=p->next) printf("%s %-8s %-5s %d\n",p->num,p->name,p->major,p->n);
	//scanf("%*d %*d %*d");
	
	int swapped;
    St *ptr1;
    St *lptr=NULL;
    do
    {
        swapped=0;
        ptr1=head;
        while(ptr1->next!=lptr)
        {
            //按总成绩降序排序 
            if (ptr1->n > ptr1->next->n)
            {
                // 交换节点
                St *temp=ptr1->next;
                ptr1->next=temp->next;
                temp->next=ptr1;
                // 更新头节点
                if(ptr1==head) head=temp;
                else
                {
                    St *prev=head;
                    while(prev->next!=ptr1) prev=prev->next;
                    prev->next=temp;
                }
                swapped=1;
            }
            else ptr1=ptr1->next;
        }
        lptr=ptr1;
    }while(swapped!=0);
	
	puts("学生的账号         学生[姓名已脱敏]      专业");
    for(p=head;p!=NULL;p=p->next) printf("%s %-8s %-5s\n",p->num,p->name,p->major);
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
		p->order_class=0;
		p->order_major=0;
		if(head==NULL) head=tail=p;
		else tail->next=p;
		tail=p;
    }
	fclose(fp);
	show_1_3(head);
}
