#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct _Stu { //dssdssss 8个数据
	int num;//[姓名已脱敏]
	char name[16]; 	//[姓名已脱敏]
	char sex[6];	//性别
	char adrs[101];//最多50个汉字*2字节/汉字=100字节，再加一个'\0'结尾符，一共需101字节
	struct _Stu *next;
} Stu;

typedef struct _enr { //dssdssss 8个数据
	int num;//[姓名已脱敏]
	char name[16]; 	//[姓名已脱敏]
	int counum;//课程号 
	char couse[30];//课程名 
	int term;//学期 
	int score;//成绩 
	struct _enr *next;
} enr;

/*函数声明列表*/

//菜单函数
void menu(void);

void menu_cou(void);

void menu_enr(void);

//从文件载入信息至链表，改变全局头指针ph
int readf(void);

int readf_cou(void);

int readf_enr(void);

//根据指针所指显示某人信息
void pri(Stu *p);

void pri_enr(enr *p);

//显示所有信息 pri函数复用
void display(Stu *head);

void display_enr(enr *head);

//新建链表插入文件链表
int create(void);

int create_enr(void);

//得到特定[姓名已脱敏]的结构体指针
Stu *seeint(int num);

enr *seeint_enr(int num);

//得到特定[姓名已脱敏]的结构体指针
Stu *seechar(char *nam);

enr *seechar_enr(char *nam);

//根据[姓名已脱敏]、[姓名已脱敏]查询学生信息，并返回该学生[姓名已脱敏]，seechar() seeint() 函数复用
int search(void);

int search_enr(void);

//根据search()返回的[姓名已脱敏],再通过seeint()找到指针，修改信息
int modify(void);

//删除函数
int del(void);

int del_enr(void);

//排序
int sort();

//文件保存
int savef();

int savef_cou();
int savef_enr();

Stu *ph = NULL;

enr *ph1 = NULL;

int choice1;


