#ifndef COURSE_H
#define COURSE_H

typedef struct _Course {
    int num;                // 课程编号
    char name[30];          // 课程名称，最多29个字符加上字符串结尾符
    int credit;             // 学分
    int hours;              // 学时
    struct _Course *next;   // 指向下一个课程节点的指针
} Course;                    // 课程信息结构体类型定义

void pri_course(Course *p);                 // 打印单个课程信息的函数声明
void display_course(Course *head);          // 显示所有课程信息的函数声明
Course *seeint_course(int num);             // 根据课程编号查找课程的函数声明
Course *seechar_course(char *name);         // 根据课程名称查找课程的函数声明
int create_course(Course **head);           // 创建新课程信息的函数声明
int search_course(Course *head);            // 查询课程信息的函数声明
int modify_course(Course *head);            // 修改课程信息的函数声明
int del_course(Course **head);              // 删除课程信息的函数声明
int sort_course(Course **head);             // 按课程编号重新排序课程的函数声明

extern Course *ph_course;  // 外部全局变量，指向课程链表的头节点

#endif // COURSE_H

