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
int sum1(BiTree T)
{
	if(T)
	{
		if(T->lchild&&T->rchild) return sum1(T->lchild)+sum1(T->rchild); //该结点不符合，递归其左右子树 
		else if(T->lchild) return sum1(T->lchild)+1; //该结点符合，递归其左子树 
		else if(T->rchild) return sum1(T->rchild)+1; //该结点符合，递归其右子树 
		else return 0;//不符合 
	}
	return 0;//不符合 
}
int main()
{
	BiTree T=NULL;//定义根结点 
	CreateBiTree(&T);//ABC##DE###FGH##I#J###
	printf("度为1的结点数是%d",sum1(T)); //abc####  abc##d##ed###
}

