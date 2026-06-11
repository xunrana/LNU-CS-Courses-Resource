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
	puts("    [姓名已脱敏]    [姓名已脱敏]     专业    C语言 计算物理学 大学物理 原子物理  光学  总成绩 班级名次 年级名次");
	int arr[6]={0},i=0; 
	for(p=head;p!=NULL;p=p->next)
	{
		i++;
	    printf("%s %-8s %-5s     %-7d %-7d %-7d %-7d %-7d %-7d %-5d %d\n",p->num,p->name,p->major,p->c,p->p1,p->p2,p->p3,p->o,p->sum,p->order_major,p->order_class);
	    arr[0]+=p->c;
	    arr[1]+=p->p1;
	    arr[2]+=p->p2;
	    arr[3]+=p->p3;
	    arr[4]+=p->o;
	    arr[5]+=p->sum;
	}
	printf("%s %-8s %-5s        %-7.3f %-7.3f %-7.3f %-7.3f %-7.3f %-7.3f\n","平均成绩"," "," ",arr[0]*1.0/i,arr[1]*1.0/i,arr[2]*1.0/i,arr[3]*1.0/i,arr[4]*1.0/i,arr[5]*1.0/i);
}
St *sort_sum(St *head)
{
    St *p0,*p_0,*p1,*p_1,*p2,*p_2;
    if(head==NULL) {puts("链表为空");return head;}
    p0=p_0=head;
    while(p_0->next)
    {
        p1=p0;
        p_1=p2=p_0;
        p_2=p_0->next;
        while(p_2)
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
	show_st(sort_sum(head));
}
