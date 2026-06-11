#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "student.h"
#include "course.h"
#include "enrol.h"
#include "file_operations.h"

void menu_students(void);
void menu_courses(void);
void menu_enrols(void);

int main() 
{
    Stu students[MAX_STUDENTS];
    Enr enrols[MAX_ENROL];
    Course *courses = NULL;
    int student_count = 0, enrol_count = 0;

    printf("请选择操作\n1、学生信息系统\n2、课程信息系统\n3、选课信息系统\n");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            if (read_students(students, &student_count)) {
                printf("学生信息初始化成功,欢迎使用!\n\n\n\n");
            } else {
                printf("\n请在本程序所在目录新建studata.txt再启动程序!\n\n\n\n");
                getchar();
                return 0;
            }
            do {
                menu_students();
                int student_choice;
                scanf("%d", &student_choice);
                switch (student_choice) {
                    case 1:
                        system("cls");
                        printf("\n=====浏览所有学生信息=====\n");
                        display_students(students, student_count);
                        break;
                    case 2:
                        system("cls");
                        printf("\n=====新建学生信息=====\n");
                        create_student(students, &student_count);
                        break;
                    case 3:
                        system("cls");
                        printf("\n=====查询学生信息=====\n");
                        search_student(students, student_count);
                        break;
                    case 4:
                        system("cls");
                        printf("\n=====修改学生信息=====\n");
                        modify_student(students, student_count);
                        break;
                    case 5:
                        system("cls");
                        printf("\n=====删除学生信息=====\n");
                        del_student(students, &student_count);
                        break;
                    case 0:
                        system("cls");
                        printf("\n=====保存学生信息=====\n\n");
                        save_students(students, student_count);
                        printf("欢迎下次使用,再见!\n");
                        return 0;
                    default:
                        system("cls");
                        printf("\n输入错误,请重新选择操作!\n");
                        break;
                }
                printf("\n按任意键可返回主菜单。\n");
                getch();
                system("cls");
            } while (1);
            break;
        case 2:
            if (read_courses(&courses)) {
                printf("课程信息初始化成功,欢迎使用!\n\n\n\n");
            } else {
                printf("\n请在本程序所在目录新建coudata.txt再启动程序!\n\n\n\n");
                getchar();
                return 0;
            }
            do {
                menu_courses();
                int course_choice;
                scanf("%d", &course_choice);
                switch (course_choice) {
                    case 1:
                        system("cls");
                        printf("\n=====浏览所有课程信息=====\n");
                        display_course(courses);
                        break;
                    case 2:
                        system("cls");
                        printf("\n=====新建课程信息=====\n");
                        create_course(&courses);
                        break;
                    case 3:
                        system("cls");
                        printf("\n=====查询课程信息=====\n");
                        search_course(courses);
                        break;
                    case 4:
                        system("cls");
                        printf("\n=====修改课程信息=====\n");
                        modify_course(courses);
                        break;
                    case 5:
                        system("cls");
                        printf("\n=====删除课程信息=====\n");
                        del_course(&courses);
                        break;
                    case 6:
                        system("cls");
                        printf("\n=====按课程号重新排序=====\n");
                        sort_course(&courses);
                        break;
                    case 0:
                        system("cls");
                        printf("\n=====保存课程信息=====\n\n");
                        save_courses(courses);
                        printf("欢迎下次使用,再见!\n");
                        return 0;
                    default:
                        system("cls");
                        printf("\n输入错误,请重新选择操作!\n");
                        break;
                }
                printf("\n按任意键可返回主菜单。\n");
                getch();
                system("cls");
            } while (1);
            break;
        case 3:
            if (read_enrols(enrols, &enrol_count)) {
                printf("选课信息初始化成功,欢迎使用!\n\n\n\n");
            } else {
                printf("\n请在本程序所在目录新建enrdata.txt再启动程序!\n\n\n\n");
                getchar();
                return 0;
            }
            do {
                menu_enrols();
                int enrol_choice;
                scanf("%d", &enrol_choice);
                switch (enrol_choice) {
                    case 1:
                        system("cls");
                        printf("\n=====浏览所有选课信息=====\n");
                        display_enrol(enrols, enrol_count);
                        break;
                    case 2:
                        system("cls");
                        printf("\n=====新建选课信息=====\n");
                        create_enrol(enrols, &enrol_count);
                        break;
                    case 3:
                        system("cls");
                        printf("\n=====查询选课信息=====\n");
                        search_enrol(enrols, enrol_count);
                        break;
                    case 5:
                        system("cls");
                        printf("\n=====删除选课信息=====\n");
                        del_enrol(enrols, &enrol_count);
                        break;
                    case 0:
                        system("cls");
                        printf("\n=====保存选课信息=====\n\n");
                        save_enrols(enrols, enrol_count);
                        printf("欢迎下次使用,再见!\n");
                        return 0;
                    default:
                        system("cls");
                        printf("\n输入错误,请重新选择操作!\n");
                        break;
                }
                printf("\n按任意键可返回主菜单。\n");
                getch();
                system("cls");
            } while (1);
            break;
        default:
            printf("输入错误，请重新选择操作!\n");
            break;
    }
}

void menu_students(void) {
    printf("************************************************\n");
    printf("*************学生信息管理系统*************\n");
    printf("************************************************\n\n");
    printf("\n\n请选择操作:\n\n");
    printf("1.浏览学生信息.\n");
    printf("2.新建学生信息.\n");
    printf("3.查询学生信息.\n");
    printf("4.修改学生信息.\n");
    printf("5.删除学生信息.\n");
    printf("0.退出并保存信息.\n");
    printf("\n  你的选择是：");
}

void menu_courses(void) {
    printf("************************************************\n");
    printf("*************课程信息管理系统*************\n");
    printf("************************************************\n\n");
    printf("\n\n请选择操作:\n\n");
    printf("1.浏览课程信息.\n");
    printf("2.新建课程信息.\n");
    printf("3.查询课程信息.\n");
    printf("4.修改课程信息.\n");
    printf("5.删除课程信息.\n");
    printf("6.按课程号重新排序.\n");
    printf("0.退出并保存信息.\n");
    printf("\n  你的选择是：");
}

void menu_enrols(void) {
    printf("************************************************\n");
    printf("*************选课信息管理系统*************\n");
    printf("************************************************\n\n");
    printf("\n\n请选择操作:\n\n");
    printf("1.浏览选课信息.\n");
    printf("2.新建选课信息.\n");
    printf("3.查询选课信息.\n");
    printf("5.删除选课信息.\n");
    printf("0.退出并保存信息.\n");
    printf("\n  你的选择是：");
}

