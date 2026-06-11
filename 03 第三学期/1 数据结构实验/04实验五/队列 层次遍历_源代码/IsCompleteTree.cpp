#include <stdio.h>
#include <stdlib.h>
#define QElemType BiTree//队列元素为BiTree 
#define Status int//函数返回、一般1为true，0为false 
typedef struct BiTNode//二叉树的节点的定义 
{
	char data;//节点中储存的数据
	struct BiTNode *lchild,*rchild;//左孩子结点、右孩子结点 
}BiTNode,*BiTree;
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
Status QueueEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear) return 1;//队列空 
	else return 0;
}
void CreateBiTree(BiTree *T)
{
	char ch;
	ch=getchar();//读入一个字符 
	if(ch=='#') *T=NULL;//该结点为空 
	else
	{
		*T=(BiTNode*)malloc(sizeof(BiTNode));//申请空间 
		if(NULL==*T) exit(-2);
		(*T)->data=ch;//ch赋值给该结点数据域的元素 
		CreateBiTree(&((*T)->lchild));//递归创建左子树 
		CreateBiTree(&((*T)->rchild));//递归创建右子树 
	}
}
int IsCompleteTree(BiTree T) 
{
    if(!T) return 1;//为完全二叉树 
    LinkQueue Q;//创建链式队列Q 
    InitQueue(Q);//初始化队列 
    EnQueue(Q,T);//根节点入队 
    int l,length=1;//l记录下一层节点数量，length为当前层节点数量 
    int f=0;//标志是否遇到不完全节点 
    while(!QueueEmpty(Q))//队列不空时循环 
	{
		l=0;//下一层数量初始化为0 
        for(int i=0;i<length;i++)//处理当前层节点 
		{
		    BiTree temp;
		    DeQueue(Q,temp);
		    //如果已经遇到不完全节点并且当前节点有左右孩子，则不是完全二叉树
		    if(f==1&&(temp->lchild||temp->rchild)) return 0; 
			if(temp->lchild) EnQueue(Q,temp->lchild),l++;//左子节点入队，并记录下一层节点数量
			else f=1;//设置标志，表示已经遇到不完全节点
			//如果已经遇到不完全节点，并且当前节点有右孩子，则不是完全二叉树
			if(f==1&&temp->rchild) return 0; 
		    if(temp->rchild) EnQueue(Q,temp->rchild),l++;//右子节点入队，并记录下一层节点数量
			else f=1;//设置标志，表示已经遇到不完全节点
        }
        length=l;
    }
    DestroyQueue(Q);//销毁队列 
    return 1;//是完全二叉树 
}
/*
(BiTree T)
{
	if(!T) return 1;
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q,T);
	int f=0; 
	while(!QueueEmpty(Q))
	{
		LinkQueue Q1;
	    InitQueue(Q1);
		while(!QueueEmpty(Q))
		{
		    BiTree temp;
		    DeQueue(Q,temp);
		    if(f==1&&(temp->lchild||temp->rchild)) return 0; 
			if(temp->lchild) EnQueue(Q1,temp->lchild);
			else f=1;
			if(f==1&&temp->rchild) return 0; 
		    if(temp->rchild) EnQueue(Q1,temp->rchild);
			else f=1;	
		}
		DestroyQueue(Q);
		Q=Q1;
	}
	DestroyQueue(Q);
	return 1;
}
*/
int main()
{
	puts("输入测试的二叉树的个数:"); 
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		getchar();
		printf("输入第%d棵二叉树\n",i);
		BiTree T=NULL;//定义根结点 
	    CreateBiTree(&T);
	    printf("二叉树是否为完全二叉树:");//A## AB### A#B## AB##C## AB##CD### AB#D##C## ABC####
	    if(IsCompleteTree(T)) printf("Yes\n");
	    else printf("No\n");
	}
}
