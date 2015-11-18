/* auteur : F.J. Hurkmans
 * datum  : November 4th 2013
 * code   : Ansi C
 * versie : 1
 */

#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "bit.h"
#include "unity.h"
#include "resource_detector.h"

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp(void)
{
    // This is run before EACH test
}

void tearDown(void)
{
    // This is run after EACH test
}

static void firstTest(void)
{
    int result = 0x2c;
    int src = 0xda;
    int subString = getSubstring(src, 3, 4, 2);
    TEST_ASSERT_EQUAL(result, subString);
}

int main (int argc, char * argv[])
{
    UnityBegin();
    
    MY_RUN_TEST(firstTest);
    
    return UnityEnd();
}
