#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include <iostream>
using namespace std;

#include "Auxiliary.h"
#include "CreateTCPClientSocket.h"

#define maxStringSize 32   /* Size of string */

int main (int argc, char *argv[])
{
    int         sock;                   	/* Socket descriptor */
    int			quit = 0;
    char *      messageString;   			/* Buffer for sending string */
	int			messageStringLen;
	int         bytesRcvd;              	/* Bytes read in single recv() */
printf("test");
    parse_args (argc, argv);
	
    sock = CreateTCPClientSocket (argv_ip, argv_port);
    
    while (!quit)
    {
        cout << "Please type your message: \n";
        cin.getline(messageString, maxStringSize);
	
		if(strcmp(messageString, "quit") == 0
		   || strcmp(messageString, "q") == 0
		   || strcmp(messageString, "QUIT") == 0 
		   || strcmp(messageString, "Quit") == 0)
		{
			quit = true;
		}
		else
		{
			delaying();
		
			send (sock, messageString, maxStringSize, 0);
			
			delaying();
			
			/*if(recv (sock, messageString, maxStringSize-1, 0) < 0);
				DieWithError ("recv() failed");
			else
				cout << messageString;*/
		}
    }
       	
    close (sock);
    info ("close & exit");
    exit (0);
}
