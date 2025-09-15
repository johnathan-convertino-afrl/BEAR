# Zebbs (Zerostage Embedded Boot Buddy System)
## Zerostage bootloader that will read apps or uboot into memory for first stage boot or baremetal execution.

---

author: Jay Convertino  

date: 2025.09.15

license: MIT

---

## Release Versions
### Current
  - none

### Past
  - none
  
## Info
  First check for u-boot.bin, if this fails, move to app.bin. If this fails then just jump to the app address regardless.
