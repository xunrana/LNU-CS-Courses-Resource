#ifndef ENROL_H
#define ENROL_H

#define MAX_ENROL 1000

typedef struct _Enr {
    int num;
    char name[16];
    int counum;
    char couse[30];
    int term;
    int score;
} Enr;

void pri_enr(Enr *p);
void display_enrol(Enr enrols[], int count);
int create_enrol(Enr enrols[], int *count);
int search_enrol(Enr enrols[], int count);
int del_enrol(Enr enrols[], int *count);

#endif // ENROL_H

