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
void show_menu(void);

void show_1(void);
St *add_st_1_1(St **head);
void delete_st_1_2(St **head,long long num); 
void show_1_3(St *head);

void show_2(void);
void show_2_1(void);
void show_major_2_1_1(St *head,char *major);
void show_2_2(void);
void add_st_2_2_1(St **tail);

St *sort_sum(St *head);
St *sort_class(St *head);
St *sort_major(St *head);
void sort_st(St *head,char *major);
void show_st(St *head);
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
	head=sort_class(head);
	int a,b,c;
	do
	{
	    show_menu();
	    while(scanf("%d",&a)!=1||a<1||a>4) {puts("Invalid");getchar();}
	    while(a==1)
		{
			show_1();
			while(scanf("%d",&b)!=1||b<1||b>4) {puts("Invalid");getchar();}
			if(b==1) 
			{
				puts("添加前的学生账号:");
				//show_1_3(head);
				show_st(head);
			    head=add_st_1_1(&head);
			    puts("添加后的学生账号:");
				//show_1_3(head);
				show_st(head);
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
		while(a==2)
		{
		    show_2();
		    while(scanf("%d",&b)!=1||b<1||b>4) {puts("Invalid");getchar();}
		    if(b==1)
		    {
		    	show_2_1();
		    	while(scanf("%d",&c)!=1||c<1||c>7) {puts("Invalid");getchar();}
		    	char major[6];
		    	if(c==7) show_st(head);
		    	else
				{ 
				    switch(c)
			        {
				        case 1:strcpy(major,"电科1");break;
				        case 2:strcpy(major,"电科2");break;
				        case 3:strcpy(major,"测控1");break;
				        case 4:strcpy(major,"测控2");break;
			 	        case 5:strcpy(major,"物理");break;
				        case 6:strcpy(major,"应物");break;
				        default:break;
			        }
			        show_major_2_1_1(head,major);
			    }
			}
			if(b==2)
			{
				show_2_2();
				while(scanf("%d",&c)!=1||c<1||c>2) {puts("Invalid");getchar();}
				if(c==2)
				{
				    add_st_2_2_1(&tail);
				    puts("录入后的全年级成绩:");
				    show_st(head);
			    }
			}
			if(b==3)
			{
				puts("请输入你要修改的学生账号:");
				long long num1;
				scanf("%lld",&num1);
				//change_st(head,num1); 
			}
			if(b==4) break;
		}
	}while(a!=4);
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
St *add_st_1_1(St **head)
{
	St *p;
	puts("请输入学生信息(信息间空格隔开):[姓名已脱敏](11位) [姓名已脱敏](最多四个汉字) 专业"); 
	p=(St *)malloc(sizeof(St));
	scanf("%lld %s %s",&p->num,p->name,p->major);
	p->next=*head;
	p=*head;
	return *head; 
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
	    printf("%lld          %-8s   %-5s\n",p->num,p->name,p->major);
	    if(p->next&&strcmp(p->major,p->next->major)!=0) putchar('\n');
	}
}
void show_2(void)
{
	puts("=======================================");
	puts("            老师你好!");
	puts("=======================================");
	puts("1:查询成绩");
	puts("2:录入[姓名已脱敏]");
	puts("3:修改[姓名已脱敏]");
	puts("4:返回上一步");
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
	puts("7:全年级");
	puts("请选择你想查询的专业:");
}
void show_major_2_1_1(St *head,char *major)
{
	St *p,*q,*head1=NULL,*tail1=NULL;
	for(p=head;p!=NULL;p=p->next)
	{
		if(strcmp(p->major,major)==0) 
		{
			q=(St *)malloc(sizeof(St));
			*q=*p;
			if(head1==NULL) head1=tail1=q;
			else 
			{
			    tail1->next=q;
			    tail1=q;
		    }
		}
	}
	tail1->next=NULL;
	show_st(head1);
	for(p=head1;p;p=p->next) free(p);
}
void show_2_2(void)
{
	puts("=======================================");
	puts("            老师你好!");
	puts("=======================================");
	puts("1:录入学生单科成绩");
	puts("2:录入学生全科成绩");
	puts("3:返回上一步");
	puts("请选择你想使用的功能:");
}
void add_st_2_2_1(St **tail)
{
	St *p;
	puts("请输入学生信息(信息间空格隔开):[姓名已脱敏](11位) [姓名已脱敏](最多四个汉字) 专业 C语言 计算物理学 大学物理 原子物理 光学"); 
	p=(St *)malloc(sizeof(St));
	scanf("%s %s %s %d %d %d %d %d",p->num,p->name,p->major,&p->c,&p->p1,&p->p2,&p->p3,&p->o);
	p->sum=p->c+p->p1+p->p2+p->p3+p->o;
	(*tail)->next=p;
	*tail=p;
	(*tail)->next=NULL;
}
St *sort_sum(St *head)
{
    St *p0,*p_0,*p1,*p_1,*p2,*p_2;
    if(head==NULL) {puts("链表为空");return head;}
    p0=p_0=head;
    while(p_0->next!=NULL)
    {
        p1=p0;
		p_1=p2=p_0;
		p_2=p_0->next;
        while(p_2!=NULL)
        {
            if(p_1->sum < p_2->sum)
            {     
			    p1=p2;
				p_1=p_2;
			}
            p2=p_2;
			p_2=p_2->next ;   
        }
        if(p_0!=p_1)
        {
            p1->next=p_1->next;
            p_1->next=p_0;
            if(p_0==head) head=p_1;
            else p0->next =p_1;
            p0=p_1;
        }
        else 
		{
		    p0=p_0 ;
			p_0=p_0->next ;
		}
    }
    return head;
}

St *sort_class(St *head)
{
	head=sort_sum(head);
    St *i=head,*j=head->next;
    int r=1,k=1;
    head->order_class=1;
    for(;j;i=j,j=j->next,k++)
    {
    	if(i->sum==j->sum) i->order_class=j->order_class=r;
    	else 
		{
	        r=k+1;
			j->order_class=k+1;
		}
	}
	sort_st(head,"测控1");
	sort_st(head,"测控2");
	sort_st(head,"电科1");
	sort_st(head,"电科2");
	sort_st(head,"物理");
	sort_st(head,"应物");
    return head;
}

St *sort_major(St *head)
{
	head=sort_sum(head);
    St *i=head,*j=head->next;
    int r=1,k=1;
    head->order_major=1;
    for(;j;i=j,j=j->next,k++)
    {
    	if(i->sum==j->sum) i->order_major=j->order_major=r;
    	else 
		{
	        r=k+1;
			j->order_major=k+1;
		}
	}
    return head;
}

void sort_st(St *head,char *major)
{
	St *p,*q,*head1=NULL,*tail1=NULL;
	for(p=head;p!=NULL;p=p->next)
	{
		if(strcmp(p->major,major)==0) 
		{
			q=(St *)malloc(sizeof(St));
			*q=*p;
			if(head1==NULL) head1=tail1=q;
			else 
			{
			    tail1->next=q;
			    tail1=q;
		    }
		}
	}
	tail1->next=NULL;
	head1=sort_major(head1);
	for(p=head1;p;p=p->next)
	{
		for(q=head;q;q=q->next) 
		if(p->num==q->num)
		{
			q->order_major=p->order_major;
			break;
		} 
	}
	for(p=head1;p!=NULL;p=p->next) free(p);
}

void show_st(St *head)
{
	St *p;
	puts("   [姓名已脱敏]     [姓名已脱敏]     专业    C语言   计算物理学   大学物理   原子物理     光学      总成绩   班级名次   年级名次");
	int arr[6]={0},i=0; 
	for(p=head;p!=NULL;p=p->next)
	{
		i++;
	    printf("%lld %-8s %-5s     %-10d %-10d %-10d %-10d %-10d %-10d %-10d %-10d\n",p->num,p->name,p->major,p->c,p->p1,p->p2,p->p3,p->o,p->sum,p->order_major,p->order_class);
	    arr[0]+=p->c;
	    arr[1]+=p->p1;
	    arr[2]+=p->p2;
	    arr[3]+=p->p3;
	    arr[4]+=p->o;
	    arr[5]+=p->sum;
	}
	printf("%s %-8s %-5s        %-10.3f %-10.3f %-10.3f %-10.3f %-10.3f %-10.3f\n","平均成绩"," "," ",arr[0]*1.0/i,arr[1]*1.0/i,arr[2]*1.0/i,arr[3]*1.0/i,arr[4]*1.0/i,arr[5]*1.0/i);
}
