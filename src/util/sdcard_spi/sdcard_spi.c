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
#include <base.h>
  
#include <stdlib.h>
#include <string.h>

#include "spi.h"
#include "sdcard_spi.h"

// MAGIC
#define SD_FAST_FREQ_HZ         1000000
#define SD_SLOW_FREQ_HZ         100000
#define SD_INIT_WORD            0xFF
#define SD_BITS_PER_TRANS       8
#define SD_ATTEMPT_FACTOR       10
#define SD_ATTEMPT_SLOW         (SD_SLOW_FREQ_HZ/(SD_BITS_PER_TRANS * SD_ATTEMPT_FACTOR))
#define SD_ATTEMPT_FAST         (SD_FAST_FREQ_HZ/(SD_BITS_PER_TRANS * SD_ATTEMPT_FACTOR))
#define SD_INIT_ATTEMPT         (SD_SLOW_FREQ_HZ/(SD_ATTEMPT_FACTOR*100))
#define SD_START_TOKEN          0xFE
#define SD_DATA_ACCEPTED_TOKEN  0x05
#define SD_DATA_REJ_CRC_TOKEN   0x0B
#define SD_DATA_REJ_WRITE_TOKEN 0x0D
#define SD_DATA_ACCEPTED_MASK   0x0F
#define SD_INDEX_OFFSET_MASK    0x01FF
#define SD_ERROR_RETURN         1 //same as STA_NOINIT from ff15/petitFS
#define SD_NOERROR_RETURN       0 //same as STA_INIT from ff15/petitFS

// SIZES
#define SD_FIXED_BYTES  512 //all read/write is in 512 byte blocks for all standards.

// Commands (2 bits start, 6 bits command index)
// Start bit is 0, transmission bit is 1 (2 bits)
#define SD_CMD_MSBS 0x40
// command indexs (6 bits)
#define SD_CMD0     0x00 // 0, reset
#define SD_CMD8     0x08 // 8, request interface condition information
#define SD_CMD13    0x0D //13, request status register
#define SD_CMD16    0x10 //16, set the block length in bytes for block commands. Fixed to 512 for high capacity cards.
#define SD_CMD17    0x11 //17, Read a block of size from set block length command
#define SD_CMD24    0x18 //24, Write a block of size from set block length command
#define SD_CMD55    0x37 //55, Define next command sent as a application command
#define SD_CMD58    0x3A //58, Read the OCR register
#define SD_ACMD13   0x0D //13, request status register
#define SD_ACMD41   0x29 //41, set host cpacity support
#define SD_ACMD42   0x2A //42, set cs pullup resistor


// Fixed Arguments
#define SD_CMD_NULL_ARG 0x00000000
// 3.3 volt and AA check pattern
#define SD_CMD8_ARG     0x000001AA
// we support high capacity cards
#define SD_ACMD41_ARG   0x40000000
// enable chip select pullup
#define SD_ACMD42_ARG   0x00000001

// Fixed CRC since we will not be using it be default (bits 7:1, and 0 is set to 1 in sendCommand).
#define SD_CMD0_CRC     0x94
#define SD_CMD8_CRC     0x86
#define SD_CMD_NULL_CRC 0x00
// terminate 7 bit CRC with one for all command sends.
#define SD_TERM_CRC     0x01

// bit masks
// response one
#define SD_RESP_IDLE_BIT_MASK_R1            (1 << 0)
#define SD_RESP_ERASE_RST_BIT_MASK_R1       (1 << 1)
#define SD_RESP_ILLEGAL_CMD_BIT_MASK_R1     (1 << 2)
#define SD_RESP_COM_CRC_ERR_BIT_MASK_R1     (1 << 3)
#define SD_RESP_ERASE_SEQ_ERR_BIT_MASK_R1   (1 << 4)
#define SD_RESP_ADDR_ERR_BIT_MASK_R1        (1 << 5)
#define SD_RESP_PARAM_ERR_BIT_MASK_R1       (1 << 6)
// response three
#define SD_RESP_OCR_CCS_BIT_MASK            (1 << 6) //30, read into a uint8_t array.
#define SD_RESP_OCR_CPS_BIT_MASK            (1 << 7) //31, read into a uint8_t array.

