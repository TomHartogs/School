#include "sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h> 

void createNewSemaphore(char * sem_name, sem_t* semdes)
{
	semdes = SEM_FAILED;
	
	printf ("Calling sem_open('%s', O_CREAT | O_EXCL)\n", sem_name);

	semdes = sem_open (sem_name, O_CREAT | O_EXCL, 0600, 0);
	if (semdes == SEM_FAILED)
	{
		perror ("ERROR: sem_open() failed");
		exit(EXIT_FAILURE);
	}
	printf ("sem_open() returned %p\n", semdes);
}

void openSemaphore(char* sem_name, sem_t** semaphoreDes)
{
	printf ("Calling sem_open('%s',%#o)\n", sem_name,0);
	*semaphoreDes = sem_open (sem_name, 0);
	if (*semaphoreDes == SEM_FAILED)
	{
		perror ("ERROR: sem_open() failed");
		exit(EXIT_FAILURE);
	}
	printf ("sem_open() returned %p\n", *semaphoreDes);
}

void closeSemaphore(char * sem_name)
{
	int rtnval;
	printf ("Calling sem_unlink('%s')\n", sem_name);
	rtnval = sem_unlink (sem_name);
	if (rtnval != 0)
	{
		perror ("ERROR: sem_unlink() failed");
	}
	printf ("sem_unlink() returned %d\n", rtnval);	
}

void semPost(sem_t* semDes)
{
	if(sem_post (semDes) == -1)
	{
		perror ("ERROR: sem_post() failed");
	}
}

void semWait(sem_t* semDes)
{
	if(sem_wait(semDes) == -1)
	{
		perror ("ERROR: sem_wait() failed");
	}
}
