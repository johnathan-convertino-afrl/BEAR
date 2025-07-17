# RISCV PLIC Driver

RISCV PLIC driver

author: Jay Convertino  

date: 2025.07.17  

license: MIT

## Release Versions
### Current
  - none

### Past
  - none
  
## Info
  Use initPlic to setup a struct at the device memory address. Use the struct to access the device registers.

  Based on the SiFive E31 core complex manual 21G1.01.00
  
  Per the above manual this core provides 127 external intterupts with 7 priority levels.
