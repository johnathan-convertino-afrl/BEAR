/***************************************************************************//**
  * @file     axi_ethernet_lite.h
  * @brief    Xilinx AXI Ethernet Lite driver
  * @details  Baremetal C driver targeting Xilinx based AXI Ethernet Lite cores.
  *           Written with riscv or arm irq structure in mind.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     01/152026
  * @version
  * - 0.0.0
  *
  * @license mit
  *
  * Copyright 2026 Johnathan Convertino
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  * IN THE SOFTWARE.
  *****************************************************************************/

#ifndef __AXI_ETHERNET_LITE_MAP_H
#define __AXI_ETHERNET_LITE_MAP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct s_axi_ethernet_lite
 * @brief A struct to use for various axi tft devices. Will get memory mapped by init.
 */
struct s_axi_ethernet_lite
{
  /**
  * @var s_axi_ethernet_lite::reserved0
  * Offset in memory to the start of the address registers.
  */
  volatile uint32_t reserved0[505];

  /**
  * @union u_mdioaddr
  * @brief Register MDIOADDR with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_ethernet_lite:u_mdioaddr:reg
    * MDIO address register
    */
    volatile uint32_t reg;

    /**
    * @struct s_mdioaddr_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_ethernet_lite:u_mdioaddr:s_mdioaddr_bits:regaddr
      * Phy register address
      */
      volatile uint8_t regaddr:5;
      /**
      * @var s_axi_ethernet_lite:u_mdioaddr:s_mdioaddr_bits:phyaddr
      * Phy device address
      */
      volatile uint8_t phyaddr:5;
      /**
      * @var s_axi_ethernet_lite:u_mdioaddr:s_mdioaddr_bits:op
      * operation access
      */
      volatile uint8_t op:1;
      /**
      * @var s_axi_ethernet_lite:u_mdioaddr:s_mdioaddr_bits:reserved
      * Unused bits
      */
      volatile uint32_t reserved:21;
    } bits;
  } mdioaddr;

  /**
  * @union u_mdiowr
  * @brief Register mdiowr with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_ethernet_lite:u_mdiowr:reg
    * MDIO write register
    */
    volatile uint32_t reg;

    /**
    * @union s_mdiowr_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_ethernet_lite:u_mdiowr:s_mdiowr_bits:wr
      * 16bit word to write
      */
      volatile uint16_t wr;
      /**
      * @var s_axi_ethernet_lite:u_mdiowr:s_mdiowr_bits:reserved
      * Unused bits
      */
      volatile uint16_t reserved;
    } bits;
  } mdiowr;
  
  /**
  * @union u_mdiord
  * @brief Register mdiord with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_ethernet_lite:u_mdiord:reg
    * MDIO read register
    */
    volatile uint32_t reg;

    /**
    * @union s_mdiord_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_ethernet_lite:u_mdiord:s_mdiord_bits:rd
      * 16bit word to write
      */
      volatile uint16_t rd;
      /**
      * @var s_axi_ethernet_lite:u_mdiord:s_mdiord_bits:reserved
      * Unused bits
      */
      volatile uint16_t reserved;
    } bits;
  } mdiord;
  
  /**
  * @union u_mdioctrl
  * @brief Register MDIOCTRL with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_ethernet_lite:u_mdioaddr:reg
    * MDIO control register
    */
    volatile uint32_t reg;

    /**
    * @struct s_mdioctrl_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_ethernet_lite:u_mdioctrl:s_mdioctrl_bits:status
      * DIO status bit
      */
      volatile uint8_t status:1;
      /**
      * @var s_axi_ethernet_lite:u_mdioctrl:s_mdioctrl_bits:reserved0
      * unused
      */
      volatile uint8_t reserved0:2;
      /**
      * @var s_axi_ethernet_lite:u_mdioctrl:s_mdioctrl_bits:ena
      * enable mdio interface
      */
      volatile uint8_t ena:1;
      /**
      * @var s_axi_ethernet_lite:u_mdioctrl:s_mdioctrl_bits:reserved1
      * Unused bits
      */
      volatile uint32_t reserved1:28;
    } bits;
  } mdioctrl;
  
  /**
  * @union u_tx_ping_len
  * @brief Register tx ping length with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_ethernet_lite:u_tx_len:reg
    * Length of transmit data register
    */
    volatile uint32_t reg;

    /**
    * @union s_tx_len_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_ethernet_lite:u_tx_ping_len:s_tx_len_bits:len
      * 16bit len
      */
      volatile uint16_t len;
      /**
      * @var s_axi_ethernet_lite:u_tx_ping_len:s_tx_len_bits:reserved
      * Unused bits
      */
      volatile uint16_t reserved;
    } bits;
  } tx_ping_len;
  
  /**
  * @union u_gier
  * @brief Register gier with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_gpio:u_gier:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_gier_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_gpio:u_gier:s_gier_bits:reserver
      * Unused bits
      */
      volatile uint32_t reserved:31;
      /**
      * @var s_gpio:u_gier:s_gier_bits:gie
      * Global interupt enable bit
      */
      volatile uint8_t gie:1;
    } bits;
  } gier;
  
  /**
  * @union u_tx_ping_ctrl
  * @brief Register TX ping Control with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_ethernet_lite:u_tx_ping_ctrl:reg
    * TX control register
    */
    volatile uint32_t reg;

    /**
    * @struct s_tx_ctrl_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_ethernet_lite:u_tx_ping_ctrl:s_tx_ctrl_bits:status
      * tx status bit
      */
      volatile uint8_t status:1;
      /**
      * @var s_axi_ethernet_lite:u_tx_ping_ctrl:s_tx_ctrl_bits:program
      * set new mac address
      */
      volatile uint8_t program:1;
      /**
      * @var s_axi_ethernet_lite:u_tx_ping_ctrl:s_tx_ctrl_bits:reserved0
      * unused
      */
      volatile uint8_t reserved0:2;
      /**
      * @var s_axi_ethernet_lite:u_tx_ping_ctrl:s_tx_ctrl_bits:irq_ena
      * enable irq
      */
      volatile uint8_t irq_ena:1;
      /**
      * @var s_axi_ethernet_lite:u_tx_ping_ctrl:s_tx_ctrl_bits:loopback
      * enable loopback internal
      */
      volatile uint8_t loopback:1;
      /**
      * @var s_axi_ethernet_lite:u_tx_ping_ctrl:s_tx_ctrl_bits:reserved1
      * Unused bits
      */
      volatile uint32_t reserved1:26;
    } bits;
  } tx_ping_ctrl;
  
  /**
  * @var s_axi_ethernet_lite::reserved1
  * Offset in memory to the start of the address registers.
  */
  volatile uint32_t reserved1[509];
  
    /**
  * @union u_tx_pong_len
  * @brief Register tx pong length with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_ethernet_lite:u_tx_pong_len:reg
    * Length of transmit data register
    */
    volatile uint32_t reg;

    /**
    * @union s_tx_len_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_ethernet_lite:u_tx_pong_len:s_tx_len_bits:len
      * 16bit len
      */
      volatile uint16_t len;
      /**
      * @var s_axi_ethernet_lite:u_tx_pong_len:s_tx_len_bits:reserved
      * Unused bits
      */
      volatile uint16_t reserved;
    } bits;
  } tx_pong_len;
  
  /**
  * @union u_tx_pong_ctrl
  * @brief Register TX pong Control with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_ethernet_lite:u_tx_pong_ctrl:reg
    * TX control register
    */
    volatile uint32_t reg;

    /**
    * @struct s_tx_ctrl_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_ethernet_lite:u_tx_pong_ctrl:s_tx_ctrl_bits:status
      * tx status bit
      */
      volatile uint8_t status:1;
      /**
      * @var s_axi_ethernet_lite:u_tx_pong_ctrl:s_tx_ctrl_bits:program
      * set new mac address
      */
      volatile uint8_t program:1;
      /**
      * @var s_axi_ethernet_lite:u_tx_pong_ctrl:s_tx_ctrl_bits:reserved0
      * Unused bits
      */
      volatile uint32_t reserved0:30;
    } bits;
  } tx_pong_ctrl;
  
  /**
  * @var s_axi_ethernet_lite::reserved2
  * Offset in memory to the start of the address registers.
  */
  volatile uint32_t reserved2[511];
  
  /**
  * @union u_rx_ping_ctrl
  * @brief Register RX ping Control with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_ethernet_lite:u_rx_ping_ctrl:reg
    * RX control register
    */
    volatile uint32_t reg;

    /**
    * @struct s_rx_ping_ctrl_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_ethernet_lite:u_rx_ping_ctrl:s_rx_ctrl_bits:status
      * rx status bit
      */
      volatile uint8_t status:1;
      /**
      * @var s_axi_ethernet_lite:u_rx_ping_ctrl:s_rx_ctrl_bits:irq_ena
      * enable interrupt for rx
      */
      volatile uint8_t irq_ena:1;
      /**
      * @var s_axi_ethernet_lite:u_rx_ping_ctrl:s_rx_ctrl_bits:reserved0
      * Unused bits
      */
      volatile uint32_t reserved0:30;
    } bits;
  } rx_ping_ctrl;
  
  /**
  * @var s_axi_ethernet_lite::reserved3
  * Offset in memory to the start of the address registers.
  */
  volatile uint32_t reserved3[511];
  
  /**
  * @union u_rx_pong_ctrl
  * @brief Register RX pong Control with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_axi_ethernet_lite:u_rx_pong_ctrl:reg
    * RX control register
    */
    volatile uint32_t reg;

    /**
    * @struct s_rx_pong_ctrl_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_axi_ethernet_lite:u_rx_pong_ctrl:s_rx_ctrl_bits:status
      * rx status bit
      */
      volatile uint8_t status:1;
      /**
      * @var s_axi_ethernet_lite:u_tx_pong_ctrl:s_tx_ctrl_bits:reserved0
      * Unused bits
      */
      volatile uint32_t reserved0:31;
    } bits;
  } rx_pong_ctrl;
};

#ifdef __cplusplus
}
#endif

#endif


