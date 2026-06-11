#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct LNode{
	char data[30];//数据域 
	struct LNode *next;//指针域 
}LNode,*LinkList;
void CreateListR(LinkList *L,int n)//尾插法创建链表 
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
LinkList insertsort(LinkList *L)
{
	if(!(*L)) return NULL;
	LinkList p=(*L)->next,Lnew=(LinkList)malloc(sizeof(LNode));
	if(p)
	{
		LinkList tail=(LinkList)malloc(sizeof(LNode));
		Lnew->next=tail;
		strcpy(tail->data,p->data);
		tail->next=NULL;
		while(p->next)
		{
			LinkList q=(LinkList)malloc(sizeof(LNode)),p1=NULL;
			strcpy(q->data,p->next->data);
			p1=Lnew;
			while(p1->next&&strcmp(p->next->data,p1->next->data)>0) p1=p1->next;
			q->next=p1->next;
			p1->next=q;
			p=p->next;
		}
	}
	freelist(L);
	return Lnew;
}

int main()
{
	puts("请输入链表中包含的元素个数n(一个正整数)");
	int n;
	scanf("%d",&n);
	LinkList L1=NULL;
	puts("请输入链表中的元素(单词间以空格隔开)");
	CreateListR(&L1,n);
	puts("This List:");
	ShowList(L1);
	puts("After sorting:");
	L1=insertsort(&L1);
	ShowList(L1);
	freelist(&L1); 
	/*
	5 apple orange banana mango pineapple
	*/
}
