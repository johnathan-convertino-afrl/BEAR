#include <base.h>

#include <axi_tft.h>

#include <stdint.h>
#include <stdio.h>

int main()
{
  uint32_t const_data = 0;
  
  uint8_t pixel = 0;
  
  uint8_t shift = 0;
  
  struct s_axi_tft *p_axi_tft = initAxiTft(TFT_ADDR);

  __delay_ms(2);
  
  setAxiTftTDEon(p_axi_tft);
  
  setAxiTftIntrEna(p_axi_tft);
  
  printf("\n\rSTARTING COLOR PIXEL WRITES\n\r");
  
  printf("\n\rVIDEO ADDRESS 0x%lx\n\r", getAxiTftVmemAddr(p_axi_tft));
  
  for(;;)
  {
    while(!getAxiTftStatus(p_axi_tft));
    
    writeAxiTftVRAMconst(p_axi_tft, 0, const_data, XRES*YRES);
    
    pixel++;
    
    const_data = (uint32_t)(pixel << (8*shift));
    
    if(pixel == 0xFF)
      shift = (shift+1)%3;
  }
}
