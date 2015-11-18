#include "element_reader.c"
#include "file.c"

int main(void)
{
	STUDENT testStudent1;
	testStudent1.StudentNumber = 1;
	testStudent1.StudyCredits = 10;
	addStudentSortedToFile("test.txt", &testStudent1);
	return 0;
}
