/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2014      */
/*-----------------------------------------------------------------------*/

#include <base.h>

#include <sdcard_spi/sdcard_spi.h>
#include <uart/uart.h>

#include "diskio.h"

static struct s_sdcard_spi g_sdcard_spi;

struct s_uart *p_uart;

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (void)
{
  DSTATUS status;
  
  // char temp[3] = {"\0"};
  
  // temp[0] = 'R';
  
  p_uart = initUart(UART_ADDR);

  status = initSdcardSpi(&g_sdcard_spi, SPI_ADDR, 0);
  
  // temp[1] = (char)(g_sdcard_spi.last_r1 + 48);
  
  // sendUartString(p_uart, temp);
  
  // temp[1] = (char)(g_sdcard_spi.state + 48);
  
  // sendUartString(p_uart, temp);
  
  // temp[1] = (char)(status + 48);
  
  // sendUartString(p_uart, temp);
  
  sendUartString(p_uart, getSdcardSpiStateString(&g_sdcard_spi));
  
  return status;
}



/*-----------------------------------------------------------------------*/
/* Read Partial Sector                                                   */
/*-----------------------------------------------------------------------*/

DRESULT disk_readp (
  BYTE* buff,		/* Pointer to the destination object */
  DWORD sector,	/* Sector number (LBA) */
  UINT offset,	/* Offset in the sector */
  UINT count		/* Byte count (bit15:destination) */
)
{
  DRESULT res;
  
  // char buffer[3] = {'\0'};
  
  if((offset + count) > 512)
  {
    res = RES_PARERR;
    return res;
  }

  res = readSdcardSpi(&g_sdcard_spi, sector, buff, offset, count);
  
//   sendUartString(p_uart, "READ RESULT");
//   
//   buffer[0] = buff[0];
//   buffer[1] = buff[1];
//   
//   sendUartString(p_uart, buffer);
	
  
  // sendUartString(p_uart, getSdcardSpiStateString(&g_sdcard_spi));

  return res;
}



/*-----------------------------------------------------------------------*/
/* Write Partial Sector                                                  */
/*-----------------------------------------------------------------------*/

DRESULT disk_writep (
  const BYTE* buff,		/* Pointer to the data to be written, NULL:Initiate/Finalize write operation */
  DWORD sc		/* Sector number (LBA) or Number of bytes to send */
)
{
  static UINT sector;
  DRESULT res;

  if(!buff) 
  {
    if(sc) 
    {
      sector = sc;
      res = RES_OK;
    }
    else
    {
      res = RES_OK;
    }
  }
  else
  {
    res = writeSdcardSpi(&g_sdcard_spi, sector, (uint8_t *)buff, sc);
    
    // if(res > 0) sendUartString(p_uart, getSdcardSpiStateString(&sdcard_spi));
  }

  return res;
}

