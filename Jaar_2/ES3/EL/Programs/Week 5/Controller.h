#pragma once

#include <libusb-1.0/libusb.h>
#include <stdint.h>
#include <stdio.h>

#include "buttonInfo.h"

class Controller
{
	private:
		uint8_t inputEndpoint;
		uint8_t outputEndpoint;
		
		libusb_device_handle* handle;
		
		buttonStates buttons;
		
	public:	
		Controller(libusb_device* device, uint8_t inputEndpoint, uint8_t outputEndpoint);	
		buttonStates GetButtonStates();
		bool ClaimInterface(int interfaceNumber);
		bool SetLeds(ledModes mode);
		bool SetRumble(int bigMotorSpeed, int smallMotorSpeed);
		void PrintStatus();
		void UpdateValues();
};
