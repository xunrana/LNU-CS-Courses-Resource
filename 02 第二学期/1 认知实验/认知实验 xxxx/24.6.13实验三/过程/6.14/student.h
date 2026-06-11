#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 1000

typedef struct _Stu {
    int num;
    char name[16];
    char sex[6];
    char adrs[101];
} Stu;

void pri(Stu *p);
void display_students(Stu students[], int count);
int create_student(Stu students[], int *count);
int search_student(Stu students[], int count);
int modify_student(Stu students[], int count);
int del_student(Stu students[], int *count);

#endif // STUDENT_H

