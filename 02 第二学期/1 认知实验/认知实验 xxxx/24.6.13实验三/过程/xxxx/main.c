// main.c

#include <stdio.h>
#include "student.h"
#include "course.h"
#include "enrol.h"
#include "file_operations.h"

int main() {
    load_students_from_file();
    load_courses_from_file();
    load_enrollments_from_file();

    // Example menu-driven program
    int choice;
    do {
        printf("\n1. Manage Students\n2. Manage Courses\n3. Manage Enrollments\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Student management operations
                break;
            case 2:
                // Course management operations
                break;
            case 3:
                // Enrollment management operations
                break;
            case 4:
                // Save data to files before exiting
                save_students_to_file();
                save_courses_to_file();
                save_enrollments_to_file();
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

