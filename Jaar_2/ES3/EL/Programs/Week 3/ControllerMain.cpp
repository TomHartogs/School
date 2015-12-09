#include "Controller.h"
#include <cstdlib>
#include <unistd.h>

int interfaceNumber = 1;
uint16_t MicrosoftVID = 0x045e;
uint16_t XboxPID = 0x028e;

int main()
{
	Controller xboxController = Controller(MicrosoftVID, XboxPID, (1 | LIBUSB_ENDPOINT_IN), (2 | LIBUSB_ENDPOINT_OUT));	
	
	if(xboxController.Open())
		printf("Controller opened\n");
	else
		exit(EXIT_FAILURE);
		
	xboxController.ClaimInterface(interfaceNumber);
	
	xboxController.SetLeds(Rotating);
	
	xboxController.SetRumble(0, 0);
	
	printf("\033[2J");
	while(1)
	{
		xboxController.PrintStatus();
		usleep(1000);
	}
	
	return 0;
}
