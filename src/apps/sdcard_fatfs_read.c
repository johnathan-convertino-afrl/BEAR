#include <base.h>

#include <pff3a/diskio.h>

#include <stdint.h>
#include <stdio.h>

int main()
{
  // int index = 0;
  int error = 0;
  
  uint8_t r_buf[512] = {0};
  
  FATFS file_sys;
  
  printf("\n\rMOUNT DRIVE\n\r");
  
  error = pf_mount(&file_sys);
  
  if(error)
  {
    printf("MOUNT FAILED, %d\n\r", error);
    
    return 0;
  }
  
  printf("OPEN TEXT\n\r");
  
  error = pf_open("input.txt");
  
  if(error)
  {
    printf("FILE OPEN FAILED, %d\n\r", error);
    return 0;
  }

  for(;;)
  {
    unsigned int index_char;
    unsigned int len;
    
    
    __delay_ms(2);
    
    error = pf_read(r_buf, 512, &len);
    
    if(error)
    {
      printf("FAILED TO READ FILE, %d\n\r", error);
      continue;
    }
    
    for(index_char = 0; index_char < len; index_char++)
    {
      if(index_char%64 == 0)
      {
        printf("\n\r");
      }
      
      
      putchar(r_buf[index_char]);
    }
    
    if(len < 512)
    {
      printf("\n\rFINISHED READING FILE\n\r");
      return 0;
    }
  }
}
