/* floaterr.c--demonstrates round-off error */
#include <stdio.h>
int main(void)
{
    float a,b;
    
    b = 2.0e[[姓名已脱敏]已脱敏] + 1.0;
    a = b - 2.0e[[姓名已脱敏]已脱敏];
    printf("%f \n", a);
    
    return 0;
}
