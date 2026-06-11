#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 100//栈初始化的容量 
#define STACKINCREMENT 10
typedef char SElemType;
typedef char Status;
typedef struct       //定义顺序栈 
{
	SElemType *base; //栈底指针 
	SElemType *top;  //栈顶指针 
	int stacksize;   //当前栈的大小（已经分配的空间） 
}SqStack;
int InitStack(SqStack *S)
{
	S->base=(SElemType*)malloc(sizeof(SElemType)*INIT_SIZE);//为栈申请空间 
	if(!S->base) exit(1);
	S->top=S->base;  //初始化栈顶指针和栈底指针指向同一个位置，栈为空 
	S->stacksize=INIT_SIZE;//栈的大小 
	return 1;        //成功初始化栈，函数返回1 
}
Status StackEmpty(SqStack S)
{
	if(S.top==S.base) return true;  //栈顶指针和栈底指针指向同一个位置，栈为空
	else return false;              //栈不空 
}
Status Pop(SqStack *S,SElemType *e)
{
	if(S->top==S->base) return -1; //栈为空，不能pop出元素，返回-1 
	*e=*(--S->top);  //栈不空,栈顶指针后退一个单位，取出栈顶元素 
	return 1;
}
Status Push(SqStack *S,SElemType e)
{
	if(((S->top)-(S->base))==S->stacksize) 
	{//如果此时栈的容量达到最大容量，需要再为栈扩大容量申请空间
		S->base=(SElemType*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S->base) exit(-2);
		S->top=S->base+S->stacksize;
		S->stacksize+=STACKINCREMENT;
	}
	*S->top++=e;//先将元素e存入栈顶位置，然后s->top++,移动栈顶指针到下一个位置
	return 1;
}
int main()
{
	SqStack S;
	if(InitStack(&S)==1) puts("栈初始化成功！");
	puts("输入一个正整数(十进制)");
	int nums;
	char e;//定义栈内元素 
	scanf("%d",&nums);//读入十进制数 
	printf("十进制数%d的十六进制数为\n",nums); 
	if(nums==0) Push(&S,'0');//直接入0 
	else while(nums)
	{
		if(nums%16>9) e=nums%16-10+'a';//将字符字母入栈 
		else e=nums%16+'0';//将字符数字入栈 
		Push(&S,e);
		nums/=16;//更新nums 
	}
	while(!StackEmpty(S))
	{
		Pop(&S,&e);//弹栈 
		putchar(e);//输出 
	}
}
