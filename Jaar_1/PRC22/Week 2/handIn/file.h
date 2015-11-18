#ifndef _FILE_H
#define _FILE_H

#include "element_reader.h"

extern int computeAverageStudyResults (char* FileName, double* Average);
/* pre    :
 * post   : Calculates the average of all study results in a file
 * returns: -1 if an error occurs, 0 if a valid average is computed
 */

extern int linearSearchStudentsFile (char* FileName, int Number, STUDENT* StudentPtr);
/* pre    : 
 * post   : Returns student information of student with student number Number
 * returns: -1 if Number is not available or in case of an error, 0 if Number is available
 */

extern int binarySearchStudentsFile (char* FileName, int Number, STUDENT* StudentPtr);
/* pre    : 
 * post   : Returns student information of student with student number Number
 * returns: -1 if Number is not available or in case of an error, 0 if Number is available
 */

extern int addStudentSortedToFile (char* FileName, STUDENT* StudentPtr);
/* pre    : 
 * post   : Adds information from StudentPtr to FileName in a sorted way,
 *          if FileName does not exist, a new file is created.
 * returns: -1 in case of an error
 *          0  if a student with the given student number already exists
 *          1  if the student is added to the file
 */

extern int removeStudentFromFile (char* FileName, int StudentNumber);
/* pre    : 
 * post   : Removes student with StudentNumber from file
 * returns: 0 if StudentNumber was removed from file
 *          -1 if StudentNumber was not found or an error occurs
 */

#endif
