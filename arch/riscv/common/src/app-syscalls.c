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
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <base.h>

#include "global_pointers.h"

#define NUM_OF_TRIES 10

FATFS *p_file_sys = NULL;
  
int _close(int file)
{
  //can't really close the uart either
  if(file != 3) return 0;

  free(p_file_sys);

  p_file_sys = NULL;

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
  // int error = 0;

  if(file != 3) return -1;

  //SEEK_SET is 0 "START TO OFFSET"
  //SEEK_CUR is 1 "CURRENT PLUS OFFSET PTR"
  //SEEK_END is 2 "END AND OFFSET?"
  // printf("SEEK CAUGHT %d %d SEEK: %d %d %d FILE PTR: %u %u\n", ptr, dir, SEEK_SET, SEEK_CUR, SEEK_END, p_file_sys->fptr, p_file_sys->fsize);

  switch(dir)
  {
    case SEEK_SET:
      if(pf_lseek(ptr)) return -1;
      break;
    case SEEK_CUR:
      if(pf_lseek(p_file_sys->fptr + ptr)) return -1;
      break;
    case SEEK_END:
      p_file_sys->fptr = p_file_sys->fsize;
      break;
  }

  // printf("SEEK COMPLETE %d\n", p_file_sys->fptr);
  return p_file_sys->fptr;
}

int _open(const char *name, int flags, ...)
{
  char str_char;
  int varargs = 0;
  int error = 0;

  va_list args;

  va_start(args, flags);

  va_end(args);

  __delay_ms(1000);

  if(!p_file_sys)
  {
    int tries = NUM_OF_TRIES;

    p_file_sys = malloc(sizeof(FATFS));

    if(!p_file_sys) return -1;

    do
    {
      error = pf_mount(p_file_sys);

      if(!error) break;
    }
    while(--tries);
  }

  if(error)
  {
    printf("MOUNT FAILED TO ACCESS SDCARD, %d\n\r", error);

    return -error;
  }

  error = pf_open(name);

  if(error) return -error;

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
  int index = 0;
  int error;

  if(file == 3)
  {
    error = pf_read(ptr, len, &index);

    if(error)
    {
      printf("READ ERROR %d %d %d %d\n", p_file_sys->fptr, len, index, error);

      return -1;
    }

    return index;
  }

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
  int index = 0;
  int error;

  if(file == 3)
  {

    error = pf_write(ptr, len, &index);

    if(error)
    {
      printf("WRITE ERROR %d %d %d %d\n", p_file_sys->fptr, len, index, error);

      return -1;
    }

    return index;
  }

  if(file > 2 || !file) return -1;

  for(index = 0; index < len; index++)
  {
    while(getUartTxFifoFull(__gp_uart));
    
    setUartTxData(__gp_uart, ptr[index]);

    if(ptr[index] == '\n')
    {
      while(getUartTxFifoFull(__gp_uart));

      setUartTxData(__gp_uart, (uint8_t)0x0D);
    }
  }
  
  return index;
}

int _link(const char *oldpath, const char *newpath) {
  (void)oldpath;
  (void)newpath;

  errno = ENOSYS;

  __asm__ volatile ("ebreak");
  return -1;
}

int _unlink(const char *pathname) {
  (void)pathname;

  errno = ENOENT;

  __asm__ volatile ("ebreak");
  return -1;
}
