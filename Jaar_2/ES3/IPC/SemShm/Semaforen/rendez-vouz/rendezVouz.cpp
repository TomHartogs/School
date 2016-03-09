#include <stdio.h>
#include <semaphore.h>
#include <string>
#include "sem.h"
#include <fcntl.h> 

int start = 0;

int checkParameters(int argc, char* argv[])
{
	if(argc != 3)
	{
		if(argc == 4 && std::string(argv[1]) == "-start")
			start = 1;
		else
		{
			perror ("Invalid parameter entered\n"
					"./program -start(optional) statement1 statement2\n");
			return 0;	
		}
	}
	return 1;
}

int main(int argc, char* argv[])
{
	if(!checkParameters(argc, argv))
	{
		return -1;
	}
	sem_t*	 	semdes = SEM_FAILED;
	sem_t*		counting_semdes = SEM_FAILED;
	
	if(start == 1)
	{
		semdes = createNewSemaphore((char*)"rendezVouzSem", 0);
		counting_semdes = createNewSemaphore((char*)"rendezVouzCountingSem", 0);
	}
	else
	{
		semdes = openSemaphore((char*)"rendezVouzSem");
		counting_semdes = openSemaphore((char*)"rendezVouzCountingSem");
	}
	
	if(start)
		printf("%s\n", argv[2]);
	else
		printf("%s\n", argv[1]);
	
	semPost(counting_semdes);
	int value = 0;
	sem_getvalue(counting_semdes, &value);
	
	if(value == 4)
	{
		for(int i = 0; i < 3; i++)
			semPost(semdes);
	}
	else
		semWait(semdes);

	if(start)
		printf("%s\n", argv[3]);
	else
		printf("%s\n", argv[2]);
		
	if(start)
	{
		closeSemaphore((char*)"rendezVouzSem");
		closeSemaphore((char*)"rendezVouzCountingSem");
	}
		
	return (0);
}
