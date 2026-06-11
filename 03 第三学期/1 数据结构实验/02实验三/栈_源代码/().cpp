#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 100//栈初始化的容量 
#define STACKINCREMENT 10
typedef char SElemType;
typedef int Status;
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
void match()
{
	SqStack S;
	if(InitStack(&S)==1) puts("栈初始化成功！");
	puts("输入一个算术表达式");
	char ch,e;
	int f=0;
	while((ch=getchar())!='\n')
	{
		if(ch=='('||ch==')')
		{
			if(ch=='(') Push(&S,ch);//左括号入栈
			else if(Pop(&S,&e)==-1) f=1;  //右括号如果没有左括号与其匹配,标记匹配失败
		} 
	}
	if(f==0&&StackEmpty(S)) puts("匹配成功");//匹配成功的条件是：最终栈为空栈，  //且为被标记匹配失败
	else puts("匹配失败");
}
int main()
{
	match();
}

