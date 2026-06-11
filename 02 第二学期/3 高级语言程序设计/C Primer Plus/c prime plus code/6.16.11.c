#include <stdio.h>
int main(void)
{
	/*
	int a[8],i;
	for(i=0;i<8;i++) scanf("%d",&a[i]);
	for(i=0;i<8;i++) printf("%d ",a[7-i]);
	*/
	
	
	
	/*
	char a[8];
	gets(a);
	int b=7;
	while(b+1)
	printf("%c",a[b--]);
	*/
	
	int vals[8];
    int i; 
    printf("Please enter 8 integers.\n");
    for (i = 0; i < 8; i++)
    scanf("%d", &vals[i]);
    printf("Here, in reverse order, are the values you entered:\n");
    for (i = 8  - 1; i >= 0; i--)
    printf("%d ", vals[i]);
    printf("\n");
    return 0;
}

