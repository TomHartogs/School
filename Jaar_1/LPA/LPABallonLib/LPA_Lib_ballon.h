/*****************************************************************************
* Balloon Unit control of LPA box
* author:  Corne Govers
* version: 10-06-2011
*****************************************************************************/

#ifndef LPA_LIB_BALLON_H
#define LPA_LIB_BALLON_H

/******************************************************************************
* States:
* Burner which drives the temperature in the balloon. It's is either OFF or ON.
*		When the burner is ON (and the valve CLOSED), the balloon will gain height.
*		When the burner is OFF, ultimately the balloon shall lose height.
* Valve which releases the hot air quickly. It is either CLOSED or OPEN.
*		When the valve is OPEN, the balloon loses height.
* 
* Note: Height is measured in meters relative to earth surface. 
*       So if height = 0 then balloon is at ground zero.
*		For this simulation heigth should be between 100 and 400 meter.
*/ 
typedef enum {OFF, ON} BurnerState;
typedef enum {CLOSED, OPEN} ValveState;


/******************************************************************************
* function Balloon_reset initializes the simulator on RP6 control hardware.
*	It's a fresh start for all simulation parameters. 
* pre:  no pre-conditions needed
* post: actual height = random between 100 and 400 meter. 
*		BurnerState = OFF (Green LED on) AND 
*       valveState = CLOSED (RGB-Led is Green)
*/
void Balloon_reset( void );

/******************************************************************************
* function Balloon_get_height detects the actual height of the balloon.
* pre:  function Balloon_reset() has been called at least once
* post: -
* return: actual height in meter. 0 <= height 
*/
unsigned int Balloon_get_height( void );

/******************************************************************************
* function Balloon_get_temperature detects the actual temperature in the balloon.
* pre:  function Balloon_reset() has been called at least once
* post: -
* return: temperature in Celsius.
*/
int Balloon_get_temperature( void );

/******************************************************************************
* function Balloon_set_burner switches the burner ON or OFF
* When the burner is ON, the temperature increment of the air in the balloon is proportional to time 
*      but with a certain delay (a few seconds). As a result there will be a net force on the balloon
*      and thus a acceleration (down or up). This acceleration causes a (vertcal) speed change and thus
*      a change of height.
* When the burner is OFF, the temperature in the balloon will slowly drop because of heat losses
*      to the environment. Ultimately this will result in loss of height.
* pre:  function Balloon_reset() has been called at least once
* post: Burner is switched ON or OFF, depending on argument
*       If bs = ON then burner is ON. RED led on LPA-box turns on. (After a while) balloon gains height (if Valve closed).
*       If bs = OFF then burner is OFF. GREEN led on LPA-box is on. (After a while) balloon loses height.
* Note: Calling Balloon_set_burner(ON) for second, third etc time has no effect. 
*       Ditto with argument (OFF).
*/
void Balloon_set_burner( BurnerState bs );

/******************************************************************************
* function Balloon_get_burnerstate returns the burner state
* pre:  function Balloon_reset() has been called at least once
* post: -
* return: actual burner state (either ON or OFF)
*/
BurnerState Balloon_get_burnerstate( void );

/******************************************************************************
* function Balloon_set_valve opens or closes the valve.
* When the valve is open, the temperature decreases proportional to the temperature 
*      difference between balloon (T) and environment (T0): dT/dt = k.(T - T0).
* pre:  function Balloon_reset() has been called at least once.
* post: Valve is OPEN or CLOSED, depending on argument
*       If OPEN then RGB led on LPA-box is RED.
*       If CLOSED then RGB led on LPA-box is GREEN.
*/
void Balloon_set_valve( ValveState vs );

/******************************************************************************
* function Balloon_get_valvestate returns the valve state
* pre:  function Balloon_reset() has been called at least once
* post: -
* return: actual valve state (either OPEN or CLOSED)
*/
ValveState Balloon_get_valvestate( void );


#endif
