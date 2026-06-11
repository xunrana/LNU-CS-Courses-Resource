#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 1000  // 定义最大学生数为 1000

typedef struct _Stu {
    int num;               // [姓名已脱敏]
    char name[16];         // [姓名已脱敏]，最多15个字符加上字符串结尾符
    char sex[6];           // 性别，最多5个字符加上字符串结尾符
    char adrs[101];        // 地址，最多100个字符加上字符串结尾符
} Stu;                     // 学生结构体类型定义

void pri(Stu *p);          // 打印单个学生信息的函数声明
void display_students(Stu students[], int count);  // 显示所有学生信息的函数声明
int create_student(Stu students[], int *count);    // 创建新学生信息的函数声明
int search_student(Stu students[], int count);     // 查询学生信息的函数声明
int modify_student(Stu students[], int count);     // 修改学生信息的函数声明
int del_student(Stu students[], int *count);       // 删除学生信息的函数声明

#endif // STUDENT_H

