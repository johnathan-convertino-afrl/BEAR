/***************************************************************************//**
  * @file     plic.h
  * @brief    RISCV PLIC driver
  * @details  Baremetal C driver targeting RISCV PLIC devices that are SiFive compliant.
  * @author   Johnathan Convertino (johnathan.convertino.1@us.af.mil)
  * @date     08/26/2024
  * @version
  * - 0.0.0
  *
  * @license mit
  *
  * Copyright 2024 Johnathan Convertino
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

#ifndef __PLIC_DRV_H
#define __PLIC_DRV_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct s_plic
 * @brief A struct to use for various plic devices. Will get memory mapped by init.
 */
struct s_plic
{
  /**
  * @var s_plic::reserv1
  * reserved 1
  */
  volatile uint32_t reserv1;
  /**
  * @var s_plic::priority1
  * irq priority reg
  */
  volatile uint32_t priority1;
  /**
  * @var s_plic::priority2
  * irq priority reg
  */
  volatile uint32_t priority2;
  /**
  * @var s_plic::priority3
  * irq priority reg
  */
  volatile uint32_t priority3;
  /**
  * @var s_plic::priority4
  * irq priority reg
  */
  volatile uint32_t priority4;
  /**
  * @var s_plic::priority5
  * irq priority reg
  */
  volatile uint32_t priority5;
  /**
  * @var s_plic::priority6
  * irq priority reg
  */
  volatile uint32_t priority6;
  /**
  * @var s_plic::priority7
  * irq priority reg
  */
  volatile uint32_t priority7;
  /**
  * @var s_plic::priority8
  * irq priority reg
  */
  volatile uint32_t priority8;
  /**
  * @var s_plic::priority9
  * irq priority reg
  */
  volatile uint32_t priority9;
  /**
  * @var s_plic::priority10
  * irq priority reg
  */
  volatile uint32_t priority10;
  /**
  * @var s_plic::priority11
  * irq priority reg
  */
  volatile uint32_t priority11;
  /**
  * @var s_plic::priority12
  * irq priority reg
  */
  volatile uint32_t priority12;
  /**
  * @var s_plic::priority13
  * irq priority reg
  */
  volatile uint32_t priority13;
  /**
  * @var s_plic::priority14
  * irq priority reg
  */
  volatile uint32_t priority14;
  /**
  * @var s_plic::priority15
  * irq priority reg
  */
  volatile uint32_t priority15;
  /**
  * @var s_plic::priority16
  * irq priority reg
  */
  volatile uint32_t priority16;
  /**
  * @var s_plic::priority17
  * irq priority reg
  */
  volatile uint32_t priority17;
  /**
  * @var s_plic::priority18
  * irq priority reg
  */
  volatile uint32_t priority18;
  /**
  * @var s_plic::priority19
  * irq priority reg
  */
  volatile uint32_t priority19;
  /**
  * @var s_plic::priority20
  * irq priority reg
  */
  volatile uint32_t priority20;
  /**
  * @var s_plic::priority21
  * irq priority reg
  */
  volatile uint32_t priority21;
  /**
  * @var s_plic::priority22
  * irq priority reg
  */
  volatile uint32_t priority22;
  /**
  * @var s_plic::priority23
  * irq priority reg
  */
  volatile uint32_t priority23;
  /**
  * @var s_plic::priority24
  * irq priority reg
  */
  volatile uint32_t priority24;
  /**
  * @var s_plic::priority25
  * irq priority reg
  */
  volatile uint32_t priority25;
  /**
  * @var s_plic::priority26
  * irq priority reg
  */
  volatile uint32_t priority26;
  /**
  * @var s_plic::priority27
  * irq priority reg
  */
  volatile uint32_t priority27;
  /**
  * @var s_plic::priority28
  * irq priority reg
  */
  volatile uint32_t priority28;
  /**
  * @var s_plic::priority29
  * irq priority reg
  */
  volatile uint32_t priority29;
  /**
  * @var s_plic::priority30
  * irq priority reg
  */
  volatile uint32_t priority30;
  /**
  * @var s_plic::priority31
  * irq priority reg
  */
  volatile uint32_t priority31;
  /**
  * @var s_plic::priority32
  * irq priority reg
  */
  volatile uint32_t priority32;
  /**
  * @var s_plic::priority33
  * irq priority reg
  */
  volatile uint32_t priority33;
  /**
  * @var s_plic::priority34
  * irq priority reg
  */
  volatile uint32_t priority34;
  /**
  * @var s_plic::priority35
  * irq priority reg
  */
  volatile uint32_t priority35;
  /**
  * @var s_plic::priority36
  * irq priority reg
  */
  volatile uint32_t priority36;
  /**
  * @var s_plic::priority37
  * irq priority reg
  */
  volatile uint32_t priority37;
  /**
  * @var s_plic::priority38
  * irq priority reg
  */
  volatile uint32_t priority38;
  /**
  * @var s_plic::priority39
  * irq priority reg
  */
  volatile uint32_t priority39;
  /**
  * @var s_plic::priority40
  * irq priority reg
  */
  volatile uint32_t priority40;
  /**
  * @var s_plic::priority41
  * irq priority reg
  */
  volatile uint32_t priority41;
  /**
  * @var s_plic::priority42
  * irq priority reg
  */
  volatile uint32_t priority42;
  /**
  * @var s_plic::priority43
  * irq priority reg
  */
  volatile uint32_t priority43;
  /**
  * @var s_plic::priority44
  * irq priority reg
  */
  volatile uint32_t priority44;
  /**
  * @var s_plic::priority45
  * irq priority reg
  */
  volatile uint32_t priority45;
  /**
  * @var s_plic::priority46
  * irq priority reg
  */
  volatile uint32_t priority46;
  /**
  * @var s_plic::priority47
  * irq priority reg
  */
  volatile uint32_t priority47;
  /**
  * @var s_plic::priority48
  * irq priority reg
  */
  volatile uint32_t priority48;
  /**
  * @var s_plic::priority49
  * irq priority reg
  */
  volatile uint32_t priority49;
  /**
  * @var s_plic::priority50
  * irq priority reg
  */
  volatile uint32_t priority50;
  /**
  * @var s_plic::priority51
  * irq priority reg
  */
  volatile uint32_t priority51;
  /**
  * @var s_plic::priority52
  * irq priority reg
  */
  volatile uint32_t priority52;
  /**
  * @var s_plic::priority53
  * irq priority reg
  */
  volatile uint32_t priority53;
  /**
  * @var s_plic::priority54
  * irq priority reg
  */
  volatile uint32_t priority54;
  /**
  * @var s_plic::priority55
  * irq priority reg
  */
  volatile uint32_t priority55;
  /**
  * @var s_plic::priority56
  * irq priority reg
  */
  volatile uint32_t priority56;
  /**
  * @var s_plic::priority57
  * irq priority reg
  */
  volatile uint32_t priority57;
  /**
  * @var s_plic::priority58
  * irq priority reg
  */
  volatile uint32_t priority58;
  /**
  * @var s_plic::priority59
  * irq priority reg
  */
  volatile uint32_t priority59;
  /**
  * @var s_plic::priority60
  * irq priority reg
  */
  volatile uint32_t priority60;
  /**
  * @var s_plic::priority61
  * irq priority reg
  */
  volatile uint32_t priority61;
  /**
  * @var s_plic::priority62
  * irq priority reg
  */
  volatile uint32_t priority62;
  /**
  * @var s_plic::priority63
  * irq priority reg
  */
  volatile uint32_t priority63;
  /**
  * @var s_plic::priority64
  * irq priority reg
  */
  volatile uint32_t priority64;
  /**
  * @var s_plic::priority65
  * irq priority reg
  */
  volatile uint32_t priority65;
  /**
  * @var s_plic::priority66
  * irq priority reg
  */
  volatile uint32_t priority66;
  /**
  * @var s_plic::priority67
  * irq priority reg
  */
  volatile uint32_t priority67;
  /**
  * @var s_plic::priority68
  * irq priority reg
  */
  volatile uint32_t priority68;
  /**
  * @var s_plic::priority69
  * irq priority reg
  */
  volatile uint32_t priority69;
  /**
  * @var s_plic::priority70
  * irq priority reg
  */
  volatile uint32_t priority70;
  /**
  * @var s_plic::priority71
  * irq priority reg
  */
  volatile uint32_t priority71;
  /**
  * @var s_plic::priority72
  * irq priority reg
  */
  volatile uint32_t priority72;
  /**
  * @var s_plic::priority73
  * irq priority reg
  */
  volatile uint32_t priority73;
  /**
  * @var s_plic::priority74
  * irq priority reg
  */
  volatile uint32_t priority74;
  /**
  * @var s_plic::priority75
  * irq priority reg
  */
  volatile uint32_t priority75;
  /**
  * @var s_plic::priority76
  * irq priority reg
  */
  volatile uint32_t priority76;
  /**
  * @var s_plic::priority77
  * irq priority reg
  */
  volatile uint32_t priority77;
  /**
  * @var s_plic::priority78
  * irq priority reg
  */
  volatile uint32_t priority78;
  /**
  * @var s_plic::priority79
  * irq priority reg
  */
  volatile uint32_t priority79;
  /**
  * @var s_plic::priority80
  * irq priority reg
  */
  volatile uint32_t priority80;
  /**
  * @var s_plic::priority81
  * irq priority reg
  */
  volatile uint32_t priority81;
  /**
  * @var s_plic::priority82
  * irq priority reg
  */
  volatile uint32_t priority82;
  /**
  * @var s_plic::priority83
  * irq priority reg
  */
  volatile uint32_t priority83;
  /**
  * @var s_plic::priority84
  * irq priority reg
  */
  volatile uint32_t priority84;
  /**
  * @var s_plic::priority85
  * irq priority reg
  */
  volatile uint32_t priority85;
  /**
  * @var s_plic::priority86
  * irq priority reg
  */
  volatile uint32_t priority86;
  /**
  * @var s_plic::priority87
  * irq priority reg
  */
  volatile uint32_t priority87;
  /**
  * @var s_plic::priority88
  * irq priority reg
  */
  volatile uint32_t priority88;
  /**
  * @var s_plic::priority89
  * irq priority reg
  */
  volatile uint32_t priority89;
  /**
  * @var s_plic::priority90
  * irq priority reg
  */
  volatile uint32_t priority90;
  /**
  * @var s_plic::priority91
  * irq priority reg
  */
  volatile uint32_t priority91;
  /**
  * @var s_plic::priority92
  * irq priority reg
  */
  volatile uint32_t priority92;
  /**
  * @var s_plic::priority93
  * irq priority reg
  */
  volatile uint32_t priority93;
  /**
  * @var s_plic::priority94
  * irq priority reg
  */
  volatile uint32_t priority94;
  /**
  * @var s_plic::priority95
  * irq priority reg
  */
  volatile uint32_t priority95;
  /**
  * @var s_plic::priority96
  * irq priority reg
  */
  volatile uint32_t priority96;
  /**
  * @var s_plic::priority97
  * irq priority reg
  */
  volatile uint32_t priority97;
  /**
  * @var s_plic::priority98
  * irq priority reg
  */
  volatile uint32_t priority98;
  /**
  * @var s_plic::priority99
  * irq priority reg
  */
  volatile uint32_t priority99;
  /**
  * @var s_plic::priority100
  * irq priority reg
  */
  volatile uint32_t priority100;
  /**
  * @var s_plic::priority101
  * irq priority reg
  */
  volatile uint32_t priority101;
  /**
  * @var s_plic::priority102
  * irq priority reg
  */
  volatile uint32_t priority102;
  /**
  * @var s_plic::priority103
  * irq priority reg
  */
  volatile uint32_t priority103;
  /**
  * @var s_plic::priority104
  * irq priority reg
  */
  volatile uint32_t priority104;
  /**
  * @var s_plic::priority105
  * irq priority reg
  */
  volatile uint32_t priority105;
  /**
  * @var s_plic::priority106
  * irq priority reg
  */
  volatile uint32_t priority106;
  /**
  * @var s_plic::priority107
  * irq priority reg
  */
  volatile uint32_t priority107;
  /**
  * @var s_plic::priority108
  * irq priority reg
  */
  volatile uint32_t priority108;
  /**
  * @var s_plic::priority109
  * irq priority reg
  */
  volatile uint32_t priority109;
  /**
  * @var s_plic::priority110
  * irq priority reg
  */
  volatile uint32_t priority110;
  /**
  * @var s_plic::priority111
  * irq priority reg
  */
  volatile uint32_t priority111;
  /**
  * @var s_plic::priority112
  * irq priority reg
  */
  volatile uint32_t priority112;
  /**
  * @var s_plic::priority113
  * irq priority reg
  */
  volatile uint32_t priority113;
  /**
  * @var s_plic::priority114
  * irq priority reg
  */
  volatile uint32_t priority114;
  /**
  * @var s_plic::priority115
  * irq priority reg
  */
  volatile uint32_t priority115;
  /**
  * @var s_plic::priority116
  * irq priority reg
  */
  volatile uint32_t priority116;
  /**
  * @var s_plic::priority117
  * irq priority reg
  */
  volatile uint32_t priority117;
  /**
  * @var s_plic::priority118
  * irq priority reg
  */
  volatile uint32_t priority118;
  /**
  * @var s_plic::priority119
  * irq priority reg
  */
  volatile uint32_t priority119;
  /**
  * @var s_plic::priority120
  * irq priority reg
  */
  volatile uint32_t priority120;
  /**
  * @var s_plic::priority121
  * irq priority reg
  */
  volatile uint32_t priority121;
  /**
  * @var s_plic::priority122
  * irq priority reg
  */
  volatile uint32_t priority122;
  /**
  * @var s_plic::priority123
  * irq priority reg
  */
  volatile uint32_t priority123;
  /**
  * @var s_plic::priority124
  * irq priority reg
  */
  volatile uint32_t priority124;
  /**
  * @var s_plic::priority125
  * irq priority reg
  */
  volatile uint32_t priority125;
  /**
  * @var s_plic::priority126
  * irq priority reg
  */
  volatile uint32_t priority126;
  /**
  * @var s_plic::priority127
  * irq priority reg
  */
  volatile uint32_t priority127;
  /**
   * @var s_plic::reserved2
   * unused regs
   */
  volatile uint32_t reserved2[896];
  /**
  * @union u_pending1
  * @brief Register pending1 with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_plic:u_pending1:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_pending1_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_plic:u_pending1:s_pending_bits:i0
      * interrupt pending
      */
      volatile uint8_t i0:1;
            /**
      * @var s_plic:u_pending1:s_pending_bits:i1
      * interrupt pending
      */
      volatile uint8_t i1:1;
            /**
      * @var s_plic:u_pending1:s_pending_bits:i2
      * interrupt pending
      */
      volatile uint8_t i2:1;
            /**
      * @var s_plic:u_pending1:s_pending_bits:i3
      * interrupt pending
      */
      volatile uint8_t i3:1;
            /**
      * @var s_plic:u_pending1:s_pending_bits:i4
      * interrupt pending
      */
      volatile uint8_t i4:1;
            /**
      * @var s_plic:u_pending1:s_pending_bits:i5
      * interrupt pending
      */
      volatile uint8_t i5:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i6
      * interrupt pending
      */
      volatile uint8_t i6:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i7
      * interrupt pending
      */
      volatile uint8_t i7:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i8
      * interrupt pending
      */
      volatile uint8_t i8:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i9
      * interrupt pending
      */
      volatile uint8_t i9:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i10
      * interrupt pending
      */
      volatile uint8_t i10:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i11
      * interrupt pending
      */
      volatile uint8_t i11:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i12
      * interrupt pending
      */
      volatile uint8_t i12:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i13
      * interrupt pending
      */
      volatile uint8_t i13:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i14
      * interrupt pending
      */
      volatile uint8_t i14:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i15
      * interrupt pending
      */
      volatile uint8_t i15:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i16
      * interrupt pending
      */
      volatile uint8_t i16:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i17
      * interrupt pending
      */
      volatile uint8_t i17:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i18
      * interrupt pending
      */
      volatile uint8_t i18:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i19
      * interrupt pending
      */
      volatile uint8_t i19:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i20
      * interrupt pending
      */
      volatile uint8_t i20:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i21
      * interrupt pending
      */
      volatile uint8_t i21:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i22
      * interrupt pending
      */
      volatile uint8_t i22:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i23
      * interrupt pending
      */
      volatile uint8_t i23:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i24
      * interrupt pending
      */
      volatile uint8_t i24:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i25
      * interrupt pending
      */
      volatile uint8_t i25:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i26
      * interrupt pending
      */
      volatile uint8_t i26:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i27
      * interrupt pending
      */
      volatile uint8_t i27:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i28
      * interrupt pending
      */
      volatile uint8_t i28:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i29
      * interrupt pending
      */
      volatile uint8_t i29:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i30
      * interrupt pending
      */
      volatile uint8_t i30:1;
      /**
      * @var s_plic:u_pending1:s_pending_bits:i31
      * interrupt pending
      */
      volatile uint8_t i31:1;
    } bits;
  } pending1;
  /**
  * @union u_pending2
  * @brief Register pending2 with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_plic:u_pending2:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_pending2_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_plic:u_pending2:s_pending_bits:i32
      * interrupt pending
      */
      volatile uint8_t i32:1;
            /**
      * @var s_plic:u_pending2:s_pending_bits:i33
      * interrupt pending
      */
      volatile uint8_t i33:1;
            /**
      * @var s_plic:u_pending2:s_pending_bits:i34
      * interrupt pending
      */
      volatile uint8_t i34:1;
            /**
      * @var s_plic:u_pending2:s_pending_bits:i35
      * interrupt pending
      */
      volatile uint8_t i35:1;
            /**
      * @var s_plic:u_pending2:s_pending_bits:i36
      * interrupt pending
      */
      volatile uint8_t i36:1;
            /**
      * @var s_plic:u_pending2:s_pending_bits:i37
      * interrupt pending
      */
      volatile uint8_t i37:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i38
      * interrupt pending
      */
      volatile uint8_t i38:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i39
      * interrupt pending
      */
      volatile uint8_t i39:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i40
      * interrupt pending
      */
      volatile uint8_t i40:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i41
      * interrupt pending
      */
      volatile uint8_t i41:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i42
      * interrupt pending
      */
      volatile uint8_t i42:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i43
      * interrupt pending
      */
      volatile uint8_t i43:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i44
      * interrupt pending
      */
      volatile uint8_t i44:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i45
      * interrupt pending
      */
      volatile uint8_t i45:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i46
      * interrupt pending
      */
      volatile uint8_t i47:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i48
      * interrupt pending
      */
      volatile uint8_t i48:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i49
      * interrupt pending
      */
      volatile uint8_t i49:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i50
      * interrupt pending
      */
      volatile uint8_t i50:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i51
      * interrupt pending
      */
      volatile uint8_t i51:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i52
      * interrupt pending
      */
      volatile uint8_t i52:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i53
      * interrupt pending
      */
      volatile uint8_t i53:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i54
      * interrupt pending
      */
      volatile uint8_t i54:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i55
      * interrupt pending
      */
      volatile uint8_t i55:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i56
      * interrupt pending
      */
      volatile uint8_t i56:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i24
      * interrupt pending
      */
      volatile uint8_t i24:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i57
      * interrupt pending
      */
      volatile uint8_t i57:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i58
      * interrupt pending
      */
      volatile uint8_t i58:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i59
      * interrupt pending
      */
      volatile uint8_t i59:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i60
      * interrupt pending
      */
      volatile uint8_t i60:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i61
      * interrupt pending
      */
      volatile uint8_t i61:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i62
      * interrupt pending
      */
      volatile uint8_t i62:1;
      /**
      * @var s_plic:u_pending2:s_pending_bits:i63
      * interrupt pending
      */
      volatile uint8_t i63:1;
    } bits;
  } pending2;
 /**
  * @union u_pending3
  * @brief Register pending3 with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_plic:u_pending3:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_pending3_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_plic:u_pending3:s_pending_bits:i64
      * interrupt pending
      */
      volatile uint8_t i64:1;
            /**
      * @var s_plic:u_pending3:s_pending_bits:i65
      * interrupt pending
      */
      volatile uint8_t i65:1;
            /**
      * @var s_plic:u_pending3:s_pending_bits:i66
      * interrupt pending
      */
      volatile uint8_t i66:1;
            /**
      * @var s_plic:u_pending3:s_pending_bits:i67
      * interrupt pending
      */
      volatile uint8_t i67:1;
            /**
      * @var s_plic:u_pending3:s_pending_bits:i68
      * interrupt pending
      */
      volatile uint8_t i68:1;
            /**
      * @var s_plic:u_pending3:s_pending_bits:i69
      * interrupt pending
      */
      volatile uint8_t i69:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i70
      * interrupt pending
      */
      volatile uint8_t i70:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i71
      * interrupt pending
      */
      volatile uint8_t i71:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i72
      * interrupt pending
      */
      volatile uint8_t i72:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i73
      * interrupt pending
      */
      volatile uint8_t i73:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i74
      * interrupt pending
      */
      volatile uint8_t i74:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i75
      * interrupt pending
      */
      volatile uint8_t i75:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i76
      * interrupt pending
      */
      volatile uint8_t i76:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i77
      * interrupt pending
      */
      volatile uint8_t i77:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i78
      * interrupt pending
      */
      volatile uint8_t i78:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i79
      * interrupt pending
      */
      volatile uint8_t i79:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i80
      * interrupt pending
      */
      volatile uint8_t i80:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i81
      * interrupt pending
      */
      volatile uint8_t i81:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i82
      * interrupt pending
      */
      volatile uint8_t i82:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i83
      * interrupt pending
      */
      volatile uint8_t i83:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i84
      * interrupt pending
      */
      volatile uint8_t i84:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i85
      * interrupt pending
      */
      volatile uint8_t i85:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i86
      * interrupt pending
      */
      volatile uint8_t i86:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i87
      * interrupt pending
      */
      volatile uint8_t i87:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i88
      * interrupt pending
      */
      volatile uint8_t i88:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i89
      * interrupt pending
      */
      volatile uint8_t i89:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i90
      * interrupt pending
      */
      volatile uint8_t i90:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i91
      * interrupt pending
      */
      volatile uint8_t i91:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i92
      * interrupt pending
      */
      volatile uint8_t i92:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i93
      * interrupt pending
      */
      volatile uint8_t i93:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i94
      * interrupt pending
      */
      volatile uint8_t i94:1;
      /**
      * @var s_plic:u_pending3:s_pending_bits:i95
      * interrupt pending
      */
      volatile uint8_t i95:1;
    } bits;
  } pending3;
 /**
  * @union u_pending4
  * @brief Register pending4 with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_plic:u_pending4:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_pending4_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_plic:u_pending4:s_pending_bits:i96
      * interrupt pending
      */
      volatile uint8_t i96:1;
            /**
      * @var s_plic:u_pending4:s_pending_bits:i97
      * interrupt pending
      */
      volatile uint8_t i97:1;
            /**
      * @var s_plic:u_pending4:s_pending_bits:i98
      * interrupt pending
      */
      volatile uint8_t i98:1;
            /**
      * @var s_plic:u_pending4:s_pending_bits:i99
      * interrupt pending
      */
      volatile uint8_t i99:1;
            /**
      * @var s_plic:u_pending4:s_pending_bits:i100
      * interrupt pending
      */
      volatile uint8_t i100:1;
            /**
      * @var s_plic:u_pending4:s_pending_bits:i101
      * interrupt pending
      */
      volatile uint8_t i101:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i102
      * interrupt pending
      */
      volatile uint8_t i102:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i103
      * interrupt pending
      */
      volatile uint8_t i103:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i104
      * interrupt pending
      */
      volatile uint8_t i104:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i105
      * interrupt pending
      */
      volatile uint8_t i105:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i106
      * interrupt pending
      */
      volatile uint8_t i106:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i107
      * interrupt pending
      */
      volatile uint8_t i107:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i108
      * interrupt pending
      */
      volatile uint8_t i108:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i109
      * interrupt pending
      */
      volatile uint8_t i109:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i110
      * interrupt pending
      */
      volatile uint8_t i110:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i111
      * interrupt pending
      */
      volatile uint8_t i111:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i112
      * interrupt pending
      */
      volatile uint8_t i112:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i113
      * interrupt pending
      */
      volatile uint8_t i113:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i114
      * interrupt pending
      */
      volatile uint8_t i114:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i115
      * interrupt pending
      */
      volatile uint8_t i115:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i116
      * interrupt pending
      */
      volatile uint8_t i116:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i117
      * interrupt pending
      */
      volatile uint8_t i117:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i118
      * interrupt pending
      */
      volatile uint8_t i118:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i119
      * interrupt pending
      */
      volatile uint8_t i119:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i120
      * interrupt pending
      */
      volatile uint8_t i120:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i121
      * interrupt pending
      */
      volatile uint8_t i121:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i122
      * interrupt pending
      */
      volatile uint8_t i122:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i123
      * interrupt pending
      */
      volatile uint8_t i123:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i124
      * interrupt pending
      */
      volatile uint8_t i124:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i125
      * interrupt pending
      */
      volatile uint8_t i125:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i126
      * interrupt pending
      */
      volatile uint8_t i126:1;
      /**
      * @var s_plic:u_pending4:s_pending_bits:i127
      * interrupt pending
      */
      volatile uint8_t i127:1;
    } bits;
  } pending4;
  /**
  * @var s_plic::reserved3
  * unused regs
  */
  volatile uint32_t reserved3[1020];
  /**
  * @union u_enable1
  * @brief Register enable1 with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_plic:u_enable1:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_enable1_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_plic:u_enable1:s_enable_bits:i0
      * interrupt enable
      */
      volatile uint8_t i0:1;
            /**
      * @var s_plic:u_enable1:s_enable_bits:i1
      * interrupt enable
      */
      volatile uint8_t i1:1;
            /**
      * @var s_plic:u_enable1:s_enable_bits:i2
      * interrupt enable
      */
      volatile uint8_t i2:1;
            /**
      * @var s_plic:u_enable1:s_enable_bits:i3
      * interrupt enable
      */
      volatile uint8_t i3:1;
            /**
      * @var s_plic:u_enable1:s_enable_bits:i4
      * interrupt enable
      */
      volatile uint8_t i4:1;
            /**
      * @var s_plic:u_enable1:s_enable_bits:i5
      * interrupt enable
      */
      volatile uint8_t i5:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i6
      * interrupt enable
      */
      volatile uint8_t i6:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i7
      * interrupt enable
      */
      volatile uint8_t i7:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i8
      * interrupt enable
      */
      volatile uint8_t i8:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i9
      * interrupt enable
      */
      volatile uint8_t i9:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i10
      * interrupt enable
      */
      volatile uint8_t i10:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i11
      * interrupt enable
      */
      volatile uint8_t i11:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i12
      * interrupt enable
      */
      volatile uint8_t i12:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i13
      * interrupt enable
      */
      volatile uint8_t i13:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i14
      * interrupt enable
      */
      volatile uint8_t i14:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i15
      * interrupt enable
      */
      volatile uint8_t i15:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i16
      * interrupt enable
      */
      volatile uint8_t i16:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i17
      * interrupt enable
      */
      volatile uint8_t i17:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i18
      * interrupt enable
      */
      volatile uint8_t i18:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i19
      * interrupt enable
      */
      volatile uint8_t i19:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i20
      * interrupt enable
      */
      volatile uint8_t i20:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i21
      * interrupt enable
      */
      volatile uint8_t i21:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i22
      * interrupt enable
      */
      volatile uint8_t i22:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i23
      * interrupt enable
      */
      volatile uint8_t i23:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i24
      * interrupt enable
      */
      volatile uint8_t i24:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i25
      * interrupt enable
      */
      volatile uint8_t i25:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i26
      * interrupt enable
      */
      volatile uint8_t i26:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i27
      * interrupt enable
      */
      volatile uint8_t i27:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i28
      * interrupt enable
      */
      volatile uint8_t i28:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i29
      * interrupt enable
      */
      volatile uint8_t i29:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i30
      * interrupt enable
      */
      volatile uint8_t i30:1;
      /**
      * @var s_plic:u_enable1:s_enable_bits:i31
      * interrupt enable
      */
      volatile uint8_t i31:1;
    } bits;
  } enable1;
  /**
  * @union u_enable2
  * @brief Register enable2 with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_plic:u_enable2:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_enable2_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_plic:u_enable2:s_enable_bits:i32
      * interrupt enable
      */
      volatile uint8_t i32:1;
            /**
      * @var s_plic:u_enable2:s_enable_bits:i33
      * interrupt enable
      */
      volatile uint8_t i33:1;
            /**
      * @var s_plic:u_enable2:s_enable_bits:i34
      * interrupt enable
      */
      volatile uint8_t i34:1;
            /**
      * @var s_plic:u_enable2:s_enable_bits:i35
      * interrupt enable
      */
      volatile uint8_t i35:1;
            /**
      * @var s_plic:u_enable2:s_enable_bits:i36
      * interrupt enable
      */
      volatile uint8_t i36:1;
            /**
      * @var s_plic:u_enable2:s_enable_bits:i37
      * interrupt enable
      */
      volatile uint8_t i37:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i38
      * interrupt enable
      */
      volatile uint8_t i38:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i39
      * interrupt enable
      */
      volatile uint8_t i39:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i40
      * interrupt enable
      */
      volatile uint8_t i40:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i41
      * interrupt enable
      */
      volatile uint8_t i41:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i42
      * interrupt enable
      */
      volatile uint8_t i42:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i43
      * interrupt enable
      */
      volatile uint8_t i43:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i44
      * interrupt enable
      */
      volatile uint8_t i44:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i45
      * interrupt enable
      */
      volatile uint8_t i45:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i46
      * interrupt enable
      */
      volatile uint8_t i47:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i48
      * interrupt enable
      */
      volatile uint8_t i48:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i49
      * interrupt enable
      */
      volatile uint8_t i49:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i50
      * interrupt enable
      */
      volatile uint8_t i50:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i51
      * interrupt enable
      */
      volatile uint8_t i51:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i52
      * interrupt enable
      */
      volatile uint8_t i52:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i53
      * interrupt enable
      */
      volatile uint8_t i53:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i54
      * interrupt enable
      */
      volatile uint8_t i54:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i55
      * interrupt enable
      */
      volatile uint8_t i55:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i56
      * interrupt enable
      */
      volatile uint8_t i56:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i24
      * interrupt enable
      */
      volatile uint8_t i24:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i57
      * interrupt enable
      */
      volatile uint8_t i57:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i58
      * interrupt enable
      */
      volatile uint8_t i58:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i59
      * interrupt enable
      */
      volatile uint8_t i59:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i60
      * interrupt enable
      */
      volatile uint8_t i60:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i61
      * interrupt enable
      */
      volatile uint8_t i61:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i62
      * interrupt enable
      */
      volatile uint8_t i62:1;
      /**
      * @var s_plic:u_enable2:s_enable_bits:i63
      * interrupt enable
      */
      volatile uint8_t i63:1;
    } bits;
  } enable2;
 /**
  * @union u_enable3
  * @brief Register enable3 with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_plic:u_enable3:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_enable3_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_plic:u_enable3:s_enable_bits:i64
      * interrupt enable
      */
      volatile uint8_t i64:1;
            /**
      * @var s_plic:u_enable3:s_enable_bits:i65
      * interrupt enable
      */
      volatile uint8_t i65:1;
            /**
      * @var s_plic:u_enable3:s_enable_bits:i66
      * interrupt enable
      */
      volatile uint8_t i66:1;
            /**
      * @var s_plic:u_enable3:s_enable_bits:i67
      * interrupt enable
      */
      volatile uint8_t i67:1;
            /**
      * @var s_plic:u_enable3:s_enable_bits:i68
      * interrupt enable
      */
      volatile uint8_t i68:1;
            /**
      * @var s_plic:u_enable3:s_enable_bits:i69
      * interrupt enable
      */
      volatile uint8_t i69:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i70
      * interrupt enable
      */
      volatile uint8_t i70:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i71
      * interrupt enable
      */
      volatile uint8_t i71:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i72
      * interrupt enable
      */
      volatile uint8_t i72:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i73
      * interrupt enable
      */
      volatile uint8_t i73:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i74
      * interrupt enable
      */
      volatile uint8_t i74:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i75
      * interrupt enable
      */
      volatile uint8_t i75:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i76
      * interrupt enable
      */
      volatile uint8_t i76:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i77
      * interrupt enable
      */
      volatile uint8_t i77:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i78
      * interrupt enable
      */
      volatile uint8_t i78:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i79
      * interrupt enable
      */
      volatile uint8_t i79:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i80
      * interrupt enable
      */
      volatile uint8_t i80:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i81
      * interrupt enable
      */
      volatile uint8_t i81:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i82
      * interrupt enable
      */
      volatile uint8_t i82:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i83
      * interrupt enable
      */
      volatile uint8_t i83:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i84
      * interrupt enable
      */
      volatile uint8_t i84:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i85
      * interrupt enable
      */
      volatile uint8_t i85:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i86
      * interrupt enable
      */
      volatile uint8_t i86:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i87
      * interrupt enable
      */
      volatile uint8_t i87:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i88
      * interrupt enable
      */
      volatile uint8_t i88:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i89
      * interrupt enable
      */
      volatile uint8_t i89:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i90
      * interrupt enable
      */
      volatile uint8_t i90:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i91
      * interrupt enable
      */
      volatile uint8_t i91:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i92
      * interrupt enable
      */
      volatile uint8_t i92:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i93
      * interrupt enable
      */
      volatile uint8_t i93:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i94
      * interrupt enable
      */
      volatile uint8_t i94:1;
      /**
      * @var s_plic:u_enable3:s_enable_bits:i95
      * interrupt enable
      */
      volatile uint8_t i95:1;
    } bits;
  } enable3;
  /**
  * @union u_enable4
  * @brief Register enable4 with packed struct to access individual bits
  */
  union
  {
    /**
    * @var s_plic:u_enable4:reg
    * Global interupt register
    */
    volatile uint32_t reg;

    /**
    * @union s_enable4_bits
    * @brief packed struct with bits.
    */
    struct
    {
      /**
      * @var s_plic:u_enable4:s_enable_bits:i96
      * interrupt enable
      */
      volatile uint8_t i96:1;
            /**
      * @var s_plic:u_enable4:s_enable_bits:i97
      * interrupt enable
      */
      volatile uint8_t i97:1;
            /**
      * @var s_plic:u_enable4:s_enable_bits:i98
      * interrupt enable
      */
      volatile uint8_t i98:1;
            /**
      * @var s_plic:u_enable4:s_enable_bits:i99
      * interrupt enable
      */
      volatile uint8_t i99:1;
            /**
      * @var s_plic:u_enable4:s_enable_bits:i100
      * interrupt enable
      */
      volatile uint8_t i100:1;
            /**
      * @var s_plic:u_enable4:s_enable_bits:i101
      * interrupt enable
      */
      volatile uint8_t i101:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i102
      * interrupt enable
      */
      volatile uint8_t i102:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i103
      * interrupt enable
      */
      volatile uint8_t i103:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i104
      * interrupt enable
      */
      volatile uint8_t i104:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i105
      * interrupt enable
      */
      volatile uint8_t i105:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i106
      * interrupt enable
      */
      volatile uint8_t i106:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i107
      * interrupt enable
      */
      volatile uint8_t i107:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i108
      * interrupt enable
      */
      volatile uint8_t i108:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i109
      * interrupt enable
      */
      volatile uint8_t i109:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i110
      * interrupt enable
      */
      volatile uint8_t i110:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i111
      * interrupt enable
      */
      volatile uint8_t i111:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i112
      * interrupt enable
      */
      volatile uint8_t i112:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i113
      * interrupt enable
      */
      volatile uint8_t i113:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i114
      * interrupt enable
      */
      volatile uint8_t i114:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i115
      * interrupt enable
      */
      volatile uint8_t i115:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i116
      * interrupt enable
      */
      volatile uint8_t i116:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i117
      * interrupt enable
      */
      volatile uint8_t i117:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i118
      * interrupt enable
      */
      volatile uint8_t i118:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i119
      * interrupt enable
      */
      volatile uint8_t i119:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i120
      * interrupt enable
      */
      volatile uint8_t i120:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i121
      * interrupt enable
      */
      volatile uint8_t i121:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i122
      * interrupt enable
      */
      volatile uint8_t i122:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i123
      * interrupt enable
      */
      volatile uint8_t i123:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i124
      * interrupt enable
      */
      volatile uint8_t i124:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i125
      * interrupt enable
      */
      volatile uint8_t i125:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i126
      * interrupt enable
      */
      volatile uint8_t i126:1;
      /**
      * @var s_plic:u_enable4:s_enable_bits:i127
      * interrupt enable
      */
      volatile uint8_t i127:1;
    } bits;
  } enable4;
  /**
  * @var s_plic::reserved4
  * unused regs
  */
  volatile uint32_t reserved4[522236];
  /**
  * @var s_plic::threshold
  * threshold
  */
  volatile uint32_t threshold;
  /**
  * @var s_plic::claim
  * claim
  */
  volatile uint32_t claim;
};

/*********************************************//**
  * @brief Initializes plic structure and device
  * to defaults, no IRQ.
  *
  * @param memory_address is the starting memory_address
  * of the gpio on the system bus.
  *
  * @return s_plic is a struct with a pointer to the
  * device memory address
  *************************************************/
struct s_plic *initPlic(uint32_t memory_address);

#ifdef __cplusplus
}
#endif

#endif

