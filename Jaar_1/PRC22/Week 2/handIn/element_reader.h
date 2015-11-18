#ifndef _ELEMENT_READER_H
#define _ELEMENT_READER_H

#include <stdbool.h>
#include <stdio.h>


typedef struct
{
    int     StudentNumber;
    char    Surname[25];
    int     StudyCredits;
} STUDENT;

extern int readElement(FILE* FilePtr, int ElementNr, STUDENT* StudentPtr);
/* pre    : 
 * post   : If file contains enough elements, element 'ElementNr' is read into StudentPtr
 * returns: On succes: 1 (1 element was read)
 *          If element does not exist: 0
 *          In case of an error (file could not be read, input pointers are NULL): -1
 */

extern int writeElement(FILE* FilePtr, int ElementNr, const STUDENT* StudentPtr);
/* pre    : 
 * post   : Element 'ElementNr' is written into file with data from StudentPtr
 * returns: On succes: 0
 *          In case of an error (file could not be written, input pointers are NULL): -1
 */

#endif
