#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct s
{
	char num[12];//[姓名已脱敏] 
	int n;// =atoll(num)
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
void show_1(void);
void add_st_acc(St **tail);
void show_1_3(St *head);
void delete_st(St **head,char *num); 
void show_2(void);
void show_2_1(void);
void show_major(St *head,char *major);
void order_st_m(St* head);
void show_st(St *head);
void order_st_c(St** head);
void add_st(St **tail);
void change_st(St *head,char *num);
void show_2_2(void); 
void show_2_3(void); 
void show_3(void);
void show_3_1(void);
St find(St *head,char *num);
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
    tail->next=NULL;
	fclose(fp);
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
				show_1_3(head);
			    add_st_acc(&tail);
			    puts("添加后的学生账号:");
				show_1_3(head);
			}
			if(b==2)
			{
				puts("删除前的学生账号:");
				show_1_3(head);
				puts("请输入你要删除的学生账号:");
				getchar(); 
				char num[12];
				gets(num);
				delete_st(&head,num);
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
		    	order_st_c(&head);
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
			        show_major(head,major);
			    }
			}
			if(b==2)
			{
				show_2_2();
				while(scanf("%d",&c)!=1||c<1||c>2) {puts("Invalid");getchar();}
				if(c==2)
				{
				    add_st(&tail);
				    puts("录入后的全年级成绩:");
				    show_st(head);
			    }
			}
			if(b==3)
			{
				puts("请输入你要修改的学生账号:");
				getchar();
				char num[12];
				scanf("%s",num);
				change_st(head,num); 
			}
			if(b==4) break;
		}
		while(a==3)
		{
			show_3();
			while(scanf("%d",&b)!=1||b<1||b>3) {puts("Invalid");getchar();}
			if(b==1)
			{
				puts("请输入您的[姓名已脱敏]:");
			    char num[12];
			    scanf("%s",num);
			    St *temp=(St *)malloc(sizeof(St));
				*temp=find(head,num);
				show_3_1();
				while(scanf("%d",&c)!=1||c<1||c>5) {puts("Invalid");getchar();}
				printf("%s %s,你好\n",temp->num,temp->name);
				puts("你该科目的成绩是:");
				switch(c)
				{
					case 1:	printf("%d\n",temp->c);break;
				    case 2:	printf("%d\n",temp->p1);break;
				    case 3:	printf("%d\n",temp->p2);break;
				    case 4:	printf("%d\n",temp->p3);break;
				    case 5:	printf("%d\n",temp->o);break;
				}
				free(temp);
			}
			if(b==2)
			{
				puts("请输入您的[姓名已脱敏]:");
			    char num[12];
			    scanf("%s",num);
			    St *temp=(St *)malloc(sizeof(St));
				*temp=find(head,num);
				puts("   [姓名已脱敏]     [姓名已脱敏]     专业  C语言  计算物理学   大学物理  原子物理     光学    总成绩   专业名次  年纪名次");
				printf("%s %-8s %-5s %-10d %-10d %-10d %-10d %-10d %-10d %-10d %-10d\n",temp->num,temp->name,temp->major,temp->c,temp->p1,temp->p2,temp->p3,temp->o,temp->sum,temp->order_major,temp->order_class);
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
	puts("1:添加学生账号");
	puts("2:删除学生账号");
	puts("3:查看学生账号(按[姓名已脱敏]升序):");
	puts("4:返回上一步");
	puts("请选择你想使用的功能:");
}

void add_st_acc(St **tail)
{
	St *p;
	puts("请输入学生信息(信息间空格隔开):[姓名已脱敏](11位) [姓名已脱敏](最多四个汉字) 专业"); 
	p=(St *)malloc(sizeof(St));
	scanf("%s %s %s",p->num,p->name,p->major);
	(*tail)->next=p;
	*tail=p;
	(*tail)->next=NULL;
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

void show_1_3(St *head)
{
	St *p;
	for(p=head;p!=NULL;p=p->next) p->n=atoll(p->num)%100000000;
	int swapped;
    St *ptr1;
    St *lptr=NULL;
    do
    {
        swapped=0;
        ptr1=head;
        while(ptr1->next!=lptr)
        {
            if (ptr1->n > ptr1->next->n)
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
	    printf("%s %-8s %-5s\n",p->num,p->name,p->major);
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


void show_major(St *head,char *major)
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
	order_st_m(head1);
	for(p=head1;p!=NULL;p=p->next) free(p);
}



void order_st_m(St* head)
{
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
            if (ptr1->sum < ptr1->next->sum)
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
	show_st(head);
}


void show_st(St *head)
{
	St *p;
	puts("   [姓名已脱敏]     [姓名已脱敏]     专业  C语言  计算物理学   大学物理  原子物理     光学    总成绩   班级名次  年级名次");
	int arr[6]={0},i=0; 
	for(p=head;p!=NULL;p=p->next)
	{
		i++;
	    printf("%s %-8s %-5s %-10d %-10d %-10d %-10d %-10d %-10d %-10d %-10d\n",p->num,p->name,p->major,p->c,p->p1,p->p2,p->p3,p->o,p->sum,p->order_major,p->order_class);
	    arr[0]+=p->c;
	    arr[1]+=p->p1;
	    arr[2]+=p->p2;
	    arr[3]+=p->p3;
	    arr[4]+=p->o;
	    arr[5]+=p->sum;
	}
	printf("%s %-8s %-5s    %-10.3f %-10.3f %-10.3f %-10.3f %-10.3f %-10.3f\n","平均成绩"," "," ",arr[0]*1.0/i,arr[1]*1.0/i,arr[2]*1.0/i,arr[3]*1.0/i,arr[4]*1.0/i,arr[5]*1.0/i);
}

void order_st_c(St** head)
{
    int swapped;
    St* ptr1;
    St* lptr = NULL;
    St* temp_head = *head;  // 临时指针用于跟踪新的头节点

    do
    {
        swapped = 0;
        ptr1 = temp_head;
        while (ptr1->next != lptr)
        {
            if (ptr1->sum < ptr1->next->sum)
            {
                St* temp = ptr1->next;
                ptr1->next = temp->next;
                temp->next = ptr1;

                if (ptr1 == temp_head)
                    temp_head = temp;
                else
                {
                    St* prev = temp_head;
                    while (prev->next != ptr1)
                        prev = prev->next;
                    prev->next = temp;
                }
                swapped = 1;
            }
            else
                ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped != 0);
    *head = temp_head;  // 更新头指针为新的头节点
    St *i=*head,*j=(*head)->next;
    int r=1,k=1;
    (*head)->order_class=1;
    for(;j;i=j,j=j->next,k++)
    {
    	if(i->sum==j->sum) i->order_class=j->order_class=r;
    	else 
		{
	        r=k+1;
			j->order_class=k+1;
		}
	}
	/*show_major(*head,"测控1"); 
	show_major(*head,"测控2"); 
	show_major(*head,"电科1"); 
	show_major(*head,"电科2"); 
	show_major(*head,"物理"); 
	show_major(*head,"应物"); */
}
/*
    
}*/

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

void add_st(St **tail)
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


void change_st(St *head,char *num)
{
	St *i;
	for(i=head;i;i=i->next)
	{
		if(strcmp(i->num,num)==0)
		{
			puts("请输入你想要修改的科目");
			show_2_3();
			int d; 
			while(scanf("%d",&d)!=1||d<1||d>5)  {puts("Invalid");getchar();}
			puts("请输入该科目的成绩:");
			switch(d){
				case 1:scanf("%d",&i->c);break;
				case 2:scanf("%d",&i->p1);break;
				case 3:scanf("%d",&i->p2);break;
				case 4:scanf("%d",&i->p3);break;
				case 5:scanf("%d",&i->o);break;
			}
            puts("修改后该同学的成绩为:");
            i->sum=i->c+i->p1+i->p2+i->p3+i->o;
            puts("   [姓名已脱敏]     [姓名已脱敏]     专业  C语言  计算物理学   大学物理  原子物理     光学      总成绩  ");
            printf("%s %-8s %-5s %-10d %-10d %-10d %-10d %-10d %-10d\n",i->num,i->name,i->major,i->c,i->p1,i->p2,i->p3,i->o,i->sum);
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

St find(St *head,char *num)
{
	St *i;
	for(i=head;i;i=i->next)
	if(strcmp(i->num,num)==0) return *i;
}
