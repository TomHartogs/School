#include <stdlib.h>
#include "integer_file.h"
#include <stdio.h>
#include <string.h>

int create_file(char* filename, int high, int low)
/* pre : -
 * post: If all parameters are valid, a new file is created with name filename. The file contains integers,
 *       starting from high and counting down to low. Result 0 is returned.
 *       If parameters are invalid (null or high is lower than low), -1 is returned.
 *       thus create_file("test.txt", 3999, 3000) will result in a text file that contains 1000 integers
 *       starting at 3999 and counting down to 3000
 */
{
    // TODO: implement
    if(filename && high > low)
    {
		char filetype[] = ".txt";
		strcat(filename, filetype);
		FILE *file;
		file = fopen(filename, "w");
		for(; high > low - 1; high--)
		{
			fprintf(file, "%d\n", high);
		}
		fclose(file);
		return 0;
	}
	else
	{
		return -1;
	}
}

int delete_file(char* filename)
/* pre : -
 * post: If filename is valid, file is removed from disk and 0 is returned. Else -1 is returned.
 */
{
    // TODO: implement
    if(filename)
    {
		char filetype[] = ".txt";
		strcat(filename, filetype);
	   if(remove(filename) == 0) 
	   {
		  printf("File deleted successfully\n");
		  return 0;
	   }
	}
	printf("Error: unable to delete the file\n");
	return -1;
}

int read_value(FILE* fileptr, int pos)
/* pre : -
 * post: the value on position pos is read from the correct location in the already opened file
 *       if fileptr is NULL, -1 is returned.
 */
{
    // TODO: implement
    if(fileptr)
    {
		char buff[255];
		fseek(fileptr, pos, SEEK_SET);
		int fgetc( FILE * fileptr );
		char* test = fgets(buff, 255, (FILE*)fileptr);
		printf("%s\n", test);
		printf("%s\n", buff);
		int value = atoi(buff);
		return value;
	}
	return -1;
}
