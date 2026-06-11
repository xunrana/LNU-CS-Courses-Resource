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
int ListDel_Sq(SqList *L,int i,int k)
{// 删除下标为[i-1,i-1+k-1]的元素，数组越界，return 0，无法删除
    if(i+k-2>=L->length) return 0;
	int j=i+k-2+1;
	i=i-1;
	while(j<L->length) L->elem[i++]=L->elem[j++];//更新删除后元素
	L->length=i;//更新顺序表有效长度
	return 1;
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
	printf("第i个数开始删除k个数，输入i，k：\n");
	int i,k;
	scanf("%d %d",&i,&k);
	ListDel_Sq(&L,i,k);
	PrintList(L);
	free(L.elem);
}

