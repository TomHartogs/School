#include "file.h"
#include "element_reader.h"
#include "unity.h" 

void setUp(void)
{
    // This is run before EACH test
}

void tearDown(void)
{
    // This is run after EACH test
}

void addStudentToFile_TEST(void)
{
	STUDENT student;
	student.StudentNumber = 10;
	student.StudyCredits = 3;
	fileName = "test.txt";
	TEST_ASSERT_EQUAL(addStudentSortedToFile(&fileName, &student), 1);
	STUDENT student1;
	student1.StudentNumber = 0;
	student1.StudyCredits = 0;
	TEST_ASSERT_EQUAL(linearSearchStudentsFile(&fileName, student.StudentNumber + 1, &student1), -1);
	TEST_ASSERT_EQUAL(linearSearchStudentsFile(&fileName, student.StudentNumber, &student1), 0);
	TEST_ASSERT_EQUAL(student1.StudentNumber, 10);
	TEST_ASSERT_EQUAL(student1.StudyCredits, 3);
}

void computeAverageStudyResults_TEST(void)
{
	STUDENT student;
	student.StudyCredits = 3;
	STUDENT student1;
	student.StudyCredits = 7;
	STUDENT student2;
	student.StudyCredits = 5;
	fileName = "test.txt";
	double average;
	addStudentSortedToFile(&fileName, &student);
	addStudentSortedToFile(&fileName, &student1);
	addStudentSortedToFile(&fileName, &student2);
	TEST_ASSERT_EQUAL(computeAverageStudyResults(&file, &average), 0); 
	TEST_ASSERT_EQUAL(average, 5);
}

void binarySearchStudentsFile_TEST(void)
{
	STUDENT student;
	student.StudentNumber = 10;
	student.StudyCredits = 3;
	STUDENT foundStudent;
	fileName = "test.txt";
	addStudentSortedToFile(&fileName, &student);
	TEST_ASSERT_EQUAL(binarySearchStudentsFile(&fileName, student.StudentNumber, &foundStudent), 0);
	TEST_ASSERT_EQUAL(foundStudent.SudentNumber, 10);
	TEST_ASSERT_EQUAL(foundStudent.StudyCredits, 3);
}

int main (int argc, char * argv[])
{
    UnityBegin();
    
    addStudentToFile_TEST();
    computeAverageStudyResults_TEST();
    binarySearchStudentsFile_TEST();
    
    return UnityEnd();
}
