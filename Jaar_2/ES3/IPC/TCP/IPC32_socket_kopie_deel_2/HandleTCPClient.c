#include <stdio.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include <iostream>
using namespace std;
#include <string.h>

#include "Auxiliary.h"
#include "HandleTCPClient.h"

#define maxStringSize 32   /* Size of receive buffer */

void HandleTCPClient (int clntSocket)
{
    // 'clntSocket' is obtained from AcceptTCPConnection()

    char 	echoBuffer[maxStringSize];        /* Buffer for echo string */
    int  	recvMsgSize;                   /* Size of received message */
    int 	quit = 0;

	while (!quit)
	{
		/* Receive message from client */
		recvMsgSize = recv (clntSocket, echoBuffer, maxStringSize-1, 0);
		if (recvMsgSize < 0)
			DieWithError ("recv() failed");

		// TODO: add code to print the received string;
		cout << "Received string: " << echoBuffer << endl;
		
		delaying ();
		
		cout << "Please type your message: \n";
		cin.getline(echoBuffer, maxStringSize);
		if(strcmp(echoBuffer, "quit") == 0
		   || strcmp(echoBuffer, "q") == 0
		   || strcmp(echoBuffer, "QUIT") == 0 
		   || strcmp(echoBuffer, "Quit") == 0)
		{
			quit = true;
		}
		else
			send (clntSocket, echoBuffer, maxStringSize, 0);
		
		delaying ();
	}
	
    close (clntSocket);    /* Close client socket */
    info ("close");
}
