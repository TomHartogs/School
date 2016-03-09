#include <stdio.h>
#include <iostream>

#include "mySerial.h"

mySerial::mySerial(int baudRate)
	: _baudRate(baudRate)
{
}

void mySerial::Send(const char* message, int len)
{
	for(int i = 0; i < len; i++)
	{
		AddByteToSendQueue(message[i]);
	}
}

bool mySerial::GetParityBit(Parity mode, uint8_t byte)
{
	int totalBytesHigh = 0;
	for(int i = 0; i < 8; i++)
	{
		totalBytesHigh += (byte & (1 << i)) >> i;
	}
	Parity current = (Parity)(totalBytesHigh % 2);
	
	if(current == mode)
		return false;
	else
		return true;
}

void mySerial::AddByteToSendQueue(uint8_t byte)
{
	bool packagedByteBuffer[11] = {0};
	
	packagedByteBuffer[0] = _startBit;
	for(int i = 0; i < 8; i++)
	{
		packagedByteBuffer[i+1] = (byte & (1 << i)) >> i;
	}
	packagedByteBuffer[9] = GetParityBit(_parity, byte);
	packagedByteBuffer[10] = _stopBit;
	
	_sendQueue.push(packagedByteBuffer);
}
