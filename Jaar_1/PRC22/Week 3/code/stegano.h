/*
 * stegano.h
 *
 *  Created on: Jun 8, 2015
 *      Author: F. Hurkmans
 */

#ifndef STEGANO_H_
#define STEGANO_H_

#include <stdint.h>

void multiplex (const char* File0, const char* File1);
void multiplexText (const char* File0, const char* File1);
void demultiplex (const char* File0, const char* File1, const char* File2);
void demultiplexText (const char* File0, const char* File1, const char* File2);
uint8_t combineByte(uint8_t pixel0, uint8_t pixel1, int NrBits);
void splitByte(uint8_t pixel, uint8_t* newPixel0, uint8_t* newPixel1, int NrOfBits);

#endif /* STEGANO_H_ */
