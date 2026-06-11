#include <stdio.h>
void show_arr(const double x[],int  n);
void copy_arr(double x[],const double source[],int n);                //x[]==*x
void copy_ptr(double *x,const double *source,int n);                   
void copy_ptrs(double *x,const double *source,const double *end);
int main(void)
{
	double source[5]={1.1,2.2,3.3,4.4,5.5};
	double target1[5],target2[5],target3[5];
	printf("Source array:\n");
	show_arr(source,5);
	
	copy_arr(target1,source,5);
	printf("Target1:\n");
	show_arr(target1,5);
	
	copy_ptr(target2,source,5);
	printf("Target2:\n");
	show_arr(target2,5);
	
	copy_ptrs(target3,source,source+5);
	printf("Target3:\n");
	show_arr(target3,5);
	
	printf("Done.\n");
	return 0;
}
void show_arr(const double x[],int n)
{
	int i;
	for(i=0;i<n;i++) printf("%g\n",x[i]);
	//putchar('\n');
}
void copy_arr(double x[],const double source[],int n)
{
	int i=-1;
	//for(i=0;i<n;i++)
	while(i++<5) 
	x[i]=source[i];
}
void copy_ptr(double *x,const double *source,int n)
{
	int i;
	for(i=0;i<n;i++,x++,source++) 
	//*(x+i)=*(source+i);
	*x=*source;
}
void copy_ptrs(double *x,const double *source,const double *end)
{
	int i;
	for(i=0;i<end-source;i++)
	*(x+i)=*(source+i);
}
