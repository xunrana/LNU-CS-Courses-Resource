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
void Firstsort(LinkList *L)
{
	LinkList premin=(*L),minNode=premin->next,cur=(*L)->next; //初始minNode为第二个结点（头节点不存储数据） pre为其前一个结点 
	while(cur->next)//当前结点从第三个结点(不为空)开始遍历 
	{   //如果当前结点小于最小的结点 
		if(cur->next->data < minNode->data)
		{
			minNode=cur->next;//更新最小的结点（更新其值和指向） 
			premin=cur;       //更新最小的结点的前一个结点 
		}
		cur=cur->next;
	}
	if(minNode!=(*L)->next) //如果当前结点不等于初始链表的第二个结点，说明需要更换结点间指向 
	{
		premin->next=minNode->next;//删除最小的结点原来的位置 
		minNode->next=(*L)->next;//令整个链表（除头节点）接到最小的结点后面 
		(*L)->next=minNode;//链接到头节点 
	}
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
	Firstsort(&L); 
	puts("After Firstsorting:");
	ShowList(L);
    free(&L);
}