int main()
{
	ph = NULL;
	printf("请选择操作\n");
	printf("1、学生信息系统\n");
	printf("2、课程信息系统\n");
	printf("3、选课信息系统\n");
	scanf("%d",&choice1);
	if(choice1==1){
		if (readf()) {
			printf("文件初始化成功,欢迎使用!\n\n\n\n");
		} else {
			printf("\n请在本程序所在目录新建studata.txt再启动程序!\n\n\n\n");
			getchar();
			return 0;
		}
	
		do {
			int choice;
			menu();
			scanf("%d", &choice);
			switch (choice) {
				case 1:
					system("cls");
					printf("\n=====浏览所有学生信息=====\n");
					if (ph==NULL) {
						printf("学生信息为空，请返回主菜单新建信息\n");
					} else {
						display(ph);
					}
					break;
				case 2:
					system("cls");
					printf("\n=====新建学生信息=====\n");
					if(create()) {
						printf("信息成功输入\n");
					} else {
						printf("信息输入结束\n");
					}
					break;
				case 3:
					system("cls");
					printf("\n=====查询学生信息=====\n");
					search();
					break;
				case 4:
					system("cls");
					printf("\n=====修改学生信息=====\n");
					if(modify())break;
				case 5:
					system("cls");
					printf("\n=====删除学生信息=====\n");
					if(del()) {
						printf("\n删除成功！\n");
						break;
					} else { //bug
						printf("\n无此[姓名已脱敏]信息！\n");
						break;
					}
				case 6:
					system("cls");
					printf("\n=====按[姓名已脱敏]重新排序=====\n");
					if(sort()) {
						printf("冒泡排序成功！\n");
					} else {
						printf("结点个数小于2，无法进行冒泡排序！");
					}
					break;
				case 0:
					system("cls");
					printf("\n=====保存学生信息=====\n\n");
					if(savef()) {
						printf("储存成功\n\n");
					} else {
						printf("储存失败\n\n");
					}
					printf("欢迎下次使用,再见!\n");
					if (!ph) {	//释放内存
						free(ph);
					}
					printf("\n按任意键结束。\n");
					getch();
					return 0;
	
				default:
					system("cls");
					printf("\n输入错误,请重新选择操作!\n");
					break;
			}
	
			while(1) {
				printf("\n按任意键可返回主菜单。\n");
				if(getch()) break;
			}
			system("cls");
		} while(1);
	}else if(choice1==2){
		if (readf_cou()) {
			printf("文件初始化成功,欢迎使用!\n\n\n\n");
		} else {
			printf("\n请在本程序所在目录新建coudata.txt再启动程序!\n\n\n\n");
			getchar();
			return 0;
		}
	
		do {
			int choice;
			menu();
			scanf("%d", &choice);
			switch (choice) {
				case 1:
					system("cls");
					printf("\n=====浏览所有课程信息=====\n");
					if (ph==NULL) {
						printf("课程信息为空，请返回主菜单新建信息\n");
					} else {
						display(ph);
					}
					break;
				case 2:
					system("cls");
					printf("\n=====新建课程信息=====\n");
					if(create()) {
						printf("信息成功输入\n");
					} else {
						printf("信息输入结束\n");
					}
					break;
				case 3:
					system("cls");
					printf("\n=====查询课程信息=====\n");
					search();
					break;
				case 4:
					system("cls");
					printf("\n=====修改课程信息=====\n");
					if(modify())break;
				case 5:
					system("cls");
					printf("\n=====删除课程信息=====\n");
					if(del()) {
						printf("\n删除成功！\n");
						break;
					} else { //bug
						printf("\n无此课程号信息！\n");
						break;
					}
				case 6:
					system("cls");
					printf("\n=====按课程号重新排序=====\n");
					if(sort()) {
						printf("冒泡排序成功！\n");
					} else {
						printf("结点个数小于2，无法进行冒泡排序！");
					}
					break;
				case 0:
					system("cls");
					printf("\n=====保存课程信息=====\n\n");
					if(savef_cou()) {
						printf("储存成功\n\n");
					} else {
						printf("储存失败\n\n");
					}
					printf("欢迎下次使用,再见!\n");
					if (!ph) {	//释放内存
						free(ph);
					}
					printf("\n按任意键结束。\n");
					getch();
					return 0;
	
				default:
					system("cls");
					printf("\n输入错误,请重新选择操作!\n");
					break;
			}
	
			while(1) {
				printf("\n按任意键可返回主菜单。\n");
				if(getch()) break;
			}
			system("cls");
		} while(1);
	}else{
		if (readf_enr()) {
			printf("文件初始化成功,欢迎使用!\n\n\n\n");
		} else {
			printf("\n请在本程序所在目录新建enrdata.txt再启动程序!\n\n\n\n");
			getchar();
			return 0;
		}
	
		do {
			int choice;
			menu_enr();
			scanf("%d", &choice);
			switch (choice) {
				case 1:
					system("cls");
					printf("\n=====浏览所有选课信息=====\n");
					if (ph1==NULL) {
						printf("选课信息为空，请返回主菜单新建信息\n");
					} else {
						display_enr(ph1);
					}
					break;
				case 2:
					system("cls");
					printf("\n=====新建选课信息=====\n");
					if(create_enr()) {
						printf("信息成功输入\n");
					} else {
						printf("信息输入结束\n");
					}
					break;
				case 3:
					system("cls");
					printf("\n=====查询选课信息=====\n");
					search_enr();
					break;
				case 5:
					system("cls");
					printf("\n=====删除选课信息=====\n");
					if(del_enr()) {
						printf("\n删除成功！\n");
						break;
					} else { //bug
						printf("\n无此选课号信息！\n");
						break;
					}
				case 0:
					system("cls");
					printf("\n=====保存选课信息=====\n\n");
					if(savef_enr()) {
						printf("储存成功\n\n");
					} else {
						printf("储存失败\n\n");
					}
					printf("欢迎下次使用,再见!\n");
					if (!ph1) {	//释放内存
						free(ph1);
					}
					printf("\n按任意键结束。\n");
					getch();
					return 0;
	
				default:
					system("cls");
					printf("\n输入错误,请重新选择操作!\n");
					break;
			}
	
			while(1) {
				printf("\n按任意键可返回主菜单。\n");
				if(getch()) break;
			}
			system("cls");
		} while(1);
	}

}

//菜单
void menu()
{
	printf("************************************************\n");
	printf("*************学生信息管理系统*************\n");
	printf("************************************************\n\n");
	printf("\n\n请选择操作:\n\n");
	printf("1.浏览学生信息.\n");
	printf("2.新建学生信息.\n");
	printf("3.查询学生信息.\n");
	printf("4.修改学生信息.\n");
	printf("5.删除学生信息.\n");
	printf("6.按[姓名已脱敏]重新排序.\n");
	printf("0.退出并保存信息.\n");
	printf("\n  你的选择是：");
}

