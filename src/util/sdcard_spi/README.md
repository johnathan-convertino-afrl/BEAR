# SDCARD IO Over SPI
## Baremetal C functions SDCARD SPI bare read and write.
---

author: Jay Convertino  

date: 2025.09.15  

license: MIT  

---

## Release Versions
### Current
  - v0.0.0

### Past
  - none

## Info
  Functions to add SDCARD read and write over SPI.

## Provides
  - initSdcardSpi             ... Initializes sdcard over spi
  - readSdcardSpi             ... Read the sdcard over spi in 512 byte blocks for all standards.
  - writeSdcardSpi            ... Write the sdcard over spi in 512 byte blocks for all standards.
  - *getSdcardSpiStateString  ... Return a string based on the state of the device
