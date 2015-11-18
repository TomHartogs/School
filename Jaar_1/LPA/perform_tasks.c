#include "perform_tasks.h"

int pcInCharge = 0;
int desiredHeight = 0;
int buffer = 2;

void performTasks(MESSAGE* _message)
{	
	switch (_message->action) 
	{
		case GET_HEIGHT:
			_message->data = Balloon_get_height();
			Write(*_message);
			break;
		case SET_HEIGHT:
			if(pcInCharge)
			{
				if(_message->data > 400)
					desiredHeight = 40;
				else if(_message->data < 0)
					desiredHeight = 0;
				else
					desiredHeight = _message->data/10;
			}
			break;
		case RP6_IN_CHARGE:
			pcInCharge = 0;
			break;
		case PC_IN_CHARGE:
			pcInCharge = 1;
			break;
		default:
			break;
	}
}

void cleanMessage(MESSAGE* _message)
{
	_message->data = -1;
	_message->action = -1;
}

void setHeightRp6(int height)
{
	if(!pcInCharge)
	{
		desiredHeight = height/10;
	}
}

void maintainHeight( void )
{
	int currentHeight = Balloon_get_height();
	if(currentHeight <= desiredHeight)
	{
		Balloon_set_valve(CLOSED);
		Balloon_set_burner(ON);
	}
	else if(currentHeight >= desiredHeight)
	{
		int difference = (desiredHeight - currentHeight);
		if(difference < 2)
		{
			Balloon_set_valve(OPEN);
			Balloon_set_burner(ON);
		}
		else
		{
			Balloon_set_valve(OPEN);
			Balloon_set_burner(OFF);
		}
	}
	else if(currentHeight + buffer <= desiredHeight && currentHeight - buffer >= desiredHeight)
	{
		Balloon_set_valve(CLOSED);
		Balloon_set_burner(OFF);
	}
}

void showSimParams( void )
{
	clearPosLCD(0,7,3);
	setCursorPosLCD(0, 7);
	writeIntegerLCD( Balloon_get_height(), DEC);
	
	setCursorPosLCD(0, 11);
	writeIntegerLCD(desiredHeight, DEC);

	clearPosLCD(1,3,5);
	setCursorPosLCD(1, 3);
	if(Balloon_get_valvestate() == OPEN) {
		writeStringLCD("OPEN  ");
	} else {
		writeStringLCD("CLOSED");
	}

	clearPosLCD(1,13,5);
	setCursorPosLCD(1, 13);
	if(Balloon_get_burnerstate() == ON) {
		writeStringLCD("ON ");
	} else {
		writeStringLCD("OFF");
	}
	
	int currentHeight = Balloon_get_height();		
	if(currentHeight >= 8 && currentHeight <= 12)
		setLEDs(0b0001);
	else if(currentHeight >= 18 && currentHeight <= 22)
		setLEDs(0b0010);
	else if(currentHeight >= 28 && currentHeight <= 32)
		setLEDs(0b0100);
	else if(currentHeight >= 38 && currentHeight <= 42)
		setLEDs(0b1000);
	else
		setLEDs(0b0000);
		
}
