#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <mqueue.h>
#include <list>
#include <iostream>

#include "MessageQueue.h"
#include "Controller.h"

#define VENDOR_ID 0x045e
#define PRODUCT_ID 0x028e

static int  shm_fd = -1;

static char* my_shm_create (const char* shm_name, int size)
{
    int     rtnval;
    char *  shm_addr;
    
    shm_unlink(shm_name);
    
    shm_fd = shm_open (shm_name, O_CREAT | O_EXCL | O_RDWR, 0600);
    
    if (shm_fd == -1)
    {
        perror ("ERROR: shm_open() failed");
    }
    
    rtnval = ftruncate (shm_fd, size);
    
    if (rtnval != 0)
    {
        perror ("ERROR: ftruncate() failed");
    }
    
    shm_addr = (char *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    if (shm_addr == MAP_FAILED)
    {
        perror ("ERROR: mmap() failed");
    }

    return (shm_addr);
}

int is_Controller(libusb_device *dev)
{
	struct libusb_device_descriptor desc;

	libusb_get_device_descriptor( dev, &desc ); 

	if( desc.idVendor == VENDOR_ID && desc.idProduct == PRODUCT_ID)
	{
		printf("match found\n");
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{  
	libusb_init(NULL);
	
	libusb_device_handle *h = NULL;
	libusb_device **list;
	
	int8_t cnt = libusb_get_device_list(NULL, &list);
	
	int8_t i = 0;
	int8_t err = 0;

	std::list<Controller> controllers;
	
	if(cnt < 0)
	{
		printf( "no usb devices found\n" );
		exit(EXIT_FAILURE);
	}
	else
	{		
		for(i = 0; i < cnt; i++) 
		{
			libusb_device* device = list[i];
			if(is_Controller(device))
			{
				Controller tempController(device, (1 | LIBUSB_ENDPOINT_IN), (1 | LIBUSB_ENDPOINT_OUT)); //endpoint = 0x01 original controller and 0x02 with fake controller
				controllers.push_back(tempController);
			}
		}
	}
	
	libusb_free_device_list(list, 1);
	
	int attachedControllers = controllers.size();
	
	const char* 		shm_name = "sharedmem\0";
    int       		 	size = -1;
	char *      		shm_addr = (char *) MAP_FAILED;
	size = (attachedControllers * sizeof(buttonStates)) + 1;

    shm_addr = my_shm_create (shm_name, size);
    shm_addr[0] = attachedControllers;
    shm_addr++;
    
    int buttonStateSize = sizeof(buttonStates);
    
    struct mq_attr attr;

	/* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; 					//******perhaps change??******
    attr.mq_msgsize = 20;
    attr.mq_curmsgs = 0;
    mode_t mode  = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    
    mq_unlink("/xpadCom");
    mqd_t mq = mq_open("/xpadCom", O_CREAT | O_RDONLY | O_NONBLOCK, mode, &attr);
    std::cout << errno << std::endl;
    
	char messageBuffer[20];
	mq_receive(mq, messageBuffer, 20, 0);
	std::cout << messageBuffer << std::endl;
	
	while(true)
	{
		std::list<Controller>::iterator iterator;
		int number = 0;
		for (iterator = controllers.begin(); iterator != controllers.end(); ++iterator) 
		{
			(*iterator).UpdateValues();
			buttonStates states = (*iterator).GetButtonStates();
			if(states.digitalButtonState[YBtn] == 1 || states.digitalButtonState[YBtn] == 0)
				memcpy(shm_addr+(number*buttonStateSize), &states, buttonStateSize);
			number++;
		}
		
		char messageBuffer[20];
		if(mq_receive(mq, messageBuffer, 20, 0) > 0)
		{
			std::cout<<messageBuffer<<std::endl;
			std::string command(messageBuffer);
			if(command.compare(0, 6, "Buzzer") == 0)
			{
				int controllerNumber = atoi(command.substr(6, 1).c_str());
				if(controllers.size() > controllerNumber)
				{
					std::list<Controller>::iterator it = controllers.begin();
					std::advance(it, controllerNumber);
					if(command.compare(7, 2, "On") == 0)
						(*it).SetRumble(100, 100);
					else if(command.compare(7, 3, "Off") == 0)					
						(*it).SetRumble(0, 0);
				}
			}
			if(command.compare(0, 4, "Leds") == 0)
			{
				int controllerNumber = atoi(command.substr(4, 1).c_str());
				if(controllers.size() > controllerNumber)
				{
					std::list<Controller>::iterator it = controllers.begin();
					std::advance(it, controllerNumber);
					if(command.compare(5, 8, "Rotating") == 0)
						(*it).SetLeds(Rotating);
					else if(command.compare(5, 8, "Blinking") == 0)					
						(*it).SetLeds(Blinking);
				}
			}
			memset(messageBuffer, 0, sizeof(messageBuffer));
		}
	}
	
	daemon(0,0);
	return (0);
}
