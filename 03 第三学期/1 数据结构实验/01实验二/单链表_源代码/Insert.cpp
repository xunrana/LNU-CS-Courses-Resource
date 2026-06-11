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
void Insert(LinkList *L,int e)
{
	LinkList p=*L;
	while(p->next&&p->next->data < e) p=p->next;//找到插入位置的前一个结点 
	LinkList q=(LinkList)malloc(sizeof(LNode));//为新节点申请内存 
	q->data=e;
	q->next=p->next;//先为新节点链接后面 
	p->next=q; //再为新节点链接前面 
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
	puts("请输入你要插入的元素e");
	int e;
	scanf("%d",&e);
	Insert(&L,e);
	puts("After inserting:");
	ShowList(L);
    free(&L);
}
