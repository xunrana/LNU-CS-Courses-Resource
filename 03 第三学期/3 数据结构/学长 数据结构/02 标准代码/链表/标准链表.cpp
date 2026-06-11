/*
 * @Author: Peren Liu
 * @Description: 标准链表
 * @Date: [[姓名已脱敏]已脱敏]22-09-19 09:14:36
 * @LastEditTime: [[姓名已脱敏]已脱敏]22-09-22 12:26:10
 */
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;
typedef struct LNode {
    ElemType data;
    struct LNode* next;
} LNode, * LinkList;
// 初始化
Status InitList_L(LinkList& L) {
    L = (LinkList)malloc(sizeof(LNode));
    if (!L)
        exit(OVERFLOW);
    L->next = NULL;
    return OK;
}
// 输出链表
void PrintList_L(LinkList L) {
    LinkList p = L->next;
    while (p) {
        printf("%d ", p->data);
        if (p->next)
            printf("-> ");
        p = p->next;
    }
    printf("\n");
}
// 获取第i个元素
Status GetElem_L(LinkList L, int i, ElemType& e) {
    int j = 1;
    LinkList p = L->next;
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;
    e = p->data;
    return OK;
}
// 在第i个元素之前插入元素e
Status ListInsert_L(LinkList& L, int i, ElemType e) {
    int j = 0;
    LinkList p = L, s;
    while (p && j < i - 1) {
        p = p->next;
        ++j;
    }
    if (!p || j > i - 1)
        return ERROR;
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}
// 在非递减有序链表中插入元素e，使链表仍然有序
Status ListInsert_L2(LinkList& L, ElemType e) {
    // L为头结点
    LinkList p = L, s;
    while (p->next && p->next->data < e)
        p = p->next;
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}
// 头插法
Status ListInsert_L3(LinkList& L, ElemType e) {
    LinkList s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = L->next;
    L->next = s;
    return OK;
}
// 尾插法
Status ListInsert_L4(LinkList& L, ElemType e) {
    LinkList s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = NULL;
    LinkList p = L;
    while (p->next)
        p = p->next;
    p->next = s;
    return OK;
}
// 删除第i个元素,并用e返回其值
Status ListDelete_L(LinkList& L, int i, ElemType& e) {
    int j = 0;
    LinkList p = L, q;
    while (p->next && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i - 1)
        return ERROR;
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}
// 获取链表长度
int GetLength(LinkList L) {
    int len = 0;
    LinkList p = L->next;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

int main() {
    LinkList L;
    InitList_L(L);
    for (int i = 1; i <= 10; i++)
        ListInsert_L(L, i, i);
    PrintList_L(L);
    printf("Length: %d\n", GetLength(L));
    return 0;
}