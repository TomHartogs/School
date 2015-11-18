/*
 * bit.c
 *
 *  Created on: Jun 8, 2015
 *      Author: F. Hurkmans
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "resource_detector.h"
#include "bit.h"

unsigned int makeBitmask(unsigned int width, unsigned int shift)
/* pre : -
 * post: a bitmask with a given width and a given shift is generated (so w=5 and s=1 gives 00111110)
 */
{
    // TODO: implement
	int bitMask = 0;
	if(width < 32)
	{
		bitMask = (1 << width) - 1;
		bitMask <<= shift;
	}
	else
	{
		bitMask = 0xffffffff;
	}
    return bitMask;
}

uint8_t
getSubstring (uint8_t Src, uint8_t SrcPos, uint8_t NrOfBits, uint8_t DestPos)
{
	uint8_t bitMask = makeBitmask(NrOfBits, SrcPos);
	Src &= bitMask;
	if(SrcPos < DestPos)
	{
		return Src <<= (DestPos - SrcPos);
	}
	else
	{
		return Src >>= (SrcPos - DestPos);
	}
}
