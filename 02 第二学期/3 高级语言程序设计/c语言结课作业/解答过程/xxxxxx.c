#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Student{//定义学生结构
	int stuNo;//[姓名已脱敏]
	char name[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//[姓名已脱敏]
	char major[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//专业 
	char sex[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//性别
	int age;//年龄 
};
struct Score{//定义[姓名已脱敏]结构体
	int stuNo;//[姓名已脱敏]
	char name[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//[姓名已脱敏]
	char major[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//专业 
	int C;//C语言 
	int jswlx;//计算物理学
	int dxwl;//大学物理
	int yzwl;//原子物理
	int gx;//光学
}; 
struct Teacher{//定义教师结构体 

	int worknum;//工号
	char name[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//[姓名已脱敏]
	char sex[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//性别 
	int age;//年龄 
}; 
//定义平均分结构体
struct Avg
{
	int stuNo;//[姓名已脱敏]
	char name[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//[姓名已脱敏]
	float score;//平均分 
}; 
int main()
{	
	int stuNo;//[姓名已脱敏]
	char name[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//[姓名已脱敏]
	char major[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//专业
	int C;//C语言 
	int jswlx;//计算物理学
	int dxwl;//大学物理
	int yzwl;//原子物理
	int gx;//光学
	int total = 0;//学生总人数 
	int tTotal = 0;//教师总人数 
	int worknum;//工号
	char tname[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//教师[姓名已脱敏]
	char tsex[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];//教师性别 
	int tage;//教师年龄 
	struct Teacher tea[1000];
	struct Student stu[1000];
	struct Score score[1000];
	struct Avg avg[1000];
	int identity;	
	//打开文件 
	FILE *fp;
	FILE *tfp;
	fp = fopen("[姓名已脱敏]单","r+");
	tfp = fopen("teacher_inf","r+");
	if(fp != NULL)
	{
		while (fscanf(fp, "%d\t%s\t%s\t%d\t%d\t%d\t%d\t%d", &stuNo, &name, &major, &C,&jswlx,&dxwl,&yzwl,&gx) != EOF)
		{
			score[total].stuNo = stuNo;
			strcpy(score[total].name,name);
			strcpy(score[total].major,major);
			score[total].C = C;
			score[total].jswlx = jswlx;
			score[total].dxwl = dxwl;
			score[total].yzwl = yzwl;
			score[total].gx = gx;
			total++;
		}
		fclose(fp);
	}
	else
	{
		printf("打开文件失败！") ;
	}
	
	if(tfp != NULL)
	{
		while (fscanf(tfp, "%d\t%s\t%s\t%d", &worknum, &tname, &tsex, &tage) != EOF)
		{
			tea[tTotal].worknum = worknum;
			strcpy(tea[tTotal].name,tname);
			strcpy(tea[tTotal].sex,tsex);
			tea[tTotal].age = tage;
			tTotal++;
		}
		fclose(fp);
	}
	else
	{
		printf("打开文件失败！");
	};
	
	printf("===================================================\n");
	printf("                   欢迎使用\n");
	printf("               学生信息管理系统\n");
	printf("===================================================\n");
	
	
	while(1)
	{
		printf("请选择您的身份\n");
		printf("1-管理员 2-教师 3-学生 0-退出\n");
		scanf("%d",&identity);
		//管理员的功能
		if(identity == 1)
		{
			int admin;
			while(1)
			{
				printf("1-查看所有教师 2-查看所有学生 3-录取老师 4-录取学生 0-返回\n");
				scanf("%d",&admin);
				
				if(admin == 1)
				{
					int i;
					for( i = 0; i < tTotal; i++)
					{
						printf("%d\t%s\t%s\t%d\n",tea[i].worknum,tea[i].name,tea[i].sex,tea[i].age);
					}
				}
				
					if(admin == 2)
				{
					int i;
					for(i = 0; i < total; i++)
					{
						printf("%d\t%s\t%s\n",score[i].stuNo,score[i].name,score[i].major);
					}
				}

					if(admin == 3)
				{
					int num,jixu,i;
					while(1)
					{
						printf("请输入要录取的人数\n");
						scanf("%d",&num);
						printf("请分别输入工号、[姓名已脱敏]、性别、年龄\n"); 
						for( i = 0; i < num; i++)
						{
							scanf("%d%s%s%d",&tea[tTotal].worknum,&tea[tTotal].name,&tea[tTotal].sex,&tea[tTotal].age);
							tTotal++;
						}
						printf("添加成功！是否继续添加 1-是 2-否\n");
						scanf("%d",&jixu);
						if(jixu == 2)
						{
							break;
						}
					}
				}
				
					if(admin == 4)
				{
					int num,jixu,i;
					while(1)
					{
						printf("请输入要录取的人数\n");
						scanf("%d",&num);
						printf("请分别输入[姓名已脱敏]、[姓名已脱敏]、专业、性别、年龄\n");
						for( i = 0; i < num; i++)
						{
							scanf("%d%s%s%s%d",&stu[total].stuNo,&stu[total].name,&stu[total].major,
							&stu[total].sex,&stu[total].age);
							total++;
						}
						printf("添加成功，是否继续添加？ 1-是 2-否\n");
						scanf("%d",&jixu);
						if(jixu == 2)
						{
							break;
						}
					}
				}
				
			 if(admin == 0)
				{
					break;
				}
			}
		}
		//教师功能
        if(identity == 2)
		{
			int teacher;
			while(1)
			{
				printf("1-录入成绩 2-修改成绩 3-删除成绩 4-查询成绩 0-返回\n");
				scanf("%d",&teacher);
				
				//录入成绩 
				if(teacher == 1)
				{
					int people;
					int jixu;
					int i;
					while(1)
					{
						printf("请输入录入的人数\n");
						scanf("%d",&people);
						printf("请输入[姓名已脱敏]、[姓名已脱敏]、专业和五门课成绩\n");
						for( i = 0; i < people; i++)
						{
							scanf("%d%s%s%d%d%d%d%d",&score[total].stuNo,&score[total].name,&score[total].major,&score[total].C,&score[total].jswlx,&score[total].dxwl,&score[total].yzwl,&score[total].gx);
							total++;
						}
						printf("是否继续添加 1-是 2-否\n");
						scanf("%d",&jixu);
						if(jixu == 2)
						{
							break;
						}
					}
				}
				
				//修改成绩 
			 if(teacher == 2)
				{
					int modifyNo;//[姓名已脱敏] 
					int find = 2;//是否找到 
					int index;//返回下标 
					int i;
					printf("请输入学生[姓名已脱敏]\n");
					scanf("%d",&modifyNo);
					for(i = 0; i < total; i++)
					{
						if(score[i].stuNo == modifyNo)
						{
							find = 1;
							index = i; 
							break;
						} 
					}
					
					if(find == 1)
					{
						printf("请分别输入C语言、计算物理学、大学物理、原子物理、光学(空格隔开)\n");
						scanf("%d%d%d%d%d",&score[index].C,&score[index].jswlx,&score[index].dxwl,&score[index].yzwl,&score[index].gx);
						printf("修改成功，当前该[姓名已脱敏]为\n");
						printf("C语言：%d 计算物理学：%d 大学物理：%d 原子物理：%d 光学: %d\n",score[index].C,
						score[index].jswlx,score[index].dxwl,score[index].yzwl,score[index].gx);
					}
					else
					{
						printf("没有找到这个学生！\n");
					}
				}
				
				//删除成绩 
				 if(teacher == 3)
				{
					int delNo;
					int index;
					int find = 2;
					int i;
					printf("请输入要删除成绩的[姓名已脱敏]\n"); 
					scanf("%d",&delNo);
					for(i = 0; i < total; i++)
					{
						if(score[i].stuNo == delNo)
						{
							index = i;
							find = 1;
							break;
						}
					}
					
					if(find == 1)
					{
						score[index].C = 0;
						score[index].jswlx = 0;
						score[index].dxwl = 0;
						score[index].yzwl = 0;
						score[index].gx = 0;
					}
					 if(find == 2)
					{
						printf("查无此人！\n");
					}
				}
				//查询成绩 
				 if(teacher == 4)
				{
					int select;
					printf("1-查询所有[姓名已脱敏] 2-按[姓名已脱敏]查询 3-按[姓名已脱敏]查询\n");
					printf("4-统计平均分 5-查看C语言最高的同学\n"); 
					scanf("%d",&select);
						//查询所有学生的成绩 
				if(select == 1)
					{
						int i;
						printf("[姓名已脱敏]\t\t[姓名已脱敏]\t专业\tC语言\t计算物理学\t大学物理\t原子物理\t光学\n");
						for(i = 0; i < total; i++)
						{
							printf("%d\t%s\t%s\t%d\t%d\t\t%d\t\t%d\t%d\n",score[i].stuNo,score[i].name,score[i].major,
							   score[i].C,score[i].jswlx,score[i].dxwl,score[i].yzwl,score[i].gx);
						}
					}
				 	//按[姓名已脱敏]查询 
				 if(select == 2)
					{
						int selectNo,index;
						int find = 2;
						int i;
						printf("请输入[姓名已脱敏]\n");
						scanf("%d",&selectNo);
						for(i = 0; i < total; i++)
						{
							if(score[i].stuNo == selectNo)
							{
								index = i;
								find = 1;
								break;
							}
						}	
							
						if(find == 1)
						{
							printf("C语言：%d 计算物理学：%d 大学物理：%d 原子物理：%d 光学: %d\n",score[index].C,
								score[index].jswlx,score[index].dxwl,score[index].yzwl,score[index].gx);
						}
						else
						{
							printf("没有找到此人，请重新输入！\n"); 
						}			
					}
					
					//按[姓名已脱敏]查询 
				if(select == 3)
					{
						char selectName[[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬];
						int index,i,find = 2;
						printf("请输入[姓名已脱敏]：\n");
						scanf("%d",&selectName);
						for(i = 0; i <total; i++)
						{
							if(strcmp(score[i].name,selectName)==0)
							{
								index = i;
								find = 1;
								break;
							}
						} 
						if(find == 1)
						{
							printf("C语言：%d 计算物理学：%d 大学物理：%d 原子物理：%d 光学: %d\n",score[index].C,
								score[index].jswlx,score[index].dxwl,score[index].yzwl,score[index].gx);
						}
						else
						{
							printf("没有找到此人，请重新输入！\n"); 
						}
					}
					
					//统计平均分 
					 if(select == 4)
					{
						int goal;//总分 
						int i;
						float avgScore;
						for(i = 0;i < total; i++)
						{
							goal = score[i].C+score[i].jswlx+score[i].dxwl+score[i].yzwl+score[i].gx;
							avgScore = (float)goal/5;
							avg[i].stuNo = score[i].stuNo;
							strcpy(avg[i].name,score[i].name);
							avg[i].score = avgScore;
							printf("[姓名已脱敏]：%d\t   [姓名已脱敏]：%s\t  平均分：%.2f\n",avg[i].stuNo,avg[i].name,avg[i].score);
						}
					} 
					
					//查看C语言最高的同学 
					 if(select == 5)
					{
						int CScore = 0;
						int index,i;
						for(i = 0; i < total; i++)
						{
							if(score[i].C > CScore)
							{
								CScore = score[i].C;
								index = i;
							}
						}
						printf("[姓名已脱敏]：%d\t[姓名已脱敏]：%s\t成绩：%d\n",score[index].stuNo,score[index].name,score[index].C);
					}
				}
				if(teacher == 0)
				{
					break;
				}
			} 
		}
		//学生 
		 if(identity == 3)
		{
			int inputNo;
			int find = 2;
			int index;
			int i;
			printf("请输入[姓名已脱敏]\n");
			scanf("%d",&inputNo);
			for(i = 0; i < total; i++)
			{
				if(score[i].stuNo == inputNo)
				{
					find = 1;
					index = i;
					break;
				}
			}
			
			if(find == 1)
			{
				int stuSelect;
				int tGoal;//总成绩
				while(1)
				{
					printf("1-查询单科成绩 2-查询总成绩 3-查询平均成绩 0-返回\n");
					scanf("%d",&stuSelect);
					if(stuSelect == 1)
					{
						int course;
						printf("1-查询C语言 2-查询计算物理学 3-查询大学物理 4-查询原子物理 5-查询光学\n");
						scanf("%d",&course);
						if(course == 1)
						{
							printf("C语言成绩：%d\n",score[index].C);
						}
						 if(course == 2)
						{
							printf("计算物理学成绩：%d\n",score[index].jswlx);
						}
						 if(course == 3)
						{
							printf("大学物理成绩：%d\n",score[index].dxwl);
						}
						 if(course == 4)
						{
							printf("原子物理成绩：%d\n",score[index].yzwl);
						}
						 if(course == 5)
						{
							printf("光学成绩: %d\n",score[index].gx);
						}
					}
					
					 if(stuSelect == 2)
					{
						tGoal = score[index].C+score[index].jswlx+score[index].dxwl+score[index].yzwl+score[index].gx;
						printf("总成绩为：%.2f\n",tGoal); 
					}
					
					 if(stuSelect == 3)
					{
						float tAvg;//平均成绩 
						tGoal = score[index].C+score[index].jswlx+score[index].dxwl+score[index].yzwl+score[index].gx;
						tAvg = (float)tGoal / 5; 
						printf("平均成绩为：%.2f\n",tAvg); 
					}
					
					 if(stuSelect == 0)
					{
						break;
					 }	
				}	
			}
			else
				printf("查无此人！\n"); 
		} 
		
		 if(identity == 0)
		{
			printf("谢谢您的使用！\n");
			break;
		 }
	}
	return 0;
}

