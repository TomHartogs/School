#include "Controller.h"
#include <iostream>

#define messageSize 20
#define timeOut 1000

Controller::Controller(uint16_t vendorId, uint16_t productId, uint8_t inputEndpoint, uint8_t outputEndpoint)
	:vendorId(vendorId), productId(productId), 
	inputEndpoint(inputEndpoint), outputEndpoint(outputEndpoint)
{
	libusb_init(NULL);
};

bool Controller::Open()
{
	libusb_device_handle* tempHandle = libusb_open_device_with_vid_pid(NULL, vendorId, productId);
	if(tempHandle != NULL)
	{
		handle = tempHandle;
		return true;
	}
	return false;
};

bool Controller::ClaimInterface(int interfaceNumber)
{
	int driverActive = libusb_kernel_driver_active(handle, interfaceNumber);
	if(driverActive != 0)
		libusb_detach_kernel_driver(handle, interfaceNumber);
	
	int e = libusb_claim_interface(handle, interfaceNumber);
	if(e != 0)
	{
		printf("Error claiming interface");
		return false;
	}
	return true;
};

bool Controller::SetLeds(ledModes mode)
{
	int transferred;
	unsigned char data[3] = { 1, 3, mode };
	int e = libusb_interrupt_transfer(handle, outputEndpoint, data, sizeof data, &transferred, timeOut);
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
};

bool Controller::SetRumble(int bigMotorSpeed, int smallMotorSpeed)
{
	int transferred;
	uint8_t messageType = 0x00;
	uint8_t messageLength = 0x08;
	uint8_t messagePadding = 0x00;
	unsigned char data[] = { messageType, messageLength, messagePadding, bigMotorSpeed, smallMotorSpeed, messagePadding, messagePadding, messagePadding };
	int e = libusb_interrupt_transfer(handle, outputEndpoint, data, sizeof data, &transferred, timeOut);
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
};

void Controller::PrintStatus()
{	
	UpdateValues();
	printf("\033[1;0H");
	std::cout << "  " << digitalButtons[dPadUp] << "       " << digitalButtons[YBtn] <<std::endl;
	std::cout << digitalButtons[dPadLeft] << "   " << digitalButtons[dPadRight] << "   " << digitalButtons[XBtn] << "   " << digitalButtons[BBtn] << std::endl;
	std::cout << "  " << digitalButtons[dPadDown] << "       " << digitalButtons[ABtn] << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	std::cout << analogButtons[leftTrigger] << std::endl;
};

void Controller::UpdateValues()
{	
	unsigned char dataBuffer[messageSize];
	int transferred;
	int e = libusb_interrupt_transfer(handle, inputEndpoint, dataBuffer, sizeof dataBuffer, &transferred, timeOut);
	if(e != 0 || transferred != messageSize)
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
	else
	{
		int byteNumber = 2;
		int currNumber = 0;
		
		uint8_t maskFirstBit = 00000001;
		for(; currNumber < 8; currNumber++)
			digitalButtons[currNumber] = (dataBuffer[byteNumber]>>currNumber)&maskFirstBit;
		
		byteNumber++;
		
		for(int i = 0; i < 8; i++, currNumber++)
		{
			if(i != 3)
				digitalButtons[currNumber] = (dataBuffer[byteNumber]>>i)&maskFirstBit;
			else
				currNumber--;
		}
		
		byteNumber++;
		
		currNumber = 0;
		for(;currNumber < 2; currNumber++, byteNumber++)
			analogButtons[currNumber] = dataBuffer[byteNumber];

		for(;currNumber < 6; currNumber++, byteNumber += 2)
			analogButtons[currNumber] = ((uint16_t)dataBuffer[byteNumber] << 8) | dataBuffer[byteNumber+1];
	}

};


