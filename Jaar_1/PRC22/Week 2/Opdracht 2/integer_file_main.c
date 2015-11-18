#include <stdio.h>
#include "integer_file.c"
#include "integer_file.h"

int main()
{
	char fileName[100];
	int high;
	int low;
	printf("What do you want to name the file? (automatic text file)\n");
	scanf("%99s",fileName);
	printf("What should be the highest number?\n");
	scanf("%d", &high);
	printf("What should be the lowest number?\n");
	scanf("%d", &low);
	printf("Filename: %s\nHighest value:%d\nLowest value:%d\n", fileName, high, low);
	printf("%d\n", create_file(fileName, high, low));
	
	return 0;
}


