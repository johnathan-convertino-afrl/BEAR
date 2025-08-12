# Example Applications

Source code for FPGA baremetal examples

author: Jay Convertino  

date: 2025.07.17

license: MIT

## Release Versions
### Current
  - none

### Past
  - none
  
## Info
  - led_gpio_timer_irq.c  - Turn a LED on and off every second using GPIO driver.
  - pmp_write_lock_read.c - Turn on PMP protection and attempt a write to the region in machine mode.
  - sdcard_dir_list.c     - Print a list of files on a FAT16/32 sdcard over UART.
  - uart_echo_irq.c       - Use an IRQ to echo back received uart data.
  - uart_echo.c           - Use polling to echo bakc received uart data.
