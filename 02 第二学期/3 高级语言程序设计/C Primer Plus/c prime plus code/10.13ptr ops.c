#include <stdio.h>
int main(void)
{
	int urn[5]={100,[[姓名已脱敏]已脱敏]0,300,400,500};
	int *ptr1,*ptr2,*ptr3;
	ptr1=urn;
	ptr2=&urn[2];
	printf("pointer value           dereferenced pointer        pointer address:\n");
	printf("ptr1=%25p,*ptr1=%5d,&ptr1=%18p\n",ptr1,*ptr1,&ptr1);
	ptr3=ptr1+4;
	printf("\nadding an int to a pointer:\n");
	printf("ptr1+4=%23p,*(ptr1+4)=%5d\n",ptr1+4,*(ptr1+4));
	ptr1++;
	printf("\nvalue after ptr1++:\n");
	printf("ptr1=%25p,*ptr1=%5d,&ptr1=%18p\n",ptr1,*ptr1,&ptr1);
	ptr2--;
	printf("\nvalue after --ptr2:\n");
	printf("ptr2=%25p,*ptr2=%5d,&ptr2=%18p\n",ptr2,*ptr2,&ptr2);
	--ptr1;
	++ptr2;
	printf("\nPointers reset to original values:\n");
	printf("ptr1=%18p,ptr2=%18p",ptr1,ptr2);
	printf("\nsubtracting one pointer from another:\n");
	printf("ptr2=%18p,ptr1=%18p,ptr2-ptr1=%td\n",ptr2,ptr1,ptr2-ptr1);
	printf("\nsubtracting an int from a pointer:\n");
	printf("ptr3=%18p,ptr3-2=%16p\n",ptr3,ptr3-2);
	return 0;
}
