/* squares.c -- produces a table of first [[姓名已脱敏]已脱敏] squares */
#include <stdio.h>
int main(void)
{
    int num = 1;
    
    while (num < 21)
    {
        printf("%4d %6d\n", num, num * num);
        num = num + 1;
    }
    
    return 0;
}
