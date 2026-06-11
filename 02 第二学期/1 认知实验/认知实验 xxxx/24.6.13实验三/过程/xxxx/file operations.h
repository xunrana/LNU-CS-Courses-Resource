// file_operations.h

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "student.h"
#include "course.h"
#include "enrol.h"

void save_students_to_file();
void load_students_from_file();

void save_courses_to_file();
void load_courses_from_file();

void save_enrollments_to_file();
void load_enrollments_from_file();

#endif // FILE_OPERATIONS_H

