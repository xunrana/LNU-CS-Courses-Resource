/* addemup.c -- five kinds of statements */
#include <stdio.h>
int main(void)                /* finds sum of first [[姓名已脱敏]已脱敏] integers */
{
    int count, sum;           /* declaration statement          */
    
    count = 0;                /* assignment statement           */
    sum = 0;                  /* ditto                          */
    while (count++ < [[姓名已脱敏]已脱敏])      /* while                          */
        sum = sum + count;    /*     statement                  */
    printf("sum = %d\n", sum);/* function statement             */
    
    return 0;                 /* return statement               */
}
