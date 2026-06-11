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
    int order_major;//专业名次 
    int order_class; //年级名次 
    struct s*next;//下一个同学 
}St;

void show_menu(void);

void show_1(void);
void add_st_1_1(St **head,char *num);
void delete_st_1_2(St **head,char* num);
void show_1_3(St *head);

 
void show_2(void);
void show_2_1(void);
St *sort_class(St *head);
St *sort_sum(St *head);
void sort_st(St *head,char *major);
St *sort_major(St *head);
void show_major_2_1_1(St *head,char *major);
void show_st(St *head);
void show_2_2(void);
void show_2_2_1(void);
void add_st(St **head,char *num);
void show_2_3(void); 
void change_st(St **head,char* num);
 

void show_3(void);
void show_3_1(void);
St find(St *head,char* num);
int main()
{
    St *p,*head=NULL,*tail=NULL;
    FILE *fp;
    if((fp=fopen("[姓名已脱敏]单","r"))==NULL)
    {
        puts("cannot open file.");
        exit(0);
    }
    char ch[100];
    fgets(ch,100,fp);
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
    tail->next=NULL;
    fclose(fp);
    int a,b,c,f,f1;
    do
    {
        show_menu();
        while(scanf("%d",&a)!=1||a<1||a>4) {puts("Invalid");getchar();}
        while(a==1)
        {
            show_1();
            while(scanf("%d",&b)!=1||b<1||b>4) {puts("Invalid");getchar();}
            f1=0;
            if(b==1) 
            {
                puts("添加前的学生账号:");
                show_1_3(head);
                char num1[12];
                while(1)
				{
					f=1;
					puts("请输入你要添加的学生账号:(输入quit返回上一步)");
				    scanf("%s",num1);
				    if(strcmp(num1,"quit")==0) {f1=1;break;} 
				    for(p=head;p;p=p->next) if(strcmp(p->num,num1)==0) {f=0;break;}
					if(f==0) puts("你输入的学生账号已存在"); 
					else break;
				}
				if(f1==1) continue;
                add_st_1_1(&head,num1);
                puts("添加后的学生账号:");
                show_1_3(head);
            }
            if(b==2)
            {
                puts("删除前的学生账号:");
                show_1_3(head);
                char num1[12];
                while(1)
				{
					f=0;
					puts("请输入你要删除的学生账号:(输入quit返回上一步)");
				    scanf("%s",num1);
				    if(strcmp(num1,"quit")==0) {f1=1;break;} 
				    for(p=head;p;p=p->next) if(strcmp(p->num,num1)==0) {f=1;break;}
				    if(f==1) break;
					else puts("你输入的学生账号不存在"); 
				}
				if(f1==1) continue;
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
            f1=0;
            if(b==1)
            {
                show_2_1();
                head=sort_class(head);
                while(scanf("%d",&c)!=1||c<1||c>8) {puts("Invalid");getchar();}
                char major[6];
                if(c==8) continue;
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
            	char num1[12];
            	while(1)
				{
					f=0;
					puts("请输入你要录入[姓名已脱敏]的账号:(输入quit返回上一步)");
				    scanf("%s",num1);
				    if(strcmp(num1,"quit")==0) {f1=1;break;} 
				    for(p=head;p;p=p->next) if(strcmp(p->num,num1)==0) {f=1;break;}
				    if(f==1) puts("你输入的学生账号已存在成绩");
					else break; 
				}
				if(f1==1) continue;
                add_st(&head,num1);
                puts("录入后的全年级成绩:");
                head=sort_class(head);
                show_st(head);
            }
            if(b==3)
            {
                char num1[12];
                while(1)
				{
					f=0;
					puts("请输入你要修改的学生账号:(输入quit返回上一步)");
				    scanf("%s",num1);
				    if(strcmp(num1,"quit")==0) {f1=1;break;}
				    for(p=head;p;p=p->next) if(strcmp(p->num,num1)==0) {f=1;break;}
				    if(f==1) break;
					else puts("你输入的学生账号不存在"); 
				}
				if(f1==1) continue;
                change_st(&head,num1); 
            }
            if(b==4) break;
        }
        while(a==3)
        {
            head=sort_class(head);
            show_3();
            while(scanf("%d",&b)!=1||b<1||b>3) {puts("Invalid");getchar();}
            f1=0;
            if(b==1)
            {
            	char num1[12];
                while(1)
				{
					f=0;
					puts("请输入你的学生账号:(输入quit返回上一步)");
				    scanf("%s",num1);
				    if(strcmp(num1,"quit")==0) {f1=1;break;}
				    for(p=head;p;p=p->next) if(strcmp(p->num,num1)==0) {f=1;break;}
				    if(f==1) break;
					else puts("你输入的学生账号不存在"); 
				}
				if(f1==1) continue;
                St *temp=(St *)malloc(sizeof(St));
                *temp=find(head,num1);
                show_3_1();
                while(scanf("%d",&c)!=1||c<1||c>6) {puts("Invalid");getchar();}
                printf("%s %s,你好\n",temp->num,temp->name);
                puts("你该科目的成绩是:");
                switch(c)
                {
                    case 1: printf("%d\n",temp->c);break;
                    case 2: printf("%d\n",temp->p1);break;
                    case 3: printf("%d\n",temp->p2);break;
                    case 4: printf("%d\n",temp->p3);break;
                    case 5: printf("%d\n",temp->o);break;
                }
                free(temp);
            }
            if(b==2)
            {
                char num1[12];
                while(1)
				{
					f=0;
					puts("请输入你的学生账号:(输入quit返回上一步)");
				    scanf("%s",num1);
				    if(strcmp(num1,"quit")==0) {f1=1;break;}
				    for(p=head;p;p=p->next) if(strcmp(p->num,num1)==0) {f=1;break;}
				    if(f==1) break;
					else puts("你输入的学生账号不存在"); 
				}
				if(f1==1) continue;
                St *temp;
				temp=(St *)malloc(sizeof(St));
                (*temp)=find(head,num1);
                puts("    [姓名已脱敏]     [姓名已脱敏]      专业   C语言 计算物理 大物 原子物理 光学    总分   班排  年排");
                printf("%-12s %-9s %-6s   %-6d %-6d %-6d %-6d %-6d %-6d %-5d %d\n",temp->num,temp->name,temp->major,temp->c,temp->p1,temp->p2,temp->p3,temp->o,temp->sum,temp->order_major,temp->order_class);
                free(temp);
			}
            if(b==3) break;
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
    puts("1:添加学生账号:");
    puts("2:删除学生账号:");
    puts("3:查看学生账号:");
    puts("4:返回上一步:");
    puts("请选择你想使用的功能:");
}
void add_st_1_1(St **head,char *num)
{
    St *p;
    p=(St *)malloc(sizeof(St));
    puts("请输入学生其他信息(信息间空格隔开):[姓名已脱敏](最多四个汉字) 专业");
	strcpy(p->num,num); 
    scanf("%s %s",p->name,p->major);
    p->next=*head;
    *head=p;
}
void delete_st_1_2(St **head,char *num) 
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
            if((strcmp(j->num,num)==0))
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
    puts("学生的账号         学生[姓名已脱敏]      专业");
    for(p=head;p!=NULL;p=p->next)
    printf("%s %-8s %-5s\n",p->num,p->name,p->major);
    putchar('\n');
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
    puts("8:返回上一步");
    puts("请选择你想查询的专业:");
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
        if(strcmp(p->num,q->num)==0)
        {
            q->order_major=p->order_major;
            break;
        } 
    }
    for(p=head1;p;p=q)
	{ 
	    q=p->next;
        free(p);
    }
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
    for(p=head1;p;p=q)
	{ 
	    q=p->next;
        free(p);
    }
}
void show_st(St *head)
{
    St *p;
    puts("    [姓名已脱敏]     [姓名已脱敏]      专业   C语言 计算物理 大物 原子物理 光学    总分   班排  年排");
    int arr[6]={0},i=0; 
    for(p=head;p!=NULL;p=p->next)
    {
        i++;
        printf("%-12s %-9s %-6s   %-6d %-6d %-6d %-6d %-6d %-6d %-5d %d\n",p->num,p->name,p->major,p->c,p->p1,p->p2,p->p3,p->o,p->sum,p->order_major,p->order_class);
        arr[0]+=p->c;
        arr[1]+=p->p1;
        arr[2]+=p->p2;
        arr[3]+=p->p3;
        arr[4]+=p->o;
        arr[5]+=p->sum;
    }
    printf("%-12s %-9s %-6s   %-6.3f %-6.3f %-6.3f %-6.3f %-6.3f %-6.3f\n","平均分"," "," ",arr[0]*1.0/i,arr[1]*1.0/i,arr[2]*1.0/i,arr[3]*1.0/i,arr[4]*1.0/i,arr[5]*1.0/i);
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
void show_2_2_1(void)
{
    puts("=======================================");
    puts("            老师你好!");
    puts("=======================================");
    puts("1:c语言");
    puts("2:计算机物理学");
    puts("3:大学物理");
    puts("4:原子物理");
    puts("5:光学");
    puts("请输入你想要录入的成绩:");
}
void add_st(St **head,char *num)
{
    St *p;
    puts("请继续输入学生信息(信息间空格隔开):[姓名已脱敏](最多四个汉字) 专业 C语言 计算物理学 大学物理 原子物理 光学"); 
    p=(St *)malloc(sizeof(St));
    strcpy(p->num,num); 
    scanf("%s %s %d %d %d %d %d",p->name,p->major,&p->c,&p->p1,&p->p2,&p->p3,&p->o);
    p->sum=p->c+p->p1+p->p2+p->p3+p->o;
    p->next=*head;
    *head=p;
}
void change_st(St **head,char* num)
{
    St *i;
    for(i=*head;i;i=i->next)
    {
        if((strcmp(i->num,num)==0))
        {
            puts("请输入你想要修改的科目:");
            show_2_3();
            int d; 
            while(scanf("%d",&d)!=1||d<1||d>5)  {puts("Invalid");getchar();}
            switch(d)
            {
                case 1:printf("%s同学c语言的成绩为%d\n请输入%s同学c语言修改后的成绩:\n",i->name,i->c,i->name);break;
                case 2:printf("%s同学计算物理学的成绩为%d\n请输入%s同学计算物理学修改后的成绩:\n",i->name,i->p1,i->name);break;
                case 3:printf("%s同学大学物理的成绩为%d\n请输入%s同学大学物理修改后的成绩:\n",i->name,i->p2,i->name);break;
                case 4:printf("%s同学原子物理的成绩为%d\n请输入%s同学原子物理修改后的成绩:\n",i->name,i->p3,i->name);break;
                case 5:printf("%s同学光学的成绩为%d\n请输入%s同学光学修改后的成绩:\n",i->name,i->o,i->name);break;
            }
            switch(d)
            {
                case 1:scanf("%d",&i->c);break;
                case 2:scanf("%d",&i->p1);break;
                case 3:scanf("%d",&i->p2);break;
                case 4:scanf("%d",&i->p3);break;
                case 5:scanf("%d",&i->o);break;
            }
            puts("修改后该同学的成绩为:");
            i->sum=i->c+i->p1+i->p2+i->p3+i->o;
            *head=sort_class(*head);
            puts("    [姓名已脱敏]     [姓名已脱敏]      专业   C语言 计算物理 大物 原子物理 光学    总分   班排  年排");
            printf("%-12s %-9s %-6s   %-6d %-6d %-6d %-6d %-6d %-6d %-5d %d\n",i->num,i->name,i->major,i->c,i->p1,i->p2,i->p3,i->o,i->sum,i->order_major,i->order_class);
        }
    }
} 
void show_2_3(void)
{
    puts("1:c语言");
    puts("2:计算机物理学");
    puts("3:大学物理");
    puts("4:原子物理");
    puts("5:光学");
}


void show_3(void)
{
    puts("=======================================");
    puts("            学生你好!");
    puts("=======================================");
    puts("1:查询单科成绩");
    puts("2:查询总成绩及排名");
    puts("3:返回上一步"); 
    puts("请输入你想使用的功能:");
}
void show_3_1(void)
{
    puts("=======================================");
    puts("            学生你好!");
    puts("=======================================");
    puts("1:查询C语言成绩");
    puts("2:查询计算物理学成绩");
    puts("3:查询大学物理成绩");
    puts("4:查询原子物理成绩");
    puts("5:查询光学成绩");
    puts("6:返回上一步");
    puts("请选择你想使用的功能:");
}
St find(St *head,char* num)
{
    St *i;
    for(i=head;i;i=i->next)
    if((strcmp(i->num,num)==0)) return *i;
}
