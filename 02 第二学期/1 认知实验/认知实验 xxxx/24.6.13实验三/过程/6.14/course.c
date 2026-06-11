#include "course.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Course *ph_course = NULL;

void pri_course(Course *p) {
    if (p) {
        printf("课程号:%d\t课程名:%s\t学分:%d\t学时:%d\n", p->num, p->name, p->credit, p->hours);
    } else {
        printf("所给信息无效\n");
    }
}

void display_course(Course *head) {
    Course *p = head;
    while (p) {
        pri_course(p);
        p = p->next;
    }
}

Course *seeint_course(int num) {
    Course *p = ph_course;
    while (p && p->num != num) {
        p = p->next;
    }
    return p;
}

Course *seechar_course(char *name) {
    Course *p = ph_course;
    while (p && strcmp(name, p->name)) {
        p = p->next;
    }
    return p;
}

int create_course(Course **head) {
    Course *p = (Course *)malloc(sizeof(Course));
    if (!p) {
        printf("内存分配失败\n");
        return 0;
    }
    printf("请输入课程号: ");
    scanf("%d", &p->num);
    if (seeint_course(p->num)) {
        printf("课程号为%d的记录已存在!\n", p->num);
        free(p);
        return 0;
    }
    printf("请输入课程名: ");
    scanf("%s", p->name);
    printf("请输入学分: ");
    scanf("%d", &p->credit);
    printf("请输入学时: ");
    scanf("%d", &p->hours);
    p->next = *head;
    *head = p;
    return 1;
}

int search_course(Course *head) {
    int num;
    char name[30];
    printf("\n\n输入序号以继续：\n1.按号查找\n2.按名查找\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("请输入要查询的课程号: ");
        scanf("%d", &num);
        Course *p = seeint_course(num);
        if (p) {
            pri_course(p);
            return p->num;
        }
    } else if (choice == 2) {
        printf("请输入要查询的课程名: ");
        scanf("%s", name);
        Course *p = seechar_course(name);
        if (p) {
            pri_course(p);
            return p->num;
        }
    }
    printf("无此记录\n");
    return 0;
}

int modify_course(Course *head) {
    Course *p = seeint_course(search_course(head));
    if (!p) {
        printf("不存在此课程号的记录!\n");
        return 1;
    }
    printf("0.修改课程号\n1.修改课程名\n2.修改学分\n3.修改学时\n请选择要修改的信息: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 0:
            printf("请输入课程号: ");
            scanf("%d", &p->num);
            break;
        case 1:
            printf("请输入课程名: ");
            scanf("%s", p->name);
            break;
        case 2:
            printf("请输入学分: ");
            scanf("%d", &p->credit);
            break;
        case 3:
            printf("请输入学时: ");
            scanf("%d", &p->hours);
            break;
        default:
            printf("输入错误，请重新选择操作!\n");
    }
    return 1;
}

int del_course(Course **head) {
    int num;
    printf("请输入要删除信息的课程号: ");
    scanf("%d", &num);
    Course *p = *head, *pre = NULL;
    while (p && p->num != num) {
        pre = p;
        p = p->next;
    }
    if (!p) {
        printf("无此课程号信息\n");
        return 0;
    }
    if (!pre) {
        *head = p->next;
    } else {
        pre->next = p->next;
    }
    free(p);
    printf("删除成功\n");
    return 1;
}

int sort_course(Course **head) {
    if (!*head || !(*head)->next) {
        printf("结点个数小于2，无法进行冒泡排序\n");
        return 0;
    }
    for (Course *p1 = *head; p1->next; p1 = p1->next) {
        for (Course *p2 = *head; p2->next; p2 = p2->next) {
            if (p2->num > p2->next->num) {
                Course temp = *p2;
                *p2 = *(p2->next);
                *(p2->next) = temp;
                Course *nextTemp = p2->next->next;
                p2->next->next = p2;
                p2->next = nextTemp;
            }
        }
    }
    return 1;
}

