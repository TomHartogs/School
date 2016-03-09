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


void CloseAndUnlink()
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
}

int main(void)
{
	shm_name[0] = 't';
	shm_name[1] = 'e';
	shm_name[2] = 's';
	shm_name[3] = 't';
	size = 4;
	shm_addr = my_shm_create (shm_name, size);
	shm_addr = my_shm_open (shm_name);
	
	*shm_addr = 0;
	printf ("1\n");
	*shm_addr = 1;
	while(*shm_addr != 0)
	{}
	printf ("3\n");
	*shm_addr = 1;
	while(*shm_addr != 0)
	{}
	printf ("5\n");
	*shm_addr = 1;
	while(*shm_addr != 0)
	{}
	
	CloseAndUnlink();
	return (0);
}
