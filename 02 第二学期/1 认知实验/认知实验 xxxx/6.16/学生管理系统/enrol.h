#ifndef ENROL_H
#define ENROL_H

#define MAX_ENROL 1000  // 定义最大选课数为 1000

typedef struct _Enr {
    int num;            // 选课编号
    char name[50];      // 学生[姓名已脱敏]，最多49个字符加上字符串结尾符
    int counum;         // 学生[姓名已脱敏]
    char couse[50];     // 课程名称，最多49个字符加上字符串结尾符
    int term;           // 学期
    int score;          // 成绩
} Enr;                  // 选课信息结构体类型定义

void pri_enr(Enr *p);                   // 打印单个选课信息的函数声明
void display_enrol(Enr enrols[], int count);  // 显示所有选课信息的函数声明
int create_enrol(Enr enrols[], int *count);    // 创建新选课信息的函数声明
int search_enrol(Enr enrols[], int count);     // 查询选课信息的函数声明
int del_enrol(Enr enrols[], int *count);       // 删除选课信息的函数声明

#endif // ENROL_H

