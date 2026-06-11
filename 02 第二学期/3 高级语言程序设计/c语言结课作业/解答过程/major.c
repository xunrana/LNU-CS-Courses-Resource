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

St *order_st_c(St* head)
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
            /* 按总成绩降序排序 */
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
	return head;
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
	order_st(head1);
}


void order_st(St* head)
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
            /* 按总成绩降序排序 */
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
	head=order_st_c(head);
	while(1)
	{ 
	    char major[6];
	    puts("请输入专业:(输入quit退出):");
	    gets(major);
	    if(strcmp(major,"quit")==0) break;
	    show_major(head,major);
    }
}

