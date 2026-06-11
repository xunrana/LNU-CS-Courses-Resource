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
int sumLeaf(BiTree T)
{
	if(T)//根结点不为空时 
	{
		if(!T->lchild&&!T->rchild) return 1;//该结点为叶子结点 
		return sumLeaf(T->lchild)+sumLeaf(T->rchild);//递归返回左子树的叶子节点+右子树的叶子节点 
	}
	return 0;//根节点为空是，返回0 
}
int main()
{
	BiTree T=NULL;//定义根结点 
	CreateBiTree(&T);//ABC##DE###FGH##I#J###
	printf("度为0的结点数是%d",sumLeaf(T));
}

