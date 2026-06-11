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
St find(St *head,long long num)
{
	St *i;
	for(i=head;i;i=i->next)
	if(i->num==num) return *i;
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
	    while(a==2)
		{
		    show_2();
		    while(scanf("%d",&b)!=1||b<1||b>4) {puts("Invalid");getchar();}
		    /*if(b==1)
		    {
		    	show_2_1();
		    	head=sort_class(head);
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
			}*/
			if(b==2)
			{
				show_2_2();
				while(scanf("%d",&c)!=1||c<1||c>2) {puts("Invalid");getchar();}
				if(c==1)
				{
					show_2_2_1();
					int d;
					long long temp;
					while(scanf("%d",&d)!=1||d<1||d>5) {puts("Invalid");getchar();}
					puts("请输入你想录入的学生[姓名已脱敏]:");
					scanf("%lld",&temp);
					puts("请输入该同学该科目的成绩:"); 
					St *t=(St *)malloc(sizeof(St));
					*t=find(head,temp); 
					switch(d)
					{
						case 1:scanf("%d",&t->c);break;
						case 2:scanf("%d",&t->p1);break;
						case 3:scanf("%d",&t->p2);break;
						case 4:scanf("%d",&t->p3);break;
						case 5:scanf("%d",&t->o);break;	
					}
					puts("录入后该学生的成绩:");
			    	printf("%lld %-8s %-5s     %-10d %-10d %-10d %-10d %-10d %-10d %-10d %-10d\n",t->num,t->name,t->major,t->c,t->p1,t->p2,t->p3,t->o,t->sum,t->order_major,t->order_class);
				    free(t);
				}
				/*if(c==2)
				{
				    add_st(&tail);
				    puts("录入后的全年级成绩:");
				    head=sort_class(head);
				    show_st(head);
			    }*/
			}
			/*if(b==3)
			{
				puts("请输入你要修改的学生账号:");
				long long num1;
				scanf("%lld",&num1);
				change_st(head,num1); 
			}*/
			if(b==4) break;
		}
}
