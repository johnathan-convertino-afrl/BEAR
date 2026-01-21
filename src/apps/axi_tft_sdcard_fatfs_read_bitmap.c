#include <base.h>

#include <beario/beario.h>
#include <bmpm/bmpm.h>
#include <axi_tft.h>
#include <pff3a/diskio.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int error = 0;
  unsigned int len;
  const int c_LEN = XRES*YRES*sizeof(uint32_t)+HEADER_SIZE;
  
  beario_printf("\n\rSTARTING BITMAP TO RAW AXI TFT DISPLAY %d\n\r", c_LEN);

  void *p_buf = malloc(c_LEN);
  
  beario_printf("\n\rMALLOC COMPLETE\n\r");
  
  FATFS file_sys;
  
  struct s_axi_tft *p_axi_tft = initAxiTft(TFT_ADDR);
  
  beario_printf("\n\rVIDEO ADDRESS 0x%x\n\r", getAxiTftVmemAddr(p_axi_tft));
  
  beario_printf("\n\rMOUNT DRIVE\n\r");
  
  error = pf_mount(&file_sys);
  
  if(error)
  {
    beario_printf("MOUNT FAILED, %d\n\r", error);
    
    return 0;
  }
  
  beario_printf("OPEN BITMAP, image.bmp\n\r");
  
  error = pf_open("image.bmp");
  
  if(error)
  {
    beario_printf("FILE OPEN FAILED, %d\n\r", error);
    return 0;
  }

  __delay_ms(2);
  
  error = pf_read(p_buf, c_LEN, &len);
  
  if(error)
  {
    beario_printf("FAILED TO READ FILE, %d\n\r", error);
    return 0;
  }
  
  beario_printf("CONVERT BITMAP TO RAW, %d\n\r", len);
  
  len = bmpmConvertToRaw(&p_buf, len);
  
  if(!len)
  {
    beario_printf("FAILED TO CONVERT FILE, %d\n\r", len);
    return 0;
  }
  
  beario_printf("WIDTH: %d HEIGHT %d WORD_LEN %d OFFSET %d FIRST_WORD 0x%x\n\r", bmpmGetWidth(), bmpmGetHeight(), len/sizeof(uint32_t), bmpmGetOffset(), *((uint32_t *)p_buf));
  
  writeAxiTftVRAMbuffer(p_axi_tft, 0, p_buf, len/sizeof(uint32_t));
  
  beario_printf("RAW IMAGE WRITTEN TO AXI TFT\n\r");
  
  for(;;)
  {
    __delay_ms(1000);
  }
  
  return 0;
}
