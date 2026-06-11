#ifndef COURSE_H
#define COURSE_H

typedef struct _Course {
    int num;
    char name[30];
    int credit;
    int hours;
    struct _Course *next;
} Course;

void pri_course(Course *p);
void display_course(Course *head);
Course *seeint_course(int num);
Course *seechar_course(char *name);
int create_course(Course **head);
int search_course(Course *head);
int modify_course(Course *head);
int del_course(Course **head);
int sort_course(Course **head);

extern Course *ph_course;

#endif // COURSE_H

