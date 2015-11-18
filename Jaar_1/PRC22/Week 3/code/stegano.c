/*
 * stegano.c
 *
 *  Created on: Jun 8, 2015
 *      Author: F. Hurkmans
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

//#include "resource_detector.h"
#include "bit.h"
#include "bmp.h"
#include "header.h"
#include "stegano.h"

#define MAX_FILENAME 80

void
multiplex (const char* File0, const char* File1)
{
    FILE* FilePtr0 			= NULL;
    FILE* FilePtr1 			= NULL;
    FILE* FilePtr2 			= NULL;
    char  buf[MAX_FILENAME];

	int NrOfBits = 0;
    for (; NrOfBits <= 8; NrOfBits++)
    {
        // NrBits: number of bits for the hidden image
        snprintf (buf, MAX_FILENAME, "mux_%s_%s_%d.bmp", File0, File1, NrOfBits);
        FilePtr0 			= fopen (File0, "rb");
        FilePtr1 			= fopen (File1, "rb");
        FilePtr2 			= fopen (buf,   "wb");

        // to be implemented
        
        //------------Create new header----------
		BMP_MAGIC_t magic0;
		BMP_MAGIC_t magic1;
		BMP_FILE_t file0;
		BMP_FILE_t file1;
		BMP_INFO_t info0;
		BMP_INFO_t info1;

		readHdr(FilePtr0, &magic0, &file0, &info0);
		readHdr(FilePtr1, &magic1, &file1, &info1);

		file0.creator1 		= info1.width;
		file0.creator2 		= info1.height;
		info0.nimpcolors 	= NrOfBits;
		
		writeHdr(FilePtr2, &magic0, &file0, &info0);
		
		//-------Calculate-Pixels-In-Image-------
        int pixelsInImage 	= info0.width * info0.height;
		const int pixelColors = 3;
		
        //---------------------------------------
		int i = 0;
        for (; i < pixelsInImage; i++)
        {
			uint8_t pixel0[pixelColors];
			uint8_t pixel1[pixelColors];
			uint8_t newPixel[pixelColors];
			if(	fread(pixel0, pixelColors, 1, FilePtr0) && fread(pixel1, pixelColors, 1, FilePtr1))
			{
				int i = 0;
				for(; i < pixelColors; i++)
				{
					newPixel[i] = combineByte(pixel0[i], pixel1[i], NrOfBits);
				}
				fwrite(newPixel, pixelColors, 1, FilePtr2);
			}
			//Reset pixels??
		}
		fclose(FilePtr0);
		fclose(FilePtr1);
		fclose(FilePtr2);
    }
}

void
multiplexText (const char* File0, const char* File1)
{
    FILE* FilePtr0 = NULL;
    FILE* FilePtr1 = NULL;
    FILE* FilePtr2 = NULL;
    char  buf[MAX_FILENAME];

    snprintf (buf, MAX_FILENAME, "mux_%s_%s.bmp", File0, File1);
    FilePtr0 	= fopen (File0, "rb");
    FilePtr1 	= fopen (File1, "rb");
    FilePtr2 	= fopen (buf,   "wb");

    // to be implemented
	BMP_MAGIC_t magic;
	BMP_FILE_t file;
	BMP_INFO_t info;

	readHdr(FilePtr0, &magic, &file, &info);

	fseek(FilePtr1, 0, SEEK_END);
	int bytesInText = ftell(FilePtr1);
	fseek(FilePtr1, 0, SEEK_SET);
	char textArray[bytesInText];
	
	//-------Calculate-Bytes-In-Image-------
	const int pixelColors 	= 3;
	int bytesInImage 		= info.width * info.height * pixelColors;
	
	file.creator1 = bytesInText;
	writeHdr(FilePtr2, &magic, &file, &info);
	
	if(fread(textArray, bytesInText, 1, FilePtr1))
	{
		int bytesHandled = 0;
		int bitsOfCharLeft = 7;
		
		int i = 0;
		for(; i < bytesInImage; i++)
		{
			uint8_t pixel = 0;
			uint8_t newPixel = 0;
			
			if(fread(&pixel, 1, 1, FilePtr0))
			{
				if(bytesHandled < bytesInText)
				{
					newPixel = getSubstring(pixel, 1, 7, 1) | getSubstring(textArray[bytesHandled], bitsOfCharLeft, 1, 0);
					fwrite(&newPixel, 1, 1, FilePtr2);
					if(bitsOfCharLeft == 0)
					{
						bytesHandled++;
						bitsOfCharLeft = 7;
					}
					else
					{
						bitsOfCharLeft--;
					}
				}
				else
				{
					fwrite(&pixel, 1, 1, FilePtr2);
				}
			}
		}
	}
}


void
demultiplex (const char* File0, const char* File1, const char* File2)
{
    FILE* FilePtr0 = NULL;
    FILE* FilePtr1 = NULL;
    FILE* FilePtr2 = NULL;

    FilePtr0 	= fopen (File0, "rb");
    FilePtr1 	= fopen (File1, "wb");
    FilePtr2 	= fopen (File2, "wb");

    // to be implemented
	BMP_MAGIC_t magic;
	BMP_FILE_t file;
	BMP_INFO_t info;

	readHdr(FilePtr0, &magic, &file, &info);
	
	int NrOfBits = info.nimpcolors;
	
	file.creator1 = 0;
	file.creator2 = 0;
	info.nimpcolors = 0;
	
	writeHdr(FilePtr1, &magic, &file, &info);
	writeHdr(FilePtr2, &magic, &file, &info);
	
	//-------Calculate-Pixels-In-Image-------
	int pixelsInImage 	= info.width * info.height;
	const int pixelColors = 3;
	
	//---------------------------------------
	int i = 0;
	for (; i < pixelsInImage; i++)
	{
		uint8_t pixel[pixelColors];
		uint8_t newPixel0[pixelColors];
		uint8_t newPixel1[pixelColors];
		if(fread(pixel, pixelColors, 1, FilePtr0))
		{
			int i = 0;
			for(; i < pixelColors; i++)
			{
				splitByte(pixel[i], &newPixel0[i], &newPixel1[i], NrOfBits);
			}
			fwrite(newPixel0, pixelColors, 1, FilePtr1);
			fwrite(newPixel1, pixelColors, 1, FilePtr2);
		}
	}
	fclose(FilePtr0);
	fclose(FilePtr1);
	fclose(FilePtr2);
}

void
demultiplexText (const char* File0, const char* File1, const char* File2)
{
    FILE* FilePtr0 = NULL;
    FILE* FilePtr1 = NULL;
    FILE* FilePtr2 = NULL;

    FilePtr0 	= fopen (File0, "rb");  //binair lezen 
    FilePtr1 	= fopen (File1, "wb");  //binair schrijven 
    FilePtr2 	= fopen (File2, "wb");  //binair schrijven 

    // to be implemented
	BMP_MAGIC_t magic;
	BMP_FILE_t file;
	BMP_INFO_t info;

	readHdr(FilePtr0, &magic, &file, &info);
	
	int nrOfBytesHidden = file.creator1;
	file.creator1 = 0;
	file.creator2 = 0;
	info.nimpcolors = 0;
	
	writeHdr(FilePtr1, &magic, &file, &info);
	writeHdr(FilePtr2, &magic, &file, &info);
	
	//-------Calculate-Pixels-In-Image-------
	int pixelsInImage 	= info.width * info.height;
	
	int bytesHandled = 0;
	int bitsOfCharLeft = 7;
	uint8_t newChar = 0;
	//---------------------------------------
	int i = 0;
	for (; i < pixelsInImage; i++)
	{
		uint8_t pixel = 0;
		uint8_t newPixel = 0;
		uint8_t newCharPiece = 0;
		
		if(fread(&pixel, 1, 1, FilePtr0))
		{
			newPixel = getSubstring(pixel, 1, 7, 1);
			fwrite(&newPixel, 1, 1, FilePtr1);
			
			if(bytesHandled < nrOfBytesHidden)
			{
				newCharPiece = getSubstring(pixel, 0, 1, bitsOfCharLeft);
				newChar |= newCharPiece;
				if(bitsOfCharLeft == 0)
				{
					bitsOfCharLeft = 7;
					fwrite(&newChar, 1, 1, FilePtr2);
				}
				else
				{
					bitsOfCharLeft--;
				}
				bytesHandled++;
			}
		}
	}
	fclose(FilePtr0);
	fclose(FilePtr1);
	fclose(FilePtr2);
}

uint8_t combineByte(uint8_t pixel0, uint8_t pixel1, int NrOfBits)
{
	return getSubstring(pixel0, NrOfBits, 8 - NrOfBits, NrOfBits) | getSubstring(pixel1, 8 - NrOfBits, NrOfBits, 0);
}

void splitByte(uint8_t pixel, uint8_t* newPixel0, uint8_t* newPixel1, int NrOfBits)
{
	////------------------------------nr of bits?-------------------
	////								 \/
	*newPixel0 = getSubstring(pixel, 8 - NrOfBits, NrOfBits, NrOfBits);
	*newPixel1 = getSubstring(pixel, 0, NrOfBits, 0);
}
