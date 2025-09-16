#include <base.h>

#include <beario/beario.h>
#include <sdcard_spi/sdcard_spi.h>

#include <stdint.h>

int main()
{
  int index = 0;
  int error = 0;
  
  uint8_t r_buf[512] = {0};
  
  struct s_sdcard_spi sdcard_spi;
  
  error = initSdcardSpi(&sdcard_spi, SPI_ADDR, 0);
  
  beario_printf("\n\r");

  beario_printf("RAW READ STATUS %s\n", getSdcardSpiStateString(&sdcard_spi));

  for(;;)
  {
    int index_char;
    
    __delay_ms(2);
    
    beario_printf("Starting read..\n");
    
    // read 256 KiB of SD CARD data.
    for(index = 0; index < 512; index++)
    {
      error = readSdcardSpi(&sdcard_spi, index, r_buf, 0, 512);
      
      if(error)
      {
        beario_printf("RAW READ ERROR: %s\n", getSdcardSpiStateString(&sdcard_spi));
        
        continue;
      }
      
      for(index_char = 0; index_char < 512; index_char++)
      {
        if(index_char == 0) beario_putchar('\r');
        
        if(index_char%80 == 0)
        {
          beario_putchar('\r');
        }
        
        beario_putchar(r_buf[index_char]);
      }
    }
  }
}
