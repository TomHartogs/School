#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "element_reader.h"
#include "element_reader.c"

/* post   : If file contains enough elements, element 'ElementNr' is read into StudentPtr
 * returns: On succes: 1 (1 element was read)
 *          If element does not exist: 0
 *          In case of an error (file could not be read, input pointers are NULL): -1
 */

int main(void)
{	
	STUDENT student;
	STUDENT students[100];
	strcpy(student.Surname, "test");
	char test = 't' ;
	int *testp = test;
	printf("%s", student.Surname);
	students[1].StudentNumber = 1;
	students[8].StudentNumber = 5;
		printf("students number test 1: %i\n", students[8].StudentNumber);
	student.StudentNumber = 10;
	student.StudyCredits = 3;
	char fileName[100] = "test.txt";
	printf("What file do you want to write to?\n");
	scanf("%99s",fileName);
	FILE *file;
	file = fopen(fileName, "wb");
	printf("StudentNumber: %i\n", student.StudentNumber);
	printf("StudyCredits: %i\n", student.StudyCredits);
	writeElement(file, 0, &student);
	fclose(file);
	STUDENT student1;
	file = fopen(fileName, "rb");
	if(readElement(file, 0, &student1) == 1)
	{
		printf("StudentNumber1: %i\n", student1.StudentNumber);
		printf("StudyCredits1: %i\n", student1.StudyCredits);
	}
	else
	{
		printf("Element not found");
	}
	printf("%lu\n", ftell(file));
	printf("%i\n", fseek(file, 0, SEEK_END));
	printf("%lu\n", ftell(file));
	fseek(file, 0, SEEK_END);
	int numberOfStudentsInFile = ftell(file) / sizeof(STUDENT);
	printf("Number of students in file: %i\n", numberOfStudentsInFile);
	fclose(file);
	return 0;
}
