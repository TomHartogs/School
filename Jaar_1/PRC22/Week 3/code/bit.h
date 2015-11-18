/*
 * bit.h
 *
 *  Created on: Jun 8, 2015
 *      Author: F. Hurkmans
 */

#ifndef BIT_H_
#define BIT_H_

#include <stdint.h>

unsigned int makeBitmask(unsigned int width, unsigned int shift);
/* pre : -
 * post: a bitmask with a given width and a given shift is generated (so w=5 and s=1 gives 00111110)
 */
 
uint8_t getSubstring (uint8_t Src, uint8_t SrcPos, uint8_t NrOfBits, uint8_t DestPos);
/* description: get a substring of bits from a uint8_t (i.e. a byte)
 *
 * example: getSubstring (Src, 3, 4, 1) with Src=ABCDEFGH (bit H is LSB)
 *          = 000BCDE0
 *
 * parameters:
 *      Src:       byte to get the substring from
 *      SrcPos:    position of the first bit of the substring (LSB=0)
 *      NrOfBits:  length of the substring
 *      DestPos:   position of the first bits of the destination substring
 *
 * return:
 *      substring, starting at DestPos
 */

#endif /* BIT_H_ */
