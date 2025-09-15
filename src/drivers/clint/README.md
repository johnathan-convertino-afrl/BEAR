# Baremetal RISCV CLINT driver
## Based on SiFive E31 mapping

---

author: Jay Convertino  

date: 2025.07.27  

license: MIT  

---

## Release Versions
### Current
  - none

### Past
  - none
  
## Info
  Use initClint to setup a struct at the device memory address. Use the struct to access the device registers.
  
  Based on the SiFive E31 core complex manual 21G1.01.00
  
  Per the above manual this core provides sofware, timer and external intterupts directly to the hart.

### Provides
  - initClint                 ... Initializes clint structure and device
  - setClintMTimeCmp          ... set clint mtime compare
  - setClintMTimeCmpOffset    ... set clint mtime compare with an offset
  - getClintMTime             ... get clint mtime
  - calcMtimecmpSeconds       ... calculate number of seconds to for mtimercmp
  - calcMtimecmpMilliseconds  ... calculate number of milliseconds to for mtimercmp
  - calcMtimecmpMicroseconds  ... calculate number of microseconds to for mtimercmp
