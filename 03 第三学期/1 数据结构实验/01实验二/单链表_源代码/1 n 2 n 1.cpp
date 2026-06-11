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
		p->data=i;
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
		printf("%-3d ",p->data);
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
void resort(LinkList &L)
{
	LinkList prem,m,p,p1,p2,t,t1,t2,pre=NULL;
	prem=NULL;
	m=p=L;
	p1=L->next;
	while(p)
	{
		if(p->next) p=p->next->next;
		else p=p->next;
		prem=m;
		m=m->next;
	}
	prem->next=NULL;
	printf("mid:%-3d\n",m->data);
	
	while(m)
	{
		t=m->next;
		m->next=pre;
		pre=m;
		m=t;
	}
	p2=pre;
	
	printf("p1:");
	p=p1;
	while(p) printf("%-3d ",p->data),p=p->next;
	putchar('\n');
	
	printf("p2:");
	p=p2;
	while(p) printf("%-3d ",p->data),p=p->next;
	putchar('\n');
	
	while(p2->next&&p1->next)
	{
		t1=p1->next;
		t2=p2->next;
		p1->next=p2;
		p2->next=t1;
		p1=t1;
		p2=t2;
	}
	p1->next=p2;
}
int main()
{
	puts("请输入链表中包含的元素个数n(一个正整数)");
	int n;
	scanf("%d",&n);
	LinkList L=NULL;
	CreateListR(&L,n);
	puts("This List:");
	ShowList(L);
	puts("After resorting:\n");
	resort(L);
	puts("This List:");
	ShowList(L);
}
