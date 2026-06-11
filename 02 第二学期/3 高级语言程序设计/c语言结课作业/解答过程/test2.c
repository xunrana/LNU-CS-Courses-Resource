#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s
{
    char num[12];   // [姓名已脱敏]
    char name[9];   // 学生[姓名已脱敏]
    char major[6];  // 学生专业
    int c;          // c语言
    int p1;         // 计算物理
    int p2;         // 大学物理
    int p3;         // 原子物理
    int o;          // optics 光学
    int sum;        // 总成绩
    int order_major;
    int order_class;
    struct s* next; // 下一个同学
} St;

void show_st(St* head)
{
    St* p;
    puts("   [姓名已脱敏]     [姓名已脱敏]     专业     C语言  计算物理学   大学物理  原子物理   光学    总成绩   班级名次  年级名次");
    for (p = head; p != NULL; p = p->next)
        printf("%s %-8s %-5s %3d %3d %3d %3d %3d %3d\n", p->num, p->name, p->major, p->c, p->p1, p->p2, p->p3, p->o, p->sum);
}

void order_st(St* head)
{
    int swapped;
    St* ptr1;
    St* lptr = NULL;

    /* 如果链表为空，直接返回 */
    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            /* 按总成绩降序排序 */
            if (ptr1->sum < ptr1->next->sum)
            {
                // 交换节点
                St* temp = ptr1->next;
                ptr1->next = temp->next;
                temp->next = ptr1;

                // 更新头节点
                if (ptr1 == head)
                    head = temp;
                else
                {
                    St* prev = head;
                    while (prev->next != ptr1)
                        prev = prev->next;
                    prev->next = temp;
                }
                swapped = 1;
            }
            else
                ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    show_st(head); // 显示排序后的结果
}


int main()
{
    St *p, *head = NULL, *tail = NULL;
    int a = 5;

    while (a--)
    {
        p = (St*)malloc(sizeof(St));
        if (p == NULL)
        {
            printf("内存分配失败");
            return 1;
        }

        scanf("%s %s %s %d %d %d %d %d", p->num, p->name, p->major, &p->c, &p->p1, &p->p2, &p->p3, &p->o);
        p->sum = p->o + p->p1 + p->p2 + p->p3 + p->c;
        p->order_major = 0;
        p->order_class = 0;

        p->next = NULL; // 确保新节点的next指针为NULL

        if (head == NULL)
            head = tail = p;
        else
        {
            tail->next = p;
            tail = p;
        }
    }

    order_st(head);

    // 释放内存
    St* current = head;
    while (current != NULL)
    {
        St* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

