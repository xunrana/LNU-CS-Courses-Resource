#include "file_operations.h"
#include <stdio.h>
#include <stdlib.h>

int read_students(Stu students[], int *count) {
    FILE *pf = fopen("studata.txt", "r");
    if (!pf) {
        return 0;
    }
    *count = 0;
    while (fscanf(pf, "%d %s %s %s", &students[*count].num, students[*count].name, students[*count].sex, students[*count].adrs) != EOF) {
        (*count)++;
    }
    fclose(pf);
    return 1;
}

int read_courses(Course **head) {
    FILE *pf = fopen("coudata.txt", "r");
    if (!pf) {
        return 0;
    }
    Course *tail = NULL;
    while (!feof(pf)) {
        Course *p = (Course *)malloc(sizeof(Course));
        if (fscanf(pf, "%d %s %d %d", &p->num, p->name, &p->credit, &p->hours) == EOF) {
            free(p);
            break;
        }
        p->next = NULL;
        if (*head == NULL) {
            *head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }
    fclose(pf);
    return 1;
}

int read_enrols(Enr enrols[], int *count) {
    FILE *pf = fopen("enrdata.txt", "r");
    if (!pf) {
        return 0;
    }
    *count = 0;
    printf("%d\n",21313); 
    while (fscanf(pf, "%d %s %d %s %d %d", &enrols[*count].num, enrols[*count].name, &enrols[*count].counum, enrols[*count].couse, &enrols[*count].term, &enrols[*count].score) != EOF) {
        (*count)++;
    }
    fclose(pf);
    return 1;
}

int save_students(Stu students[], int count) {
    FILE *pf = fopen("studata.txt", "w");
    if (!pf) {
        return 0;
    }
    int i; 
    for (i = 0; i < count; i++) {
        fprintf(pf, "%d %s %s %s\n", students[i].num, students[i].name, students[i].sex, students[i].adrs);
    }
    fclose(pf);
    return 1;
}

int save_courses(Course *head) {
    FILE *pf = fopen("coudata.txt", "w");
    if (!pf) {
        return 0;
    }
    Course *p = head;
    while (p) {
        fprintf(pf, "%d %s %d %d\n", p->num, p->name, p->credit, p->hours);
        p = p->next;
    }
    fclose(pf);
    return 1;
}

int save_enrols(Enr enrols[], int count) {
    FILE *pf = fopen("enrdata.txt", "w");
    if (!pf) {
        return 0;
    }
    int i;
    for (i = 0; i < count; i++) {
        fprintf(pf, "%d %s %d %s %d %d\n", enrols[i].num, enrols[i].name, enrols[i].counum, enrols[i].couse, enrols[i].term, enrols[i].score);
    }
    fclose(pf);
    return 1;
}

