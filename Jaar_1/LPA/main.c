/*****************************************************************************/
// Includes:
#include "RP6ControlLib.h"
#include <stdlib.h>

//Own includes
#include "action_enum.h"
#include "initialize.h"
#include "message.h"
#include "perform_tasks.h"   

/*****************************************************************************/
// Main function - The program starts here:

MESSAGE _message;

int main(void)
{
	Initialize();														//Initializes all standard Rp6 functions
	
	clearReceptionBuffer();												//Clears the buffer for clean receiving

	while(true) 														//Start loop
	{
		ReadKeys();
		if(Read(&_message))												//Check if a message has been read
		{				
			performTasks(&_message);								    //Perform action thats set in _message
			
			cleanMessage(&_message);									//Clean the message for the next run
		}
		maintainHeight();
		showSimParams();
	}
	return 0;
}

void ReadKeys()
{
	uint8_t key = getPressedKeyNumber(); 
	if(key) // If a key is pressed... (key != 0)
	{
		setHeightRp6((key - 1) * 100);
		while(getPressedKeyNumber())
		{
			showSimParams(); 
		}
	}	
}



