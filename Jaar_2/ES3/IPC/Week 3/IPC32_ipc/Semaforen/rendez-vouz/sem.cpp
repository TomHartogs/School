#include "sem.h"
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h> 

sem_t* createNewSemaphore(char * sem_name, int StartingValue)
{
	sem_t* semdes = SEM_FAILED;
	
	semdes = sem_open (sem_name, O_CREAT | O_EXCL, 0600, StartingValue);
	if (semdes == SEM_FAILED)
	{
		perror ("ERROR: sem_open() failed");
	}
	return semdes;
}

sem_t* openSemaphore(char* sem_name)
{
	sem_t* semdes = SEM_FAILED;
	semdes = sem_open (sem_name, 0);
	if (semdes == SEM_FAILED)
	{
		perror ("ERROR: sem_open() failed");
	}
	return semdes;
}

void closeSemaphore(char* sem_name)
{
	int rtnval;
	rtnval = sem_unlink (sem_name);
	if (rtnval != 0)
	{
		perror ("ERROR: sem_unlink() failed");
	}
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
