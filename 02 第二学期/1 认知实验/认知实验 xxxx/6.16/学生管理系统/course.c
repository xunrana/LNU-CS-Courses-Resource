#include "course.h"             // 包含课程信息的头文件
#include <stdio.h>              // 标准输入输出库
#include <stdlib.h>             // 标准库，包含动态内存分配函数
#include <string.h>             // 字符串处理库

Course *ph_course = NULL;       // 全局变量，课程链表的头指针

void pri_course(Course *p) {    // 打印课程信息函数定义
    if (p) {                    // 如果参数指针不为空
        printf("课程号:%d\t课程名:%s\t学分:%d\t学时:%d\n", p->num, p->name, p->credit, p->hours);  // 输出课程信息
    } else {                    // 如果参数指针为空
        printf("所给信息无效\n");  // 输出无效信息提示
    }
}

void display_course(Course *head) {  // 显示所有课程信息函数定义
    Course *p = head;           // 定义遍历指针并初始化为头指针
    while (p) {                 // 循环遍历链表
        pri_course(p);          // 调用打印课程信息函数
        p = p->next;            // 指针移动到下一个节点
    }
}

Course *seeint_course(int num) {  // 按课程号查找课程函数定义
    Course *p = ph_course;      // 定义遍历指针并初始化为头指针
    while (p && p->num != num) {  // 循环遍历链表，直到找到匹配的课程号或遍历结束
        p = p->next;            // 指针移动到下一个节点
    }
    return p;                   // 返回找到的课程节点或NULL
}

Course *seechar_course(char *name) {  // 按课程名查找课程函数定义
    Course *p = ph_course;      // 定义遍历指针并初始化为头指针
    while (p && strcmp(name, p->name)) {  // 循环遍历链表，直到找到匹配的课程名或遍历结束
        p = p->next;            // 指针移动到下一个节点
    }
    return p;                   // 返回找到的课程节点或NULL
}

int create_course(Course **head) {  // 创建新课程记录函数定义
    Course *p = (Course *)malloc(sizeof(Course));  // 分配新课程节点的内存空间
    if (!p) {                   // 内存分配失败检查
        printf("内存分配失败\n");  // 输出内存分配失败提示
        return 0;               // 返回失败标志
    }
    printf("请输入课程号: ");    // 提示输入课程号
    scanf("%d", &p->num);       // 输入课程号
    if (seeint_course(p->num)) {  // 检查课程号是否已存在
        printf("课程号为%d的记录已存在!\n", p->num);  // 输出课程号已存在提示
        free(p);                // 释放分配的内存空间
        return 0;               // 返回失败标志
    }
    printf("请输入课程名: ");    // 提示输入课程名
    scanf("%s", p->name);       // 输入课程名
    printf("请输入学分: ");     // 提示输入学分
    scanf("%d", &p->credit);    // 输入学分
    printf("请输入学时: ");     // 提示输入学时
    scanf("%d", &p->hours);     // 输入学时
    p->next = *head;            // 将新节点插入链表头部
    *head = p;                  // 更新链表头指针
    return 1;                   // 返回成功标志
}

int search_course(Course *head) {  // 查找课程记录函数定义
    int num;                    // 定义课程号变量
    char name[30];              // 定义课程名字符串
    printf("\n\n输入序号以继续：\n1.按号查找\n2.按名查找\n");  // 提示选择查找方式
    int choice;                 // 定义选择变量
    scanf("%d", &choice);       // 输入选择
    if (choice == 1) {          // 如果选择按号查找
        printf("请输入要查询的课程号: ");  // 提示输入课程号
        scanf("%d", &num);      // 输入课程号
        Course *p = seeint_course(num);  // 调用按课程号查找函数
        if (p) {                // 如果找到匹配记录
            pri_course(p);      // 打印课程信息
            return p->num;      // 返回课程号
        }
    } else if (choice == 2) {   // 如果选择按名查找
        printf("请输入要查询的课程名: ");  // 提示输入课程名
        scanf("%s", name);      // 输入课程名
        Course *p = seechar_course(name);  // 调用按课程名查找函数
        if (p) {                // 如果找到匹配记录
            pri_course(p);      // 打印课程信息
            return p->num;      // 返回课程号
        }
    }
    printf("无此记录\n");      // 输出未找到记录提示
    return 0;                   // 返回失败标志
}

