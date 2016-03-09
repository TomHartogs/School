#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

static int  shm_fd = -1;
char *      shm_addr = (char *) MAP_FAILED;
char        line[80];
char        shm_name[80];
int         size = -1;
int         choice = ' ';
int         rtnval;

static char *
my_shm_create (char * shm_name, int size)
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
my_shm_open (char * shm_name)
{
    int     size;
    char *  shm_addr;
    
    shm_fd = shm_open (shm_name, O_RDWR, 0600);
    
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


void Close()
{
	rtnval = close (shm_fd);
	
	if (rtnval != 0)
	{
		perror ("ERROR: close() failed");
	}
	
	shm_fd = -1;
}

int main(void)
{ 
	shm_name[0] = 't';
	shm_name[1] = 'e';
	shm_name[2] = 's';
	shm_name[3] = 't';
	while(shm_fd == -1)
	{
		shm_addr = my_shm_open (shm_name);
	}
	
	while(*shm_addr != 1)
	{}
	printf ("2\n");
	*shm_addr = 0;
	while(*shm_addr != 1)
	{}
	printf ("4\n");
	*shm_addr = 0;
	while(*shm_addr != 1)
	{}
	printf ("6\n");
	*shm_addr = 0;
	
	Close();
	
	return (0);
}
