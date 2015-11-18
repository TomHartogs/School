#include "element_reader.h" 

/* post   : If file contains enough elements, element 'ElementNr' is read into StudentPtr
 * returns: On succes: 1 (1 element was read)
 *          If element does not exist: 0
 *          In case of an error (file could not be read, input pointers are NULL): -1
 */
 
int sizeOfSingleStudent = sizeof(STUDENT);

extern int readElement(FILE* FilePtr, int ElementNr, STUDENT* StudentPtr)
{
	if(FilePtr && ElementNr >= 0 && StudentPtr && fseek(FilePtr, (ElementNr * sizeOfSingleStudent), SEEK_SET) == 0)
	{
		if (fread(StudentPtr, sizeOfSingleStudent, 1, FilePtr))
		{
			return 1;
		}
		return 0;
	}
	return -1;
}

/* post   : Element 'ElementNr' is written into file with data from StudentPtr
 * returns: On succes: 0
 *          In case of an error (file could not be written, input pointers are NULL): -1
 */
extern int writeElement(FILE* FilePtr, int ElementNr, const STUDENT* StudentPtr)
{
	if(FilePtr && ElementNr >= 0 && StudentPtr && fseek(FilePtr, (ElementNr * sizeOfSingleStudent), SEEK_SET) == 0)
	{
		if(fwrite(StudentPtr, sizeOfSingleStudent, 1, FilePtr))
		{
			return 0;
		}
	}
	return -1;
}
