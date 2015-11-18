#ifndef INTEGER_FILE_H
#define INTEGER_FILE_H

int create_file(char* filename, int high, int low);

int delete_file(char* filename);

int read_value(FILE* fileptr, int pos);


#endif
