#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "student.h"  // 包含学生结构体和相关操作的头文件
#include "course.h"   // 包含课程结构体和相关操作的头文件
#include "enrol.h"    // 包含选课结构体和相关操作的头文件

// 函数声明

// 从文件中读取学生信息并初始化到数组中
int read_students(Stu students[], int *count);

// 从文件中读取课程信息并初始化到链表中
int read_courses(Course **head);

// 从文件中读取选课信息并初始化到数组中
int read_enrols(Enr enrols[], int *count);

// 将学生信息保存到文件中
int save_students(Stu students[], int count);

// 将课程信息保存到文件中
int save_courses(Course *head);

// 将选课信息保存到文件中
int save_enrols(Enr enrols[], int count);

#endif // FILE_OPERATIONS_H

