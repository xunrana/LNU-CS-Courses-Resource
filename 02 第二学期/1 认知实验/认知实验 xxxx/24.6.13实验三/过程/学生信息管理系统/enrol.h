struct JWStudents
{
	int No;
	char Name[10];
	int Student_Courses[[[姓名已脱敏]已脱敏]];
	int Score[[[姓名已脱敏]已脱敏]];
}JWStudent[1000];

void Prepare(); 
char* Get_Course_Name(struct Courses_List* phead,int Get_Course_No);
void Course_Selection();
void Course_Delete();
void Course_Selected_Print(struct Courses_List* phead);
void Score_In(struct Courses_List* phead);
void Score_Change();

