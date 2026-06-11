#include <stdio.h>
#include <stdlib.h>//malloc函数头文件 
typedef struct node
{
	int val;
	struct node *next;
}LNode,*LinkList;
void ShowList(LinkList head)
{
	LinkList current=head->next;//头节点的下一个结点
	while(current) 
	{
		printf("%d ",current->val); //打印数值 
		current=current->next;//头节点往后移动 
	}
	putchar('\n');
}
LinkList CreateList()
{
	LinkList head=(LinkList)malloc(sizeof(LNode));
	LinkList p=NULL,tail=NULL;
	int val;
	while(1)
	{
		scanf("%d",&val);
		if(val==-1) break;
		if(!p)//若p为空 开辟空间 
		{
			p=tail=(LinkList)malloc(sizeof(LNode));
			tail->val=val;
		}
		else//若p不为空 为tail->next开辟空间 
		{
			tail->next=(LinkList)malloc(sizeof(LNode));
			tail->next->val=val;
			tail=tail->next;
		}
		tail->next=NULL;
	}
	head->next=p;//头节点不存储数据 
	return head;
}
LinkList DeleteLast(LinkList L,int n)
{
    LinkList p=L->next,t;
    int length=0,cnt=0;
    while(p) 
	{
		length++;
		p=p->next;
	}
	if(n>length) printf("没有倒数第%d个结点\n",n);
	else if(n==length)
	{
		t=L->next;
		L->next=t->next;
		free(t);
		printf("删除后："); 
		ShowList(L);
	}
	else
	{
		p=L->next; 
		while(p) 
	    {
		    cnt++;
		    if(cnt==length-n) break;
		    p=p->next;
	    }
		t=p->next;
		p->next=t->next;
		free(t);
		printf("删除后："); 
		ShowList(L);
	}
	return L;
}
int main()
{
//测试用例：
//1 2 3 4 5 -1 1
//1 2 3 4 5 -1 5
//1 2 3 4 5 -1 3
	LinkList L; 
	L=CreateList();
	int n;
	scanf("%d",&n);
	printf("删除前："); 
	ShowList(L);
	L=DeleteLast(L,n);
} 

LinkList DeleteLast1(LinkList L,int n)
{
    LinkList p1=L,p2=L,t;
	int cnt=0;
    for(int i=0;i<=n;i++) 
	{
		cnt++;
		p1=p1->next;
		if(!p1) break;
	}
	if(cnt==n) printf("没有倒数第%d个结点\n",n);
	else
	{
		while(p1)
		{
			p1=p1->next;
			p2=p2->next;
		}
		t=p2->next;
		p2->next=t->next;
		free(t);
		printf("删除后："); 
		ShowList(L);
	}
	return L;
}
