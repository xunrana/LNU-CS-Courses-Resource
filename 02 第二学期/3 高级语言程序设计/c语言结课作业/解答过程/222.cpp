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

void show_menu(void);
int input_f(void);
void show_st(St *p1);
void show_1(void);
void add_st(void);
void delete_st(void);
void show_1_3(void);
void show_2(void); 
void show_2_1(void);
void show_major(char *str); 
void bubbleSort(St *h);


int main()
{
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
	
	
	
	
	while(1)
	{
		show_menu();
		while(1)
		{
			a=input_f();
            if(a==1)
	        {
		        show_1();
		        b=input_f();
		        if(b==1)
		        {
			        puts("请输入您要添加的人数:(正整数)");
			        c=input_f();
			        while(c--) add_st();
		        }
		        if(b==2)
		        {     
			        puts("请输入您要删除的人数:(正整数)");
			        c=input_f();
			        while(c--) delete_st(); 
		        }
		        if(b==3) show_1_3();
	        }
	        if(a==2)
	        {
		        show_2();
		        b=input_f();
		        if(b==1)
		        {
			        show_2_1();	
			        char e[6];
			        c=input_f();
			        switch(c)
			        {
				        case 1:strcpy(e,"电科1");break;
				        case 2:strcpy(e,"电科2");break;
				        case 3:strcpy(e,"测控1");break;
				        case 4:strcpy(e,"测控2");break;
			 	        case 5:strcpy(e,"物理");break;
				        case 6:strcpy(e,"应物");break;
				        default:break;
			        }
			        show_major(e);
			        puts("");
			        puts("");
					//show_st(head); 
		        } 
	        }
	        if(a==3)
	        {
	        	
			}
		}
    }
}
void show_menu(void)
{
	puts("=======================================");
	puts("            学生信息管理系统");
	puts("=======================================");
	puts("您的身份:");
	puts("1:管理员");
	puts("2:教师");
	puts("3:学生");
	puts("请输入您的身份(1-3):");
}
void show_st(St *p1)
{
	puts("   [姓名已脱敏]     [姓名已脱敏]     专业     C语言  计算物理学   大学物理  原子物理   光学    总成绩");
	for(p=p1;p!=NULL;p=p->next)
	printf("%s %-8s %-5s %3d %3d %3d %3d %3d %3d\n",p->num,p->name,p->major,p->c,p->p1,p->p2,p->p3,p->o,p->sum);

}






void show_1(void)
{
	puts("=======================================");
	puts("            管理员你好!");
	puts("=======================================");
	puts("1:添加学生账号");
	puts("2:删除学生账号");
	puts("3:查看教师和学生账号列表");
	puts("请选择你想使用的功能:");
}







int input_f(void)
{
	int l;
	while(scanf("%d",&l)!=1) 
	{
	    getchar();
		puts("Invalid input!Please try again.(1-3)");
    }
    return l;
}





void add_st(void)
{
	puts("请输入学生信息(信息间空格隔开):[姓名已脱敏](11位) [姓名已脱敏](最多四个汉字) 专业 C语言 计算物理学 大学物理 原子物理 光学"); 
	p=(St *)malloc(sizeof(St));
	scanf("%s %s %s %d %d %d %d %d",p->num,p->name,p->major,&p->c,&p->p1,&p->p2,&p->p3,&p->o);
	tail->next=p;
	tail=p;
}




void delete_st(void)
{
	puts("请输入你想要删除的学生的11位[姓名已脱敏]:");
	char a[12];
	scanf("%s",a);
	while(strcmp(head->num,a)==0) head=head->next;
	St *i=head,*j=head->next;
    while(j!=NULL)
    {
    	if(strcmp(j->num,a)==0)
		{
		    i->next=j->next;
		    free(j);
	    }
	    else i=j;
	    j=i->next;
	}
}




void show_1_3(void)
{
	puts("学生的账号         学生[姓名已脱敏]");
    for(p=head;p!=NULL;p=p->next) printf("%s        %s\n",p->num,p->name);
}



void show_2(void)
{
	puts("=======================================");
	puts("            老师你好!");
	puts("=======================================");
	puts("1:查询成绩");
	puts("2:录入[姓名已脱敏]");
	puts("3:修改[姓名已脱敏]");
	puts("请选择你想使用的功能:");
}




void show_2_1(void)
{
	puts("=======================================");
	puts("            老师你好!");
	puts("=======================================");
	puts("各班级成绩单(从高到低排序):");
	puts("1:电科1");
	puts("2:电科2");
	puts("3:测控1");
	puts("4:测控2");
	puts("5:物理");
	puts("6:应物");
	puts("请选择你想查询的专业:");
}




void show_major(char *str)
{
	St *head1=NULL,*tail1=NULL;
	for(p=head;p!=NULL;p=p->next)
	{
		if(strcmp(p->major,str)==0) 
		{
			St *q=(St *)malloc(sizeof(St));
			*q=*p;
			if(head1==NULL) 
			{
				head1=tail1=q;
				tail1->next=(St *)malloc(sizeof(St));
			}
			else 
			{
			    tail1->next=q;
			    tail1=q;
		    }
		}
	}
	tail1->next=NULL;
	bubbleSort(head1);
	
}

// 冒泡排序函数
void bubbleSort(St *h) 
{
    if(h==NULL||h->next==NULL) return; // 空链表或只有一个节点，无需排序
    for(St *i=h;i->next!=NULL;i=i->next)
	{
        for(St *j=h->next;j->next!=NULL;j=j->next) 
		{
            if (i->sum < j->sum)
        {
            // 交换节点的连接关系
            St *temp = j->next;
            j->next = i->next;
            i->next = temp;

            if (j == h->next)
            {
                // 更新头节点指针
                h->next = i;
            }
            else
            {
                // 找到前一个节点，更新其 next 指针
                St *prev = h;
                while (prev->next != j)
                {
                    prev = prev->next;
                }
                prev->next = i;
            }
            
            // 更新当前节点指针，保证遍历不会跳过节点
            St *temp2 = i;
            i = j;
            j = temp2;
        }
        }
    }
    
    show_st(h);
}











