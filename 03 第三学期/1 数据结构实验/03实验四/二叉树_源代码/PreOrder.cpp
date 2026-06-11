#include <stdio.h>
#include <stdlib.h>
typedef struct BiTNode
{
	char data;//数据元素 
	struct BiTNode *lchild,*rchild;//左结点、右结点 
}BiTNode,*BiTree;
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
void PreOrder(BiTree T)//先序遍历：根左右
{
	if(T)//该根结点不空时 
	{
	    printf("%c",T->data);//输入根节点元素 
	    PreOrder(T->lchild);//递归先序遍历左子树 
	    PreOrder(T->rchild);//递归先序遍历右子树 
	}
}
void InOrder(BiTree T)//中序遍历：左根右
{
	if(T)//该根结点不空时 
	{
		InOrder(T->lchild);//递归中序遍历左子树 
	    printf("%c",T->data);//输出根节点元素 
	    InOrder(T->rchild);//递归中序遍历右子树 
	}
}
void PostOrder(BiTree T)//后序遍历：左右根
{
	if(T)//该根结点不空时 
	{
		PostOrder(T->lchild);//递归后序遍历左子树 
	    PostOrder(T->rchild);//递归后序遍历右子树 
	    printf("%c",T->data);//输出根节点元素 
	}
}
int main()
{
	BiTree T=NULL;//定义根结点 
	CreateBiTree(&T);//ABC##DE###FGH##I#J###
	puts("先序遍历的结果是:");
	PreOrder(T); 
	putchar('\n');
	
	puts("中序遍历的结果是:");
	InOrder(T); 
	putchar('\n');
	
	puts("后序遍历的结果是:");
	PostOrder(T); 
	putchar('\n');
}