// create some strings to return for printing messages to terminal, each lines up the enum state.
char *c_MSG_STRINGS[] =
  {
    "READY HIGH CAPACITY V2",
    "READY STANDARD CAPACITY V2",
    "READY STANDARD CAPACITY V2",
    "V1 CARD DETECTED",
    "V2 CARD DETECTED",
    "COMMAND 0, CARD RESET, FAILED",
    "COMMAND 8, INTERFACE CONDITION, FAILED",
    "VOLTAGE SETTINGS FAILED CHECK",
    "VOLTAGE RANGE FAILED CHECK",
    "CHECK PATTERN ECHO FAILED",
    "COMMAND 16, SET BLOCK LENGTH, FAILED",
    "COMMAND 58, READ OCR, FAILED",
    "APP COMMAND 41, SET HC MODE, FAILED",
    "READ HAS FAILED, TIMEOUT",
    "READ HAS FAILED, START",
    "WRITE HAS FAILED",
    "UKNOWN FAILURE",
    "NOT READY"
  };

// private function prototypes.
// send a byte of data to the spi device.
static inline void sendRawData(struct s_spi *p_spi, uint8_t data);
// send a standard command to the sdcard.
static inline void sendCommand(struct s_spi *p_spi, uint8_t cmd, uint32_t arg, uint8_t crc);
// send a application command to the sdcard.
static inline void sendAppCommand(struct s_spi *p_spi, uint8_t acmd, uint32_t arg, uint8_t crc);
// recv a byte of data from the spi device.
static inline uint8_t recvRawData(struct s_spi *p_spi);
// recv a response that is not all 0xFF (usually for R1)
static inline uint8_t recvRespOneByte(struct s_spi *p_spi, uint32_t tries);
// recv a response that is any length, first byte will use recvRespOneByte
static inline void recvRespBytes(struct s_spi *p_spi, uint8_t *p_buff, const uint8_t num_bytes, uint32_t tries);
// wait for transmission to be over and delay for a bit to hold chip select high.
static inline void waitForTrans(struct s_spi *p_spi, uint32_t len);

