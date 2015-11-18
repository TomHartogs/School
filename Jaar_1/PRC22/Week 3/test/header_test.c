/* auteur : F.J. Hurkmans
 * datum  : November 4th 2013
 * code   : Ansi C
 * versie : 1
 */

#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"
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

static void file_Write_Read_Test(void)
{
	BMP_MAGIC_t magic;
	BMP_FILE_t file;
	BMP_INFO_t info;
	
    magic.magic[0] = 1;
    magic.magic[1] = 2;
    
    file.filesz = 4;
    file.creator1 = 5;
    file.creator2 = 6;
    file.bmp_offset = 7;
    
    info.header_sz = 8;
    info.width = 9;
    info.height = 10;
    info.nplanes = 11;
    info.bitspp = 12; 
    info.compress_type = 13;
    info.bmp_bytesz = 14;
    info.hres = 15;
    info.vres = 16;
    info.ncolors = 17;
    info.nimpcolors = 18;
    
	char fileName[100] = "test.bmp";

	FILE* filePtr;
	filePtr = fopen(fileName, "wb");
	writeHdr(filePtr, &magic, &file, &info);
	fclose(filePtr);

	BMP_MAGIC_t magicRead;
	BMP_FILE_t fileRead;
	BMP_INFO_t infoRead;
	
	filePtr = fopen(fileName, "rb");
	readHdr(filePtr, &magicRead, &fileRead, &infoRead);
	fclose(filePtr);
    
    TEST_ASSERT_EQUAL(magic.magic[0], magicRead.magic[0]);
    TEST_ASSERT_EQUAL(magic.magic[1], magicRead.magic[1]);
    
    TEST_ASSERT_EQUAL(file.filesz, fileRead.filesz);
    TEST_ASSERT_EQUAL(file.creator1, fileRead.creator1);
    TEST_ASSERT_EQUAL(file.creator2, fileRead.creator2);
    TEST_ASSERT_EQUAL(file.bmp_offset, fileRead.bmp_offset);
    
    TEST_ASSERT_EQUAL(info.header_sz, infoRead.header_sz);
    TEST_ASSERT_EQUAL(info.width, infoRead.width);
    TEST_ASSERT_EQUAL(info.height, infoRead.height);
    TEST_ASSERT_EQUAL(info.nplanes, infoRead.nplanes);
    TEST_ASSERT_EQUAL(info.bitspp, infoRead.bitspp);
    TEST_ASSERT_EQUAL(info.compress_type, infoRead.compress_type);
    TEST_ASSERT_EQUAL(info.bmp_bytesz, infoRead.bmp_bytesz);
    TEST_ASSERT_EQUAL(info.hres, infoRead.hres);
    TEST_ASSERT_EQUAL(info.vres, infoRead.vres);
    TEST_ASSERT_EQUAL(info.ncolors, infoRead.ncolors);
    TEST_ASSERT_EQUAL(info.nimpcolors, infoRead.nimpcolors);
}

int main (int argc, char * argv[])
{
    UnityBegin();
    
    MY_RUN_TEST(file_Write_Read_Test);
    
    return UnityEnd();
}
