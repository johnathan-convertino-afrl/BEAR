/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2014      */
/*-----------------------------------------------------------------------*/

#include <base.h>

#include <sdcard_spi/sdcard_spi.h>

#include "diskio.h"

struct s_sdcard_spi g_sdcard_spi;

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (void)
{
  DSTATUS status;

  status = initSdcardSpi(&g_sdcard_spi, SPI_ADDR, 0);
  
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
  
  if((offset + count) > 512)
  {
    res = RES_PARERR;
    return res;
  }

  res = readSdcardSpi(&g_sdcard_spi, sector, buff, offset, count);

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
  }

  return res;
}

