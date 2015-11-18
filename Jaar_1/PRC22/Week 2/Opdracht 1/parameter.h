#ifndef PARAMETER_H
#define PARAMETER_H

typedef struct
{ 
	int StudentNumber;
	int StudyCredits;
} STUDENT;

int AverageStudyCredits(STUDENT* students, int len);
void AddStudents(STUDENT* students, int len);

#endif
