#include "enrol.h"            // 包含选课信息的头文件
#include <stdio.h>            // 标准输入输出库
#include <stdlib.h>           // 标准库，包含动态内存分配函数
#include <string.h>           // 字符串处理库

void pri_enr(Enr *p) {        // 打印选课信息函数定义
    if (p) {                  // 如果参数指针不为空
        printf("[姓名已脱敏]:%d\t[姓名已脱敏]:%s\t课程号:%d\t课程名:%s\t学期:%d\t成绩:%d\n",
               p->num, p->name, p->counum, p->couse, p->term, p->score);  // 输出选课信息
    } else {                  // 如果参数指针为空
        printf("所给信息无效\n");  // 输出无效信息提示
    }
}

void display_enrol(Enr enrols[], int count) {  // 显示所有选课信息函数定义
    int i;                    // 定义循环变量
    for (i = 0; i < count; i++) {  // 遍历选课信息数组
        pri_enr(&enrols[i]);   // 调用打印选课信息函数
    }
}

int create_enrol(Enr enrols[], int *count) {  // 创建新选课记录函数定义
    if (*count >= MAX_ENROL) {  // 如果选课记录已满
        printf("选课记录已满\n");  // 输出记录已满提示
        return 0;               // 返回失败标志
    }
    Enr *p = &enrols[*count];  // 获取待创建记录的指针
    printf("请输入[姓名已脱敏]: ");     // 提示输入[姓名已脱敏]
    scanf("%d", &p->num);       // 输入[姓名已脱敏]
    int i;                      // 定义循环变量
    for (i = 0; i < *count; i++) {  // 遍历已有记录
        if (enrols[i].num == p->num) {  // 如果[姓名已脱敏]已存在
            printf("[姓名已脱敏]为%d的记录已存在!\n", p->num);  // 输出[姓名已脱敏]已存在提示
            return 0;           // 返回失败标志
        }
    }
    printf("请输入[姓名已脱敏]: ");     // 提示输入[姓名已脱敏]
    scanf("%s", p->name);       // 输入[姓名已脱敏]
    printf("请输入课程号: ");   // 提示输入课程号
    scanf("%d", &p->counum);    // 输入课程号
    printf("请输入课程名: ");   // 提示输入课程名
    scanf("%s", p->couse);      // 输入课程名
    printf("请输入学期: ");     // 提示输入学期
    scanf("%d", &p->term);      // 输入学期
    printf("请输入成绩: ");     // 提示输入成绩
    scanf("%d", &p->score);     // 输入成绩
    (*count)++;                 // 记录数加1
    return 1;                   // 返回成功标志
}

int search_enrol(Enr enrols[], int count) {  // 查找选课记录函数定义
    int num;                    // 定义[姓名已脱敏]变量
    char nam[16];               // 定义[姓名已脱敏]字符串
    printf("\n\n输入序号以继续：\n1.按号查找\n2.按名查找\n");  // 提示选择查找方式
    int choice;                 // 定义选择变量
    scanf("%d", &choice);       // 输入选择
    if (choice == 1) {          // 如果选择按号查找
        printf("请输入要查询的[姓名已脱敏]: ");  // 提示输入[姓名已脱敏]
        scanf("%d", &num);      // 输入[姓名已脱敏]
        int i;                  // 定义循环变量
        for (i = 0; i < count; i++) {  // 遍历选课记录
            if (enrols[i].num == num) {  // 如果找到匹配[姓名已脱敏]
                pri_enr(&enrols[i]);  // 打印选课信息
                return i;           // 返回匹配记录的索引
            }
        }
    } else if (choice == 2) {   // 如果选择按名查找
        printf("请输入要查询的[姓名已脱敏]: ");  // 提示输入[姓名已脱敏]
        scanf("%s", nam);        // 输入[姓名已脱敏]
        int i;                  // 定义循环变量
        for (i = 0; i < count; i++) {  // 遍历选课记录
            if (strcmp(enrols[i].name, nam) == 0) {  // 如果找到匹配[姓名已脱敏]
                pri_enr(&enrols[i]);  // 打印选课信息
                return i;           // 返回匹配记录的索引
            }
        }
    }
    printf("无此记录\n");       // 输出未找到记录提示
    return -1;                  // 返回失败标志
}

int del_enrol(Enr enrols[], int *count) {  // 删除选课记录函数定义
    int num;                    // 定义[姓名已脱敏]变量
    printf("请输入要删除信息的[姓名已脱敏]: ");  // 提示输入要删除的[姓名已脱敏]
    scanf("%d", &num);          // 输入[姓名已脱敏]
    int i;                      // 定义循环变量
    for (i = 0; i < *count; i++) {  // 遍历选课记录
        if (enrols[i].num == num) {  // 如果找到匹配[姓名已脱敏]
            int j;              // 定义内层循环变量
            for (j = i; j < *count - 1; j++) {  // 将后续记录向前移动
                enrols[j] = enrols[j + 1];  // 实现删除
            }
            (*count)--;         // 记录数减1
            printf("删除成功\n");  // 输出删除成功提示
            return 1;           // 返回成功标志
        }
    }
    printf("无此[姓名已脱敏]信息\n");    // 输出未找到[姓名已脱敏]提示
    return 0;                   // 返回失败标志
}

