//—°‘Ò≈≈–Ú
#include <stdio.h>
void Selection_Sort(int *a,int n); //—°‘Ò 
void Bubble_Sort(int *a,int n);    //√∞≈› 
void Insertion_Sort(int *a,int n); //≤Â»Î 
int main()
{
	int i,array[10]={5 ,2, 4, 3, 1, 7, 9, 6, 8, 10 };
	//Selection_Sort(array,10);
	//Bubble_Sort(array,10);
	Insertion_Sort(array,10);
	for(i=0;i<10;i++) printf("%d ",array[i]);
} 
void Selection_Sort(int *a,int n)
{
	int i,j,t;
	for(i=0;i<n-1;i++)
	for(j=i+1;j<n;j++)
	if(a[i]>a[j])
	{
		t=a[i];
		a[i]=a[j];
		a[j]=t;
	} 
}
void Bubble_Sort(int *a,int n)
{
	int i,j,t;
	for(i=0;i<n-1;i++)
	for(j=0;j<n-1-i;j++)
	if(a[j]>a[j+1])
	{
		t=a[j];
		a[j]=a[j+1];
		a[j+1]=t;
	}
}
void Insertion_Sort(int *a,int n)
{
	int i,j,t;
	for(i=1;i<n;i++)
	{
		t=a[i];
		j=i-1;
		while(j>=0&&a[j]>=t)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=t;
	}
}






















