#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define ROWS 10
#define COLUMNS 10

int get_strings(char (*string)[COLUMNS], char **str, int n);
int get_first(void);
int show_menu(void);
int word(char *str);
char *s_gets(char *st, int n);
void origin_output(char (*str)[COLUMNS], int n);
void ascll_output(char **str, int n);
void length_up_output(char **str, int n);
void first_word_output(char **str, int n);

int main(void)
{
    int n, choice;
    char *str[ROWS];
    char strings[ROWS][COLUMNS];

    printf("Please enter %d strings (EOF to quit):\n", ROWS);
    if ((n = get_strings(strings, str, ROWS)) != 0)
    {
        while ((choice = show_menu()) != 'q')
        {
            switch (choice)
            {
            case 'a':
            {
                origin_output(strings, n);
                break;
            }
            case 'b':
            {
                ascll_output(str, n);
                break;
            }
            case 'c':
            {
                length_up_output(str, n);
                break;
            }
            case 'd':
            {
                first_word_output(str, n);
                break;
            }
            }
        }
    }
    printf("Done.\n");

    return 0;
}

int get_strings(char (*string)[COLUMNS], char **str, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (s_gets(string[i], COLUMNS) != NULL)
        {
            str[i] = string[i];
        }
        else
        {
            break;
        }
    }
    return i;
}

int get_first(void)
{
    int ch;

    do
    {
        ch = tolower(getchar());
    } while (isspace(ch));
    while (getchar() != '\n')
        continue;

    return ch;
}

int show_menu(void)
{
    int ch;

    printf("+-------------------------------------------------------+\n");
    printf("|a) print for the origin          b) print for the ASCII|\n");
    printf("|c) print for the length          d) print for the words|\n");
    printf("|q) quit                                                |\n");
    printf("+-------------------------------------------------------+\n");
    printf("Please you choose: ");
    
    ch = get_first();
    while (ch < 'a' || ch > 'd' && ch != 'q')
    {
        printf("Please enter a, b, c, d or q: ");
        ch = get_first();
    }
    return ch;
}

int word(char *str)
{
    int length = 0;
    bool inword = false;

    /*统计字符串第一个非空白字符的单词
    长度并作为返回值传递给调用函数;*/
    while (*str)
    {
        if (!isspace(*str) && !inword)
        {
            /*↑从第一个非空白字符
            开始统计单词长度*/
            inword = true;
            length++;
        }
        else if (!isspace(*str) && inword)
        {
            length++;
        }
        else if (isspace(*str) && inword)
        {
            /*↑若遇到第一个单词后的空白符
            则退出循环*/
            break;
        }
        str++;
    }
    return length;
}

char *s_gets(char *st, int n)
{
    char *ret_val;
    char *find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
        {
            *find = '\0';
        }
        else
        {
            while (getchar() != '\n')
                continue;
        }
    }
    return ret_val;
}

void origin_output(char (*str)[COLUMNS], int n)
{
	int i; 
    printf("Source strings:\n", n);
    for ( i = 0; i < n; i++)
    {
        puts(str[i]);
    }
    putchar('\n');
}

void ascll_output(char **str, int n)
{
	int i,j;
    for ( i = 0; i < n - 1; i++)
    {
        for ( j = i + 1; j < n; j++)
        {
            if (strcmp(str[i], str[j]) > 0)
            {
                char *temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
    printf("Print source strings for ASCII:\n", n);
    for ( i = 0; i < n; i++)
    {
        puts(str[i]);
    }
    putchar('\n');
}

void length_up_output(char **str, int n)
{
	int i,j;
    for ( i = 0; i < n - 1; i++)
    {
        for ( j = i + 1; j < n; j++)
        {
            if (strlen(str[i]) > strlen(str[j]))
            {
                char *temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
    printf("Print source strings for length:\n", n);
    for ( i = 0; i < n; i++)
    {
        puts(str[i]);
    }
    putchar('\n');
}

void first_word_output(char **str, int n)
{
	int i,j;
    for ( i = 0; i < n - 1; i++)
    {
        for ( j = i + 1; j < n; j++)
        {
            if (word(str[i]) > word(str[j]))
            {
                char *temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
    printf("Print source strings for the first word:\n", n);
    for ( i = 0; i < n; i++)
    {
        puts(str[i]);
    }
    putchar('\n');
}

