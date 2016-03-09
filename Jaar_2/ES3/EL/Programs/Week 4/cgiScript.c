#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include "buttonInfo.h"

static int  shm_fd = -1;

static char *
my_shm_open (char * shm_name)
{
    int     size;
    char *  shm_addr;
    
    printf ("Calling shm_open('%s')\n", shm_name);
    shm_fd = shm_open (shm_name, O_RDONLY, 0600);
    if (shm_fd == -1)
    {
        perror ("ERROR: shm_open() failed");
    }
    printf ("shm_open() returned %d\n", shm_fd);
                
    printf ("Calling lseek(fd=%d,SEEK_END)\n", shm_fd);
    size = lseek (shm_fd, 0, SEEK_END);
    printf ("lseek() returned %d\n", size);
                
    printf ("Calling mmap(len=%d,fd=%d)\n", size, shm_fd);
    shm_addr = (char *) mmap (NULL, size, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_addr == MAP_FAILED)
    {
        perror ("ERROR: mmap() failed");
    }
    printf ("mmap() returned %p\n", shm_addr);

    return (shm_addr);
}

int main(int argc, char *argv[]) 
{
	char* 		shm_name = "sharedmem\0";
    int       		 	size = -1;
	char *      		shm_addr = (char *) MAP_FAILED;
	
	shm_addr = my_shm_open(shm_name);
	
    char *p;
    
    // print out the default cgi header
    printf("Content-Type: text/html\n\n");

    // print out the html header
    printf("<html>\n<head>\n<title>EL Webserver CGI example </title></head><body>");

	printf("<p>follow up link by ?*yourQuery* to show te string entered.</p>");		 
	printf("<p>Example: 192.168.0.50/cgi-bin/mycgiscript?test</p>");	
	
	int buttonStateSize = sizeof(buttonStates);
	buttonStates readState;
	memcpy(&readState, shm_addr+buttonStateSize, buttonStateSize);
	printf("%i\n", readState.digitalButtonState[YBtn]);	 
	
    // print out some html based on the query string
    p=getenv("QUERY_STRING");
    if (p==NULL)
		 printf("<p>Query String is Empty</p>");
    else 
		printf("<p>Query String: %s</p>\n",p);

    // print out the html footer
    printf("</body></html>");
    return 0;
}
