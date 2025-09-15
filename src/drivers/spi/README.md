# SPI Baremetal Driver
## Multitarget SPI driver

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
  - This driver provides a common interface with spi.h. Selecting a particular driver selects source that provides functionality to the declared header functions.

### Devices
  Target Devices:
  - Altera SPI
  - AFRL bus spi master (emulates Altera SPI device)
  
### Usage
  - Use initSpi to setup a struct at the device memory address. Use the struct to access the device registers.

### Provides
  - initSpi                         ... Initializes spi structure and device
  - getSpiData                      ... Read spi rx data
  - setSpiData                      ... Write spi tx data
  - getSpiReadReady                 ... Ready for read?
  - getSpiWriteReady                ... Ready for a write?
  - getSpiTransmitNotActive         ... Not active to transmit when 1 (no more data to transmit).
  - getSpiFifoEnabled               ... Internal fifo enabled if 1
  - getSpiReceiveFifoResetEnabled   ... Receive Fifo is being reset
  - getSpiTransmitFifoResetEnabled  ... Transmit Fifo is being reset
  - setSpiChipSelect                ... set chip select
  - clrSpiChipSelect                ... manually clear chip select
  - setSpiForceSelect               ... manually set all chip select to active (low)
  - clrSpiForceSelect               ... manually clear set all chip select to active (low)
  - setSpiClockFreq                 ... set clock frequency, does nothing at the moment.
  - setSpiResetTXfifo               ... reset tx fifo
  - setSpiResetRXfifo               ...  reset rx fifo
  - setSpiBlockRXfifo               ... block rx fifo
  - unsetSpiBlockRXfifo             ... unblock rx fifo
  - setSpiMode                      ... set mode for CPHA/CPOL
  - setSpiIrqRxEna                  ... set rx data available(ready, status bit will match) interrupt.
  - unsetSpiIrqRxEna                ... unset rx data available(ready, status bit will match) interrupt (disable).
  - setSpiIrqTxEna                  ... set tx data available(ready, status bit will match) interrupt.
  - unsetSpiIrqTxEna                ... unset tx data available(ready, status bit will match) interrupt (disable).
