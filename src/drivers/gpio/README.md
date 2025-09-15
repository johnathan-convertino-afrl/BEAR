# GPIO Bearmetal driver
## Multitarget GPIO driver

---

author: Jay Convertino  

date: 2025.07.17  

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
  - Xilinx GPIO
  - AFRL bus gpio (emulates 1 channel Xilinx GPIO)
  
### Usage
  - Use initGPIO to setup a struct at the device memory address. Use the struct to access the device registers.

### Provides
  - initGpio                  ... Initializes gpio structure and device
  - setGpioData1              ... Write data to the GPIO 1 port
  - getGpioData1              ... Read data to the GPIO 1 port
  - setGpioTriData1           ... Set GPIO tristate bits for data1 (0 output, 1 input).
  - setGpioIntrEna            ... enable gpio global interrupt generation
  - unsetGpioIntrEna          ... disable gpio global interrupt generation
  - setGpioChanOneIntrEna     ... enable gpio channel one interrupt generation
  - unsetGpioChanOneIntrEna   ... disable gpio channel one interrupt generation
  - getGpioChanOneIntrStatus  ... get channel one interrupt status
  - ackGpioChanOneIntr        ... Acknoledge the current interrupt
