/*
 * Written by:
 * Tom Hartogs T32
*/

#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>

#define bufferSize 5

sem_t *     e = SEM_FAILED;
sem_t *     s = SEM_FAILED;
sem_t *     n = SEM_FAILED;

unsigned long *      	shm = (unsigned long *) MAP_FAILED;

int 					out = 0;

void connect()
{
	char        	sem_name1[] = "e";
	char        	sem_name2[] = "s";
	char        	sem_name3[] = "n";
	char        	shm_name[] = "queue";
	static int  	shm_fd = -1;
	
	e = sem_open (sem_name1, 0);
	printf ("sem_open() returned %p\n", e);
	if(e == SEM_FAILED)
		perror("ERROR: sem_open(e) failed");
	s = sem_open (sem_name2, 0);
	printf ("sem_open() returned %p\n", s);
	if(s == SEM_FAILED)
		perror("ERROR: sem_open(s) failed");
	n = sem_open (sem_name3, 0);
	printf ("sem_open() returned %p\n", n);
	if(n == SEM_FAILED)
		perror("ERROR: sem_open(n) failed");
	
	shm_fd = shm_open (shm_name, O_RDWR, 0600);
	if (shm_fd == -1)
        perror ("ERROR: shm_open() failed");
    
    shm = (unsigned long *) mmap (NULL, lseek (shm_fd, 0, SEEK_END), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm == MAP_FAILED)
        perror ("ERROR: mmap() failed");
}

void take()
{	
	printf(("shm[%i] = %lu\n"), out, shm[out]);
	shm[out] = 0;
}

void consume()
{
	if(out >= bufferSize - 1)
		out = 0;
	else
		out++;
}

int main(void)
{
	connect();
	
	while(1)
	{
		sem_wait(n);
		//sem_wait(s);
		take();
		//sem_post(s);
		sem_post(e);
		consume();
	}
	return 0;
}
