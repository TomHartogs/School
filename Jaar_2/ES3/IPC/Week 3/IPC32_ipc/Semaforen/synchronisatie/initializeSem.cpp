#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include <iostream>

sem_t * semdes 		= SEM_FAILED;
char sem_name[5] 	= "sem0";

void createNewSemaphore(char * sem_name)
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

void closeAll()
{
	printf("closing all\n");
	for(int i = 1; i < 5; i++)
	{
		sem_name[3] = '0' + i;
		closeSemaphore (sem_name);
	}
}

int main(void)
{
    char        line[80];
    int         choice = ' ';
	
	atexit(closeAll);
	
	sem_name[3] = '1';
	createNewSemaphore(sem_name);
	sem_post(semdes);
	
	for(int i = 2; i < 5; i++)
	{
		sem_name[3] = '0' + i;
		createNewSemaphore(sem_name);
	}

    while (choice != 'q')
    {
        printf ("\nMenu\n"
                "========\n"
                "   [q]    quit\n"
                "Enter choice: "
               );
        fgets (line, sizeof (line), stdin);
        choice = line[0];
        printf ("\n");	
    }
    
   
	return (0);
}
