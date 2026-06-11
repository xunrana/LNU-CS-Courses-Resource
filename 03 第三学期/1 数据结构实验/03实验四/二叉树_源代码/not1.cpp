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
int not1(BiTree T)
{
	if(T)//不为空时 
	{
		if((T->lchild&&!T->rchild)||(!T->lchild&&T->rchild)) return 0;//该节点度为1,不满足，返回0 
		return not1(T->lchild)&&not1(T->rchild);
		//递归遍历左右子树是否存在不满足的情况，&&表示存在一个度为1的结点，函数最终返回0 
	}
	return 1; 
}
int main()
{
	BiTree T=NULL;//定义根结点 
	CreateBiTree(&T);//ABC##DE###FGH##I#J###
	printf("该二叉树是否只含度为0或2的结点：%d",not1(T)); //abc####  abc##d##ed###
}