void menu_cou()
{
	printf("************************************************\n");
	printf("*************课程信息管理系统*************\n");
	printf("************************************************\n\n");
	printf("\n\n请选择操作:\n\n");
	printf("1.浏览课程信息.\n");
	printf("2.新建课程信息.\n");
	printf("3.查询课程信息.\n");
	printf("4.修改课程信息.\n");
	printf("5.删除课程信息.\n");
	printf("6.按课程号重新排序.\n");
	printf("0.退出并保存信息.\n");
	printf("\n  你的选择是：");
}

void menu_enr()
{
	printf("************************************************\n");
	printf("*************选课信息管理系统*************\n");
	printf("************************************************\n\n");
	printf("\n\n请选择操作:\n\n");
	printf("1.浏览选课信息.\n");
	printf("2.新建选课信息.\n");
	printf("3.查询选课信息.\n");
	printf("5.删除选课信息.\n");
	printf("0.退出并保存信息.\n");
	printf("\n  你的选择是：");
}

//从文件载入信息至链表，改变全局头指针ph
int readf()
{
	FILE *pf;
	Stu *p,*tail;
	pf = fopen("studata.txt", "r");
	if(!pf) {
		return 0; //失败后不再执行以下操作
	}
	fgetc(pf);//指针移位
	while(!feof(pf)) {
		p = (Stu *)malloc(sizeof(Stu));
		fscanf(pf,"%d%s%s%s",&p->num, p->name,p->sex,p->adrs);
		//插入信息
		if(ph == NULL) {
			ph = p;
			tail = p;
		} else {
			tail->next = p;
			tail = p;
		}
		fgetc(pf);
		fgetc(pf);
		if(feof(pf)) {
			tail->next=NULL;
		}
	}
	if(!pf) {
		fclose(pf);//关闭文件

	}
	return 1;//成功
}
//从文件载入信息至链表，改变全局头指针ph
int readf_cou()
{
	FILE *pf;
	Stu *p,*tail;
	pf = fopen("coudata.txt", "r");
	if(!pf) {
		return 0; //失败后不再执行以下操作
	}
	fgetc(pf);//指针移位
	while(!feof(pf)) {
		p = (Stu *)malloc(sizeof(Stu));
		fscanf(pf,"%d%s%s%s",&p->num, p->name,p->sex,p->adrs);
		//插入信息
		if(ph == NULL) {
			ph = p;
			tail = p;
		} else {
			tail->next = p;
			tail = p;
		}
		fgetc(pf);
		fgetc(pf);
		if(feof(pf)) {
			tail->next=NULL;
		}
	}
	if(!pf) {
		fclose(pf);//关闭文件

	}
	return 1;//成功
}

int readf_enr()
{
	FILE *pf;
	enr *p,*tail;
	pf = fopen("enrdata.txt", "r");
	if(!pf) {
		return 0; //失败后不再执行以下操作
	}
	fgetc(pf);//指针移位
	while(!feof(pf)) {
		p = (enr *)malloc(sizeof(enr));
		fscanf(pf,"%d%s%d%s%d%d",&p->num, p->name,p->counum,p->couse,p->term,p->score);
		//插入信息
		if(ph1 == NULL) {
			ph1 = p;
			tail = p;
		} else {
			tail->next = p;
			tail = p;
		}
		fgetc(pf);
		fgetc(pf);
		if(feof(pf)) {
			tail->next=NULL;
		}
	}
	if(!pf) {
		fclose(pf);//关闭文件

	}
	return 1;//成功
}

//根据指针显示某人信息
void pri(Stu *p)
{
	if(p) {
		if(choice1==1){
			printf("[姓名已脱敏]:%d\t[姓名已脱敏]:%s\t性别:%s\t地址:%s\t\n",
			       p->num, p->name,p->sex,p->adrs);
		}else{
			printf("课程号:%d\t课程名:%s\t学分:%s\t学时:%s\t\n",
			       p->num, p->name,p->sex,p->adrs);
		}
	} else {
		printf("所给信息无效");
	}
	return;
}

