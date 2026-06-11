#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pri(Stu *p) {
    if (p) {
        printf("[姓名已脱敏]:%d\t[姓名已脱敏]:%s\t性别:%s\t地址:%s\n", p->num, p->name, p->sex, p->adrs);
    } else {
        printf("所给信息无效\n");
    }
}

void display_students(Stu students[], int count) {
    for (int i = 0; i < count; i++) {
        pri(&students[i]);
    }
}

int create_student(Stu students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("学生人数已满\n");
        return 0;
    }
    Stu *p = &students[*count];
    printf("请输入[姓名已脱敏]: ");
    scanf("%d", &p->num);
    for (int i = 0; i < *count; i++) {
        if (students[i].num == p->num) {
            printf("[姓名已脱敏]为%d的记录已存在!\n", p->num);
            return 0;
        }
    }
    printf("请输入[姓名已脱敏]: ");
    scanf("%s", p->name);
    printf("请输入性别: ");
    scanf("%s", p->sex);
    printf("请输入地址: ");
    scanf("%s", p->adrs);
    (*count)++;
    return 1;
}

int search_student(Stu students[], int count) {
    int num;
    char nam[16];
    printf("\n\n输入序号以继续：\n1.按号查找\n2.按名查找\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("请输入要查询的[姓名已脱敏]: ");
        scanf("%d", &num);
        for (int i = 0; i < count; i++) {
            if (students[i].num == num) {
                pri(&students[i]);
                return i;
            }
        }
    } else if (choice == 2) {
        printf("请输入要查询的[姓名已脱敏]: ");
        scanf("%s", nam);
        for (int i = 0; i < count; i++) {
            if (strcmp(students[i].name, nam) == 0) {
                pri(&students[i]);
                return i;
            }
        }
    }
    printf("无此记录\n");
    return -1;
}

int modify_student(Stu students[], int count) {
    int idx = search_student(students, count);
    if (idx == -1) {
        printf("不存在此[姓名已脱敏]的记录!\n");
        return 0;
    }
    Stu *p = &students[idx];
    printf("0.修改[姓名已脱敏]\n1.修改[姓名已脱敏]\n2.修改性别\n3.修改地址\n请选择要修改的信息: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 0:
            printf("请输入[姓名已脱敏]: ");
            scanf("%d", &p->num);
            break;
        case 1:
            printf("请输入[姓名已脱敏]: ");
            scanf("%s", p->name);
            break;
        case 2:
            printf("请输入性别: ");
            scanf("%s", p->sex);
            break;
        case 3:
            printf("请输入地址: ");
            scanf("%s", p->adrs);
            break;
        default:
            printf("输入错误，请重新选择操作!\n");
    }
    return 1;
}

int del_student(Stu students[], int *count) {
    int num;
    printf("请输入要删除信息的[姓名已脱敏]: ");
    scanf("%d", &num);
    for (int i = 0; i < *count; i++) {
        if (students[i].num == num) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("删除成功\n");
            return 1;
        }
    }
    printf("无此[姓名已脱敏]信息\n");
    return 0;
}

