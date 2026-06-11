#ifndef __BIGINT_H
#define __BIGINT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define N 5000


void show_menu(void);
int max(int x,int y);
int Input(int *num);
void Output(int *num);
void Output16(int *num);
void Add(int *num1,int *num2,int *num3);
int Sub(int *num1,int *num2,int *num3);
int Did(int *num1,int d,int *num2);
void Con(int *num1,int d,int *num2);

#endif

int num1[N],num2[N],num3[N],num4[N];


