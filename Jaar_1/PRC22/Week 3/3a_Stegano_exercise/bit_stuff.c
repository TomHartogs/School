#include <limits.h>
#include "bit_stuff.h"

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

unsigned int countOnes(unsigned int value)
/* pre : -
 * post: the number of bits with value 1 is counted and returned
 */
{
    value -= ((value >> 1) & 0x55555555);
    value = (value & 0x33333333) + ((value >> 2) & 0x33333333);
    return (((value + (value >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}
