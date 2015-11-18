#include <stdio.h> 			//for printing
#include "parameter.c"

int main()
{
	STUDENT students[10];
	int len = 10;
	AddStudents(students, len);
	int i = 0;
	for (; i < len; i++)
	{
		printf("Student number: %d", students[i].StudentNumber);
		printf(" has %d study credits.", students[i].StudyCredits);
		printf(" size of this student struct = :%d\n", sizeof(students[i]));
	}
	printf("The average of study credits is:%d \n", AverageStudyCredits(students, len));
	
	char fileName[100];
	printf("What file do you want to open?\n");
	scanf("%99s",fileName);
	
	return 0;
}
