/***************************************************************************//**
  * @file     spi.h
  * @brief    Altera AXI SPI driver
  * @details  Baremetal C driver targeting Altera based SPI lite cores.
  *           Written with riscv or arm irq structure in mind.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     07/17/2025
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

#include <stdlib.h>

#include "spi.h"
#include "sdcard_spi.h"

#define SD_FAST_FREQ_HZ 20000000
#define SD_SLOW_FREQ_HZ 400000
#define SD_INIT_WORD    0xFF
#define SD_NCR_ATTEMPT  8
#define SD_INIT_ATTEMPT 10

// Commands (2 bits start, 6 bits command index)
// Start bit is 0, transmission bit is 1 (2 bits)
#define SD_CMD_MSBS 0x40
// command indexs (6 bits)
#define SD_CMD0     0x00 // 0
#define SD_CMD8     0x08 // 8
#define SD_CMD55    0x37 //55
#define SD_ACMD41   0x29 //41


// Fixed Arguments
#define SD_CMD_NULL_ARG 0x00000000
// 3.3 volt and AA check pattern
#define SD_CMD8_ARG 0x000001AA
// we support high capacity cards
#define SD_ACMD41_ARG 0x40000000

// Fixed CRC since we will not be using it be default (bits 7:1, and 0 is set to 1 in sendCommand).
#define SD_CMD0_CRC     0x94
#define SD_CMD8_CRC     0x86
#define SD_CMD_NULL_CRC 0x00
// terminate 7 bit CRC with one for all command sends.
#define SD_TERM_CRC 0x01

#define SD_RESP_IDLE_R1     0x01
#define SD_RESP_ILLEGAL_R1  0x02

// send a byte of data to the spi device.
static inline void sendRawData(struct s_spi *p_spi, uint8_t data);
// send a standard command to the sdcard.
static inline void sendCommand(struct s_spi *p_spi, uint8_t cmd, uint32_t arg, uint8_t crc);
// send a application command to the sdcard.
static inline void sendAppCommand(struct s_spi *p_spi, uint8_t acmd, uint32_t arg, uint8_t crc);
// recv a byte of data from the spi device.
static inline uint8_t recvRawData(struct s_spi *p_spi);
// recv a response that is not all 0xFF (usually for R1)
static inline uint8_t recvRespOneByte(struct s_spi *p_spi);
// recv a response that is any length, first byte will use recvRespOneByte
static inline void recvRespBytes(struct s_spi *p_spi, uint8_t *p_buff, const uint8_t num_bytes);

// Initializes sdcard over spi device for data mode
struct s_sdcard_spi *initSdcardSpi(uint32_t memory_address, uint8_t cs_num)
{
  int index;
  
  uint8_t init_attepts = 0;
  
  // store SD responses from first byte to last (first 0 last 4).
  uint8_t sd_response[5] = 0;
  
  struct s_sdcard_spi *p_temp = NULL;
  
  struct s_spi *p_spi = NULL;
  
  // setup spi device to use for communication.
  p_spi = initSpi(memory_address);
  
  setSpiMode(p_spi 0, 0);
  
  setSpiClockFreq(p_spi, SD_SLOW_FREQ_HZ);
  
  //disable chip select for 80 clock cycle write
  clrSpiChipSelect(p_spi, cs_num);
  
  // write all ones for 80 clock cycles to the SDCARD while it is NOT selected.
  for(index = 0; index < 10; index++)
  {
    setSpiData(p_spi, SD_INIT_WORD);
  }
  
  //enable chip select
  setSpiChipSelect(p_spi, cs_num);
  
  //allocate struct 
  p_temp = malloc(sizeof(struct s_sdcard_spi));
  
  //check and return NULL if invalid
  if(!p_temp) return NULL;
  
  //set struct members
  p_temp->state = NOT_READY;
  p_temp->p_spi = p_spi;
  p_temp->cs_num = cs_num;
  
  //Try to send command 0 10 times and receive idle response.
  do
  {
    setSpiForceSelect(p_spi);
    
    sendCommand(p_spi, SD_CMD0, SD_CMD_NULL_ARG, SD_CMD0_CRC);
    
    sd_response[0] = recvRespOneByte(p_spi);
    
    clrSpiForceSelect(p_spi);
    
    init_attempts++;
  }
  while((sd_response[0] != SD_RESP_IDLE_R1) && (init_attempts < SD_INIT_ATTEMPT);

  if((sd_response[0] != SD_RESP_IDLE_R1) && (init_attempts >= SD_INIT_ATTEMPT))
  {
    p_temp->state = CMD0_FAIL;
    
    return p_temp;
  }
  
  //send command 8 and check response
  setSpiForceSelect(p_spi);
  
  sendCommand(p_spi, SD_CMD8, SD_CMD8_ARG, SD_CMD8_CRC);
  
  recvRespBytes(p_spi, sd_response, 5);
  
  clrSpiForceSelect(p_spi);
  
  //set clock to fast
  setSpiClockFreq(p_spi, SD_FAST_FREQ_HZ);
  
  switch(sd_response[0])
  {
    case SD_RESP_IDLE_R1:
      if(sd_response[3] != 0x01)
      {
        p_temp->state = VOLTAGE_RANGE_FAIL;
        return p_temp;
      }
      if(sd_reponse[4] != 0xAA)
      {
        p_temp->state = CHECK_PATTERN_FAIL;
        return p_temp;
      }
      p_temp->state = INIT_V2;
      break;
    case SD_RESP_ILLEGAL_R1|SD_RESP_IDLE_R1:
      // card does not support V2, must be a V1
      p_temp->state = INIT_V1;
      break;
    default
      //unknown failure
      p_temp->state = UNKNOWN_FAIL;
      return p_temp;
  }
  
  setSpiForceSelect(p_spi);
  
  sendAppCommand(p_spi, SD_ACMD41, SD_ACMD41_ARG, SD_CMD_NULL_CRC);
  
  clrSpiForceSelect(p_spi);

  return p_temp;
}

// send a byte of data to the spi device.
static inline void sendRawData(struct s_spi *p_spi, uint8_t data)
{
  // wait until write ready is 1, then write.
  while(!getSpiWriteReady(p_spi));
  
  // set the transmit register to the input data passed.
  setSpiData(p_spi, data);
}

// send a command to the sdcard.
static inline void sendCommand(struct s_spi *p_spi, uint8_t cmd, uint32_t arg, uint8_t crc)
{
  sendRawData(p_spi, cmd | SD_CMD_MSBS);

  sendRawData(p_spi, (uint8_t)(arg >> 24));
  sendRawData(p_spi, (uint8_t)(arg >> 16));
  sendRawData(p_spi, (uint8_t)(arg >> 8));
  sendRawData(p_spi, (uint8_t)(arg));
  
  sendRawData(p_spi, crc | SD_TERM_CRC);
}

// send a application command to the sdcard.
static inline void sendAppCommand(struct s_spi *p_spi, uint8_t acmd, uint32_t arg, uint8_t crc)
{
  uint8_t reponse;
  
  sendCommand(p_spi, SD_CMD55, SD_CMD_NULL_ARG, SD_CMD_NULL_CRC);
  
  reponse = recvRespOneByte(p_spi);
  //add a idle check?
  
  sendCommand(p_spi, acmd, arg, crc);
}

// recv a byte of data from the spi device.
static inline uint8_t recvRawData(struct s_spi *p_spi)
{
  sendRawData(p_spi, SD_INIT_WORD);
  
  // wait until read ready is 1, then read
  while(!getSpiReadReady(p_spi));
  
  // get the received data and return it.
  return getSpiData(p_spi);
}

// recv a response type R1 
static inline uint8_t recvRespOneByte(struct s_spi *p_spi)
{
  uint8_t byte_timeout = 0;
  uint8_t response = 0;
  
  do
  {
    response = recvRawData(p_spi);
    
    byte_timeout++;
  }
  while((response == SD_INIT_WORD) && (byte_timeout < SD_NCR_ATTEMPT));
        
  return response;
}

// recv a response that is any length, first byte will use recvRespOneByte
static inline void recvRespBytes(struct s_spi *p_spi, uint8_t *p_buff, const uint8_t num_bytes)
{
  int index;
  
  p_buff[0] = recvRespOneByte(p_spi);
  
  if(p_buff[0] == SD_INIT_WORD) return;
  
  for(index = 1; index < num_bytes; index++)
  {
    p_buff[index] = recvRawData(p_spi);
  }
}
