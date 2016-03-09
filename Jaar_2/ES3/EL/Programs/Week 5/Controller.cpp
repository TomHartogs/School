#include "Controller.h"
#include <iostream>

#define messageSize 20
#define timeOut 200

Controller::Controller(libusb_device* device, uint8_t inputEndpoint, uint8_t outputEndpoint)
	:inputEndpoint(inputEndpoint), outputEndpoint(outputEndpoint)
{
	libusb_open(device, &handle);
};

buttonStates Controller::GetButtonStates() { return buttons; };

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
	int transferred = 0;
	unsigned char data[3] = { 1, 3, mode };
	int e = libusb_interrupt_transfer(handle, outputEndpoint, data, sizeof data, &transferred, timeOut);
	if(e == 0)
		return true;
	else
	{
		switch(e)
		{
			case LIBUSB_ERROR_TIMEOUT:
				printf("timeout\n");
				SetLeds(mode);
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
		switch(e)
		{
			case LIBUSB_ERROR_TIMEOUT:
				printf("timeout\n");
				SetRumble(bigMotorSpeed, smallMotorSpeed);
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
	printf("\033[1;0H");
	std::cout << "  " << buttons.digitalButtonState[dPadUp] << "       " << buttons.digitalButtonState[YBtn] <<std::endl;
	std::cout << buttons.digitalButtonState[dPadLeft] << "   " << buttons.digitalButtonState[dPadRight] << "   " << buttons.digitalButtonState[XBtn] << "   " << buttons.digitalButtonState[BBtn] << std::endl;
	std::cout << "  " << buttons.digitalButtonState[dPadDown] << "       " << buttons.digitalButtonState[ABtn] << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	std::cout << buttons.analogButtonState[leftTrigger] << std::endl;
};

void Controller::UpdateValues()
{	
	unsigned char dataBuffer[messageSize];
	int transferred;
	int e = libusb_interrupt_transfer(handle, inputEndpoint, dataBuffer, sizeof dataBuffer, &transferred, timeOut);
	if(e != 0 || transferred != messageSize)
	{
		switch(e)
		{
			case LIBUSB_ERROR_TIMEOUT:
				printf("");
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
			buttons.digitalButtonState[currNumber] = (dataBuffer[byteNumber]>>currNumber)&maskFirstBit;
		
		byteNumber++;
		
		for(int i = 0; i < 8; i++, currNumber++)
		{
			if(i != 3)
				buttons.digitalButtonState[currNumber] = (dataBuffer[byteNumber]>>i)&maskFirstBit;
			else
				currNumber--;
		}
		
		byteNumber++;
		
		currNumber = 0;
		for(;currNumber < 2; currNumber++, byteNumber++)
			buttons.analogButtonState[currNumber] = dataBuffer[byteNumber];

		for(;currNumber < 6; currNumber++, byteNumber += 2)
			buttons.analogButtonState[currNumber] = ((uint16_t)dataBuffer[byteNumber] << 8) | dataBuffer[byteNumber+1];
	}
};


