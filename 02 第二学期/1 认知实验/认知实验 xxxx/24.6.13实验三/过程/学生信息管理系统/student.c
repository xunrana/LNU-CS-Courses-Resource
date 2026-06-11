#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

int cmp( const void *a , const void *b ) 
{ 
	struct Student *c = (struct Student *)a; 
	struct Student *d = (struct Student *)b; 
	return d->No - c->No; 
} 

void Student_Data_Operation(int mode)
{
	if(mode==0)//Add
	{
		for(int tmp=0;tmp<1000;tmp++)
		{
			if(Student_Data[tmp].No==0)
			{
				printf("你需要添加的[姓名已脱敏]：");
				scanf("%d",&Student_Data[tmp].No);
				printf("[姓名已脱敏]：");
				char Ctmp[10];
				gets(Ctmp);gets(Ctmp);
				strcpy(Student_Data[tmp].Name,Ctmp);
				printf("性别：");
				scanf("%c",&Student_Data[tmp].Sex);
				printf("家庭地址：");
				gets(Ctmp);gets(Ctmp);
				strcpy(Student_Data[tmp].Address,Ctmp);
				break;
			}
		}
	}
	else if(mode==1)//Delete
	{
		printf("你想删除的[姓名已脱敏]：");
		int No_tmp;
		scanf("%d",&No_tmp);
		for(int tmp=0;tmp<1000;tmp++)
		{
			if(Student_Data[tmp].No==No_tmp)
			{
				for(int tmp2=tmp;Student_Data[tmp2].No!=0;tmp2++)
				{
					Student_Data[tmp2].No=Student_Data[tmp2+1].No;
					Student_Data[tmp2].Sex=Student_Data[tmp2+1].Sex;
					strcpy(Student_Data[tmp2].Name,Student_Data[tmp2+1].Name);
					strcpy(Student_Data[tmp2].Address,Student_Data[tmp2+1].Address);
				}
				break;
			}
		}
	}
	else if(mode==2)//Change
	{
		printf("你想更改的[姓名已脱敏]：");
		int No_tmp;
		scanf("%d",&No_tmp);
		for(int tmp=0;tmp<1000;tmp++)
		{
			if(Student_Data[tmp].No==No_tmp)
			{
				printf("更改后的[姓名已脱敏]：");
				char Ctmp[10];
				gets(Ctmp);gets(Ctmp);
				strcpy(Student_Data[tmp].Name,Ctmp);
				printf("更改后的性别：");
				scanf("%c",&Student_Data[tmp].Sex);
				printf("更改后的家庭地址：");
				gets(Ctmp);gets(Ctmp);
				strcpy(Student_Data[tmp].Address,Ctmp);
				break;
			}
		}
	}
	else if(mode==3)//Examine All
	{
		printf("正在输出所有学生信息......\n");
		qsort(Student_Data,1000,sizeof(Student_Data[0]),cmp);
		for(int tmp=0;tmp<1000;tmp++)
		{
			if(Student_Data[tmp].No==0)
			{
				break;
			}
			printf("%d    ",Student_Data[tmp].No);
			printf("%s    ",Student_Data[tmp].Name);
			printf("%c    ",Student_Data[tmp].Sex);
			printf("%s\n",Student_Data[tmp].Address);
		}
	}
}
