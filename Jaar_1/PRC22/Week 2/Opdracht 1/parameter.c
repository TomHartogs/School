#include <stdlib.h>			//for random function
#include <stdio.h>
#include "parameter.h" 
#include <time.h>

int AverageStudyCredits(STUDENT* students, int len)
{
	int totalCredits = 0;
	int i = 0;
	for (; i < len; i++)
	{
		totalCredits += students[i].StudyCredits;
	}
	int average = totalCredits/len;
	return average;
}

void AddStudents(STUDENT* students, int len)
{
	srand(time(NULL));
	int i = 0;
	int random_number;
	for (; i < len; i++)
	{
		students[i].StudentNumber = i;
		random_number = rand() % 10 + 1;
		students[i].StudyCredits = random_number;
	}
}
