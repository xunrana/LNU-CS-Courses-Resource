#include <stdio.h>
int main(int argc, char *argv[])
{
	int i;
    if (argc < 2)
    {
        printf("Usage: %s words\n", argv[0]);
    }
    else
    {
        printf("Words:\n");
        for ( i = 1; i < argc; i++)
        {
            printf("%s ", argv[i]);
        }
        printf("\nReversing printing is:\n");
        for  (i = argc - 1; i > 0; i--)
        {
            printf("%s ", argv[i]);
        }
        putchar('\n');
    }

    return 0;
}

