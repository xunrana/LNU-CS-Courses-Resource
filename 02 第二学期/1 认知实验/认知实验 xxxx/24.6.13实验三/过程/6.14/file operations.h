#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "student.h"
#include "course.h"
#include "enrol.h"

int read_students(Stu students[], int *count);
int read_courses(Course **head);
int read_enrols(Enr enrols[], int *count);
int save_students(Stu students[], int count);
int save_courses(Course *head);
int save_enrols(Enr enrols[], int count);

#endif // FILE_OPERATIONS_H