// Initializes sdcard over spi device for data mode
uint8_t initSdcardSpi(struct s_sdcard_spi *p_sdcard_spi, uint32_t memory_address, uint8_t cs_num)
{
  int index;
  
  int init_attempts = 0;
  
  // store SD responses from first byte to last (first 0 last 4).
  uint8_t sd_response[5] = {0};
  
  struct s_spi *p_spi = NULL;
  
  if(!p_sdcard_spi) return SD_ERROR_RETURN;
  
  memset(p_sdcard_spi, 0, sizeof(struct s_sdcard_spi));
  
  // setup spi device to use for communication.
  p_spi = initSpi(memory_address);
  
  setSpiMode(p_spi, 0, 0);
  
  setSpiClockFreq(p_spi, SD_SLOW_FREQ_HZ);
  
  //set struct members
  p_sdcard_spi->state = NOT_READY;
  p_sdcard_spi->p_spi = p_spi;
  p_sdcard_spi->cs_num = cs_num;
  
  //Try to send command 0 x times and receive idle response.
  init_attempts = SD_INIT_ATTEMPT;
  do
  {    
    if(getSpiFifoEnabled(p_spi)) setSpiResetRXfifo(p_spi);
    
    //disable chip select for 80 clock cycle write
    clrSpiChipSelect(p_spi, cs_num);
  
    // write all ones for 80 clock cycles to the SDCARD while it is NOT selected.
    for(index = 0; index < 10; index++)
    {
      sendRawData(p_spi, SD_INIT_WORD);
    }
    
    waitForTrans(p_spi, 100);
    
    if(getSpiFifoEnabled(p_spi)) setSpiResetRXfifo(p_spi);
    
    //enable chip select
    setSpiChipSelect(p_spi, cs_num);
    
    setSpiForceSelect(p_spi);
    
    //send command 0 to reset card for SPI mode
    sendCommand(p_spi, SD_CMD0, SD_CMD_NULL_ARG, SD_CMD0_CRC);
    
    p_sdcard_spi->last_r1 = recvRespOneByte(p_spi, SD_ATTEMPT_SLOW);
    
    clrSpiForceSelect(p_spi);
    
    waitForTrans(p_spi, 100);
  }
  while((--init_attempts > 0) && (p_sdcard_spi->last_r1 != SD_RESP_IDLE_BIT_MASK_R1));
        
  if((p_sdcard_spi->last_r1 != SD_RESP_IDLE_BIT_MASK_R1) && (!init_attempts))
  {
    p_sdcard_spi->state = CMD0_FAIL;
    
    return SD_ERROR_RETURN;
  }
  
  setSpiForceSelect(p_spi);
  
  //send command 8 and check response
  sendCommand(p_spi, SD_CMD8, SD_CMD8_ARG, SD_CMD8_CRC);
  
  recvRespBytes(p_spi, sd_response, 5, SD_ATTEMPT_SLOW);
  
  p_sdcard_spi->last_r1 = sd_response[0];
  
  clrSpiForceSelect(p_spi);
  
  // check if its in idle mode, and then what voltages we have, also did the check pattern echo back?
  switch(p_sdcard_spi->last_r1)
  {
    case SD_RESP_IDLE_BIT_MASK_R1:
      if(sd_response[3] != 0x01)
      {
        p_sdcard_spi->state = VOLTAGE_SET_FAIL;
        return SD_ERROR_RETURN;
      }
      if(sd_response[4] != 0xAA)
      {
        p_sdcard_spi->state = CHECK_PATTERN_FAIL;
        return SD_ERROR_RETURN;
      }
      p_sdcard_spi->state = INIT_V2;
      break;
    //if it says illegal command, then we know this is a version one card
    case SD_RESP_ILLEGAL_CMD_BIT_MASK_R1|SD_RESP_IDLE_BIT_MASK_R1:
      // card does not support V2, must be a V1
      p_sdcard_spi->state = INIT_V1;
      break;
    default:
      //unknown failure
      p_sdcard_spi->state = CMD8_FAIL;
      return SD_ERROR_RETURN;
  }

  waitForTrans(p_spi, 10);
  
  //set clock to fast
  setSpiClockFreq(p_spi, SD_FAST_FREQ_HZ);
  
  setSpiForceSelect(p_spi);
  
  //find out if voltage range is good.
  sendCommand(p_spi, SD_CMD58, SD_CMD_NULL_ARG, SD_CMD_NULL_CRC);
  
  recvRespBytes(p_spi, sd_response, 5, SD_ATTEMPT_FAST);
  
  p_sdcard_spi->last_r1 = sd_response[0];
  
  clrSpiForceSelect(p_spi);
  
  if(sd_response[2] == 0)
  {
    p_sdcard_spi->state = VOLTAGE_RANGE_FAIL;
    
    return SD_ERROR_RETURN;
  }

  waitForTrans(p_spi, 1);
  
  //send ACMD41 till we come out of idle
  init_attempts = SD_INIT_ATTEMPT;
  do
  {
    setSpiForceSelect(p_spi);
    
    //command arg for version one cards does not set high capacity. version two attempts to set this.
    sendAppCommand(p_spi, SD_ACMD41, (p_sdcard_spi->state == INIT_V2 ? SD_ACMD41_ARG : SD_CMD_NULL_ARG), SD_CMD_NULL_CRC);
    
    p_sdcard_spi->last_r1 = recvRespOneByte(p_spi, SD_ATTEMPT_FAST);
    
    clrSpiForceSelect(p_spi);
    
    waitForTrans(p_spi, 1);
    
    //if we start getting FFF something has gone wrong in the init, we can try to reset it with command 0 and see what happens.
//     if(p_sdcard_spi->last_r1 == SD_INIT_WORD)
//     {
//       setSpiForceSelect(p_spi);
//     
//       sendCommand(p_spi, SD_CMD0, SD_CMD_NULL_ARG, SD_CMD0_CRC);
//       
//       p_sdcard_spi->last_r1 = recvRespOneByte(p_spi, SD_ATTEMPT_FAST);
//       
//       clrSpiForceSelect(p_spi);
//       
//       waitForTrans(p_spi, 1);
//     }
  }
  while((--init_attempts > 0) && (p_sdcard_spi->last_r1));
  
  if(!init_attempts)
  {
    p_sdcard_spi->state = ACMD41_FAIL;
    
    return SD_ERROR_RETURN;
  }
  
  waitForTrans(p_spi, 1);
    
  setSpiForceSelect(p_spi);
  
  if(p_sdcard_spi->state == INIT_V2)
  {
    sendCommand(p_spi, SD_CMD58, SD_CMD_NULL_ARG, SD_CMD_NULL_CRC);
    
    recvRespBytes(p_spi, sd_response, 5, SD_ATTEMPT_FAST);
    
    p_sdcard_spi->last_r1 = sd_response[0];
    
    clrSpiForceSelect(p_spi);
    
    if(sd_response[1] & SD_RESP_OCR_CPS_BIT_MASK)
    {
      p_sdcard_spi->state = READY_STANDARD_CAPACITY_V2;
      p_sdcard_spi->hc    = 0;
      
      if(sd_response[1] & SD_RESP_OCR_CCS_BIT_MASK)
      {
        p_sdcard_spi->state = READY_HIGH_CAPACITY_V2;
        p_sdcard_spi->hc    = 1;
      }
    }
    else
    {
      p_sdcard_spi->state = CMD58_FAIL;
    }
    
    p_sdcard_spi->v1 = 0;
  }
  else
  {
    sendCommand(p_spi, SD_CMD16, SD_FIXED_BYTES, SD_CMD_NULL_CRC);
    
    p_sdcard_spi->last_r1 = recvRespOneByte(p_spi, SD_ATTEMPT_FAST);
    
    clrSpiForceSelect(p_spi);
    
    if(p_sdcard_spi->last_r1)
    {
      p_sdcard_spi->state = CMD16_FAIL;
      
      return SD_ERROR_RETURN;
    }
    
    p_sdcard_spi->state = READY_STANDARD_CAPACITY_V1;
    
    p_sdcard_spi->v1 = 1;
  }
  
  waitForTrans(p_spi, 10);
  
  p_sdcard_spi->last_error_token = 0;

  return SD_NOERROR_RETURN;
}

