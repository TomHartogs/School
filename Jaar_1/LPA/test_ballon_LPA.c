/* 
 * ****************************************************************************
 * LPA Library - RP6 CONTROL M32 Examples
 * ****************************************************************************
 * Author(s): Peter Lambooij, 30 oktober 2010
 *            Corne Govers, Sinterklaas' naamdag
 * ****************************************************************************
 * Description:
 * 
 * 
 *
 * ATTENTION:
 * This and all other Examples for RP6Control assume that you did run the other 
 * example programs from the RP6 Robot Base before, understood those 
 * examples (most of it at least) and that you have read the RP6-BASE and 
 * RP6-M32 manuals. Some things are repeated here, but not everything!
 *
 * ############################################################################
 * The Robot does NOT move in this example! You can simply put it on a table
 * next to your PC and you should connect it to the PC via the USB unsigned charerface!
 * ############################################################################
 * ****************************************************************************
 */

/*****************************************************************************/
// Includes:

#include <RP6ControlLib.h> 		// The RP6 Control Library. 

#include "LPA_Lib_ballon.h"

void showSimParams( void )
{

	clearPosLCD(0,7,5);
	setCursorPosLCD(0, 7);
	writeIntegerLCD( Balloon_get_height(), DEC);

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
}

void testLPABallon( void )
{
	initLCD(); 		 // Initialize the LC-Display (LCD)
	showScreenLCD("################", "################");
	mSleep(500);
	showScreenLCD("Tst LPA BallonLIB", "versie 29jun15");
	mSleep(500);
	// ---------------------------------------
	setLEDs(0b0000); // All LEDs off!

	// This text is fixed on the LCD. Only the
	// key and ADC values are changed later on!
	showScreenLCD("hoogte: ", "VS:       BS:");
	while(true) 
	{
      // read some simulations parameter values and display them on teh LCD
      showSimParams();
      // Check if a key is pressed:
      uint8_t key = getPressedKeyNumber(); 
      // This function returns a 0 if no key is pressed and the key number from 1 to 5 otherwise.
      if(key) // If a key is pressed... (key != 0)
      {
         // ... and depending on which key was pressed, we 
         // call some library functions related to the burner and the valve.

         switch(key)
         {
            case 1: 
               Balloon_set_burner(ON);
               break;
            case 2:
               Balloon_set_burner(OFF);
               break;
            case 3: 
               Balloon_set_valve(OPEN);
               break;
            case 4: 
               Balloon_set_valve(CLOSED);
               break;
            case 5: 
               break;
         }
         // ... wait until the key is released again...
         while(getPressedKeyNumber())
         {
            showSimParams(); // use busy waiting for polling keys
         }
      }
	}
}
/*****************************************************************************/
// Main function - The program starts here:

int main(void)
{
	initRP6Control(); // Always call this first! The Processor will not work correctly otherwise. 
	Balloon_reset();  // Initialize the balloon simulator
	testLPABallon();  // jump into the never ending loop
	return 0;
}
