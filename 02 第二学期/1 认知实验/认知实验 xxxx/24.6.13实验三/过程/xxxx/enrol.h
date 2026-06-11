// enrol.h

#ifndef ENROL_H
#define ENROL_H

#define MAX_ENROLLMENTS 500

typedef struct {
    int student_id;
    char name[50];
    int course_id;
    char course_name[50];
    int semester;
    int grade;
} Enrollment;

extern Enrollment enrollments[MAX_ENROLLMENTS];
extern int num_enrollments;

void add_enrollment();
void delete_enrollment(int student_id, int course_id);
void search_enrollment(int student_id, int course_id);
void load_enrollments_from_file();
void save_enrollments_to_file();

#endif // ENROL_H

