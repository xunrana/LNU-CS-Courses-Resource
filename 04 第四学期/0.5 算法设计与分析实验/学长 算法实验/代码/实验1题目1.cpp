#include <iostream>
#define OK 1
typedef int Status;
typedef int ElemType;
typedef struct BiTNode
{
    ElemType data;
    int maxChild; // 左右孩子哪端和最大，0表示左，1表示右
    struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;
using namespace std;

Status CreateBiTree(BiTree& T) {
    // 按先序次序输入二叉树中结点的值（一个整数），0表示空树
    int num;
    cin >> num;
    if (num == 0) {
        T = NULL;
    }
    else {
        T = new BiTNode;
        T->data = num;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

// 假设二叉树中的所有节点值为int类型，采用二叉链表存储。设计递归算法求二叉树bt中从根结点到叶子结点路径和最大的一条路径。
int maxPath(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    int left = maxPath(T->lchild);
    int right = maxPath(T->rchild);
    if (left > right) {
        T->maxChild = 0;
        return left + T->data;
    }
    else {
        T->maxChild = 1;
        return right + T->data;
    }
} 

void solve(BiTree T) {
    // 追溯解路径
    BiTree p = T;
    int sum = 0;    // 路径和
    while (p) {
        cout << p->data << " -> ";
        sum += p->data;
        if (p->maxChild == 0) {
            p = p->lchild;
        }
        else {
            p = p->rchild;
        }
    }
    cout << endl << "sum: " << sum << endl;
}

int main()
{
    BiTree T;
    CreateBiTree(T);
    // 5 2 0 3 0 0 4 1 0 0 6 0 0
    maxPath(T);
    // 追溯解路径
    solve(T);
    return 0;
}