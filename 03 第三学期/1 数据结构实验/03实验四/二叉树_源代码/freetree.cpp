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
void freetree(BiTree *T)
{
	if(*T)//如果该节点不空 
	{
		if((*T)->lchild) freetree(&(*T)->lchild);//左节点不空，递归遍历左节点 
		if((*T)->rchild) freetree(&(*T)->rchild);//右节点不空，递归遍历右节点 
		free(*T);//删除根节点 
		*T=NULL;//防止野指针 
	}
}
int main()
{
	BiTree T=NULL;//定义根结点 
	CreateBiTree(&T);//ABC##DE###FGH##I#J###
	freetree(&T); //abc####  abc##d##ed###
	PreOrder(T);
}
