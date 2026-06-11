// file_operations.c

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "file_operations.h"

// Function to save students to file
void save_students_to_file() {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) {
        perror("Error opening students.txt for writing");
        return;
    }

    for (int i = 0; i < num_students; ++i) {
        fprintf(fp, "%d\t%s\t%c\t%s\n", students[i].student_id, students[i].name, students[i].gender, students[i].address);
    }

    fclose(fp);
}

// Function to load students from file
void load_students_from_file() {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        perror("Error opening students.txt for reading");
        return;
    }

    num_students = 0;
    while (fscanf(fp, "%d\t%s\t%c\t%s\n", &students[num_students].student_id, students[num_students].name, &students[num_students].gender, students[num_students].address) == 4) {
        num_students++;
    }

    fclose(fp);
}

// Function to save courses to file
void save_courses_to_file() {
    FILE *fp = fopen("courses.txt", "w");
    if (fp == NULL) {
        perror("Error opening courses.txt for writing");
        return;
    }

    Course *current = course_list;
    while (current != NULL) {
        fprintf(fp, "%d\t%s\t%d\t%d\n", current->course_id, current->course_name, current->credits, current->hours);
        current = current->next;
    }

    fclose(fp);
}

// Function to load courses from file
void load_courses_from_file() {
    FILE *fp = fopen("courses.txt", "r");
    if (fp == NULL) {
        perror("Error opening courses.txt for reading");
        return;
    }

    Course *current = NULL;
    course_list = NULL;
    int course_id, credits, hours;
    char course_name[50];

    while (fscanf(fp, "%d\t%s\t%d\t%d\n", &course_id, course_name, &credits, &hours) == 4) {
        Course *new_course = (Course *)malloc(sizeof(Course));
        if (new_course == NULL) {
            perror("Memory allocation error");
            fclose(fp);
            return;
        }
        new_course->course_id = course_id;
        strcpy(new_course->course_name, course_name);
        new_course->credits = credits;
        new_course->hours = hours;
        new_course->next = NULL;

        if (course_list == NULL) {
            course_list = new_course;
            current = course_list;
        } else {
            current->next = new_course;
            current = current->next;
        }
    }

    fclose(fp);
}

// Function to save enrollments to file
void save_enrollments_to_file() {
    FILE *fp = fopen("enrollments.txt", "w");
    if (fp == NULL) {
        perror("Error opening enrollments.txt for writing");
        return;
    }

    for (int i = 0; i < num_enrollments; ++i) {
        fprintf(fp, "%d\t%s\t%d\t%s\t%d\t%d\n", enrollments[i].student_id, enrollments[i].name, enrollments[i].course_id, enrollments[i].course_name, enrollments[i].semester, enrollments[i].grade);
    }

    fclose(fp);
}

// Function to load enrollments from file
void load_enrollments_from_file() {
    FILE *fp = fopen("enrollments.txt", "r");
    if (fp == NULL) {
        perror("Error opening enrollments.txt for reading");
        return;
    }

    num_enrollments = 0;
    while (fscanf(fp, "%d\t%s\t%d\t%s\t%d\t%d\n", &enrollments[num_enrollments].student_id, enrollments[num_enrollments].name, &enrollments[num_enrollments].course_id, enrollments[num_enrollments].course_name, &enrollments[num_enrollments].semester, &enrollments[num_enrollments].grade) == 6) {
        num_enrollments++;
    }

    fclose(fp);
}