void pri_enr(enr *p)
{
	if(p) {
		printf("[姓名已脱敏]:%d\t[姓名已脱敏]:%s\t课程号:%d\t课程名:%s\t学期：%d\t成绩：%d\t\n",
		       p->num, p->name,p->counum,p->couse,p->term,p->score);

	} else {
		printf("所给信息无效");
	}
	return;
}

//显示所有信息 pri函数复用
void display(Stu *head)
{
	Stu *p;
	p = head;//不改变传入指针的值
	while(1) {
		pri(p);
		if(p->next) {
			p = p->next;
		} else {
			break;
		}

	}
	return;
}

void display_enr(enr *head)
{
	enr *p;
	p = head;//不改变传入指针的值
	while(1) {
		pri_enr(p);
		if(p->next) {
			p = p->next;
		} else {
			break;
		}

	}
	return;
}

//得到特定[姓名已脱敏]的结构体指针
Stu *seeint(int num)
{
	Stu *p;
	p = ph;
	while (p && (p->num != num)) {
		p = p->next;
	}
	return p;
}

enr *seeint_enr(int num)
{
	enr *p;
	p = ph1;
	while (p && (p->num != num)) {
		p = p->next;
	}
	return p;
}

//得到特定[姓名已脱敏]的结构体指针
Stu *seechar(char *nam)
{
	Stu *p;
	p = ph;
	while(p && strcmp(nam,p->name)) {
		p = p->next;
	}
	return p;
}

enr *seechar_enr(char *nam)
{
	enr *p;
	p = ph1;
	while(p && strcmp(nam,p->name)) {
		p = p->next;
	}
	return p;
}


int create()
{
	Stu *p,*head,*tail;//临时操作指针、头指针、尾指针
	int a=1;
	head = NULL;
	do {
		p = (Stu *)malloc(sizeof(Stu));
		if(choice1==1){
			printf("\n请输入[姓名已脱敏]（[姓名已脱敏]为11位）:");
		}else{
			printf("\n请输入课程号（课程号为11位）:");
		}
		scanf("%d", &p->num);
		//判断该记录是否存在
		if (seeint(p->num)) {
			if(choice1==1){
				printf("[姓名已脱敏]为%d的记录已存在!\n",p->num);
			}else{
				printf("课程号为%d的记录已存在!\n",p->num);
			}
			return 0;
		}
		if(choice1==1){
			printf("请输入[姓名已脱敏]:");
		}else{
			printf("请输入课程名:");
		}
		scanf("%s",p->name);
		if(choice1==1){
			printf("请输入性别（男或女）:");
		}else{
			printf("请输入学分:");
		}
		scanf("%s",p->sex);
		if(choice1==1){
			printf("请输入地址:");
		}else{
			printf("请输入学时:");
		}
		scanf("%s",p->adrs);
		if(head == NULL) {
			head = p;
			tail = p;
		} else {
			tail->next = p;
			tail = p;
		}
		tail->next=NULL ;
		printf("\n输入0回车终止，输入任意值回车继续\n");
		scanf("%d", &a);
	} while(a!=0);
	//根据ph和head的状态，链接链表
	if(head) {
		if(ph) {
			tail->next=ph;
			ph=head;
			return 1;//ph、head都不为空时连接，返回1
		} else {
			ph=head;
			return 1;//ph为空、head不为空时赋值，返回1
		}
	} else {
		return 0;//ph、head为空时返回0，ph不空、head为空时返回0
	}
}

int create_enr()
{
	enr *p,*head,*tail;//临时操作指针、头指针、尾指针
	int a=1;
	head = NULL;
	do {
		p = (enr *)malloc(sizeof(enr));

			printf("\n请输入[姓名已脱敏]（[姓名已脱敏]为11位）:");

		scanf("%d", &p->num);
		//判断该记录是否存在
		if (seeint_enr(p->num)) {
			if(choice1==1){
				printf("[姓名已脱敏]为%d的记录已存在!\n",p->num);
		}
			return 0;
		}

			printf("请输入[姓名已脱敏]:");

		scanf("%s",p->name);
			printf("请输入课程号:");
		scanf("%d",p->counum);
			printf("请输入课程名:");
		scanf("%s",p->couse);
			printf("请输入学期:");
		scanf("%d",p->term);
			 printf("请输入成绩:");
		scanf("%d",p->score);
		if(head == NULL) {
			head = p;
			tail = p;
		} else {
			tail->next = p;
			tail = p;
		}
		tail->next=NULL ;
		printf("\n输入0回车终止，输入任意值回车继续\n");
		scanf("%d", &a);
	} while(a!=0);
	//根据ph和head的状态，链接链表
	if(head) {
		if(ph1) {
			tail->next=ph1;
			ph1=head;
			return 1;//ph、head都不为空时连接，返回1
		} else {
			ph1=head;
			return 1;//ph为空、head不为空时赋值，返回1
		}
	} else {
		return 0;//ph、head为空时返回0，ph不空、head为空时返回0
	}
}




