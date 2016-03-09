#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <mqueue.h>
#include <string>
#include <errno.h>
#include "buttonInfo.h"

static int  shm_fd = -1;

static char *
my_shm_open (const char * shm_name)
{
    int     size;
    char *  shm_addr;
   
    shm_fd = shm_open (shm_name, O_RDONLY, 0600);
    if (shm_fd == -1)
    {

    }
    size = lseek (shm_fd, 0, SEEK_END);

    shm_addr = (char *) mmap (NULL, size, PROT_READ, MAP_SHARED, shm_fd, 0);

    return (shm_addr);
}

int main(int argc, char *argv[]) 
{
	const char* 		shm_name = "sharedmem\0";
	char *      		shm_addr = (char *) MAP_FAILED;
	
	shm_addr = my_shm_open(shm_name);
	if(shm_addr == (char *) MAP_FAILED)
	{
		printf("<html>\n");
		printf("<header><title>Error</title></header>\n");
		printf("<body>Daemon not started</body>\n");
		printf("</html>\n");
		return 0;
	}
    char *parameter;

	int buttonStateSize = sizeof(buttonStates);
	int numbOfControllers = 0;
	numbOfControllers = shm_addr[0];
	shm_addr++;

    // print out the default cgi header
    printf("Content-Type: text/html\n\n");

    // print out the html header
    printf("<html>\n");
		printf("<head>\n");
			printf("<meta http-equiv=\"refresh\" content=\"1; url=?\"/>\n");
			printf("<title>EL Webserver Controller daemon</title>\n");
		printf("</head>\n");
		printf("<body>\n");
		
			buttonStates readState;
			for(int i = 0; i < numbOfControllers; i++)
			{
				memcpy(&readState, shm_addr+(buttonStateSize*i), buttonStateSize);
				
				printf("<table>\n");
					printf("<tr>\n");
					printf("<td></td>\n");
					printf("<td>&#94;:%i</td>\n", readState.digitalButtonState[dPadUp]);
					printf("<td></td>\n");
					printf("<td></td>\n");
					printf("<td></td>\n");
					printf("<td>Y:%i</td>\n", readState.digitalButtonState[YBtn]);
					printf("<td></td>\n");
					printf("</tr>\n");
					printf("<tr>\n");
					printf("<td>&#60;:%i</td>\n", readState.digitalButtonState[dPadLeft]);
					printf("<td></td>\n");
					printf("<td>&#62;:%i</td>\n", readState.digitalButtonState[dPadRight]);
					printf("<td></td>\n");
					printf("<td>X:%i</td>\n", readState.digitalButtonState[XBtn]);
					printf("<td></td>\n");
					printf("<td>B:%i</td>\n", readState.digitalButtonState[BBtn]);
					printf("</tr>\n");
					printf("<tr>\n");
					printf("<td></td>\n");
					printf("<td>v:%i</td>\n", readState.digitalButtonState[dPadDown]);
					printf("<td></td>\n");
					printf("<td></td>\n");
					printf("<td></td>\n");
					printf("<td>A:%i</td>\n", readState.digitalButtonState[ABtn]);
					printf("<td></td>\n");
					printf("</tr>\n");
				printf("</table>\n");
				printf("<a href=\"?Buzzer%iOn\">Buzzer on</a>&nbsp;\n", i);
				printf("<a href=\"?Leds%iRotating\">Rotate leds</a></br>\n", i);
				printf("<a href=\"?Buzzer%iOff\">Buzzer off</a>&nbsp;\n", i);
				printf("<a href=\"?Leds%iBlinking\">Blink leds</a><br>\n", i);
			}

    parameter=getenv("QUERY_STRING");
    if(parameter != NULL)
    {
		mqd_t mqXpadCom = mq_open("/xpadCom",  O_WRONLY | O_NONBLOCK);
		std::string command = parameter;
		if(command.length() > 1)
			mq_send(mqXpadCom, command.c_str(), command.length(), 0);
	}
	
    // print out the html footer
		printf("</body>\n");
	printf("</html>");
    
    return 0;
}
