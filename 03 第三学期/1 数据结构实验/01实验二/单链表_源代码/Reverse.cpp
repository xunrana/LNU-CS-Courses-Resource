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
void reverse(LinkList *L) 
{
    LinkList prev=NULL,curr=(*L)->next,temp;
    while(curr)//当前结点不为空时进入循环 
	{
        temp=curr->next;//储存当前结点的下一个结点 
        curr->next=prev;//改变指向 
        prev=curr;//更新前一个结点 
        curr=temp;//更新当前结点 
    }
    (*L)->next=prev;//链接头节点 
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
	reverse(&L); 
	puts("After Reversing:");
	ShowList(L);
    free(&L);
}