//根据[姓名已脱敏]、[姓名已脱敏]查询学生信息，并返回该学生[姓名已脱敏]  seechar seeint 函数复用
int search()
{
	Stu *p;
	int m=0, n;
	char nam[16];
	while(m!=1&&m!=2) {
		printf("\n\n输入序号以继续：\n1.按号查找\n2.按名查找\n");
		scanf("%d", &m);
	}
	if(m==1) {
		printf("请输入要查询的[姓名已脱敏]或课程号:");
		scanf("%d", &n);
		if(seeint(n)) {
			pri(seeint(n));
		} else {
			printf("无");
		}
	}
	if(m==2) {
		printf("请输入要查询的[姓名已脱敏]或课程名:");
		scanf("%s",nam);
		if(seechar(nam)) {
			pri(seechar(nam));
		} else {
			printf("无");
		}
	}/*为下面modify做准备 */
	if(seeint(n)) {
		p=seeint(n);
		return p->num;
	}
	if(seechar(nam)) {
		p=seechar(nam);
		return p->num;
	}
}

int search_enr()
{
	enr *p;
	int m=0, n;
	char nam[16];
	while(m!=1&&m!=2) {
		printf("\n\n输入序号以继续：\n1.按号查找\n2.按名查找\n");
		scanf("%d", &m);
	}
	if(m==1) {
		printf("请输入要查询的[姓名已脱敏]:");
		scanf("%d", &n);
		if(seeint_enr(n)) {
			pri_enr(seeint_enr(n));
		} else {
			printf("无");
		}
	}
	if(m==2) {
		printf("请输入要查询的[姓名已脱敏]:");
		scanf("%s",nam);
		if(seechar_enr(nam)) {
			pri_enr(seechar_enr(nam));
		} else {
			printf("无");
		}
	}/*为下面modify做准备 */
	if(seeint_enr(n)) {
		p=seeint_enr(n);
		return p->num;
	}
	if(seechar_enr(nam)) {
		p=seechar_enr(nam);
		return p->num;
	}
}


int modify()
{
	int choice; //用户选择序号
	Stu *p=seeint(search());
	if (p == NULL) {
		printf("不存在此[姓名已脱敏]或课程号的记录!\n");
		return 1;
	}
	if(choice1==1){
		printf("0.修改[姓名已脱敏].\n");
		printf("1.修改[姓名已脱敏].\n");
		printf("2.修改性别.\n");
		printf("7.修改地址.\n");
		printf("请选择要修改的信息:");
	}else{
		printf("0.修改课程号.\n");
		printf("1.修改课程名.\n");
		printf("2.修改学分.\n");
		printf("7.修改学时.\n");
		printf("请选择要修改的信息:");
	}
	scanf("%d", &choice);
	if(choice1==1){
		switch (choice) {
			case 0:
				printf("请输入[姓名已脱敏]:");
				scanf("%d",&p->num);
				break;
			case 1:
				printf("请输入[姓名已脱敏]:");
				scanf("%s",p->name);
				break;
			case 2:
				printf("请输入性别（男或女）:");
				scanf("%s",p->sex);
				break;
			case 7:
				printf("请输入地址:");
				scanf("%s",p->adrs);
				break;
			default:
				printf("输入错误，请重新选择操作!\n");
		}
	}else{
		switch (choice) {
			case 0:
				printf("请输入课程号:");
				scanf("%d",&p->num);
				break;
			case 1:
				printf("请输入课程名:");
				scanf("%s",p->name);
				break;
			case 2:
				printf("请输入学分:");
				scanf("%s",p->sex);
				break;
			case 7:
				printf("请输入学时:");
				scanf("%s",p->adrs);
				break;
			default:
				printf("输入错误，请重新选择操作!\n");
		}
	}
	return 1;
}

