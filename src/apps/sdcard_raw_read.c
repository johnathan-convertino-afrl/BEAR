#include <base.h>

#include <sdcard_spi/sdcard_spi.h>

#include <stdint.h>
#include <stdio.h>

int main()
{
  int index = 0;
  int error = 0;
  
  uint8_t r_buf[512] = {0};
  
  struct s_sdcard_spi sdcard_spi;
  
  error = initSdcardSpi(&sdcard_spi, SPI_ADDR, 0);
  
  printf("\n\r");

  printf("RAW READ STATUS, %s\n\r", getSdcardSpiStateString(&sdcard_spi));

  for(;;)
  {
    int index_char;
    
    __delay_ms(2);
    
    printf("\n\rStarting read..\n\r");
    
    // read 1 block of SD CARD data.
    for(index = 0; index < 1; index++)
    {
      error = readSdcardSpi(&sdcard_spi, index, r_buf, 0, 512);
      
      if(error)
      {
        printf("RAW READ ERROR: %s\n\r", getSdcardSpiStateString(&sdcard_spi));
        
        continue;
      }
      
      for(index_char = 0; index_char < 512; index_char++)
      {
        if(index_char == 0) printf("\n\r");
        
        if(index_char%80 == 0)
        {
          printf("\n\r");
        }
        
        putchar(r_buf[index_char]);
      }
    }
  }
}
