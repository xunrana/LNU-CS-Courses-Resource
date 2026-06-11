#include "student.h"           // 包含学生信息的头文件
#include <stdio.h>             // 标准输入输出库
#include <stdlib.h>            // 标准库，包含动态内存分配函数
#include <string.h>            // 字符串处理库

void pri(Stu *p) {             // 打印学生信息函数定义
    if (p) {                   // 如果参数指针不为空
        printf("[姓名已脱敏]:%d\t[姓名已脱敏]:%s\t性别:%s\t地址:%s\n", p->num, p->name, p->sex, p->adrs);  // 输出学生信息
    } else {                   // 如果参数指针为空
        printf("所给信息无效\n");  // 输出无效信息提示
    }
}

void display_students(Stu students[], int count) {  // 显示所有学生信息函数定义
    int i = 0;                 // 定义循环变量
    for (; i < count; i++) {   // 遍历学生信息数组
        pri(&students[i]);     // 调用打印学生信息函数
    }
}

int create_student(Stu students[], int *count) {  // 创建新学生记录函数定义
    if (*count >= MAX_STUDENTS) {  // 如果学生记录已满
        printf("学生人数已满\n");  // 输出人数已满提示
        return 0;                // 返回失败标志
    }
    Stu *p = &students[*count];  // 获取待创建记录的指针
    printf("请输入[姓名已脱敏]: ");      // 提示输入[姓名已脱敏]
    scanf("%d", &p->num);        // 输入[姓名已脱敏]
    int i = 0;                   // 定义循环变量
    for (; i < *count; i++) {    // 遍历已有记录
        if (students[i].num == p->num) {  // 如果[姓名已脱敏]已存在
            printf("[姓名已脱敏]为%d的记录已存在!\n", p->num);  // 输出[姓名已脱敏]已存在提示
            return 0;              // 返回失败标志
        }
    }
    printf("请输入[姓名已脱敏]: ");      // 提示输入[姓名已脱敏]
    scanf("%s", p->name);        // 输入[姓名已脱敏]
    printf("请输入性别: ");      // 提示输入性别
    scanf("%s", p->sex);         // 输入性别
    printf("请输入地址: ");      // 提示输入地址
    scanf("%s", p->adrs);        // 输入地址
    (*count)++;                  // 记录数加1
    return 1;                    // 返回成功标志
}

int search_student(Stu students[], int count) {  // 查找学生记录函数定义
    int num;                     // 定义[姓名已脱敏]变量
    char nam[16];                // 定义[姓名已脱敏]字符串
    printf("\n\n输入序号以继续：\n1.按号查找\n2.按名查找\n");  // 提示选择查找方式
    int choice;                  // 定义选择变量
    scanf("%d", &choice);        // 输入选择
    if (choice == 1) {           // 如果选择按号查找
        printf("请输入要查询的[姓名已脱敏]: ");  // 提示输入[姓名已脱敏]
        scanf("%d", &num);       // 输入[姓名已脱敏]
        int i = 0;               // 定义循环变量
        for (; i < count; i++) { // 遍历学生记录
            if (students[i].num == num) {  // 如果找到匹配[姓名已脱敏]
                pri(&students[i]);  // 打印学生信息
                return i;          // 返回匹配记录的索引
            }
        }
    } else if (choice == 2) {    // 如果选择按名查找
        printf("请输入要查询的[姓名已脱敏]: ");  // 提示输入[姓名已脱敏]
        scanf("%s", nam);         // 输入[姓名已脱敏]
        int i = 0;                // 定义循环变量
        for (; i < count; i++) {  // 遍历学生记录
            if (strcmp(students[i].name, nam) == 0) {  // 如果找到匹配[姓名已脱敏]
                pri(&students[i]);  // 打印学生信息
                return i;          // 返回匹配记录的索引
            }
        }
    }
    printf("无此记录\n");        // 输出未找到记录提示
    return -1;                   // 返回失败标志
}

int modify_student(Stu students[], int count) {  // 修改学生记录函数定义
    int idx = search_student(students, count);  // 调用查找学生记录函数获取索引
    if (idx == -1) {             // 如果未找到匹配记录
        printf("不存在此[姓名已脱敏]的记录!\n");  // 输出不存在记录提示
        return 0;                // 返回失败标志
    }
    Stu *p = &students[idx];     // 获取待修改记录的指针
    printf("0.修改[姓名已脱敏]\n1.修改[姓名已脱敏]\n2.修改性别\n3.修改地址\n请选择要修改的信息: ");  // 提示选择修改项
    int choice;                  // 定义选择变量
    scanf("%d", &choice);        // 输入选择
    switch (choice) {            // 根据选择执行对应操作
        case 0:                  // 修改[姓名已脱敏]
            printf("请输入[姓名已脱敏]: ");  // 提示输入[姓名已脱敏]
            scanf("%d", &p->num);  // 输入[姓名已脱敏]
            break;
        case 1:                  // 修改[姓名已脱敏]
            printf("请输入[姓名已脱敏]: ");  // 提示输入[姓名已脱敏]
            scanf("%s", p->name);  // 输入[姓名已脱敏]
            break;
        case 2:                  // 修改性别
            printf("请输入性别: ");  // 提示输入性别
            scanf("%s", p->sex);   // 输入性别
            break;
        case 3:                  // 修改地址
            printf("请输入地址: ");  // 提示输入地址
            scanf("%s", p->adrs);  // 输入地址
            break;
        default:                 // 默认情况，输入错误
            printf("输入错误，请重新选择操作!\n");  // 输出错误提示
    }
    return 1;                    // 返回成功标志
}

int del_student(Stu students[], int *count) {  // 删除学生记录函数定义
    int num;                     // 定义[姓名已脱敏]变量
    printf("请输入要删除信息的[姓名已脱敏]: ");  // 提示输入要删除的[姓名已脱敏]
    scanf("%d", &num);           // 输入[姓名已脱敏]
    int i = 0;                   // 定义循环变量
    for (; i < *count; i++) {    // 遍历学生记录
        if (students[i].num == num) {  // 如果找到匹配[姓名已脱敏]
            int j = i;            // 定义内层循环变量
            for (; j < *count - 1; j++) {  // 将后续记录向前移动
                students[j] = students[j + 1];  // 实现删除
            }
            (*count)--;            // 记录数减1
            printf("删除成功\n");  // 输出删除成功提示
            return 1;             // 返回成功标志
        }
    }
    printf("无此[姓名已脱敏]信息\n");     // 输出未找到[姓名已脱敏]提示
    return 0;                    // 返回失败标志
}