int del()
{
	Stu *see,*p,*pre;//p为对应[姓名已脱敏]的指针，pre是对应[姓名已脱敏]的前一个的指针
	int num;
	printf("请输入要删除信息的[姓名已脱敏]或课程号:\n");
	scanf("%d", &num);
	if(!seeint(num)) {
		return 0;
	}
	p = ph;//从头开始遍历
	if(!p) return 0;//链表为空则退出
	//第一个为要删除结点的删除方法
	if(p->num==num) {
		if(!p->next) {
			ph=NULL;
			free(p);
			return 1;
		} else {
			ph=p->next;
			free(p);
			return 1;
		}
	}
	//第二个以及之后为要删除结点的删除方法
	while(p->num!=num) {
		pre=p;
		p=p->next;
	}
	pre->next=p->next;
	free(p);
	return 1;
}

int del_enr()
{
	enr *see,*p,*pre;//p为对应[姓名已脱敏]的指针，pre是对应[姓名已脱敏]的前一个的指针
	int num;
	printf("请输入要删除信息的[姓名已脱敏]或课程号:\n");
	scanf("%d", &num);
	if(!seeint(num)) {
		return 0;
	}
	p = ph1;//从头开始遍历
	if(!p) return 0;//链表为空则退出
	//第一个为要删除结点的删除方法
	if(p->num==num) {
		if(!p->next) {
			ph1=NULL;
			free(p);
			return 1;
		} else {
			ph1=p->next;
			free(p);
			return 1;
		}
	}
	//第二个以及之后为要删除结点的删除方法
	while(p->num!=num) {
		pre=p;
		p=p->next;
	}
	pre->next=p->next;
	free(p);
	return 1;
}

int sort()
{
	Stu *c=ph,*head,*prr,*pre,*p,*temp;
	int n,count,i;
	while(c) {
		count++;
		c=c->next;
	}
	if(count<=1) {
		return 0;
	}//存在两个结点才继续
	head=(Stu*)malloc(sizeof(Stu));
	head->next=ph;//将链表的头部加空结点
	n=count*(count-1)/2;//计算遍历排序次数
	for(i=1; i<=n; i++) {
		prr=head;//prr放在第一个结点 （为空）
		pre=head->next;	//pre放在第二个结点
		p=head->next->next;//p放在第三个结点
		while(1) {
			//比较pre所指与p所指的大小并决定交换
			if((pre->num)>(p->num)) {
				temp=p->next;
				prr->next=p;
				p->next=pre;
				pre->next=temp;
				//回到原来的顺序
				temp=pre;
				pre=p;
				p=temp;
			}

			//三个指针移位
			if(!p->next) break;//若到最后一个结点则终止
			p=p->next;
			pre=pre->next;
			prr=prr->next;
		}

	}
	ph=head->next;//删除空结点
	free(head);
	printf("排序结点个数为%d,\n",count);
	return 1;
}


//将内存中的信息传入文件
int savef()
{
	FILE *pf;
	Stu *p;
	pf = fopen("studata.txt", "w");
	if(!pf) {
		return 0; //失败后不再执行以下
	}
	p=ph;//从头开始
	while (p) {
		fprintf(pf," %d\t%s\t%s\t%s\t",p->num, p->name,
		        p->sex ,p->adrs);
		p=p->next;
	}
	if(!pf) {
		fclose(pf);
	}
	return 1;
}

int savef_cou()
{
	FILE *pf;
	Stu *p;
	pf = fopen("coudata.txt", "w");
	if(!pf) {
		return 0; //失败后不再执行以下
	}
	p=ph;//从头开始
	while (p) {
		fprintf(pf," %d\t%s\t%s\t%s\t",p->num, p->name,
		        p->sex ,p->adrs);
		p=p->next;
	}
	if(!pf) {
		fclose(pf);
	}
	return 1;
}

int savef_enr()
{
	FILE *pf;
	enr *p;
	pf = fopen("enrdata.txt", "w");
	if(!pf) {
		return 0; //失败后不再执行以下
	}
	p=ph1;//从头开始
	while (p) {
		fprintf(pf," %d\t%s\t%d\t%s\t%d\t%d\t",p->num, p->name,
		        p->counum ,p->couse,p->term,p->score);
		p=p->next;
	}
	if(!pf) {
		fclose(pf);
	}
	return 1;
}
