#include <stdio.h>
#include <stdlib.h>
#define QElemType int
#define Status int
typedef struct QNode//链式队列的节点的定义 
{
	QElemType data; //节点储存的数据 
	struct QNode *next;//指向下一个节点的指针 
}QNode,*QueuePtr;
typedef struct LinkQueue//链式队列的定义 
{
	QueuePtr front;//指向队列头部的指针 
	QueuePtr rear;//指向队列尾部的指针 
}LinkQueue;
Status InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	//初始化队列，分配头节点空间 
	if(!Q.front) exit(-1);
	Q.front->next=NULL;//头节点指向空 
	return 1;
}
Status EnQueue(LinkQueue &Q,QElemType e)
{
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));//分配新节点空间 
	if(!p) exit(0);
	p->data=e;//设置新节点数据 
	p->next=NULL;
	Q.rear->next=p;//新节点作为尾节点 
	Q.rear=p;
	return 1;
}
Status DeQueue(LinkQueue &Q,QElemType &e)
{
	QueuePtr p;
	if(Q.front==Q.rear) return -1;//空队列 
	p=Q.front->next;//第一个实际节点 
	e=p->data;//获取节点数据 
	Q.front->next=p->next;//头节点指向下一个节点 
	if(Q.rear==p) Q.rear=Q.front;//若删除的是最后一个节点 
	free(p);//释放节点 
	return 1;
}
Status QueueEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear) return 1;//队列空 
	else return 0;
}
Status DestroyQueue(LinkQueue &Q)
{
	while(Q.front)
	{
		Q.rear=Q.front->next;//移动尾指针 
		free(Q.front);//释放头节点 
		Q.front=Q.rear;//头指针指向下一个节点 
	}
	return 1;
}
int main()
{
	LinkQueue Q;//声明一个链式队列 
	InitQueue(Q);//初始化链式队列 
	printf("入队的顺序为:\n");
	for(int i=1;i<=10;i++) 
	{
		printf("%d ",i);
	    EnQueue(Q,i);//入队
    }   
	printf("\n出队的顺序为:\n"); 
	while(!QueueEmpty(Q))
	{
		int e;
        DeQueue(Q,e);//出队
		printf("%d ",e);
	}
	DestroyQueue(Q);//销毁队列 
}
