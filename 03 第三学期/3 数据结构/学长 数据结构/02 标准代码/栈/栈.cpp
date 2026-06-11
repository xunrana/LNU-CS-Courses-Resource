// 栈
#include <stdio.h>
#include <stdlib.h>

#define OVERFLOW -2
#define OK 1
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Status;
typedef int SElemType;
typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

// 初始化栈
Status InitStack(SqStack &S) {
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}
// 销毁栈
Status DestroyStack(SqStack &S) {
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
    return OK;
}
// 清空栈
Status ClearStack(SqStack &S) {
    S.top = S.base;
    return OK;
}
// 判断栈是否为空
Status StackEmpty(SqStack S) {
    if (S.top == S.base) return 1;
    else return 0;
}
// 返回栈的长度
int StackLength(SqStack S) {
    return S.top - S.base;
}
// 返回栈顶元素
Status GetTop(SqStack S, SElemType &e) {
    if (S.top == S.base) return 0;
    e = *(S.top - 1);
    return OK;
}
// 插入元素
Status Push(SqStack &S, SElemType e) {
    if (S.top - S.base >= S.stacksize) {
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S.base) exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}
// 删除元素
Status Pop(SqStack &S, SElemType &e) {
    if (S.top == S.base) return 0;
    e = *--S.top;
    return OK;
}
// 遍历栈
Status StackTraverse(SqStack S, Status(*visit)(SElemType)) {
    while (S.top > S.base) {
        visit(*S.base++);
    }
    printf("\n");
    return OK;
}
Status visit(SElemType e) {
    printf("%d ", e);
    return OK;
}
int main() {
    SqStack S;
    SElemType e;
    InitStack(S);
    for(int i = 0; i < 10; i++) {
        Push(S, i);
    }
    Pop(S, e);
    printf("%d\n", e);
}