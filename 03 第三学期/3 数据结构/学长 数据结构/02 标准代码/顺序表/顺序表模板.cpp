/*
 * @Author: Peren Liu
 * @Descript：自己写顺序表
 * @Date: [[姓名已脱敏]已脱敏]22-09-17 23:06:[[姓名已脱敏]已脱敏]
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
using namespace std;
typedef int Status;
typedef int ElemType;
typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} SqList;

void ListPrint_Sq(string s, SqList L){
    // 打印顺序线性表L
}
Status InitList_Sq(SqList &L){
    // 构造一个新的线性表 L
}
Status ListInsert_Sq(SqList &L, int i, ElemType e){
    // 在顺序线性表L中第i个位置之前插入新的元素e
}
Status ListDelete_Sq(SqList &L, int i, ElemType &e){
    // 在顺序线性表L中删除第i个元素，并用e返回其值
}
int LocateElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType)){
    // 在顺序线性表L中查找第一个与e满足关系compare()的元素的位序
}
Status MergeList_Sq(SqList La, SqList Lb, SqList &Lc){
    // 已知顺序线性表La和Lb的元素按值非递减排列
    // 归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列
}
int compare(ElemType a, ElemType b){
    return b % a == 0;
}

int main(){

    return 0;
}