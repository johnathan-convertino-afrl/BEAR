/***************************************************************************//**
  * @file     bmpm.h
  * @brief    bitmap to raw conversion
  * @details  Convert 32bit XA8R8G8B images to RAW 32bit images, flips lines.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     01/13/2026
  * @version
  * - 0.0.0
  *
  * @license mit
  *
  * Copyright 2026 Johnathan Convertino
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  * IN THE SOFTWARE.
  *****************************************************************************/


#ifndef __UTIL_BMPMANIP_H
#define __UTIL_BMPMANIP_H

#define HEADER_SIZE     138
#define BMP_16BIT       0x10
#define BMP_32BIT       0x20
#define BMP_COLOR_MASK  0x1F

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*********************************************//**
  * @brief Convert bitmap image to raw pixels
  *
  * @param op_data Double pointer to memory that contains image data.
  * @param len Total number of bytes in buffer.
  * 
  * @return 0 on error, new length in on success.
  *************************************************/
uint32_t bmpmConvertToRaw(void **op_data, uint32_t len);

/*********************************************//**
  * @brief Get the width(X) of the last converted bitmap
  *
  * @return 0 on error, width on success.
  *************************************************/
signed int bmpmGetWidth();

/*********************************************//**
  * @brief Get the height(Y) of the last converted bitmap
  *
  * @return 0 on error, height on success.
  *************************************************/
signed int bmpmGetHeight();

#ifdef __cplusplus
}
#endif

#endif
