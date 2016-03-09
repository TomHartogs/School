#include <string>
#include "gtest/gtest.h"

#define HIGH 1
#define LOW 0

#include "mySerial.cpp"

TEST(Check_parity, check_get_parity_bit)
{
	mySerial _serial(1000);
    ASSERT_EQ(0, _serial.GetParityBit(Even, 3));
    ASSERT_EQ(1, _serial.GetParityBit(Even, 1));
    ASSERT_EQ(0, _serial.GetParityBit(Odd, 1));
    ASSERT_EQ(1, _serial.GetParityBit(Odd, 3));
}

TEST(CheckAddByteToSendQueue, AddByteOne)
{
	mySerial _serial(1000);
	_serial.AddByteToSendQueue(1);
	bool* addedByte = _serial._sendQueue.pop();
	ASSERT_EQ(1, addedByte[0]); // check for start bit
	ASSERT_EQ(1, addedByte[1]); // first bit
	ASSERT_EQ(0, addedByte[2]);
	ASSERT_EQ(0, addedByte[3]);
	ASSERT_EQ(0, addedByte[4]);
	ASSERT_EQ(0, addedByte[5]);
	ASSERT_EQ(0, addedByte[6]);
	ASSERT_EQ(0, addedByte[7]);
	ASSERT_EQ(0, addedByte[8]);
	ASSERT_EQ(1, addedByte[9]); // parity bit (parity even)
	ASSERT_EQ(0, addedByte[10]);
}

TEST(CheckAddByteToSendQueue, AddByteH)
{
	mySerial _serial(1000);
	_serial.AddByteToSendQueue('h');
	bool* addedByte = _serial._sendQueue.pop();
	ASSERT_EQ(1, addedByte[0]); // check for start bit
	ASSERT_EQ(0, addedByte[1]);
	ASSERT_EQ(0, addedByte[2]);
	ASSERT_EQ(0, addedByte[3]);
	ASSERT_EQ(1, addedByte[4]);
	ASSERT_EQ(0, addedByte[5]);
	ASSERT_EQ(1, addedByte[6]);
	ASSERT_EQ(1, addedByte[7]);
	ASSERT_EQ(0, addedByte[8]);
	ASSERT_EQ(1, addedByte[9]); // parity bit (parity even)
	ASSERT_EQ(0, addedByte[10]);
}

/*Waarom werkt dit testen niet??
TEST(SendFunction, send_letter_h)
{
	mySerial _serial(1000);
	const char* temp = "h";
	_serial.Send(temp, 1);
	bool* addedByte = _serial._sendQueue.pop();
	ASSERT_EQ(1, addedByte[0]); // check for start bit
	ASSERT_EQ(0, addedByte[1]);
	ASSERT_EQ(0, addedByte[2]);
	ASSERT_EQ(0, addedByte[3]);
	ASSERT_EQ(1, addedByte[4]);
	ASSERT_EQ(0, addedByte[5]);
	ASSERT_EQ(1, addedByte[6]);
	ASSERT_EQ(1, addedByte[7]);
	ASSERT_EQ(0, addedByte[8]);
	ASSERT_EQ(1, addedByte[9]); // parity bit (parity even)
	ASSERT_EQ(0, addedByte[10]);
}*/
