#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "courses.h"

struct Courses_List* BuyNode()
{
	struct Courses_List* newnode=(struct Courses_List*)malloc(sizeof(struct Courses_List));
	if(newnode==NULL)
	{
		perror("ERROR:Code 001");//malloc error
		exit(1);
	}
	newnode->next=NULL;
	return newnode;
}

void Print_Courses(struct Courses_List* phead)
{
	struct Courses_List* tmp=phead;
	tmp=(struct Courses_List*)tmp->next;
	if(tmp==NULL)
	{
		printf("无课程信息!\n");
		return;
	}
	while(tmp)
	{
		printf("%d    ",tmp->Course_No);
		printf("%s    ",tmp->Course_Name);
		printf("%d    ",tmp->Course_Score);
		printf("%d    \n",tmp->Course_Time);
		tmp=(struct Courses_List*)tmp->next;
	}
}

void Push_Courses(struct Courses_List* phead)
{
Start:;
	struct Courses_List* tmp=phead;
	//Get New Data
	printf("课序号:");
	int No_tmp=0;
	scanf("%d",&No_tmp);
	printf("课程名称:");
	char Name_tmp[50];
	gets(Name_tmp);gets(Name_tmp);
	printf("学分:");
	int Score_tmp=0;
	scanf("%d",&Score_tmp);	
	printf("学时:");
	int  Time_tmp=0;
	scanf("%d",&Time_tmp);
	//Done.
	int Judge=0;
	while(tmp)
	{
		if(tmp->Course_No==No_tmp-1)
		{
			Judge=1;
			struct Courses_List* newnode=BuyNode();
			newnode->Course_No=No_tmp;
			strcpy(newnode->Course_Name,Name_tmp);
			newnode->Course_Score=Score_tmp;
			newnode->Course_Time=Time_tmp;
			newnode->next=tmp->next;
			tmp->next=newnode;
			break;
		}
		tmp=(struct Courses_List*)tmp->next;
	}
	if(Judge==0)
	{
		printf("Warning:课序号不可有间隔!\n");
		goto Start;
	}
	return;
}

void Delete_Courses(struct Courses_List* phead)
{
Start:;
	struct Courses_List* tmp=phead;
	printf("你要删除的课序号:");
	int No_tmp=0;
	scanf("%d",&No_tmp); 
	int Judge=0;
	while(tmp)
	{
		struct Courses_List* Old=tmp;
		struct Courses_List* tmp2=tmp->next;
		if(tmp2->Course_No==No_tmp)
		{
			Old=tmp;
			Old->next=tmp2->next;
			free(tmp2);
			Judge=1;
			break;
		}
		tmp=tmp->next;
	}
	if(Judge==0)
	{
		printf("课序号不存在!重新输入!\n");
		goto Start; 
	}
	printf("Done!");
	return;
}

void Change_Courses(struct Courses_List* phead)
{
Start:;
	struct Courses_List* tmp=phead;
	printf("你要改变的课序号:");
	int No_tmp=0;
	scanf("%d",&No_tmp); 
	int Judge=0;
	while(tmp)
	{
		if(tmp->Course_No==No_tmp)
		{
			printf("课程名称:");
			char Name_tmp[50];
			gets(Name_tmp);gets(Name_tmp);
			printf("学分:");
			int Score_tmp=0;
			scanf("%d",&Score_tmp);	
			printf("学时:");
			int  Time_tmp=0;
			scanf("%d",&Time_tmp);
			
			strcpy(tmp->Course_Name,Name_tmp);
			tmp->Course_Score=Score_tmp;
			tmp->Course_Time=Time_tmp;
		}
		tmp=(struct Courses_List*)tmp->next;
	}
	if(Judge==1)
	{
		printf("课序号不存在!重新输入!\n");
		goto Start; 
	}
}