int modify_course(Course *head) {  // 修改课程记录函数定义
    Course *p = seeint_course(search_course(head));  // 调用查找课程记录函数获取要修改的课程指针
    if (!p) {                   // 如果未找到匹配记录
        printf("不存在此课程号的记录!\n");  // 输出不存在记录提示
        return 1;               // 返回失败标志
    }
    printf("0.修改课程号\n1.修改课程名\n2.修改学分\n3.修改学时\n请选择要修改的信息: ");  // 提示选择修改项
    int choice;                 // 定义选择变量
    scanf("%d", &choice);       // 输入选择
    switch (choice) {           // 根据选择执行对应操作
        case 0:                 // 修改课程号
            printf("请输入课程号: ");  // 提示输入课程号
            scanf("%d", &p->num);  // 输入课程号
            break;
        case 1:                 // 修改课程名
            printf("请输入课程名: ");  // 提示输入课程名
            scanf("%s", p->name);  // 输入课程名
            break;
        case 2:                 // 修改学分
            printf("请输入学分: ");  // 提示输入学分
            scanf("%d", &p->credit);  // 输入学分
            break;
        case 3:                 // 修改学时
            printf("请输入学时: ");  // 提示输入学时
            scanf("%d", &p->hours);  // 输入学时
            break;
        default:                // 默认情况，输入错误
            printf("输入错误，请重新选择操作!\n");  // 输出错误提示
    }
    return 1;                   // 返回成功标志
}

int del_course(Course **head) {  // 删除课程记录函数定义
    int num;                    // 定义课程号变量
    printf("请输入要删除信息的课程号: ");  // 提示输入要删除的课程号
    scanf("%d", &num);          // 输入课程号
    Course *p = *head, *pre = NULL;  // 定义遍历指针和前驱指针，并初始化
    while (p && p->num != num) {  // 循环遍历链表，直到找到匹配的课程号或遍历结束
        pre = p;                // 更新前驱指针
        p = p->next;            // 指针移动到下一个节点
    }
    if (!p) {                   // 如果未找到匹配的课程号
        printf("无此课程号信息\n"); // 输出未找到记录提示
		return 0; // 返回失败标志
	}
	if (!pre) { // 如果匹配的节点是头节点
		*head = p->next; // 更新头指针为下一个节点
	} else { // 如果匹配的节点不是头节点
		pre->next = p->next; // 调整前驱节点的指针，跳过当前节点
	}
	free(p); // 释放匹配节点的内存空间
	printf("删除成功\n"); // 输出删除成功提示
	return 1; // 返回成功标志
}
		
int sort_course(Course **head) { // 对课程链表进行冒泡排序函数定义
	if (!*head || !(*head)->next) { // 如果链表为空或只有一个节点
		printf("结点个数小于2，无法进行冒泡排序\n"); // 输出无法排序提示
		return 0; // 返回失败标志
	}
	Course *p1 = *head; // 定义外层循环遍历指针
	for (; p1->next; p1 = p1->next) { // 外层循环，控制比较次数
		Course *p2 = *head; // 定义内层循环遍历指针
		for (; p2->next; p2 = p2->next) { // 内层循环，执行相邻节点比较与交换
			if (p2->num > p2->next->num) { // 如果前一个节点的课程号大于后一个节点的课程号
				Course temp = *p2; // 交换两个节点的数据
				*p2 = *(p2->next);
				*(p2->next) = temp;
				Course *nextTemp = p2->next->next; // 调整指针连接顺序
				p2->next->next = p2;
				p2->next = nextTemp;
			}
		}
	}
	return 1; // 返回成功标志
}
