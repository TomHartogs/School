#pragma once

#include <stdint.h>

#include "stack.h"

enum Parity
{
	Even,
	Odd
};

class mySerial
{	
	private:
	FRIEND_TEST(Check_parity, check_get_parity_bit);
	FRIEND_TEST(CheckAddByteToSendQueue, AddByteOne);
	FRIEND_TEST(CheckAddByteToSendQueue, AddByteH);
	FRIEND_TEST(SendFunction, send_letter_h);

	int _baudRate;
	Stack<bool*> _sendQueue;
	void AddByteToSendQueue(uint8_t byte);
	bool GetParityBit(Parity mode, uint8_t byte);
	
	static const bool _startBit = 1;
	static const bool _stopBit = 0;
	static const Parity _parity = Even;

	public:	
		mySerial(int baudRate);
		void Send(const char* message, int len);
};
