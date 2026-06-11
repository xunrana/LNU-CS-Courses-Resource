#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000//顺序表最大容量，即L->listsize的值
typedef struct 
{
	int *elem;
	int length;
	int listsize;
}SqList;
int InitList_Sq(SqList *L)
{
	L->elem=(int*)malloc(sizeof(int)*MAX);//初始化顺序表
	if(!L->elem) exit(-2);
	L->length=0;//初始化，有效长度为0
	L->listsize=MAX;
	return 1;
}
void CreateList(SqList *L,int n)
{
	if(n<0) return ;
	printf("请为顺序表输入%d个整数：\n",n);
	for(int i=0;i<n;i++) scanf("%d",&L->elem[i]);
	L->length=n;//更新顺序表有效长度
}
void PrintList(SqList L)
{
	printf("顺序表中的数据依次为:\n");
	for(int i=0;i<L.length;i++) printf("%d ",L.elem[i]);
	putchar('\n');
}
void InsertList(SqList *L,int e)
{//函数实现需保证listsize（顺序表最大容量）>length(顺序表有效长度)
	int i,j;
	for(i=0;i<L->length;i++)
	if(e<L->elem[i]) break;
	for(int j=L->length;j>i;j--) L->elem[j]=L->elem[j-1];
	L->elem[i]=e;
	L->length=L->length+1;
}
int main()
{
	SqList L;
	InitList_Sq(&L);
	int n;
	printf("请输入顺序表元素的个数:\n");
	scanf("%d",&n); 
	CreateList(&L,n);
	PrintList(L);
	printf("输入你要插入的数:");
	int e;
	scanf("%d",&e);
	InsertList(&L,e);
	PrintList(L);
	free(L.elem);
}

