# UART baremetal driver
## Multitarget UART driver

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
  - This driver provides a common interface with uart.h. Selecting a particular driver selects source that provides functionality to the declared header functions.

### Devices
  Target Devices:
  - xilinx uart lite
  - AFRL bus uart lite (emulates xilinx interface)
  
### Usage
  - Use initUart to setup a struct at the device memory address. Use the struct to access the device registers.
  
### Provides
  - initUart            ... Initializes uart structure and device
  - getUartRxData       ... Read uart rx data
  - setUartTxData       ... Write uart tx data
  - sendUartString      ... Write Strings to UART, send with \n\r terminaton
  - recvUartString      ... Read Strings from UART, with \n\r terminaton
  - getUartRxFifoFull   ... check if rx fifo is full
  - getUartRxFifoValid  ... check if rx fifo has valid data
  - getUartTxFifoEmpty  ... check if TX fifo is empty
  - getUartTxFifoFull   ... check if tx fifo is full
  - getUartIrqEna       ... check if interrupt is enabled
  - getUartError        ... check if there is an error
  - setUartResetTXfifo  ... reset tx fifo
  - setUartResetRXfifo  ... reset rx fifo
  - setUartIntrEna      ... enable uart interrupt generation
  - unsetUartIntrEna    ... disable uart interrupt generation
