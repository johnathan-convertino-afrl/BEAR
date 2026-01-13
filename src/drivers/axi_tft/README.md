# AXI TFT Bearmetal driver
## Multitarget AXI TFT driver

---

author: Jay Convertino  

date: 2026.01.13  

license: MIT  

---

## Release Versions
### Current
  - none

### Past
  - none
  
## Info
  - This driver provides a common interface with gpio.h. Selecting a particular driver selects source that provides functionality to the declared header functions.
### Devices
  Target Devices:
  - Xilinx AXI TFT
  
### Usage
  - Use initGPIO to setup a struct at the device memory address. Use the struct to access the device registers.

### Provides
 - initAxiTft             - Initializes axi tft structure and device to defaults, no IRQ, 0 output data, ALL outputs.
 - getAxiTftVmemAddr      - get axi tft base video memory start address
 - setAxiTftVmemAddr      - set axi tft base video memory start address
 - getAxiTftDPS           - get display scan control bit, if on(1) screen is rotated 180 degrees
 - setAxiTftDPSon         - set display scan control bit to on, rotate 180 degrees
 - setAxiTftDPSoff        - set display scan control bit to off, no rotation
 - getAxiTftTDE           - get display enable bit, if on(1) screen is on.
 - setAxiTftTDEon         - set display enable control bit to on, turn on screen.
 - setAxiTftTDEoff        - set display enable controll bit to off, turn off screen.
 - setAxiTftIntrEna       - enable axi tft interrupt generation
 - unsetAxiTftIntrEna     - disable axi tft interrupt generation
 - getAxiTftStatus        - get status that doubles for address write and vsync
 - writeAxiTftVRAMbuffer  - Write buffer data to vram space
 - writeAxiTftVRAMconst   - Write constant data to vram space
