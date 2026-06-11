#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct s
{
	long long num;//[姓名已脱敏] 
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
}St;
void show_menu(void)
{
	puts("=======================================");
	puts("            学生信息管理系统");
	puts("=======================================");
	puts("您的身份:");
	puts("1:管理员");
	puts("2:教师");
	puts("3:学生");
	puts("4:退出程序"); 
	puts("请输入您的身份或退出(1-4):");
}

void show_1(void)
{
	puts("=======================================");
	puts("            管理员你好!");
	puts("=======================================");
	puts("1:添加学生账号");
	puts("2:删除学生账号");
	puts("3:查看学生账号(按[姓名已脱敏]升序):");
	puts("4:返回上一步");
	puts("请选择你想使用的功能:");
}

void add_st_1_1(St **tail)
{
	St *p;
	puts("请输入学生信息(信息间空格隔开):[姓名已脱敏](11位) [姓名已脱敏](最多四个汉字) 专业"); 
	p=(St *)malloc(sizeof(St));
	scanf("%lld %s %s",&p->num,p->name,p->major);
	(*tail)->next=p;
	*tail=p;
	(*tail)->next=NULL;
}

void delete_st_1_2(St **head,long long num) 
{
	St *i=*head,*j=(*head)->next;
	if(i->num==num)
	{
		*head=(*head)->next;
		free(i);
	}
	else
	{
		while(j)
		{
			if(j->num==num)
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

void show_1_3(St *head)
{
	St *p;
	int swapped;
    St *ptr1;
    St *lptr=NULL;
    do
    {
        swapped=0;
        ptr1=head;
        while(ptr1->next!=lptr)
        {
            if (ptr1->num > ptr1->next->num)
            {
                St *temp=ptr1->next;
                ptr1->next=temp->next;
                temp->next=ptr1;
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
    for(p=head;p!=NULL;p=p->next) 
	{
	    printf("%lld %-8s %-5s\n",p->num,p->name,p->major);
	    if(p->next&&strcmp(p->major,p->next->major)!=0) putchar('\n');
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
		fscanf(fp,"%lld %s %s %d %d %d %d %d",&p->num,p->name,p->major,&p->c,&p->p1,&p->p2,&p->p3,&p->o);
		p->sum=p->o+p->p1+p->p2+p->p3+p->c;
		p->order_class=0;
		p->order_major=0;
		if(head==NULL) head=tail=p;
		else tail->next=p;
		tail=p;
    }
    tail->next=NULL;
	fclose(fp);
	int a,b,c;
	show_menu();
		while(scanf("%d",&a)!=1||a<1||a>4) {puts("Invalid");getchar();}
		while(a==1)
		{
			show_1();
			while(scanf("%d",&b)!=1||b<1||b>4) {puts("Invalid");getchar();}
			if(b==1) 
			{
				puts("添加前的学生账号:");
				show_1_3(head);
			    add_st_1_1(&tail);
			    puts("添加后的学生账号:");
				show_1_3(head);
			}
			if(b==2)
			{
				puts("删除前的学生账号:");
				show_1_3(head);
				puts("请输入你要删除的学生账号:");
				long long num1;
				scanf("%lld",&num1);
				delete_st_1_2(&head,num1);
				puts("删除后的学生账号:");
				show_1_3(head); 
			}
			if(b==3) show_1_3(head);
			if(b==4) break;
		}
}
