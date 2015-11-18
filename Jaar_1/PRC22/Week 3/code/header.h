/*
 * header.h
 *
 *  Created on: Jun 8, 2015
 *      Author: F. Hurkmans
 */

#ifndef HEADER_H_
#define HEADER_H_

#include <stdint.h>
#include <stdio.h>

#include "bmp.h"

void readHdr (FILE* FilePtr, BMP_MAGIC_t* Magic, BMP_FILE_t* File, BMP_INFO_t* Info);
/*
 * description: read the header of a bmp File, and store the data in the provided parameters
 *
 * parameters:
 *         FilePtr: file, opened for reading
 *         Magic:   output-parameter to store the read BMP_MAGIC_t structure
 *         File:    output-parameter to store the read BMP_FILE_t structure
 *         Info:    output-parameter to store the read BMP_INFO_t structure
 *
 * Note: caller should provide enough memory for parameters 'Magic', 'File' and 'Info'
 */

void writeHdr (FILE* FilePtr, BMP_MAGIC_t* Magic, BMP_FILE_t* File, BMP_INFO_t* Info);
/*
 * description: write the header of a bmp File, where the data comes from the provided parameters
 *
 * parameters:
 *         FilePtr: file, opened for writing
 *         Magic:   input-parameter with a BMP_MAGIC_t structure
 *         File:    input-parameter with a BMP_FILE_t structure
 *         Info:    input-parameter with a BMP_INFO_t structure
 *
 */

#endif /* HEADER_H_ */
