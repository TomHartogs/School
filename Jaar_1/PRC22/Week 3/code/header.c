/*
 * header.c
 *
 *  Created on: Jun 8, 2015
 *      Author: F. Hurkmans
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//#include "resource_detector.h"
#include "header.h"

int sizeOfMagicStruct = sizeof(BMP_MAGIC_t);
int sizeOfFileStruct = sizeof(BMP_FILE_t);
int sizeOfInfoStruct = sizeof(BMP_INFO_t);

void
readHdr (FILE* FilePtr, BMP_MAGIC_t* Magic, BMP_FILE_t* File, BMP_INFO_t* Info)
{
	if (FilePtr && Magic && File && Info)
	{
		fseek(FilePtr, 0, SEEK_SET);
		if (fread(Magic, sizeOfMagicStruct, 1, FilePtr) &&
			fread(File, sizeOfFileStruct, 1, FilePtr) &&
			fread(Info, sizeOfInfoStruct, 1, FilePtr))
			{
				
			}
	}
}


void
writeHdr (FILE* FilePtr, BMP_MAGIC_t* Magic, BMP_FILE_t* File, BMP_INFO_t* Info)
{
	if (FilePtr && Magic && File && Info)
	{
		fseek(FilePtr, 0, SEEK_SET);
		fwrite(Magic, sizeOfMagicStruct, 1, FilePtr);
		fwrite(File, sizeOfFileStruct, 1, FilePtr);
		fwrite(Info, sizeOfInfoStruct, 1, FilePtr);
	}
}
