#include "file_operations.h"  // 包含文件操作相关的头文件
#include <stdio.h>            // 标准输入输出库
#include <stdlib.h>           // 标准库，包含动态内存分配函数

// 从文件中读取学生信息并初始化到数组中
int read_students(Stu students[], int *count) {
    FILE *pf = fopen("studata.txt", "r");  // 打开存储学生信息的文件以读取方式
    if (!pf) {  // 如果文件打开失败
        return 0;  // 返回失败标志
    }
    *count = 0;  // 初始化学生计数器为0
    // 循环读取文件，直到文件末尾
    while (fscanf(pf, "%d %s %s %s", &students[*count].num, students[*count].name, students[*count].sex, students[*count].adrs) != EOF) {
        (*count)++;  // 每读取一条记录，计数器加1
    }

    fclose(pf);  // 关闭文件
    return 1;  // 返回成功标志
}

// 从文件中读取课程信息并初始化到链表中
int read_courses(Course **head) {
    FILE *pf = fopen("coudata.txt", "r");  // 打开存储课程信息的文件以读取方式
    if (!pf) {  // 如果文件打开失败
        return 0;  // 返回失败标志
    }
    Course *tail = NULL;  // 定义链表尾节点指针
    // 循环读取文件，直到文件末尾
    while (!feof(pf)) {
        Course *p = (Course *)malloc(sizeof(Course));  // 分配内存以存储新的课程信息节点
        if (fscanf(pf, "%d %s %d %d", &p->num, p->name, &p->credit, &p->hours) == EOF) {  // 读取课程信息
            free(p);  // 如果读取失败，释放内存
            break;  // 退出循环
        }
        p->next = NULL;  // 初始化节点的下一个指针为NULL
        if (*head == NULL) {
            *head = p;  // 如果链表为空，将头指针指向新节点
            tail = p;   // 更新尾指针为新节点
        } else {
            tail->next = p;  // 否则将新节点链接到链表末尾
            tail = p;         // 更新尾指针为新节点
        }
    }
    fclose(pf);  // 关闭文件
    return 1;  // 返回成功标志
}

// 从文件中读取选课信息并初始化到数组中
int read_enrols(Enr enrols[], int *count) {
    FILE *pf = fopen("enrdata.txt", "r");  // 打开存储选课信息的文件以读取方式
    if (!pf) {  // 如果文件打开失败
        return 0;  // 返回失败标志
    }
    *count = 0;  // 初始化选课计数器为0
    // 循环读取文件，直到文件末尾
    while (fscanf(pf, "%d %s %d %s %d %d", &enrols[*count].num, enrols[*count].name, &enrols[*count].counum, enrols[*count].couse, &enrols[*count].term, &enrols[*count].score) != EOF) {
        (*count)++;  // 每读取一条记录，计数器加1
    }
    fclose(pf);  // 关闭文件
    return 1;  // 返回成功标志
}

// 将选课信息保存到文件中
int save_enrols(Enr enrols[], int count) {
    FILE *pf = fopen("enrdata.txt", "w");  // 打开存储选课信息的文件以写入方式
    if (!pf) {  // 如果文件打开失败
        return 0;  // 返回失败标志
    }
    int i;
    for (i = 0; i < count; i++) {  // 循环写入每条选课信息到文件中
        fprintf(pf, "%d %s %d %s %d %d\n", enrols[i].num, enrols[i].name, enrols[i].counum, enrols[i].couse, enrols[i].term, enrols[i].score);
    }
    fclose(pf);  // 关闭文件
    return 1;  // 返回成功标志
}

// 将学生信息保存到文件中
int save_students(Stu students[], int count) {
    FILE *pf = fopen("studata.txt", "w");  // 打开存储学生信息的文件以写入方式
    if (!pf) {  // 如果文件打开失败
        return 0;  // 返回失败标志
    }
    int i;
    for (i = 0; i < count; i++) {  // 循环写入每条学生信息到文件中
        fprintf(pf, "%d %s %s %s\n", students[i].num, students[i].name, students[i].sex, students[i].adrs);
    }
    fclose(pf);  // 关闭文件
    return 1;  // 返回成功标志
}

// 将课程信息保存到文件中
int save_courses(Course *head) {
    FILE *pf = fopen("coudata.txt", "w");  // 打开存储课程信息的文件以写入方式
    if (!pf) {  // 如果文件打开失败
        return 0;  // 返回失败标志
    }
    Course *p = head;
    while (p) {  // 遍历链表，将每个课程信息写入文件中
        fprintf(pf, "%d %s %d %d\n", p->num, p->name, p->credit, p->hours);
        p = p->next;  // 移动到链表的下一个节点
    }
    fclose(pf);  // 关闭文件
    return 1;  // 返回成功标志
}

