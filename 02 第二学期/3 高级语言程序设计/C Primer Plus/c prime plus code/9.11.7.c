#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int checkch(char c)
{
    if(isupper(c))
    {
        return c - 'A' + 1;
    }
    else if(islower(c))
    {
        return c - 'a' + 1;
    }
    return -1;
}
void inputstream(FILE* in)
{
    char ch;
    int x;
    while((ch = getc(in)) != EOF)
    {
        x = checkch(ch);
        if(x > 0)
        {
            printf("Is a alpha %c, it's index is %d\n", ch, x);
        }
    }
}
int main(void)
{
    FILE* in = fopen("123.txt", "r");
    inputstream(in);
    fclose(in);
    return 0;
}