// Read the sdcard over spi in 512 byte blocks for all standards.
uint8_t readSdcardSpi(struct s_sdcard_spi *p_sdcard_spi, uint32_t address, uint8_t *p_buffer, uint16_t offset, uint16_t len)
{
  int index;
  
  volatile uint8_t crc[2];
  
  uint16_t index_offset;
  
  switch(p_sdcard_spi->state)
  {
    case READY_HIGH_CAPACITY_V2:
    case READY_STANDARD_CAPACITY_V2:
    case READY_STANDARD_CAPACITY_V1:
      break;
    default:
      return SD_ERROR_RETURN;
  }
  
  if(offset >= SD_FIXED_BYTES) return SD_ERROR_RETURN;
  
  index_offset = offset;
  
  waitForTrans(p_sdcard_spi->p_spi, 0);
  
  address = (p_sdcard_spi->v1 ? address * SD_FIXED_BYTES : address);
  
  setSpiForceSelect(p_sdcard_spi->p_spi);
  
  sendCommand(p_sdcard_spi->p_spi, SD_CMD17, address, SD_CMD_NULL_CRC);
  
  p_sdcard_spi->last_r1 = recvRespOneByte(p_sdcard_spi->p_spi, SD_ATTEMPT_FAST);
  
  if(p_sdcard_spi->last_r1 == SD_INIT_WORD) 
  {
    clrSpiForceSelect(p_sdcard_spi->p_spi);
    
    p_sdcard_spi->state = READ_FAIL_TIMEOUT;
    
    return SD_ERROR_RETURN;
  }
  
  p_sdcard_spi->last_error_token = recvRespOneByte(p_sdcard_spi->p_spi, SD_ATTEMPT_FAST);
  
  if(p_sdcard_spi->last_error_token != SD_START_TOKEN) 
  {
    clrSpiForceSelect(p_sdcard_spi->p_spi);
    
    p_sdcard_spi->state = READ_FAIL_START;
    
    return SD_ERROR_RETURN;
  }
  
  while(offset--) recvRawData(p_sdcard_spi->p_spi);
  
  for(index = 0; index < len; index++)
  {
    p_buffer[index] = recvRawData(p_sdcard_spi->p_spi);
  }
  
  while(len++ < SD_FIXED_BYTES) recvRawData(p_sdcard_spi->p_spi);
  
  crc[0] = recvRawData(p_sdcard_spi->p_spi);
  crc[1] = recvRawData(p_sdcard_spi->p_spi);
  
  clrSpiForceSelect(p_sdcard_spi->p_spi);
  
  if(getSpiFifoEnabled(p_sdcard_spi->p_spi)) setSpiResetRXfifo(p_sdcard_spi->p_spi);
  
  //check CRC in future
  return SD_NOERROR_RETURN;
}

