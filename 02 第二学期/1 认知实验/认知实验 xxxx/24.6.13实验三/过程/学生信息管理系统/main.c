#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "courses.h"
#include "enrol.h" 

int main(int argc, char *argv[]) 
{
	struct Courses_List* phead=(struct Courses_List*)malloc(sizeof(struct Courses_List*));
	memset(phead,0,sizeof(struct Courses_List*));
	phead->Course_No=0;
	phead->next=NULL;
	Label:;
	system("cls");
	printf("-----------[姓名已脱敏]管理系统-----------\n");
	printf("选择功能(1.学生信息管理,2.课程信息管理,3.选课管理,4.成绩管理,0.退出):");
	int Mode=0;
	scanf("%d",&Mode);
	int SubMode=0;
	switch(Mode)
	{
		case 0:
			return 0;
		case 1:
			printf("选择模式(0.添加学生,1.删除学生,2.修改学生信息,3.列出所有学生信息,-1.退出):");
			scanf("%d",&SubMode);
			if(SubMode==-1)
			{
				break;
			}
			Student_Data_Operation(SubMode);
			break;
		case 2:
			printf("选择模式(0.添加课程,1.删除课程,2.修改课程信息,3.列出所有课程信息,-1.退出):");
			scanf("%d",&SubMode);
			if(SubMode==-1)
			{
				break;
			}
			else
			{
				switch(SubMode)
				{
					case 0:
						Push_Courses(phead);
						break;
					case 1:
						Delete_Courses(phead);
						break;
					case 2:
						Change_Courses(phead);
						break;
					case 3:
						Print_Courses(phead);
						system("pause");
						break;
					default:
						break;
				}
			}
			break;
		case 3:
			printf("选择模式(0.选课,1.删除选课,2.列出所有选课信息,-1.退出):");
			scanf("%d",&SubMode);
			if(SubMode==-1)
			{
				break;
			}
			else
			{
				switch(SubMode)
				{
					case 0:
						Course_Selection();
						break;
					case 1:
						Course_Delete();
						break;
					case 2:
						Course_Selected_Print(phead);
						system("pause");
						break;
					default:
						break;
				}
			}
			break;
		case 4:
			printf("选择模式(0.成绩录入,1.成绩修改,-1.退出):");
			scanf("%d",&SubMode);
			if(SubMode==-1)
			{
				break;
			}
			else if(SubMode==0)
			{
				Score_In(phead);
			}
			else if(SubMode=1)
			{
				Score_Change();
			}
			break;
		default:
			break;
	}
	goto Label;
	return 0;
}
