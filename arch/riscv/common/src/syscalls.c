/***************************************************************************//**
  * @file     syscalls.c
  * @brief    Provide syscalls.c for newlib.
  * @details  At the moment these are all stubs that return error if used.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     01/20/2026
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

#include <sys/stat.h> 
#include <sys/types.h>
#include <uart.h>
#include <pff3a/diskio.h>
#include <stdarg.h>
#include <unistd.h>
#include "global_pointers.h"

FATFS g_file_sys;
  
int _close(int file)
{
  //can't really close the uart either
  if(file != 3) return -1;

  return 0;
}

int _isatty(int file)
{
  if(file != 3) return 1;

  return 0;
}

int _lseek(int file, int ptr, int dir)
{
  //can't seek the uart
  if(file != 3) return 0;

  if(dir != SEEK_SET) return -1;

  if(pf_lseek(ptr)) return -1;

  return ptr;
}

int _open(const char *name, int flags, ...)
{
  char str_char;
  int varargs = 0;
  int error = 0;

  va_list args;

  va_start(args, flags);

  if(va_arg(args, int) != 0) return -1;

  va_end(args);

  error = pf_mount(&g_file_sys);

  if(error != 0) return -error;

  error = pf_open(name);

  if(error != 0) return -error;

  return 3;
}

// per bootstrapping-libc-with-newlib
int _fstat(int file, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

pid_t _getpid(void)
{
  //no multitasking.
  return (pid_t)0;
}

int _kill(pid_t pid, int sig)
{
  //be silly to kill are one task
  return -1;
}

// read call for printf functionality.
int _read(int file, char *ptr, int len)
{
  int index;

  if(file == 3)
  {
    if(pf_read(ptr, len, &index)) return -1;

    return index;
  }

  // we do not handle anything other than stdin for now
  if(file != 1) return -1;
  
  for(index = 0; index < len; index++)
  {
    while(!getUartRxFifoValid(__gp_uart));
    
    ptr[index] = getUartRxData(__gp_uart);
  }
  
  return index;
}

int _write(int file, char *ptr, int len)
{
  int index;

  if(file == 3)
  {
    if(pf_write(ptr, len, &index)) return -1;

    return index;
  }
  // we do not handle anything other than stdout or error for now
  if(file > 2 || !file) return -1;
  
  for(index = 0; index < len; index++)
  {
    while(getUartTxFifoFull(__gp_uart));
    
    setUartTxData(__gp_uart, ptr[index]);
  }
  
  return index;
}
