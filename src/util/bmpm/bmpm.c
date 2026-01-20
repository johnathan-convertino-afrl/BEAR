/***************************************************************************//**
  * @file     bmpm.c
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
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmpm.h"

struct
{
  signed int width;
  signed int height;
  uint16_t depth;
  uint32_t offset;
} g_bmp_data;

//helper functions
//detects bitmap image, if it exists and is of the right type
//this will return the offset, if its not a 24 bit bitmap -1, raw data, 0
uint32_t detectBMP(void const *p_data, uint32_t len);
//swaps rows, as bitmap reverse the bits
//0 success, -1 failure
int reverseData(void *op_data, uint32_t len, signed int width, signed int height);


//convert bitmap data to RAW, if no header detected, or incorrect header, this does nothing.
//strip header and flip data. LEN IS NUMBER OF BYTES in OP_DATA
uint32_t bmpmConvertToRaw(void **op_data, uint32_t len)
{
  uint32_t newLen = len;
  
  uint8_t *p_temp = (uint8_t *)*op_data;
  
  detectBMP(*op_data, len);
  
  if(g_bmp_data.offset <= 0) return 0;
  
  newLen -= g_bmp_data.offset;

  //copy data, excluding header
  memmove(p_temp, &p_temp[g_bmp_data.offset], newLen);
  
  
  // *op_data = ((uint8_t *)*op_data)+g_bmp_data.offset;
  
//   p_temp = realloc(*op_data, newLen);
//   
  //reverse bitmap data, its in the wrong order for raw image data
//   if(!p_temp) return 0;
//   
//   *op_data = p_temp;
  
  if(reverseData(*op_data, newLen, g_bmp_data.width, g_bmp_data.height)) return 0;
  
  return newLen;
  
}

//return width
signed int bmpmGetWidth()
{
  return g_bmp_data.width;
}

//return height
signed int bmpmGetHeight()
{
  return g_bmp_data.height;
}

// return header offset of the last converted bitmap
uint32_t bmpmGetOffset()
{
  return g_bmp_data.offset;
}

//detects bitmap image, if it exists and is of the right type
//this will return the offset byte location
uint32_t detectBMP(void const *p_data, uint32_t len)
{
  uint32_t index = 0;
  
  uint8_t *p_temp = (uint8_t *)p_data;
  //not enough data to be a bitmap, must be larger than the header
  if(len < HEADER_SIZE) return 0;
  
  g_bmp_data.width = 0;
  g_bmp_data.height = 0;
  g_bmp_data.depth = 0;
  g_bmp_data.offset = 0;
  
  for(index = 0; index < HEADER_SIZE; index++)
  {
    switch(index)
    {
      case 0:
        if(p_temp[index] != 'B') return 0;
        break;
      case 1:
        if(p_temp[index] != 'M') return 0;
        break;
      case 10:
      case 11:
      case 12:
      case 13:
        g_bmp_data.offset |= (uint32_t)(p_temp[index] << ((index - 10) * 8));
        break;
      case 18:
      case 19:
      case 20:
      case 21:
        g_bmp_data.width |= p_temp[index] << ((index - 18) * 8);
        break;
      case 22:
      case 23:
      case 24:
      case 25:
        g_bmp_data.height |= p_temp[index] << ((index - 22) * 8);
        break;
      case 28:
        g_bmp_data.depth = (uint16_t)p_temp[index];
        break;
      case 29:
        g_bmp_data.depth |= ((uint16_t)p_temp[index]) << 8;
        
        if(g_bmp_data.depth != BMP_32BIT) return 0;
      default:
        break;
    }
  }
  
  return g_bmp_data.offset;
}

//reverse data, swap bottom to top and top to bottom.
int reverseData(void *op_data, uint32_t len, signed int width, signed int height)
{
  uint32_t index;

  uint8_t *p_temp = (uint8_t *)op_data;
  
  if(len <= 0) return -1;
  
  for(index = 0; index < height/2; index++)
  {
    uint8_t tempData[width * sizeof(uint32_t)];
    
    memcpy(tempData, &p_temp[index * width * sizeof(uint32_t)], width * sizeof(uint32_t));
    
    memcpy(&p_temp[index * width * sizeof(uint32_t)], &p_temp[len - ((index+1) * width * sizeof(uint32_t))], width * sizeof(uint32_t));
    
    memcpy(&p_temp[len - ((index+1) * width * sizeof(uint32_t))], tempData, width * sizeof(uint32_t));
  }
  
  return 0;
}
