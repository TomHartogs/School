#include <stdio.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include "Auxiliary.h"
#include "HandleTCPClient.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */

void HandleTCPClient (int clntSocket)
{
    // 'clntSocket' is obtained from AcceptTCPConnection()

    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int  recvMsgSize;                   /* Size of received message */

    /* Receive message from client */
    recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
    if (recvMsgSize < 0)
    {
        DieWithError ("recv() failed");
    }
    info_d ("Recv", recvMsgSize);
    
    /*een ontvangen string wordt met '\0' afgesloten*/
	echoBuffer[recvMsgSize+1] = '\0';
	
    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
			// TODO: add code to print the received string; use printf()
		int i = 0;
		printf("received string:");
		while(echoBuffer[i] != '\0')
		{
			printf("%c", echoBuffer[i]);
			i++;
		}
		printf("%i\n", i);
			
			// TODO: add code to convert the upper/lower chars of the received string
		int j=0;
		while(echoBuffer[j] != '\0')
		{
			if ('a'<=echoBuffer[j] && echoBuffer[j]<='z')
			{
				echoBuffer[j]=char(((int)echoBuffer[j])-32);
			}

			if ('A'<=echoBuffer[j] && echoBuffer[j]<='Z')
			{
			   echoBuffer[j]=char(((int)echoBuffer[j])+32);
			}

			j++;
		}

			delaying ();
			
			/* Echo message back to client */
			if (send (clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
			{
				DieWithError ("send() failed");
			}

			// TODO: add code to display the transmitted string in verbose mode; use info_s()
			
			info_s("Message echoed: " ,echoBuffer);
			
			// receive next string
			recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
			if (recvMsgSize < 0)
			{
				DieWithError ("recv() failed");
			}
			info_d ("recv", recvMsgSize);
    }

    close (clntSocket);    /* Close client socket */
    info ("close");
}
