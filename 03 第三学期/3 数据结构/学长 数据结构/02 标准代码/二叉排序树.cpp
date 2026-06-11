#include <iostream>
#include <string>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;
typedef struct BiTNode {
    ElemType data;
    struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

using namespace std;

Status CreateBiTree(BiTree& T) {
    ElemType ch;
    cin >> ch;
    while (ch == ' ' || ch == '\n')
        // 跳过空格和换行符
        cin >> ch;
    if (ch == '#')
        T = NULL;
    else {
        T = (BiTree)malloc(sizeof(BiTNode));
        if (!T) exit(-1);
        T->data = ch;               // 生成根结点
        CreateBiTree(T->lchild);    // 递归创建左子树
        CreateBiTree(T->rchild);    // 递归创建右子树
    }
    return OK;
}

void PreOrder(BiTree T) {   // 先序遍历
    if (T) {
        cout << T->data << ' ';
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T) {    // 中序遍历
    if (T) {
        InOrder(T->lchild);
        cout << T->data << ' ';
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T) {  // 后序遍历
    if (T) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        cout << T->data << ' ';
    }
}

int CountLeaf(BiTree T) {   // 统计叶子结点数
    if (!T)
        return 0;
    if (!T->lchild && !T->rchild)
        return 1;
    return CountLeaf(T->lchild) + CountLeaf(T->rchild);
}

// 写一递归算法实现统计二叉树度为 1 结点总数,不使用全局变量
int CountOne(BiTree T) {
    if (!T) // 空树
        return 0;
    if ((!T->lchild && T->rchild) || (T->lchild && !T->rchild))
        // 有一个孩子为空
        return 1 + CountOne(T->lchild) + CountOne(T->rchild);
    // 两个孩子都不为空或者都为空
    return CountOne(T->lchild) + CountOne(T->rchild);
}

// 写一递归算法实现计算二叉树的深度
int Depth(BiTree T) {
    if (!T) // 空树
        return 0;
    int ldepth = Depth(T->lchild);
    int rdepth = Depth(T->rchild);
    return ldepth > rdepth ? ldepth + 1 : rdepth + 1;
}

int ASL(BiTree T, int depth) {
    // 求二叉排序树的平均查找长度
    if (!T) // 空树
        return 0;
    return depth + ASL(T->lchild, depth + 1) + ASL(T->rchild, depth + 1);
}

int main() {
    int length = 9;    // 二叉排序树的长度
    int arr[length] = { 15, 13, 16, 9, 35, 11, 7, 19, 1 };    // 二叉排序树的数组
    // 给出按表中元素顺序依次插入一个空的二叉排序树的过程
    // 生成二叉排序树
    BiTree T = NULL;
    for (int i = 0; i < length; i++) {
        BiTree p = T, q = NULL;
        while (p) {
            q = p;
            if (arr[i] < p->data)
                p = p->lchild;
            else
                p = p->rchild;
        }
        p = (BiTree)malloc(sizeof(BiTNode));
        p->data = arr[i];
        p->lchild = p->rchild = NULL;
        if (!q)
            T = p;
        else if (arr[i] < q->data)
            q->lchild = p;
        else
            q->rchild = p;
    }
    // 先序遍历
    PreOrder(T);
    cout << endl;
    // 中序遍历
    InOrder(T);
    cout << endl;
    // 求其在等概率下的平均查找长度
    int sum = ASL(T, 1);
    cout << "平均查找长度为: " << sum << "/" << length << " = " << (double)sum / length << endl;
}