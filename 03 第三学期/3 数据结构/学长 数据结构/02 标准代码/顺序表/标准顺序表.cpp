/*
 * @Author: Peren Liu
 * @Description: 标准顺序表
 * @Date: [[姓名已脱敏]已脱敏]22-09-16 [[姓名已脱敏]已脱敏]:30:30
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
// 定义顺序表
typedef struct {
    ElemType* elem;
    int length;
    int listsize;
} SqList;
// 构造一个新的线性表 L
Status InitList_Sq(SqList& L) {
    L.elem = (ElemType*)malloc(100 * sizeof(ElemType));
    if (!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    L.listsize = 100;
    return OK;
}
// 在顺序线性表L中第i个位置之前插入新的元素e
Status ListInsert_Sq(SqList& L, int i, ElemType e) {
    ElemType* newbase, * p, * q;
    if (i < 1 || i > L.length + 1)
        return ERROR;
    if (L.length >= L.listsize) {
        newbase = (ElemType*)realloc(L.elem, (L.listsize + 100) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);
        L.elem = newbase;
        L.listsize += 100;
    }
    q = &(L.elem[i - 1]);
    for (p = &(L.elem[L.length - 1]); p >= q; --p)
        *(p + 1) = *p;
    *q = e;
    ++L.length;
    return OK;
}
// 在顺序线性表L中删除第i个元素，并用e返回其值
Status ListDelete_Sq(SqList& L, int i, ElemType& e) {
    ElemType* p, * q;
    if (i < 1 || i > L.length)
        return ERROR;
    p = &(L.elem[i - 1]);
    e = *p;
    q = L.elem + L.length - 1;
    for (++p; p <= q; ++p)
        *(p - 1) = *p;
    --L.length;
    return OK;
}
// 在顺序线性表L中查找第一个与e相等的元素的位序
int LocateElem_Sq(SqList L, ElemType e) {
    int i = 1;
    ElemType* p = L.elem;
    while (i <= L.length && *p != e) {
        ++i;
        ++p;
    }
    if (i <= L.length)
        return i;
    else
        return 0;
}
// 打印顺序线性表L
Status ListPrint_Sq(SqList L) {
    ElemType* p = L.elem;
    printf("(%d) ", L.length);
    for (int i = 0; i < L.length; ++i) {
        printf("%d ", *p);
        ++p;
    }
    printf("\n");
    return OK;
}
// 已知顺序线性表La和Lb的元素按值非递减排列，归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列
Status MergeList_Sq(SqList La, SqList Lb, SqList& Lc) {
    ElemType* pa, * pb, * pc, * pa_last, * pb_last;
    pa = La.elem;
    pb = Lb.elem;
    Lc.listsize = Lc.length = La.length + Lb.length;
    pc = Lc.elem = (ElemType*)malloc(Lc.listsize * sizeof(ElemType));
    if (!Lc.elem)
        exit(OVERFLOW);
    pa_last = La.elem + La.length - 1;
    pb_last = Lb.elem + Lb.length - 1;
    while (pa <= pa_last && pb <= pb_last) {
        if (*pa <= *pb)
            *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }
    while (pa <= pa_last)
        *pc++ = *pa++;
    while (pb <= pb_last)
        *pc++ = *pb++;
    return OK;
}

int main() {
    SqList L;
    InitList_Sq(L);
    ListInsert_Sq(L, 1, 1);
    ListInsert_Sq(L, 2, 2);
    ListInsert_Sq(L, 3, 3);
    ListInsert_Sq(L, 4, 4);
    ListInsert_Sq(L, 5, 5);
    ElemType e;
    ListDelete_Sq(L, 3, e);
    ListPrint_Sq(L);
    free(L.elem);
    return 0;
}