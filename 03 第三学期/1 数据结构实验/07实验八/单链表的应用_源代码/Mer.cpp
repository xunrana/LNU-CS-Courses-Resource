#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct LNode{
	char data[30];//数据域 
	struct LNode *next;//指针域 
}LNode,*LinkList;
void CreateListR(LinkList *L,int n)
{
	LinkList p,r;
	*L=(LinkList)malloc(sizeof(LNode));//为头节点申请内存 
	if(*L==NULL) exit(1);
	r=*L;
	for(int i=1;i<=n;i++)
	{
		p=(LinkList)malloc(sizeof(LNode));//为储存单链表元素的结点申请内存 
		if(!p) exit(-2);
		scanf("%s",p->data);
		r->next=p;//链接上新节点 
		r=p;//更新尾结点 
	}
	r->next=NULL;//尾结点标志，指向NULL 
}
void ShowList(LinkList L)//遍历输出单链表元素 
{
	if(!L) return ;
	LinkList p=L->next;//头节点不存储元素 
	while(p)
	{
		printf("%s ",p->data);
		p=p->next;
	}
	putchar('\n');
}
void freelist(LinkList *L)//释放链表内存 
{
	LinkList p=(*L),t;//定义结点指针p 临时指针t 
	while(p)//循环释放链表结点内存 
	{
		t=p->next;//保存下一个结点地址 
		free(p);//释放当前结点 
		p=t;//移动到下一个结点 
	}
}
void Mer(LinkList *l1,LinkList *l2,LinkList *l3)
{
	LinkList p1=(*l1)->next,p2=(*l2)->next,p3=(*l3),t;//初始化链表指针
	while(p1&&p2)//开始合并排序 
	{
		if(strcmp(p1->data,p2->data)<0)//如果p1数据小于p2 
		{
			p3->next=p1;//p1连接到合并链表上 
			p3=p1;//移动合并链表的指针到p1 
			p1=p1->next;//移动到下一个结点 
		}
		else if(strcmp(p1->data,p2->data)>0)//如果p2数据小于p1 
		{
			p3->next=p2;//p2连接到合并链表上 
			p3=p2;//移动合并链表的指针到p2 
			p2=p2->next;//移动到下一个结点 
		}
		else
		{
			p3->next=p1;//p1连接到合并链表上 
			p3=p1;//移动合并链表的指针到p1 
			p1=p1->next;//移动到下一个结点 
			t=p2;
			p2=p2->next;
			free(t);//释放重复结点的内存 
		}
	}
	if(p1) p3->next=p1;//如果l1还有剩余元素，连接到合并链表上 
	if(p2) p3->next=p2;//如果l2还有剩余元素，连接到合并链表上 
}

int main()
{
	puts("请输入链表中包含的元素个数n(一个正整数)");
	int n;
	scanf("%d",&n);
	LinkList L1=NULL;
	puts("请输入链表L1中的元素(单词间以空格隔开)");
	CreateListR(&L1,n);
	puts("L1 List:");
	ShowList(L1);

	LinkList L2=NULL;
	puts("请输入链表L2中的元素(单词间以空格隔开)");
	CreateListR(&L2,n);
	puts("L2 List:");
	ShowList(L2);
	
	LinkList L3=(LinkList)malloc(sizeof(LNode));
	L3->next=NULL;
	Mer(&L1,&L2,&L3);
	puts("After Merging L3 List:");	
	ShowList(L3);
	/*
	4
    apple banana grape kiwi
    banana grape lemon orange
	*/
}
