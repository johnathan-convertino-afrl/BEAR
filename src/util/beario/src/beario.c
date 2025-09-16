/***************************************************************************//**
  * @file     beario.h
  * @brief    Generic Uart IO for C
  * @details  Baremetal C driver targeting UART
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     08/28/2025
  * @version
  * - 0.0.0
  *
  * @license mit
  *
  * Copyright 2025 Johnathan Convertino
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
#include <base.h>
  
#include <stdlib.h>
// #include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "beario.h"

#define TEMP_STR_MAX 1024

// emulates printf functionality
int beario_printf(char *str_format, ...)
{
  int index;
  int temp;
  
  static char buffer[TEMP_STR_MAX];
  va_list args;
  
  va_start(args, str_format);
  
  temp = vsnprintf(buffer, TEMP_STR_MAX, str_format, args);
  
  temp = (temp > TEMP_STR_MAX ? TEMP_STR_MAX : temp);
  
  for(index = 0; index < temp; index++)
  {
    beario_putchar((int)buffer[index]);
  }
  
  va_end(args);
  
  return temp;
}

// emulates printf for strings only
int beario_stronly_printf(char *str_format, ...)
{
  char str_char;
  int index = 0;

  va_list args;
  
  va_start(args, str_format);
  
  str_char = *str_format;
  
  while(str_char)
  {
    index++;
    char *p_next_str_char = str_format++;
    char *p_temp;
    
    switch(str_char)
    {
      case '%':
        if(*p_next_str_char == 's')
        {
          p_temp = (char *)(va_arg(args, char *));
          
          while(p_temp)
          {
            beario_putchar(*p_temp);
            
            p_temp++;
          }
        }
        else
        {
          p_next_str_char = p_next_str_char++;
        }
        break;
      default:
        beario_putchar(str_char);
        break;
    }
    
    str_char = *p_next_str_char;
  }
  
  va_end(args);
  
  return index;
}

// emulates scanf functionality
int beario_scanf(char *str_format, ...)
{
  int index = 0;
  int temp;
  
  static char buffer[TEMP_STR_MAX];
  va_list args;
  
  va_start(args, str_format);
  
  do
  {
    buffer[index++] = (char)beario_getchar();
    
    if(index >= TEMP_STR_MAX)
    {
      index--;
      break;
    }
  }
  while(buffer[index] != '\n');
  
  buffer[index] = '\0';
  
  temp = vsscanf(buffer, str_format, args);
  
  va_end(args);
  
  return temp;
}


