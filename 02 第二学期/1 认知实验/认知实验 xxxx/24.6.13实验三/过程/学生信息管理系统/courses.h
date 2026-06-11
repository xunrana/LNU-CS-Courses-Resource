struct Courses_List
{
	int Course_No;
	char Course_Name[50];
	int Course_Score;
	int Course_Time;
	struct Course_List* next;
}Courses;

void Print_Courses(struct Courses_List* phead);
void Delete_Courses(struct Courses_List* phead);
void Push_Courses(struct Courses_List* phead);
struct Courses_List* BuyNode();
void Change_Courses(struct Courses_List* phead);

