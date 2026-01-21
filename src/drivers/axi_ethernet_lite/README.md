# AXI Ethernet Lite Bearmetal driver
## Multitarget AXI Ethernet Lite driver

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
  - This driver provides a common interface with axi_ethernet_lite.h. Selecting a particular driver selects source that provides functionality to the declared header functions.
### Devices
  Target Devices:
  - Xilinx AXI Ethernet Lite
  
### Usage
  - Use initAxiEthernetLite to setup a struct at the device memory address. Use the struct to access the device registers.
  - ethernetif contains the driver file needed for lwip.

### Provides
  - initAxiEthernetLite                  ... Initializes AXI ethernet lite structure and device
