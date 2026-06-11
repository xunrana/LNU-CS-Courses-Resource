/*
[姓名已脱敏]管理 
基本要求：
定义学生（student）类，其中至少包括[姓名已脱敏]、性别、[姓名已脱敏]、班级和四门功课的成绩。
功能要求：
 1、设计菜单实现功能选择； 
 2、输入功能：输入学生信息，并保存到文件中；
 3、计算每个学生的总分与平均分并排序
 4、能根据[姓名已脱敏]修改学生信息
 5、能根据[姓名已脱敏]删除学生信息
 6、查询功能：
 1）能够根据[姓名已脱敏]查询学生信息；
 2）能够根据[姓名已脱敏]、班级查询学生信息
 3）统计[姓名已脱敏]，按照班级和科目计算平均分。
 */
 /*   students中数据 
 [姓名已脱敏]   	性别	   [姓名已脱敏]	        专业	语文	数学	英语	c++                 
张江浩	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081005101	应物	60	78	72	71
郭志杰	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081005102	应物	67	84	71	61
李宁	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081005103	应物	75	70	95	94
马奎高	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081005104	应物	72	90	60	93
白延云	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081005105	应物	86	82	51	94
郭耀华	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081005106	应物	94	73	84	99
谢望	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081001127	物理	74	81	66	66
纪望	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081001128	物理	84	82	81	53
占丽伟	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081001129	物理	90	71	77	90
雷琦晖	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081001130	物理	92	86	75	71
雷艳	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081001131	物理	94	73	84	99
张丹	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081001132	物理	99	64	81	56
杨凯	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003101	测控1	78	62	78	65
杜志煌	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003102	测控1	80	61	92	55
郭靖东	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003103	测控1	86	82	51	94
徐昊春	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003104	测控1	76	60	74	70
姜玉明	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003105	测控1	83	53	85	61
潘宏赫	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003106	测控1	81	100	64	61
米扬	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003225	测控2	82	90	80	89
郭婷婷	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003226	测控2	96	79	67	56
杨晗芳	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003227	测控2	90	71	77	90
王佳韵	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003228	测控2	87	71	95	67
陈聪	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003229	测控2	96	79	67	56
马芸芸	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬081003230	测控2	88	75	86	53
刘葳	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002124	电科1	41	76	86	98
罗哲雄	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002125	电科1	73	75	77	100
姚卡	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002126	电科1	66	89	69	56
刘琛	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002127	电科1	60	78	72	71
强创	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002128	电科1	60	78	72	71
魏凯凯	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002129	电科1	67	84	71	61
宋云雷	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬1	电科2	60	78	72	71
郝岩	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬2	电科2	60	78	72	71
马涛	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬3	电科2	60	78	72	71
刘宇	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬4	电科2	67	84	71	61
张财谦	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬5	电科2	82	90	80	89
李晓勇	F	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬091002[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬6	电科2	66	89	69	5
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct students   //typedef简化 
{
	char name[10];  //[姓名已脱敏] 
	char g[2];      //性别 F女生 M男生 
 	char num[15];   //[姓名已脱敏] 
 	char major[10]; //专业班级 
 	int r1;         //语文 
 	int r2;         //数学 
 	int r3;         //英语 
 	int r4;         //c++ 
 	int sum;        //总分 
 	int order_class;//班级名次 
 	int order_major;//年级名次 
 	struct students *next;   //指向下一个结构体的指针 
}St;

void show_menu(void);   //显示菜单 
void show_st(St *head); //显示以head为头指针的链表的所有信息 

St *sort_sum(St *head); //将以head为头指针的链表以总成绩排序重组 
St *sort_class(St *head); //将以head为头指针的链表排序，赋予班级排名，年级排名 
void sort_major(St *head,char *major); //赋予某一班级班级内排名 

void delete_st(St **head,char *num);   //删除以*head为头指针的链表中[姓名已脱敏]为num的学生信息 
void change(St **head,char *num);      //修改以*head为头指针的链表中[姓名已脱敏]为num的学生信息

void show_2(void);                    //显示二级菜单，查询成绩/信息 

void find_num(St *head,char *num);    //在以head为头指针的链表中找到[姓名已脱敏]为num的学生，并输出学生信息 
void find_name(St *head,char *num);   //在以head为头指针的链表中找到[姓名已脱敏]为name的学生，并输出学生信息  

void show_major(St *head,char *major);//在以head为头指针的链表中找到专业为major的学生，并输出该专业班级的所以学生信息 
int main()
{
	FILE *fp; 
	if((fp=fopen("students","r"))==NULL)    //打开文件"students" 
	{
		puts("cannot open file.");
		exit(0);
	} 
 	char ch1[100];        
 	fgets(ch1,100,fp);                      //第一行无用数据 
 	St *p,*head=NULL,*tail=NULL;            //建立链表准备条件 
 	while(!feof(fp))                        //从文件中读取学生信息直至结尾 
 	{
	    p=(St *)malloc(sizeof(St));         //动态内存申请，创建节点 
		fscanf(fp,"%s %s %s %s %d %d %d %d",p->name,p->g,p->num,p->major,&p->r1,&p->r2,&p->r3,&p->r4);    //从文件里读取学生数据 
		p->sum=p->r1+p->r2+p->r3+p->r4;                  //总分 
		p->order_class=p->order_major=0;
		if(head==NULL) head=tail=p;                 //第一个结构体数据
		else tail->next=p;                         //链表的尾插入 
		tail=p;                                    //尾指针的更新 
    }
    tail->next=NULL; 
	fclose(fp);//关闭文件 "students" 
	head=sort_class(head); //整理排序head链表 
	int a,b,f,f1; 
	while(1)
	{
		show_menu();   //显示菜单 
		while(scanf("%d",&a)!=1||a<1||a>6) {getchar();puts("invaild");}  //保证输入1-6之间的整数 
		if(a==1)
		{
			if((fp=fopen("students","a"))==NULL)   //"a"表示追加 
	        {
		        puts("cannot open file.");
		        exit(0);
	        }
            puts("请输入要写入学生信息:[姓名已脱敏]    性别  [姓名已脱敏]     班级 语文 数学 英语 c++");
            char input[100];
            getchar();
            gets(input);//示例：张三	M	[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬221006321	电科2	66	77	88	99 
            fprintf(fp,"%c",'\n');    //追加到下一行 
            fprintf(fp,"%s",input);  
			fclose(fp);  
			puts("已写入文件中");
		}
		if(a==2) show_st(head);  //显示head链表 
		if(a==3)
		{
			f1=0;
			char num[15];
			while(1)
			{
				f=0;
				puts("请输入[姓名已脱敏](输入quit返回上一步)");
				scanf("%s",num);
				if(strcmp(num,"quit")==0) {f1=1;break;}  //判断是否为quit 
				for(p=head;p;p=p->next) if(strcmp(p->num,num)==0) {f=1;break;}
				if(f==1) break;
				else puts("该[姓名已脱敏]不存在，请重新输入:");
			}
			if(f1==1) continue;
			change(&head,num);
		}
		if(a==4)
		{
			f1=0;
			char num[15];
			while(1)
			{
				f=0;
				puts("请输入[姓名已脱敏](输入quit返回上一步)");
				scanf("%s",num);
				if(strcmp(num,"quit")==0) {f1=1;break;} 
				for(p=head;p;p=p->next) if(strcmp(p->num,num)==0) {f=1;break;}
				if(f==1) break;
				else puts("该[姓名已脱敏]不存在，请重新输入:");
			}
			if(f1==1) continue;
			delete_st(&head,num);
		}
		if(a==5)
		{
			show_2();
			while(scanf("%d",&b)!=1||a<1||a>10) {getchar();puts("invaild");}
			if(b==1)
			{
				f1=0;
				char num[15];
				while(1)
			    {
				    f=0;
				    puts("请输入[姓名已脱敏](输入quit返回上一步)");
				    scanf("%s",num);
				    if(strcmp(num,"quit")==0) {f1=1;break;} 
				    for(p=head;p;p=p->next) if(strcmp(p->num,num)==0) {f=1;break;}
				    if(f==1) break;
			      	else puts("该[姓名已脱敏]不存在，请重新输入:");
			    }
			    if(f1==1) continue;
			    find_num(head,num);
			}
			if(b==2)
			{
				f1=0;
				char name[10];
				while(1)
			    {
				    f=0;
				    puts("请输入[姓名已脱敏](输入quit返回上一步)");
				    scanf("%s",name);
				    if(strcmp(name,"quit")==0) {f1=1;break;} 
				    for(p=head;p;p=p->next) if(strcmp(p->name,name)==0) {f=1;break;}
				    if(f==1) break;
			      	else puts("该学生不存在，请重新输入:");
			    }
			    if(f1==1) continue;
			    find_name(head,name); 
			}
			switch(b)
			{
				case 3:show_major(head,"物理");break; 
			    case 4:show_major(head,"应物");break; 
			    case 5:show_major(head,"电科1");break; 
			    case 6:show_major(head,"电科2");break; 
			    case 7:show_major(head,"测控1");break; 
			    case 8:show_major(head,"测控2");break; 
			    case 9:show_st(head);
			}
			if(b==10) break;
		}
		if(a==6) break; 
	}
 }
void show_menu(void)
{
	puts("**********************");
	puts("        你好");
	puts("**********************"); 
	puts("请输入你想要使用的功能:");
	puts("1:输入学生信息，并保存到文件\"students\"中");
	puts("2:计算每位同学的总分，平均分并排序");
	puts("3:输入[姓名已脱敏]修改学生信息");
	puts("4:输入[姓名已脱敏]删除学生信息");
	puts("5:查询功能");
	puts("6:退出");
}
void show_st(St *head)
{
 	St *i;
 	int n=0,t[5]={0};
 	printf("[姓名已脱敏]    性别  [姓名已脱敏]     班级    语文  数学   英语    c++   总分   班排 年排\n");
 	for(i=head;i;i=i->next,n++)// 遍历链表 
 	{
	    printf("%-8s %s %s %-7s %-6d %-6d %-6d %-6d %-6d %-3d %-3d\n",i->name,i->g,i->num,i->major,i->r1,i->r2,i->r3,i->r4,i->sum,i->order_major,i->order_class);
        t[0]+=i->r1;    
 	    t[1]+=i->r2; 
 	    t[2]+=i->r3; 
 	    t[3]+=i->r4; 
 	    t[4]+=i->sum; 
	}
	printf("%-8s %11s %1s %-7s %6.3f %6.3f %6.3f %6.3f %6.3f\n","平均分","","","",t[0]*1.0/n,t[1]*1.0/n,t[2]*1.0/n,t[3]*1.0/n,t[4]*1.0/n);
}
void change(St **head,char *num)
{
	St *i;
	for(i=*head;i;i=i->next) if(strcmp(i->num,num)==0) break; 
	puts("请输入该同学修改后的信息：");
	puts("[姓名已脱敏] 性别 班级 语文 数学 英语 c++");
	scanf("%s %s %s %d %d %d %d",i->name,i->g,i->major,&i->r1,&i->r2,&i->r3,&i->r4);
	i->sum=i->r1+i->r2+i->r3+i->r4;
	puts("修改后成绩单:");
	*head=sort_class(*head);
	show_st(*head);
}
void delete_st(St **head,char *num)
{
	St *i=*head,*j=(*head)->next;
	if(strcmp((*head)->num,num)==0)
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
			else 
			{
			    i=j;
			    j=j->next;
			}
		}
	}
	puts("删除后成绩单:");
	*head=sort_class(*head);
	show_st(*head);
}
void show_2(void)
{
	puts("**********************");
	puts("        你好");
	puts("**********************"); 
	puts("请输入你想要使用的功能:");
	puts("1:输入 [姓名已脱敏] 查询学生信息");
	puts("2:输入 [姓名已脱敏] 查询学生信息");
	puts("3:查询 物理  班级成绩");
	puts("4:查询 应物  班级成绩");
	puts("5:查询 电科1 班级成绩");
	puts("6:查询 电科2 班级成绩");
	puts("7:查询 测控1 班级成绩");
	puts("8:查询 测控2 班级成绩");
	puts("9:查询 年级  成绩");
	puts("10:返回上一步"); 
}
void find_num(St *head,char *num)
{
	St *i;
	for(i=head;i;i=i->next) if(strcmp(i->num,num)==0) break;
	printf("[姓名已脱敏]    性别  [姓名已脱敏]     班级 语文 数学 英语 c++ 总分 班排 年排\n");
 	printf("%-8s %s %s %-7s %-3d %-3d %-3d %-3d %-3d %-3d %-3d\n",i->name,i->g,i->num,i->major,i->r1,i->r2,i->r3,i->r4,i->sum,i->order_major,i->order_class);
}
void find_name(St *head,char *name)
{
	St *i;
	for(i=head;i;i=i->next) if(strcmp(i->name,name)==0) break;
	printf("[姓名已脱敏]    性别  [姓名已脱敏]     班级 语文 数学 英语 c++ 总分 班排 年排\n");
 	printf("%-8s %s %s %-7s %-3d %-3d %-3d %-3d %-3d %-3d %-3d\n",i->name,i->g,i->num,i->major,i->r1,i->r2,i->r3,i->r4,i->sum,i->order_major,i->order_class);
}
void show_major(St *head,char *major)
{
	St *i,*p,*head1=NULL,*tail1=NULL;
	for(i=head;i;i=i->next)
	{
		if(strcmp(i->major,major)==0)             //把同一个专业班级的学生拿出来建立一个新的链表head1 
		{
			p=(St *)malloc(sizeof(St));
			*p=*i;
			if(head1==NULL) head1=tail1=p;
			else tail1->next=p;
			tail1=p;
		}
	} 
	tail1->next=NULL;
	show_st(head1);
	for(i=head1;i;i=p)                                        //释放建立的临时链表 
	{
		p=i->next;
		free(i);
	} 
} 
St *sort_sum(St *head)
{
    St *p0,*p_0,*p1,*p_1,*p2,*p_2;
    if(head==NULL)      // 检查链表是否为空 
	{
		puts("链表为空");
        return head;
    }
    p0=p_0=head;        //初始化指针,使用双指针法进行排序
    while (p_0->next)   //外部循环遍历链表，每次找到最大和的节点并将其移到前面
    {
        p1=p0;          //用于记录当前最大和节点的前一个节点
        p_1=p2=p_0;     //用于记录当前最大和节点及其后一个节点
        p_2=p_0->next;  //初始化下一个节点
        while (p_2)     // 内部循环查找最大和的节点
        {
            if(p_1->sum < p_2->sum)   // 如果下一个节点的和更大
            {
                p1=p2;               // 更新前一个节点为当前节点
                p_1=p_2;             // 更新当前节点为下一个节点
            }
            p2=p_2;                  // 继续向后移动指针
            p_2=p_2->next;
        }
        if(p_0!=p_1)            // 如果需要，交换节点位置
        {
            p1->next=p_1->next;   // 调整前一个节点的指针
            p_1->next=p_0;       // 将当前节点移动到前面
            if(p_0==head) head=p_1;// 如果当前节点是头节点，则更新头指针
            else p0->next=p_1;   // 否则调整前一个节点的指针
            p0=p_1;              // 更新当前节点为已排序部分的最后一个节点
        }
        else
        {
            p0=p_0;            // 否则继续向后移动指针
            p_0=p_0->next;
        }
    }
    return head;              // 返回排序后的链表头指针
}
St *sort_class(St *head)      //总排序函数  按总成绩排序 并赋予年级排名 班级排名 
{
	head=sort_sum(head);              //将链表按总成绩重组 
	head->order_class=1;         //第一名 
    int r;                        //当前位次  
	St *p1,*p2;                 
    for(r=1,p1=head->next,p2=head;p1;p2=p1,p1=p1->next,r++)    //总遍历 
    { 
    	if(p1->sum==p2->sum) p1->order_class=p2->order_class;  //若当前位次的总成绩与前一个相同 ，则位次也相同 
    	else p1->order_class=r+1;                              //若不同，则赋予新位次 
	}
	sort_major(head,"测控1");
	sort_major(head,"测控2");
	sort_major(head,"物理");
	sort_major(head,"应物");
	sort_major(head,"电科1");
	sort_major(head,"电科2");
	return head;
}
void sort_major(St *head,char *major)
{
	St *i,*p,*p1,*p2,*head1=NULL,*tail1=NULL;
	for(i=head;i;i=i->next)
	{
		if(strcmp(i->major,major)==0)             //把同一个专业班级的学生拿出来建立一个新的链表head1 
		{
			p=(St *)malloc(sizeof(St));
			*p=*i;
			if(head1==NULL) head1=tail1=p;
			else tail1->next=p;
			tail1=p;
		}
	} 
	tail1->next=NULL;
	head1->order_major=1;
	int r;                                                       //当前位次 
    for(r=1,p1=head1->next,p2=head1;p1;p2=p1,p1=p1->next,r++)    //总遍历 
    { 
    	if(p1->sum==p2->sum) p1->order_major=p2->order_major;    //若当前位次的总成绩与前一个相同 ，则位次也相同 
    	else p1->order_major=r+1;                                //若不同，则赋予新位次 
	}
	for(i=head1;i;i=i->next)
	{
		for(p=head;p;p=p->next)
		{
			if(strcmp(i->num,p->num)==0) 
			{
 			    p->order_major=i->order_major;                   //把位次传回给原链表 
			    break;
			}
		}
	}
	for(i=head1;i;i=p)                                        //释放建立的临时链表 
	{
		p=i->next;
		free(i);
	} 
}
