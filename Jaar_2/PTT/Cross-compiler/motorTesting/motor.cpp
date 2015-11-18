/*
 * Robot Navigation Program
 * www.robotnav.com
 *
 * (C) Copyright 2013 - 2014 Navigation Solutions, LLC
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <fcntl.h>
#include "lms2012.h"

// Motor power 0..100
const int MOTOR_POWER = 10;
// The motor operations use a single bit (or a combination of them) 
// to determine which motor(s) will be used
// A = 0x01, B = 0x02, C = 0x04, D = 0x08
// AC = 0x05
const char MOTOR_PORT = 0x01; 

int main()
{
	//DEFINE VARIABLES
	char motor_command[3];
	int motor_file;

	//INITIALIZE DEVICE
	//Open the device file asscoiated to the motor controlers
	if((motor_file = open(PWM_DEVICE_NAME, O_WRONLY)) == -1)
		return -1; //Failed to open device
	
	//ACTUATE MOTORS
	// All motor operations use the first command byte to indicate the type of operation
	// and the second one to indicate the motor(s) port(s)
	motor_command[0] = opOUTPUT_POWER;
	motor_command[1] = MOTOR_PORT; 
	motor_command[2] = MOTOR_POWER;
	write(motor_file,motor_command,3);
	// Start the motor
	motor_command[0] = opOUTPUT_START;
	write(motor_file,motor_command,2);
	// Run the motor for a couple of seconds
	sleep(2);
	// Stops the motor
	motor_command[0] = opOUTPUT_STOP;
	write(motor_file,motor_command,2);

	//CLOSE DEVICE
	close(motor_file);
	return 0;
}
