#include <stdio.h>
#include <semaphore.h>
#include "sem.h"

sem_t *     ownSemDes = SEM_FAILED;
sem_t *     nextSemDes = SEM_FAILED;
char        sem_name[5] = "sem0";
int         value = -1;

int main(int argc, char* argv[])
{
	if(argc != 2 || (*argv[1] != '1' && *argv[1] != '2' && *argv[1] != '3' && *argv[1] != '4'))
	{
		perror ("Invalid parameter given\n"
				"Pass program number (1,2,3,4)\n");
		return 1;	
	}
	
	int programNumber = *argv[1] - '0';

	sem_name[3] = '0' + programNumber;
	openSemaphore(sem_name, &ownSemDes);
	if(programNumber == 4)
	{
		sem_name[3] = '0' + (programNumber - 3);
		openSemaphore(sem_name, &nextSemDes);
	}
	else
	{
		sem_name[3] = '0' + (programNumber + 1);
		openSemaphore(sem_name, &nextSemDes);
	}
		
	if(ownSemDes == SEM_FAILED || nextSemDes == SEM_FAILED)
		return -1;
		
	semWait(ownSemDes);
	
	printf("Program %i:   ", programNumber);
	printf("%i\n", programNumber);

	semPost(nextSemDes);
	
	semWait(ownSemDes);

	printf("Program %i:   ", programNumber);
	printf("%i\n", programNumber + 4);
	
	semPost(nextSemDes);

	return (0);
}
