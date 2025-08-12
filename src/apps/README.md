# Example Applications

Source code for FPGA baremetal example apps

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
  - sdcard_fatfs_read.c   - Read a file from a fat32 partion and print it to the screen.
  - sdcard_raw_read.c     - Read the first 512 bytes of a sdcard and print it to the screen.
  - spi_echo.c            - Loop spi data that is input to it back the device, print the value to the uart and keep going.
  - uart_echo_irq.c       - Use an IRQ to echo back received uart data.
  - uart_echo.c           - Use polling to echo back received uart data.
