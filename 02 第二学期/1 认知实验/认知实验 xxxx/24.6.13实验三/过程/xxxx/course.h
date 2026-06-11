// course.h

#ifndef COURSE_H
#define COURSE_H

typedef struct CourseNode {
    int course_id;
    char course_name[50];
    int credits;
    int hours;
    struct CourseNode *next;
} Course;

extern Course *course_list;

void add_course(int course_id, const char *course_name, int credits, int hours);
void update_course(int course_id);
void delete_course(int course_id);
void search_course(int course_id);
void load_courses_from_file();
void save_courses_to_file();

#endif // COURSE_H

