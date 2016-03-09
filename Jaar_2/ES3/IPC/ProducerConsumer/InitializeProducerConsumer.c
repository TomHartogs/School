#include <stdio.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/fcntl.h>

#define bufferSize 5

sem_t *     semdes = SEM_FAILED;
int         rtnval;
static int  shm_fd = -1;
char *  	shm_addr;

void createNewSemaphore(char * sem_name)
{
	printf ("Enter name: ");

	printf ("Calling sem_open('%s', O_CREAT | O_EXCL)\n", sem_name);

	semdes = sem_open (sem_name, O_CREAT | O_EXCL, 0600, 4);
	
	if (semdes == SEM_FAILED)
	{
		perror ("ERROR: sem_open() failed");
	}
	printf ("sem_open() returned %p\n", semdes);	
}

void closeSemaphore(char * sem_name)
{
	printf ("Calling sem_unlink('%s')\n", sem_name);
	rtnval = sem_unlink (sem_name);
	if (rtnval != 0)
	{
		perror ("ERROR: sem_unlink() failed");
	}
	printf ("sem_unlink() returned %d\n", rtnval);	
}

static char *
createShm (char * shm_name, int size)
{
    int     rtnval;
    char *  shm_addr;
    
    shm_fd = shm_open (shm_name, O_CREAT | O_EXCL | O_RDWR, 0600);
    
    if (shm_fd == -1)
    {
        perror ("ERROR: shm_open() failed");
    }
    
    rtnval = ftruncate (shm_fd, size);
    
    if (rtnval != 0)
    {
        perror ("ERROR: ftruncate() failed");
    }
    
    shm_addr = (char *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    if (shm_addr == MAP_FAILED)
    {
        perror ("ERROR: mmap() failed");
    }

    return (shm_addr);
}

static char *
openShm (char * shm_name)
{
    int     size;
    
    shm_fd = shm_open (shm_name, O_RDWR, 0600);
	printf ("shm_open() returned %i\n", shm_fd);
	
    if (shm_fd == -1)
    {
        perror ("ERROR: shm_open() failed");
    }

    size = lseek (shm_fd, 0, SEEK_END);

    shm_addr = (char *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    if (shm_addr == MAP_FAILED)
    {
        perror ("ERROR: mmap() failed");
    }

    return (shm_addr);
}

void CloseAndUnlink(char * shm_name)
{
	rtnval = close (shm_fd);
	
	if (rtnval != 0)
	{
		perror ("ERROR: close() failed");
	}
	
	shm_fd = -1;
	
	rtnval = shm_unlink (shm_name);
	if (rtnval != 0)
	{
		perror ("ERROR: shm_unlink() failed");
	}
	printf("Shm closed and unlinked\n");
}


int main(void)
{
    char        	line[80];
    int         	choice = ' ';
    char        	sem_name1[] = "e";
	char        	sem_name2[] = "s";
	char        	sem_name3[] = "n";
	char        	shm_name[] = "queue";
	unsigned long 	b[bufferSize];
	int 			i;
	for(i = 0; i < bufferSize; i++)
		b[i] = 0;

	//*shm_addr = 0;
	
	do
	{
		printf("Press i to initialize\n");
		choice = getchar();
	}
    while (choice != 'i');
    
    createNewSemaphore(sem_name1);
	createNewSemaphore(sem_name2);
	createNewSemaphore(sem_name3);
	
	shm_addr = createShm(shm_name, sizeof(b));
	shm_addr = openShm(shm_name);
	
	printf("*********************\n");
    printf("*****Initialized*****\n");
    printf("*********************\n");
    
	do
	{
		printf("Press q to close and unlink all\n");
		choice = getchar();
	}
    while (choice != 'q');
    
    closeSemaphore(sem_name1);
    closeSemaphore(sem_name2);
    closeSemaphore(sem_name3);
    
    CloseAndUnlink(shm_name);
    
    printf("*********************\n");
    printf("*******Unlinked******\n");
    printf("*********************\n");

	return (0);
}
