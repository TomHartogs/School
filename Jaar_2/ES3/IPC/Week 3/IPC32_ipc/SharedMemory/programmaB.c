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
remove_nl (char * s)
{
    int len;
    
    len = strlen (s);
    if (s [len - 1] == '\n')
    {
        s [len - 1] = '\0';
    }
    
    return (s);
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

void OpenShm()
{
	printf ("Enter name: ");
	fgets  (shm_name, sizeof (shm_name), stdin);
	remove_nl (shm_name);
	
	shm_addr = my_shm_open (shm_name);
}

void CloseShm()
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
	OpenShm();
	
	if(shm_fd != -1 || shm_addr != MAP_FAILED)
	{
		printf ("data (@ %#x): '%s'\n", (unsigned int) shm_addr, shm_addr);
		
		while(*shm_addr != 'a')
		{}
		
		printf ("data (@ %#x): '%s'\n", (unsigned int) shm_addr, shm_addr);
		
		*shm_addr = 'A';
		
		printf ("data (@ %#x): '%s'\n", (unsigned int) shm_addr, shm_addr);

		CloseShm();
	}
	
	return (0);
}
