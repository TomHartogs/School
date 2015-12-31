#ifndef XPADTEST_H
#define XPADTEST_H

#include <libusb-1.0/libusb.h>
#include <stdio.h>

typedef struct 
{
	uint8_t type;
	uint8_t size;
	uint8_t dPadUp : 1;
	uint8_t dPadDown : 1;
	uint8_t dPadLeft : 1;
	uint8_t dPadRight : 1;
	uint8_t StartBut : 1;
	uint8_t BackBut : 1;
	uint8_t LeftStickPress : 1;
	uint8_t RightStickPress : 1;
	uint8_t ButtonLB : 1;
	uint8_t ButtonRB : 1;
	uint8_t LogoButton : 1;
	uint8_t Unused : 1;
	uint8_t ButtonA : 1;
	uint8_t ButtonB : 1;
	uint8_t ButtonX : 1;
	uint8_t ButtonY : 1;
	uint8_t LeftTrigger;
	uint8_t RightTrigger;
	int16_t LeftStickXaxis;
	int16_t LeftStickYaxis;
	int16_t RightStickXaxis;
	int16_t RightStickYaxis;
   
} XboxController;

void SetLeds(uint8_t mode, libusb_device_handle * h);
void SetMotors(uint8_t big, uint8_t smal, libusb_device_handle * handle);
void printdemo(XboxController* xbox);
void xboxinfo(unsigned char* data, XboxController* xbox);

#endif



