#include <stdio.h>
#include <stdlib.h>
typedef struct LNode{
	int data;//数据域 
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
		scanf("%d",&p->data);
		r->next=p;//链接上新节点 
		r=p;//更新尾结点 
	}
	r->next=NULL;//尾结点标志，指向NULL 
}
void ShowList(LinkList L)
{
	LinkList p=L->next;//头节点不存储元素 
	while(p)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	putchar('\n');
}
void free(LinkList *L)
{
	LinkList p=(*L),t;
	while(p)
	{
		t=p->next;
		free(p);
		p=t;
	}
}
int Change(LinkList *L,int m)
{
	if(m<1) return 0;//输入错误
    LinkList p1=*L,p2=*L,t;
	while(m--)//令p2指向第k+1个结点 
	{
		if(p2->next==NULL) return 0; //说明单链表没有第k+1个结点，无法删除 
		p2=p2->next;
	}
	while(p2->next)//同时移动指针，退出循环的条件是p2指向最后一个结点 
	{
		p1=p1->next;
		p2=p2->next;
	}
	t=p1->next;
	p1->next=NULL;
	
	p2->next=(*L)->next;
	(*L)->next=t;
	return 1;
} 
LNode Mid(LinkList *L)
{
	LinkList p1=*L,p2=*L;
	while(p2)
	{
		p1=p1->next;
		p2=p2->next;
		if(p2) p2=p2->next;
	}
	return *p1;
} 
int main()
{
	puts("请输入链表中包含的元素个数n(一个正整数)");
	int n;
	scanf("%d",&n);
	LinkList L=NULL;
	puts("请输入链表中的元素(整数间以空格隔开)");
	CreateListR(&L,n);
	puts("This List:");
	ShowList(L);
	
	
	printf("%d\n",Mid(&L).data);
	/*
    puts("请输入m：");
	int m;
	scanf("%d",&m);
	printf("%d\n",Change(&L,m)); 
	puts("After Changing:");
	ShowList(L);
	free(&L);
	*/
}