// Write the sdcard over spi in 512 byte blocks for all standards.
uint8_t writeSdcardSpi(struct s_sdcard_spi *p_sdcard_spi, uint32_t address, uint8_t *p_buffer, uint16_t len)
{
  int index;
  
  uint8_t response;
  
  switch(p_sdcard_spi->state)
  {
    case READY_HIGH_CAPACITY_V2:
    case READY_STANDARD_CAPACITY_V2:
    case READY_STANDARD_CAPACITY_V1:
      break;
    default:
      return SD_ERROR_RETURN;
  }
  
  if(len > SD_FIXED_BYTES) return SD_ERROR_RETURN;
  
  address = (p_sdcard_spi->v1 ? address * SD_FIXED_BYTES : address);
  
  setSpiForceSelect(p_sdcard_spi->p_spi);
  
  sendCommand(p_sdcard_spi->p_spi, SD_CMD24, address, SD_CMD_NULL_CRC);
  
  p_sdcard_spi->last_r1 = recvRespOneByte(p_sdcard_spi->p_spi, SD_ATTEMPT_FAST);
  
  if(p_sdcard_spi->last_r1) 
  {
    clrSpiForceSelect(p_sdcard_spi->p_spi);
    
    p_sdcard_spi->state = WRITE_FAIL;
    
    return SD_ERROR_RETURN;
  }
  
  sendRawData(p_sdcard_spi->p_spi, SD_START_TOKEN);
  
  for(index = 0; index < len; index++)
  {
    sendRawData(p_sdcard_spi->p_spi, p_buffer[index]);
  }
  
  for(; index < SD_FIXED_BYTES; index++)
  {
    sendRawData(p_sdcard_spi->p_spi, 0x00);
  }
  
  p_sdcard_spi->last_error_token = recvRespOneByte(p_sdcard_spi->p_spi, SD_ATTEMPT_FAST);
  
  if((p_sdcard_spi->last_error_token & SD_DATA_ACCEPTED_MASK) != SD_DATA_ACCEPTED_TOKEN)
  {
    clrSpiForceSelect(p_sdcard_spi->p_spi);
    
    p_sdcard_spi->state = WRITE_FAIL;
    
    return SD_ERROR_RETURN;
  }
  
  //if 00 card is busy writing... lets wait.
  //should time this out.
  while(!recvRawData(p_sdcard_spi->p_spi));
  
  clrSpiForceSelect(p_sdcard_spi->p_spi);
  
  if(getSpiFifoEnabled(p_sdcard_spi->p_spi)) setSpiResetRXfifo(p_sdcard_spi->p_spi);
  
  return SD_NOERROR_RETURN;
}

// Return a string based on the state of the device
char *getSdcardSpiStateString(struct s_sdcard_spi *p_sdcard_spi)
{
  return c_MSG_STRINGS[p_sdcard_spi->state];
}

//below are private functions.

// send a byte of data to the spi device.
static inline void sendRawData(struct s_spi *p_spi, uint8_t data)
{
  // wait until write ready is 1, then write.
  while(!getSpiWriteReady(p_spi))
  {
    __delay(1);
  }
  
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
  
  reponse = recvRespOneByte(p_spi, SD_ATTEMPT_FAST);
  //add a idle check? and return error?
  
  waitForTrans(p_spi, 0);
  
  clrSpiForceSelect(p_spi);
  
  __delay_us(100);
  
  setSpiForceSelect(p_spi);
  
  sendCommand(p_spi, acmd, arg, crc);
}

// recv a byte of data from the spi device.
static inline uint8_t recvRawData(struct s_spi *p_spi)
{
  sendRawData(p_spi, SD_INIT_WORD);
  
  // wait until read ready is 1, then read
  while(!getSpiReadReady(p_spi))
  {
    __delay(1);
  }
  
  // get the received data and return it.
  return getSpiData(p_spi);
}

// recv a response type R1 
static inline uint8_t recvRespOneByte(struct s_spi *p_spi, uint32_t tries)
{
  uint32_t byte_tries = 0;
  uint8_t response = 0;
  
  do
  {
    response = recvRawData(p_spi);
    
    byte_tries++;
  }
  while((response == SD_INIT_WORD) && (byte_tries < tries));
        
  return response;
}

// recv a response that is any length, first byte will use recvRespOneByte
static inline void recvRespBytes(struct s_spi *p_spi, uint8_t *p_buff, const uint8_t num_bytes, uint32_t tries)
{
  int index;
  
  p_buff[0] = recvRespOneByte(p_spi, tries);
  
  if(p_buff[0] == SD_INIT_WORD) return;
  
  for(index = 1; index < num_bytes; index++)
  {
    p_buff[index] = recvRawData(p_spi);
  }
}

static inline void waitForTrans(struct s_spi *p_spi, uint32_t len)
{
  while(!getSpiTransmitNotActive(p_spi))
  {
    __delay(1);
  }
  
  __delay_us(len);
}
