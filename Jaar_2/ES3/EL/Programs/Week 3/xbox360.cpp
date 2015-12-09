#include <stdio.h>
#include <cstdlib> 
#include <libusb-1.0/libusb.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

#define messageSize 20
#define timeOut 0

enum ledModes
{
	AllBlinking = 0x01,
	OneFlashThenOn = 0x02,
	TwoFlashesThenOn = 0x03,
	ThreeFlashesThenOn = 0x04,
	FourFlashesThenOn = 0x05,
	OneOn = 0x06,
	TwoOn = 0x07,
	ThreeOn = 0x08,
	FourOn = 0x09,
	Rotating = 0x0a,
	Blinking = 0x0b,
	SlowBlinking = 0x0c,
	Alternating = 0x0d
};

struct message {
  uint8_t 	messageType;
  uint8_t  	packetSize;
  int 		dpadUp;
	int		dpadDown;
	int		dpadLeft;
	int 	dpadRight;
	int		startBtn;
	int		backBtn;
	int		leftStickPress;
	int 	rightStickPress;
	int 	lbBtn;
	int 	rbBtn;
	int 	logoBtn;
	int 	aBtn;
	int 	bBtn;
	int 	xBtn;
	int 	yBtn;
  uint8_t 	leftTrigger;
  uint8_t  rightTrigger;
} _Message;

libusb_device_handle *handle = NULL;

uint16_t MicrosoftVID = 0x045e;
uint16_t XboxPID = 0x028e;

int interfaceNumber = 1;
uint8_t inputEndpoint = (1 | LIBUSB_ENDPOINT_IN);

//For white controller
uint8_t outputEndpoint = (2 | LIBUSB_ENDPOINT_OUT);

bool ClaimInterface(libusb_device_handle* deviceHandle, int interfaceNumber);
bool OpenDevice(uint16_t VendorId, uint16_t ProductId);

bool SetLeds(libusb_device_handle* deviceHandle, uint8_t endPointAdress, ledModes mode);
bool SetRumble(libusb_device_handle* deviceHandle, uint8_t endPointAdress, int bigMotorSpeed, int smallMotorSpeed);
void ReadController(libusb_device_handle* deviceHandle, uint8_t endPointAdress, struct message *_Message);

int main()
{
	libusb_init(NULL);
	
	if(!OpenDevice(MicrosoftVID, XboxPID))
		exit(EXIT_FAILURE);
	else
		std::cout << "Device opened" << std:: endl;
		
	if(!ClaimInterface(handle, interfaceNumber))
		exit(EXIT_FAILURE);
	else
		std::cout << "Interface claimed" << std:: endl;
	
	if(!SetLeds(handle, outputEndpoint, TwoOn))
		exit(EXIT_FAILURE);
	else
		std::cout << "Leds set" << std:: endl;
		
	if(!SetRumble(handle, outputEndpoint, 100, 100))
		exit(EXIT_FAILURE);
	else
		std::cout << "Rumble set" << std:: endl;
		
	usleep(2000000);
	
	if(!SetRumble(handle, inputEndpoint, 0, 0))
		exit(EXIT_FAILURE);
	else
		std::cout << "Rumble turned off" << std:: endl;
		
	while(1)
	{
		ReadController(handle, outputEndpoint, &_Message);
	}
	
	libusb_exit(NULL);
	return 0;
}

bool OpenDevice(uint16_t VendorId, uint16_t ProductId)
{
	handle = libusb_open_device_with_vid_pid(NULL, VendorId, ProductId);
	if(handle == NULL)
	{
		printf("Error opening device\n");
		return false;
	}	
	return true;
}

bool ClaimInterface(libusb_device_handle* deviceHandle, int interfaceNumber)
{
	int driverActive = libusb_kernel_driver_active(deviceHandle, interfaceNumber);
	if(driverActive != 0)
		libusb_detach_kernel_driver(deviceHandle, interfaceNumber);
	
	int e = libusb_claim_interface(deviceHandle, interfaceNumber);
	if(e != 0)
	{
		printf("Error claiming interface");
		return false;
	}	
	return true;
}

bool SetLeds(libusb_device_handle* handle, uint8_t endPointAdress, ledModes mode)
{
	int transferred;
	unsigned char data[3] = { 1, 3, mode };
	int e = libusb_interrupt_transfer(handle, endPointAdress, data, sizeof data, &transferred, timeOut);
	if(e == 0)
		return true;
	else
	{
		printf("%i\n", transferred);
		switch(e)
		{
			case LIBUSB_ERROR_TIMEOUT:
				printf("timeout\n");
				break;
			case LIBUSB_ERROR_PIPE:
				printf("pipe");
				break;
			case LIBUSB_ERROR_OVERFLOW:
				printf("overflow");
				break;
			case LIBUSB_ERROR_NO_DEVICE:
				printf("No device");
				break;
			default:
				printf("Other");
				break;
		}
		return false;
	}
		
}

bool SetRumble(libusb_device_handle* deviceHandle, uint8_t endPointAdress, int bigMotorSpeed, int smallMotorSpeed)
{
	int transferred;
	unsigned char data[] = { 0x00, 0x08, 0x00, bigMotorSpeed, smallMotorSpeed, 0x00, 0x00, 0x00 };
	int e = libusb_interrupt_transfer(handle, endPointAdress, data, sizeof data, &transferred, timeOut);
	if(e == 0)
		return true;
	else
	{
		printf("%i\n", transferred);
		switch(e)
		{
			case LIBUSB_ERROR_TIMEOUT:
				printf("timeout\n");
				break;
			case LIBUSB_ERROR_PIPE:
				printf("pipe");
				break;
			case LIBUSB_ERROR_OVERFLOW:
				printf("overflow");
				break;
			case LIBUSB_ERROR_NO_DEVICE:
				printf("No device");
				break;
			default:
				printf("Other");
				break;
		}
		return false;
	}
}

void ReadController(libusb_device_handle* deviceHandle, uint8_t endPointAdress, struct message *_Message)
{
	unsigned char dataBuffer[messageSize];
	int transferred;
	int e = libusb_interrupt_transfer(handle, endPointAdress, dataBuffer, sizeof dataBuffer, &transferred, timeOut);
	if(e == 0)
	{
		
	}
	else
	{
		printf("%i\n", transferred);
		switch(e)
		{
			case LIBUSB_ERROR_TIMEOUT:
				printf("timeout\n");
				break;
			case LIBUSB_ERROR_PIPE:
				printf("pipe");
				break;
			case LIBUSB_ERROR_OVERFLOW:
				printf("overflow");
				break;
			case LIBUSB_ERROR_NO_DEVICE:
				printf("No device");
				break;
			default:
				printf("Other");
				break;
		}
	}
}
