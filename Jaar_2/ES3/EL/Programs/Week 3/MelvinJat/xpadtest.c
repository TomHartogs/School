/*
 * de volgende code laat het ledje op de gamepad rondspinnen:
*/
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include "xpadtest.h"
#define LastBit 0x01
#define SevendBit 0x02
#define SixedBit 0x04
#define FifthBit 0x08
#define FourthBit 0x10
#define ThirthBit 0x20
#define SecondBit 0x40
#define FistBit 0x80

int main(int argc, char *argv[])
{
	//XboxController xbox;	
	libusb_device_handle *h;
	//int error;
	//int transferred;
	int interface = 1;
	int keralcheck;
	//unsigned char xboxImput[20];
	//Init usblib opens it and check interface and claims it.
	libusb_init(NULL);
	h = libusb_open_device_with_vid_pid(NULL, 0x045e, 0x028e);
	keralcheck = libusb_kernel_driver_active(h, interface);
	if(keralcheck == 1)
	{
		libusb_detach_kernel_driver(h, interface);	
	}
	libusb_claim_interface(h, interface);	
	if (h == NULL) 
	{
		fprintf(stderr, "Failed to open device\n");
		return (1);
	}
	
	//Gets info and writes to the motors with the LT and RT.
	
	int tempint = 0;
	unsigned char data[] = { 1, 3, 0x0a };
	libusb_interrupt_transfer(h, 0x01, data, sizeof data, &tempint, 0);
	
	return (0);
}

void SetLeds(uint8_t mode, libusb_device_handle * h)
{
	int tempint = 0;
	unsigned char data[] = { 1, 3, mode };
	libusb_interrupt_transfer(h, 0x01, data, sizeof data, &tempint, 0);
}

void SetMotors(uint8_t bigmotor, uint8_t smallmotor, libusb_device_handle * h)
{
	int tempint = 0;
	unsigned char data[] = { 0x00, 0x08, 0x00, smallmotor, bigmotor, 0x00, 0x00, 0x00 };
	libusb_interrupt_transfer(h, 0x01, data, sizeof data, &tempint, 0);
}

//prints a 1 if button is pressed
void printdemo(XboxController* xbox)
{
	printf("dPadUp = %u \n" , xbox->dPadUp);
	printf("dPadDown = %u \n" , xbox->dPadDown);
	printf("dPadLeft = %u \n" , xbox->dPadLeft);
	printf("dPadRight = %u \n" , xbox->dPadRight);
	printf("StartBut = %u \n" , xbox->StartBut);
	printf("BackBut = %u \n" , xbox->BackBut);
	printf("LeftStickPress = %u \n" , xbox->LeftStickPress);
	printf("RightStickPress = %u \n" , xbox->RightStickPress);
	printf("ButtonLB = %u \n" , xbox->ButtonLB);
	printf("ButtonRB = %u \n" , xbox->ButtonRB);
	printf("LogoButton = %u \n" , xbox->LogoButton);
	printf("ButtonA = %u \n" , xbox->ButtonA);
	printf("ButtonB = %u \n" , xbox->ButtonB);
	printf("ButtonX = %u \n" , xbox->ButtonX);
	printf("ButtonY = %u \n" , xbox->ButtonY);
	printf("LeftTrigger = %u \n" , xbox->LeftTrigger);
	printf("RightTrigger = %u \n" , xbox->RightTrigger);
	printf("LeftStickXaxis = %d \n" , xbox->LeftStickXaxis);
	printf("LeftStickYaxis = %d \n" , xbox->LeftStickYaxis);
	printf("RightStickXaxis = %d \n" , xbox->RightStickXaxis);
	printf("RightStickYaxis = %d \n" , xbox->RightStickYaxis);
	printf("\n\n");
}

void xboxinfo(unsigned char data[20], XboxController* xbox)
{
	xbox->type = data[0];
	xbox->size = data[1];
	xbox->dPadUp = (data[2] & LastBit);
	xbox->dPadDown = ((data[2] & SevendBit) >> 1);
	xbox->dPadLeft = ((data[2] & SixedBit)  >> 2);
	xbox->dPadRight = ((data[2] & FifthBit) >> 3);
	xbox->StartBut = ((data[2] & FourthBit) >> 4);
	xbox->BackBut = ((data[2] & ThirthBit) >> 5);
	xbox->LeftStickPress = ((data[2] & SecondBit) >> 6);
	xbox->RightStickPress = ((data[2] & FistBit) >> 7);
	xbox->ButtonLB = (data[3] & LastBit);
	xbox->ButtonRB = ((data[3] & SevendBit) >> 1);
	xbox->LogoButton = ((data[3] & SixedBit) >> 2);
	xbox->ButtonA = ((data[3] & FourthBit) >> 4);
	xbox->ButtonB = ((data[3] & ThirthBit) >> 5);
	xbox->ButtonX = ((data[3] & SecondBit) >> 6);
	xbox->ButtonY = ((data[3] & FistBit) >> 7);
	xbox->LeftTrigger = data[4];
	xbox->RightTrigger = data[5];
	xbox->LeftStickXaxis = (data[7] << 8) | data[6];
	xbox->LeftStickYaxis = (data[9] << 8) | data[8];
	xbox->RightStickXaxis = (data[11] << 8) | data[10];
	xbox->RightStickYaxis = (data[13] << 8) | data[12];
}




