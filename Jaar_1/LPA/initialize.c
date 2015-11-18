#include "initialize.h" 

/**
 * This function initializes the Rp6.
 */
void Initialize()
{
	// init rp6
	initRP6Control();  
	initLCD();
	Balloon_reset();

    // do some init stuff
	setLEDs(0b1111);
	showScreenLCD("LPA Tom Hartogs", "Hot Air Balloon");
	mSleep(1000);
	showScreenLCD("height:  ", "VS:       BS:");
	setLEDs(0b0000);
}
