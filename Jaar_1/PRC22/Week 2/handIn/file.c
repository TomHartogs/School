/*
 * a. Correct i = 5;
 * b. Correct j = 24 V 48; afhankelijk van systeem.
 * c. Incorrect r heeft de waarde van a[1] en verwijst niet naar het gehele array
 * d. Correct, waarde!? geen idee, q is niet geinitialliseerd. 
 * e. Correct, waarde!? geen idee
 */
 
#include "file.h" 
#include <unistd.h>

/* post   : Calculates the average of all study results in a file
 * returns: -1 if an error occurs, 0 if a valid average is computed
 */
extern int computeAverageStudyResults (char* FileName, double* Average)
{
	if(access(FileName, R_OK ) != -1 && Average)
	{
		FILE *ptr_file = fopen(*FileName, "rb");
		if(ptr_file)
		{
			fseek(ptr_file, 0, SEEK_END);
			int numberOfStudentsInFile = ftell(ptr_file) / sizeof(STUDENT);
			*Average = 0;							//* nodig anders veranderd de pointer toch?
			int i = 0;
			for (; i < numberOfStudentsInFile; i++)
			{
				STUDENT student;
				readElement(ptr_file, i, &student);
				*Average += student.StudyCredits; 	//* nodig anders veranderd de pointer toch?
			}
			*Average /= numberOfStudentsInFile;		//* nodig anders kan je waar de pointer naar verwijst niet veranderen toch?
			return 0;
		}
	}
	return -1;
}

/* post   : Returns student information of student with student number Number
 * returns: -1 if Number is not available or in case of an error, 0 if Number is available
 */
extern int linearSearchStudentsFile (char* FileName, int Number, STUDENT* StudentPtr)
{
	if(access(FileName, R_OK ) != -1 && Number)
	{
		FILE *ptr_file = fopen(*FileName, "rb");
		if(ptr_file)
		{
			fseek(ptr_file, 0, SEEK_END);
			int numberOfStudentsInFile = ftell(ptr_file) / sizeof(STUDENT);
			fseek(ptr_file, 0, SEEK_SET);
			int i = 0;
			for (; i < numberOfStudentsInFile; i++)
			{
				STUDENT student;
				readElement(ptr_file, i, &student);
				if(Number == student.StudentNumber)
				{
					*StudentPtr = student;
					return 0;
				}
			}
		}
	}
	return -1;
}

/* post   : Returns student information of student with student number Number
 * returns: -1 if Number is not available or in case of an error, 0 if Number is available
 */
extern int binarySearchStudentsFile (char* FileName, int Number, STUDENT* StudentPtr)
{
	if(access(FileName, R_OK ) != -1 && Number)
	{
		FILE *ptr_file = fopen(*FileName, "rb");
		if(ptr_file)
		{
			fseek(ptr_file, 0, SEEK_END);
			int minIndex = 0;
			int maxIndex = (ftell(ptr_file) / sizeof(STUDENT)) - 1;
			fseek(ptr_file, 0, SEEK_SET);
			int IndexesSearched = 0;
			int maxSearchesNeeder = log2(maxIndex) + 1;
			STUDENT student;
			student.StudentNumber = -1;
			int currentNumber = maxIndex/2;
			while(true)
			{
				readElement(ptr_file, currentNumber, &student);
				IndexesSearched++;
				if(IndexesSearched > maxIndex)
				{
					return -1;
				}
				else if(student.StudentNumber == Number)
				{
					*StudentPtr = student;
					return 0;
				}
				else if(student.StudentNumber > Number)
				{
					maxIndex = currentNumber;
					currentNumber = minIndex + (maxIndex - minIndex / 2);
				}
				else if(student.StudentNumber < Number)
				{
					minIndex = currentNumber;
					currentNumber = minIndex + (maxIndex - minIndex / 2);
				}
			}
		}
	}
	return -1;
}

/* post   : Adds information from StudentPtr to FileName in a sorted way,
 *          if FileName does not exist, a new file is created.
 * returns: -1 in case of an error
 *          0  if a student with the given student number already exists
 *          1  if the student is added to the file
 */
extern int addStudentSortedToFile (char* FileName, STUDENT* StudentPtr)
{
	if(StudentPtr)
	{
		FILE *ptr_file = fopen(*FileName, "r+b");
		if(ptr_file)
		{
		    fseek(ptr_file, 0, SEEK_END);
			int numberOfStudentsInFile = ftell(ptr_file) / sizeof(STUDENT);
			fseek(ptr_file, 0, SEEK_SET);
			STUDENT tempStudent;
			tempStudent.StudentNumber  = -1;
			int studentAdded = 0;
			int i = 0;
			for (; i < numberOfStudentsInFile; i++)
			{
				STUDENT foundStudent;
				STUDENT studentPtr = *StudentPtr; //get student number of pointer student?
				readElement(ptr_file, i, &foundStudent);
				if(tempStudent.StudentNumber != -1)
				{
					writeElement(ptr_file, i, &tempStudent);
					tempStudent = foundStudent;
				}
				else
				{
					if(studentPtr.StudentNumber == foundStudent.StudentNumber)
					{
						return 0;
					}
					else if(studentPtr.StudentNumber < foundStudent.StudentNumber)
					{
						readElement(ptr_file, i, &tempStudent);
						writeElement(ptr_file, i, &StudentPtr);
						numberOfStudentsInFile++;
						studentAdded = 1;
					}
				}
			}
			if (studentAdded)
			{
				return 1;
			}
		}
	}
	return -1;
}

/* post   : Removes student with StudentNumber from file
 * returns: 0 if StudentNumber was removed from file
 *          -1 if StudentNumber was not found or an error occurs
 */
extern int removeStudentFromFile (char* FileName, int StudentNumber)
{
	if(access(FileName, W_OK ) != -1 && StudentNumber)
	{
		FILE *ptr_file = fopen(*FileName, "r+b");
		if(ptr_file)
		{
		    fseek(ptr_file, 0, SEEK_END);
			int numberOfStudentsInFile = ftell(ptr_file) / sizeof(STUDENT);
			fseek(ptr_file, 0, SEEK_SET);
			STUDENT tempStudent;
			tempStudent.StudentNumber  = -1;
			int studentRemoved = 0;
			int i = 0;
			for (; i < numberOfStudentsInFile; i++)
			{
				STUDENT foundStudent;
				readElement(ptr_file, i, &foundStudent);
				if(tempStudent.StudentNumber != -1)
				{
					readElement(ptr_file, i + 1, &tempStudent);
					writeElement(ptr_file, i, &tempStudent);
				}
				else
				{
					if(StudentNumber == foundStudent.StudentNumber)
					{
						readElement(ptr_file, i + 1, &tempStudent);
						writeElement(ptr_file, i, &tempStudent);
						numberOfStudentsInFile--;
						studentRemoved = 1;
					}
				}
			}
			if (studentRemoved)
			{
				return 0;
			}
		}
	}
	return -1;
}
