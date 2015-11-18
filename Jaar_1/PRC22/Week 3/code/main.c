/*
 * main.c
 *
 *  Created on: Nov 6, 2011
 *      Author: student
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "resource_detector.h"
#include "stegano.h"
#include "bit.h"
#include "bmp.h"

#define    MAX_STRLEN    80

static bool WithMenu = true;

static void
testBit (void)
{
	uint8_t src;
	uint8_t src_pos;
	uint8_t nrof_bits;
	uint8_t dest_pos;

	for (int j = 1; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int k = 0; k < 8; k++)
			{
				if ((i + j <= 8) && (k + j <= 8))
				{
					src = 0xd4;
					src_pos = i;
					nrof_bits = j;
					dest_pos = k;
					printf ("SteganoGetSubstring(0x%02x,%d,%d,%d) = 0x%02x\n",
							src, src_pos, nrof_bits, dest_pos,
							getSubstring(src, src_pos, nrof_bits, dest_pos));
				}
			}
		}
	}
}

static void
testBmp (const char * file)
{
	FILE *		fp;
	uint32_t	d;
	uint8_t		a[3];

	printf ("header of '%s':", file);
	fp = fopen (file, "rb");
	fseek (fp, 0x02, SEEK_SET);	// skip 'BM' magic
	for (int i = 0; i < 13; i++)
	{
		if ((i % 4) == 0)
		{
			printf ("\n");
		}
		int result = fread (&d, sizeof (d), 1, fp);
        if (result != 1)
        {
            perror("fread failed");
            return;
        }
		printf ("%08x ", d);
	}

	printf ("\nfirst 8 pixels: ");
	fseek (fp, sizeof (BMP_MAGIC_t) + sizeof (BMP_FILE_t) + sizeof (BMP_INFO_t),
			SEEK_SET);
	for (int i = 0; i < 8; i++)
	{
		int result = fread(&a, sizeof (a), 1, fp);
        if (result != 1)
        {
            perror("fread failed");
            return;
        }
	    printf ("%02x%02x%02x ", a[0], a[1], a[2]);
	}
	printf ("\nlast  8 pixels: ");
	fseek (fp, -24, SEEK_END);
	for (int i = 0; i < 8; i++)
	{
		int result = fread (&a, sizeof (a), 1, fp);
        if (result != 1)
        {
            perror("fread failed");
            return;
        }
		printf ("%02x%02x%02x ", a[0], a[1], a[2]);
	}
	printf ("\n");
	fclose (fp);
}

static int
getInt (const char* Message)
{
    char Line[MAX_STRLEN];
    char* Result = NULL;
    int  Value = -1;

    if (WithMenu)
    {
        printf ("%s", Message);
    }
    Result = fgets (Line, sizeof(Line), stdin);
    if (Result != NULL)
    {
        sscanf (Result, "%d", &Value);
    }

    return Value;
}

static void
getStr (const char* Message, char* Str)
{
    char Line[MAX_STRLEN];
    char* Result = NULL;

    if (WithMenu)
    {
        printf ("%s", Message);
    }
    Result = fgets (Line, sizeof(Line), stdin);
    if (Result != NULL)
    {
        sscanf (Result, "%s", Str);
    }
}


extern int
main (int argc, char * argv[])
{
    char File0 [MAX_STRLEN];
    char File1 [MAX_STRLEN];
    char File2 [MAX_STRLEN];
    int  Choice;
    bool Quit = false;

    printf ("PRC assignment 'SteganoC' (version 2)\n"
            "-------------------------------------\n");

    if (argc != 1)
    {
        fprintf (stderr, "%s: argc=%d\n", argv[0], argc);
    }

    while (!Quit)
    {
        if (WithMenu)
        {
            printf ("\n\nMENU\n"
                "===================\n"
                "[1] multiplex\n"
                "[2] multiplex text\n"
                "[3] demultiplex\n"
                "[4] demultiplex text\n"
            	"[6] test bit\n"
            	"[7] test bmp\n"
            	"[8] show/hide menu\n"
                "[9] quit\n");
        }
        Choice = getInt ("Choice: ");

        switch (Choice)
        {
            case 1:
                getStr ("enter input file (visible): ", File0);
                getStr ("enter input file (hidden): ", File1);
                multiplex (File0, File1);
                break;
            case 2:
                getStr ("enter input file (visible): ", File0);
                getStr ("enter input file (text): ", File1);
                multiplexText (File0, File1);
                break;
            case 3:
                getStr ("enter input file: ", File0);
                getStr ("enter output file (visible): ", File1);
                getStr ("enter output file (hidden): ", File2);
                demultiplex (File0, File1, File2);
                break;
            case 4:
                getStr ("enter input file: ", File0);
                getStr ("enter output file (visible): ", File1);
                getStr ("enter output file (text): ", File2);
                demultiplexText (File0, File1, File2);
                break;
            case 6:
             	testBit();
                break;
            case 7:
            	getStr ("enter input file: ", File0);
             	testBmp(File0);
                break;
            case 8:
                if (WithMenu)
                {
                    printf ("printing of MENU is disabled\n");
                }
                WithMenu = !WithMenu;
                break;
            case 9:
                Quit = true;
                break;
            default:
                printf ("ERROR: invalid Choice: %d\n", Choice);
                break;
        }
    }
    return (0);
}

