struct Student
{
	int No;
	char Name[10];
	char Sex;
	char Address[10];
}Student_Data[1000];

int cmp( const void *a , const void *b );
void Student_Data_Operation(int mode);
