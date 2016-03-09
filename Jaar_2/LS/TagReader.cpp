#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <list>
#include <phidget21.h>
#include <iostream>
#include <fstream>
#include <string>

int happyScanner = 102952;
int neutralScanner = 103012;
int sadScanner = 64245;

struct Tag
{
	mutable int scannedBySerialNumber;
	std::string tagValue;
};

std::list<Tag> scannedTags;

bool teacherScanned = false;
std::string teacherTag = "";

bool quit = false;

bool byScanner (const Tag& first, const Tag& second)
{
	return first.scannedBySerialNumber < second.scannedBySerialNumber;
}

bool byValue (const Tag& first, const Tag& second)
{
  return first.tagValue < second.tagValue;
}

int CCONV DetachHandler(CPhidgetHandle RFID, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (RFID, &name);
	CPhidget_getSerialNumber(RFID, &serialNo);
	printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int CCONV ErrorHandler(CPhidgetHandle RFID, void *userptr, int ErrorCode, const char *unknown)
{
	printf("Error handled. %d - %s\n", ErrorCode, unknown);
	return 0;
}

int CCONV TagHandler(CPhidgetRFIDHandle RFID, void *usrptr, char *TagVal, CPhidgetRFID_Protocol proto)
{
	//turn on the LED
	CPhidgetRFID_setLEDOn(RFID, 1);
	CPhidgetRFID_setOutputState ( RFID, 0, PTRUE);
	CPhidgetRFID_setOutputState ( RFID, 1, PFALSE);	
	
	printf("Tag Read: %s\n", TagVal);
	
	if(!teacherScanned)
	{
		teacherTag = std::string(TagVal);
		teacherScanned = true;
		printf("Teacher tag scanned\n");
	}
	else if (std::string(TagVal) == teacherTag)
		quit = true;
	else	
	{
		//Append written tag + readerId to scannedTags list
		Tag temp;
		temp.tagValue = std::string(TagVal);
		int serialNo;
		CPhidget_getSerialNumber((CPhidgetHandle)RFID, &serialNo);
		temp.scannedBySerialNumber = serialNo;
		bool existed = false;
		for (std::list<Tag>::const_iterator iterator = scannedTags.begin(), end = scannedTags.end(); iterator != end; ++iterator) 
		{
			if(temp.tagValue == (*iterator).tagValue)
			{
				(*iterator).scannedBySerialNumber = temp.scannedBySerialNumber;
				existed = true;
			}
		}
		if(!existed)
			scannedTags.push_back(temp);
	}
	return 0;
}

int CCONV TagLostHandler(CPhidgetRFIDHandle RFID, void *usrptr, char *TagVal, CPhidgetRFID_Protocol proto)
{
	//turn off the LED
	CPhidgetRFID_setLEDOn(RFID, 0);
	CPhidgetRFID_setOutputState ( RFID, 0, PFALSE);
	CPhidgetRFID_setOutputState ( RFID, 1, PTRUE);

	printf("Tag Lost: %s\n", TagVal);
	return 0;
}

int display_properties(CPhidgetRFIDHandle phid)
{
	int serialNo, version, numOutputs, antennaOn, LEDOn;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetRFID_getOutputCount (phid, &numOutputs);
	CPhidgetRFID_getAntennaOn (phid, &antennaOn);
	CPhidgetRFID_getLEDOn (phid, &LEDOn);


	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
	printf("# Outputs: %d\n\n", numOutputs);
	printf("Antenna Status: %d\nOnboard LED Status: %d\n", antennaOn, LEDOn);

	return 0;
}

int create_list_with_available_devices(int *foundSerialNumbers)
{
	CPhidgetManagerHandle manager = 0;
	CPhidgetManager_create(&manager);
	CPhidgetManager_open((CPhidgetManagerHandle) manager);

	// Allow the Phidgets time to attach
	sleep(1);

	// Retrieve the list of attached Phidgets from the manager
	CPhidgetHandle* phidgetList;
	int count;

	CPhidgetManager_getAttachedDevices((CPhidgetManagerHandle) manager, &phidgetList, &count);

	int serialNumber;
	const char *name;

	//Iterate over the returned Phidget data
	int i;
	for (i = 0; i < count; i++) {
	  CPhidget_getDeviceName(phidgetList[i], &name);
	  CPhidget_getSerialNumber(phidgetList[i], &serialNumber);
	  printf("%s, %d\n", name, serialNumber);
	  // Store name and serial number into a persistent variable
	  foundSerialNumbers[i] = serialNumber;
	}
	// Use the Phidget API to free the memory in the phidgetList Array    
	CPhidgetManager_freeAttachedDevicesArray(phidgetList);

	// Close the manager    
	CPhidgetManager_close((CPhidgetManagerHandle) manager);
	CPhidgetManager_delete((CPhidgetManagerHandle) manager);
	return count;
}

int main()
{
	int foundSerialNumbers[10];
	int nrOfSerialNumbersFound = create_list_with_available_devices(foundSerialNumbers);
		
	CPhidgetRFIDHandle rfidReaders[nrOfSerialNumbersFound];
	if(nrOfSerialNumbersFound < 1)
	{
		printf("No readers found\n");
		exit(EXIT_SUCCESS);
	}
	
	printf("Press enter to start\n");
	getchar();
	
	//Open each found devices and attach handlers
	for(int i = 0; i < nrOfSerialNumbersFound; i++)
	{
		CPhidgetRFID_create(&rfidReaders[i]);
		CPhidgetRFID_set_OnTag2_Handler(rfidReaders[i], TagHandler, NULL);
		CPhidgetRFID_set_OnTagLost2_Handler(rfidReaders[i], TagLostHandler, NULL);
		CPhidget_open((CPhidgetHandle)rfidReaders[i], foundSerialNumbers[i]);
		if(CPhidget_waitForAttachment((CPhidgetHandle)rfidReaders[i], 1000))
			return -1;	
		display_properties(rfidReaders[i]);
		CPhidgetRFID_setAntennaOn(rfidReaders[i], 1);
		CPhidgetRFID_setOutputState ( rfidReaders[i], 0, PFALSE);
		CPhidgetRFID_setOutputState ( rfidReaders[i], 1, PTRUE);
	}
	
	
	printf("Scan first tag to use as teacher tag\n");
	
	while(!teacherScanned)
	{
		
	}
	
	//Start scanning until teacher scans card again
	printf("Scan teacher tag again to exit and save scanned tags\n");
	
	int a = 1;
	int b = 0;
	int c = 0;
	int temp = 0;
	while(!quit)
	{
		CPhidgetRFID_setAntennaOn(rfidReaders[0], a); 
		CPhidgetRFID_setAntennaOn(rfidReaders[1], b);
		CPhidgetRFID_setAntennaOn(rfidReaders[2], c); 
		temp = a;
		a = c;
		c = b;
		b = temp;
		
		nanosleep((const struct timespec[]){{0, 250000000L}}, NULL);
	}
	
	scannedTags.sort(byValue);
	scannedTags.sort(byScanner);
	
	std::ofstream myfile;
	myfile.open ("scannedTags.txt");
	
	int scannerNr = 0;
	
	for (std::list<Tag>::const_iterator iterator = scannedTags.begin(), end = scannedTags.end(); iterator != end; ++iterator) 
	{
		int currScanNr = (*iterator).scannedBySerialNumber;
		if(scannerNr != currScanNr)
		{
			if(currScanNr == happyScanner)
				myfile << " Happy scanned : ";
			else if(currScanNr == neutralScanner)
				myfile << " Neutral scanned : ";
			else if(currScanNr == sadScanner)
				myfile << "Sad scanned : ";
			scannerNr = currScanNr;
		}
		myfile << (*iterator).tagValue << ", ";
	}
	
	myfile.close();	
	
	CPhidgetRFID_setOutputState ( rfidReaders[0], 0, PFALSE);
	CPhidgetRFID_setOutputState ( rfidReaders[0], 1, PFALSE);
	CPhidgetRFID_setOutputState ( rfidReaders[1], 0, PFALSE);
	CPhidgetRFID_setOutputState ( rfidReaders[1], 1, PFALSE);
	CPhidgetRFID_setOutputState ( rfidReaders[2], 0, PFALSE);
	CPhidgetRFID_setOutputState ( rfidReaders[2], 1, PFALSE);
	
	return 0;
}
