#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "courses.h"
#include "enrol.h"

void Prepare()
{
	memset(JWStudent,0,sizeof(struct JWStudents));
	for(int tmp=0;tmp<1000;tmp++)
	{
		if(Student_Data[tmp].No==0)
		{
			break;
		}
		JWStudent[tmp].No=Student_Data[tmp].No;
		strcpy(JWStudent[tmp].Name,Student_Data[tmp].Name);
	}
	return;
}

char* Get_Course_Name(struct Courses_List* phead,int Get_Course_No)
{
	struct Courses_List* tmp=phead;
	tmp=(struct Courses_List*)tmp->next;
	while(tmp)
	{
		if(tmp->Course_No==Get_Course_No)
		{
			return tmp->Course_Name;
		}
		tmp=tmp->next;
	}
	return NULL;
}
void Course_Selection()
{
	Prepare();
	printf("ÊäÈëÄãµÄ[ĞÕÃûÒÑÍÑÃô]:");
	int num;
	scanf("%d",&num);
	for(int tmp=0;tmp<1000;tmp++)
	{
		if(JWStudent[tmp].No==0)
		{
			break;
		}
		else if(JWStudent[tmp].No==num)
		{
			num=tmp;
			break;
		}
	}
Label:; 
	int Course_num=0;
	printf("ÊäÈëÄãÒªÑ¡µÄ¿ÎĞòºÅ(-1ÊÇÍË³ö):");
	scanf("%d",&Course_num);
	if(Course_num==-1)
	{
		return;
	}
	for(int tmp=0;tmp<[[å§“åå·²è„±æ•]å·²è„±æ•];tmp++)
	{
		if(JWStudent[num].Student_Courses[tmp]==0)
		{
			JWStudent[num].Student_Courses[tmp]=Course_num;
			break;
		}
	}
	goto Label;
}

void Course_Delete()
{
	printf("ÊäÈëÄãµÄ[ĞÕÃûÒÑÍÑÃô]:");
	int num;
	scanf("%d",&num);
	for(int tmp=0;tmp<1000;tmp++)
	{
		if(JWStudent[tmp].No==0)
		{
			break;
		}
		else if(JWStudent[tmp].No==num)
		{
			num=tmp;
			break;
		}
	}
Label:; 
	int Course_num=0;
	printf("ÊäÈëÄãÒªÉ¾³ıµÄ¿ÎĞòºÅ(-1ÊÇÍË³ö):");
	scanf("%d",&Course_num);
	if(Course_num==-1)
	{
		return;
	}
	for(int tmp=0;tmp<[[å§“åå·²è„±æ•]å·²è„±æ•];tmp++)
	{
		if(JWStudent[num].Student_Courses[tmp]==Course_num)
		{
			for(int tmp2=tmp;tmp2<19;tmp++)
			{
				JWStudent[num].Student_Courses[tmp2]=JWStudent[num].Student_Courses[tmp2+1];
			}
			JWStudent[num].Student_Courses[19]=0;
			break;
		}
	}
	goto Label;
}

void Course_Selected_Print(struct Courses_List* phead)
{
	printf("ÊäÈëÄãµÄ[ĞÕÃûÒÑÍÑÃô]:");
	int num;
	scanf("%d",&num);
	for(int tmp=0;tmp<1000;tmp++)
	{
		if(JWStudent[tmp].No==0)
		{
			break;
		}
		else if(JWStudent[tmp].No==num)
		{
			num=tmp;
			break;
		}
	}
	for(int tmp=0;tmp<[[å§“åå·²è„±æ•]å·²è„±æ•];tmp++)
	{
		if(JWStudent[num].Student_Courses[tmp]==0)
		{
			break;
		}
		printf("%s:%d  ",Get_Course_Name(phead,JWStudent[num].Student_Courses[tmp]),JWStudent[num].Score[tmp]);;
	}
	printf("\n");
	return;
}

void Score_In(struct Courses_List* phead)
{
	printf("ÊäÈë[ĞÕÃûÒÑÍÑÃô]:");
	int num;
	scanf("%d",&num);
	for(int tmp=0;tmp<1000;tmp++)
	{
		if(JWStudent[tmp].No==0)
		{
			break;
		}
		else if(JWStudent[tmp].No==num)
		{
			num=tmp;
			break;
		}
	}
	for(int tmp=0;tmp<[[å§“åå·²è„±æ•]å·²è„±æ•];tmp++)
	{
		if(JWStudent[num].Student_Courses[tmp]==0)
		{
			break;
		}
		printf("%s  :",Get_Course_Name(phead,JWStudent[num].Student_Courses[tmp]));
		int score_tmp;
		scanf("%d",&score_tmp);
		JWStudent[num].Score[tmp]=score_tmp;
	}
}

void Score_Change()
{
	printf("ÊäÈë[ĞÕÃûÒÑÍÑÃô]:");
	int num;
	scanf("%d",&num);
	for(int tmp=0;tmp<1000;tmp++)
	{
		if(JWStudent[tmp].No==0)
		{
			break;
		}
		else if(JWStudent[tmp].No==num)
		{
			num=tmp;
			break;
		}
	}
Label:; 
	int Course_num=0;
	printf("ÊäÈëÄãÒªĞŞ¸ÄµÄ¿ÎĞòºÅ(-1ÊÇÍË³ö):");
	scanf("%d",&Course_num);
	if(Course_num==-1)
	{
		return;
	}
	for(int tmp=0;tmp<[[å§“åå·²è„±æ•]å·²è„±æ•];tmp++)
	{
		if(JWStudent[num].Student_Courses[tmp]==0)
		{
			break;
		}
		else if(JWStudent[num].Student_Courses[tmp]==Course_num)
		{
			scanf("%d",&JWStudent[num].Score[tmp]);
		}
	}
	goto Label;
}
