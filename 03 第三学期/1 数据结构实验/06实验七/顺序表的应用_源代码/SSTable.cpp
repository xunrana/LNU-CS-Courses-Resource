#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
typedef struct{
	long long ISBN;//书籍的ISBN编号
	char bname[40];//书籍名称
	double bprice;//书籍价格 
}ElemType;
typedef struct{//顺序查找表结构体
	ElemType *elem;//元素数组指针
	int length;//数组长度
}SSTable;
void CreateList(SSTable *L,int n)//创建图书列表
{
	if(n>N||n<1) return ;//如果数量超出范围，直接返回
	L->elem=(ElemType*)malloc((n+1)*sizeof(ElemType));//分配内存
	L->length=n;//设置数组长度 
	printf("按顺序依次输入:ISBN 书名 定价(空格隔开)\n");//提示输入格式 
	//逐个输入书籍信息
	for(int i=1;i<=n;i++) scanf("%lld %s %lf",&L->elem[i].ISBN,L->elem[i].bname,&L->elem[i].bprice);
}
void ShowList(SSTable L)//显示图书列表
{
	puts("    ISBN            name         price");//打印表头
	//打印每本书籍的信息
	for(int i=1;i<=L.length;i++) printf("%lld %-[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬s %.6f\n",L.elem[i].ISBN,L.elem[i].bname,L.elem[i].bprice);
}
int Partition(SSTable *L,int low,int high)//划分函数 
{
	long long pivotkey=L->elem[low].ISBN;//以第一个元素为基准 
	ElemType t;
	while(low<high)
	{
		//从右往左找到小于基准的元素
		while(low<high&&L->elem[high].ISBN>=pivotkey) high--;
		t=L->elem[high];
		L->elem[high]=L->elem[low];
		L->elem[low]=t;//交换元素 
		//从左往右找到大于基准的元素
		while(low<high&&L->elem[low].ISBN<=pivotkey) low++;
		t=L->elem[high];
		L->elem[high]=L->elem[low];
		L->elem[low]=t;//交换元素 
	}
	return low;//返回基准的位置 
}
void QSort(SSTable *L,int low,int high)//快速排序 
{
	if(low<high)
	{
		int pivotloc=Partition(L,low,high);//划分数组 
		QSort(L,low,pivotloc-1);//左半部分递归排序 
		QSort(L,pivotloc+1,high);//右半部分递归排序 
	}
}
int Find_ISBN(SSTable L,long long ISBN)//二分查找 
{
	int low=1,high=L.length;//初始化查找的范围 
	while(low<=high)//循环查找的条件 
	{
		int mid=(low+high)/2;//计算中间位置 
		if(ISBN==L.elem[mid].ISBN) return mid;//找到则返回位置 
		else if(ISBN<L.elem[mid].ISBN) high=mid-1;//缩小右边界 
		else low=mid+1;//缩小左边界 
	}
	return 0;//没找到返回0 
}
int Find_bname(SSTable L,char *bname)//顺序查找 
{
	int p=L.length;//从最后一个开始找 
	while(p&&strcmp(L.elem[p].bname,bname)!=0) p--;//从后往前找	
	return p;//返回找到的位置或0（表示未找到） 
}

int main()
{
	SSTable ST;//创建图书表 
	int n;
	printf("请输入一共有多少本图书:");
	scanf("%d",&n); //输入图书数量 
	CreateList(&ST,n);//创建图书列表 
	puts("你依次输入的图书是:"); 
	ShowList(ST);//显示输入的图书 
	puts("按ISBN排序后：");
	QSort(&ST,1,n);//按ISBN排序 
	ShowList(ST);//显示排序后的图书 
	
	long long ISBN;
	puts("输入你想要查找的图书的ISBN:"); 
	scanf("%lld",&ISBN); 
	if(Find_ISBN(ST,ISBN)==0) printf("没有ISBN为：%lld的书。",ISBN);
	else printf("ISBN:%lld的位次是%d\n",ISBN,Find_ISBN(ST,ISBN));
	
	char bname[40];
	puts("输入你想要查找的图书的书名:");
	scanf("%s",bname);
	if(Find_bname(ST,bname)==0) printf("没有书名为：%s的书。",bname);
	else printf("ISBN:%s的位次是%d\n",bname,Find_bname(ST,bname));
} 
