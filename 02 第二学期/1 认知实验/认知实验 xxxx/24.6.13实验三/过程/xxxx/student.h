// student.h

#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100

typedef struct {
    int student_id;
    char name[50];
    char gender;
    char address[100];
} Student;

extern Student students[MAX_STUDENTS];
extern int num_students;

void add_student();
void update_student(int student_id);
void delete_student(int student_id);
void search_student(int student_id);
void load_students_from_file();
void save_students_to_file();

#endif // STUDENT_H

