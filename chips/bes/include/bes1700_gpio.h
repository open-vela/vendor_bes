/************************************************************************************
 * bes1700_gpio.h
 * General Purpose Input/Output (GPIO) definitions for the BES1700
 *
 *   Copyright (C) 2009-2011, 2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __ARCH_ARM_SRC_BES_BES2001_GPIO_H
#define __ARCH_ARM_SRC_BES_BES2001_GPIO_H

/************************************************************************************
 * Included Files
 ************************************************************************************/
#include <nuttx/config.h>
/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/
/* Configuration ********************************************************************/

#undef GPIO_HAVE_PULLDOWN
#undef GPIO_HAVE_PERIPHCD
#undef GPIO_HAVE_SCHMITT
#undef GPIO_HAVE_DELAYR

/* Bit-encoded input to bes_configgpio() ********************************************/

/* 32-bit Encoding:
 *
 *   DAA MMCC CIII VPPB BBBB
 */

/* VOLTAGE_DOMAINS
*  
*/
#define GPIO_VOLD_SHIFT                24                         /* Bits 24-25: Alternate function */
#define GPIO_VOLD_MASK                 (3 << GPIO_VOLD_SHIFT)
#  define GPIO_VOLD(n)                 ((n) << GPIO_VOLD_SHIFT)
#  define GPIO_PIN_VOLTAGE_VIO         (0  << GPIO_VOLD_SHIFT) 
#  define GPIO_PIN_VOLTAGE_MEM         (1  << GPIO_VOLD_SHIFT)
#  define GPIO_PIN_VOLTAGE_VBAT        (2  << GPIO_VOLD_SHIFT)

/* supports up to 128 alternate functions per pin:
 *
 *    .... .... .... AAAA .... .... .... ....
 */
#define GPIO_ALT_SHIFT                    16                         /* Bits 16-23: Alternate function */
#define GPIO_ALT_MASK                     (0x1ff << GPIO_ALT_SHIFT)
#  define GPIO_ALT(n)                     ((n) << GPIO_ALT_SHIFT)
#  define GPIO_ALT_NONE                   (0  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_GPIO                   (1  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_AS_GPIO                (1  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_CTS           (2 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_RTS           (3 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_RX            (4 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_TX            (5 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_WCI_RX        (6 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_WCI_TX        (7 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_DNTC_IN            (8 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_DNTC_OUT           (9 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C_M0_SCL         (10 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C_M0_SDA         (11 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C_M1_SCL         (12 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C_M1_SDA         (13 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C_M2_SCL         (14 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C_M2_SDA         (15 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C_M3_SCL         (16 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C_M3_SDA         (17 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C_M4_SCL         (18 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C_M4_SDA         (19 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_MCLK          (20 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_MCLK_IN       (21 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SCK           (22 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDI0          (23 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDO           (24 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_WS            (25 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_MCLK          (26 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_MCLK_IN       (27 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SCK           (28 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDI0          (29 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDO           (30 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_WS            (31 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C_M0_SCL         (32 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C_M0_SDA         (33 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_PWM0               (34 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_PWM1               (35 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_PWM2               (36 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_PWM3               (37 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SDMMC0_CLK         (38 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SDMMC0_CMD         (39 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SDMMC0_DATA0       (40 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SDMMC0_DATA1       (41 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SDMMC0_DATA2       (42 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SDMMC0_DATA3       (43 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SDMMC0_DATA4       (44 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SDMMC0_DATA5       (45 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SDMMC0_DATA6       (46 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SDMMC0_DATA7       (47 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPDIF0_DI          (48 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPDIF0_DO          (49 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_CLK           (50 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_CS0           (51 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_CS1           (52 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_CS2           (53 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_DI0           (54 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_DI1           (55 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_DI2           (56 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_DIO           (57 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_CLK           (58 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_CS0           (59 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_CS1           (60 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_CS2           (61 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_DI0           (62 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_DI1           (63 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_DI2           (64 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_DIO           (65 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPISLV_CLK         (66 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPISLV_CS          (67 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPISLV_DIO         (68 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPISLV_DO          (69 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART0_RX           (70 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART0_TX           (71 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART1_CTS          (72 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART1_RTS          (73 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART1_RX           (74 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART1_TX           (75 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART2_CTS          (76 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART2_RTS          (77 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART2_RX           (78 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART2_TX           (79 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_32K_OUT            (80 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_OUT                (81 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_IN             (82 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_OUT            (83 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_SCL                (84 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_SDA                (85 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_RST               (86 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TCK               (87 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDI               (88 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDO               (89 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TMS               (90 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_RST1              (91 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TCK1              (92 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDI1              (93 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDO1              (94 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TMS1              (95 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_PWM                (96 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_TE0                (97 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_TE1                (98 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_TRIG               (99 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_VSYNC              (100 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_CK                (101 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_D                 (102 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_CK                (103 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_D                 (104 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_CK                (105 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_D                 (106 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PU_OSC                 (107 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PU_RC                  (108 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_CS0           (109 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_CLK           (110 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO0          (111 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO1          (112 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO2          (113 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO3          (114 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_CS0           (115 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_CLK           (116 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO0          (117 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO1          (118 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO2          (119 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO3          (120 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_DNTC_IN            (121 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_DNTC_OUT           (122 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M0_SCL         (123 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M0_SDA         (124 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M1_SCL         (125 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M1_SDA         (126 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M2_SCL         (127 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M2_SDA         (128 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M3_SCL         (129 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M3_SDA         (130 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M4_SCL         (131 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M4_SDA         (132 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_MCLK          (133 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_MCLK_IN       (134 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SCK           (135 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDI0          (136 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDO           (137 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_WS            (138 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_MCLK          (139 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_MCLK_IN       (140 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SCK           (141 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDI0          (142 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDO           (143 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_WS            (144 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I3C_M0_SCL         (145 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I3C_M0_SDA         (146 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM0               (147 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM1               (148 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM2               (149 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM3               (150 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SCI_RESET          (151 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SCI_CLK            (152 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SCI_DIO            (153 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_CLK         (154 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_CMD         (155 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA0       (156 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA1       (157 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA2       (158 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA3       (159 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA4       (160 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA5       (161 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA6       (162 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA7       (163 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPDIF0_DI          (164 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPDIF0_DO          (165 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DCN           (166 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CLK           (167 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CS0           (168 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CS1           (169 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CS2           (170 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DI0           (171 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DI1           (172 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DI2           (173 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DIO           (174 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DCN           (175 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CLK           (176 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CS0           (177 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CS1           (178 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CS2           (179 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DI0           (180 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DI1           (181 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DI2           (182 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DIO           (183 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_CLK         (184 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_CS          (185 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_DIO         (186 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_DO          (187 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART0_RX           (188 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART0_TX           (189 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_CTS          (190 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_RTS          (191 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_RX           (192 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_TX           (193 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_CTS          (194 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_RTS          (195 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_RX           (196 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_TX           (197 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_CTS            (198 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_RTS            (199 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_RX             (200 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_TX             (201 << GPIO_ALT_SHIFT)

/* Input/Output mode:
 *
 *   MM.. .... .... ....
 */

#define GPIO_MODE_SHIFT            (14)        /* Bits 14-15: GPIO mode */
#define GPIO_MODE_MASK             (3 << GPIO_MODE_SHIFT)
#  define GPIO_INPUT               (0 << GPIO_MODE_SHIFT) /* Input */
#  define GPIO_OUTPUT              (1 << GPIO_MODE_SHIFT) /* Output */
#  define GPIO_PERIPHA             (2 << GPIO_MODE_SHIFT) /* Controlled by periph A signal */
#  define GPIO_PERIPHB             (3 << GPIO_MODE_SHIFT) /* Controlled by periph B signal */

/* These bits set the configuration of the pin:
 *
 *   ..CC C... .... ....
 */

#define GPIO_CFG_SHIFT             (11)        /* Bits 11-13: GPIO configuration bits */
#define GPIO_CFG_MASK              (7 << GPIO_CFG_SHIFT)

#  define GPIO_CFG_NOPULL          (0 << GPIO_CFG_SHIFT) /* Default, no pull */
#  define GPIO_CFG_PULLUP          (1 << GPIO_CFG_SHIFT) /* Bit 11: Internal pull-up */
#  define GPIO_CFG_PULLDOWN        (2 << GPIO_CFG_SHIFT) /* Bit 12: Internal pull-down */

/* Additional interrupt modes:
 *
 *   .... .III .... ....
 */

#define GPIO_INT_SHIFT             (8)         /* Bits 8-10: GPIO interrupt bits */
#define GPIO_INT_MASK              (7 << GPIO_INT_SHIFT)
#  define _GPIO_INT_EDGE_BOTH      (1 << 10)   /* Bit 10: both edge */
#  define _GPIO_INT_LEVEL          (1 << 9)    /* Bit 9: Level detection interrupt */
#  define _GPIO_INT_EDGE           (0)         /*        (vs. Edge detection interrupt) */
#  define _GPIO_INT_RH             (1 << 8)    /* Bit 9: Rising edge/High level detection interrupt */
#  define _GPIO_INT_FL             (0)         /*        (vs. Falling edge/Low level detection interrupt) */

#  define GPIO_INT_HIGHLEVEL       (_GPIO_INT_LEVEL | _GPIO_INT_RH)
#  define GPIO_INT_LOWLEVEL        (_GPIO_INT_LEVEL | _GPIO_INT_FL)
#  define GPIO_INT_RISING          (_GPIO_INT_EDGE  | _GPIO_INT_RH)
#  define GPIO_INT_FALLING         (_GPIO_INT_EDGE  | _GPIO_INT_FL)
#  define GPIO_INT_BOTHEDGES       (_GPIO_INT_EDGE  | _GPIO_INT_EDGE_BOTH)


/* This identifies the bit in the port:
 *
 *   .... .... BBBB BBBB
 */
// port 0   Gpio[31:0] 
#define GPIO_PIN_SHIFT             0           /* Bits 0-4: GPIO number: 0-31  with interrupt*/
#define GPIO_PIN_MASK              (255 << GPIO_PIN_SHIFT)
#define GPIO_PIN0                  (0  << GPIO_PIN_SHIFT)
#define GPIO_PIN0_0                (0  << GPIO_PIN_SHIFT)
#define GPIO_PIN1                  (1  << GPIO_PIN_SHIFT)
#define GPIO_PIN0_1                (1  << GPIO_PIN_SHIFT)
#define GPIO_PIN2                  (2  << GPIO_PIN_SHIFT)
#define GPIO_PIN0_2                (2  << GPIO_PIN_SHIFT)
#define GPIO_PIN3                  (3  << GPIO_PIN_SHIFT)
#define GPIO_PIN0_3                (3  << GPIO_PIN_SHIFT)
#define GPIO_PIN4                  (4  << GPIO_PIN_SHIFT)
#define GPIO_PIN0_4                (4  << GPIO_PIN_SHIFT)
#define GPIO_PIN5                  (5  << GPIO_PIN_SHIFT)
#define GPIO_PIN0_5                (5  << GPIO_PIN_SHIFT)
#define GPIO_PIN6                  (6  << GPIO_PIN_SHIFT)
#define GPIO_PIN0_6                (6  << GPIO_PIN_SHIFT)
#define GPIO_PIN7                  (7  << GPIO_PIN_SHIFT)
#define GPIO_PIN0_7                (7  << GPIO_PIN_SHIFT)
#define GPIO_PIN8                  (8  << GPIO_PIN_SHIFT)
#define GPIO_PIN1_0                (8  << GPIO_PIN_SHIFT)
#define GPIO_PIN9                  (9  << GPIO_PIN_SHIFT)
#define GPIO_PIN1_1                (9  << GPIO_PIN_SHIFT)
#define GPIO_PIN10                 (10 << GPIO_PIN_SHIFT)
#define GPIO_PIN1_2                (10 << GPIO_PIN_SHIFT)
#define GPIO_PIN11                 (11 << GPIO_PIN_SHIFT)
#define GPIO_PIN1_3                (11 << GPIO_PIN_SHIFT)
#define GPIO_PIN12                 (12 << GPIO_PIN_SHIFT)
#define GPIO_PIN1_4                (12 << GPIO_PIN_SHIFT)
#define GPIO_PIN13                 (13 << GPIO_PIN_SHIFT)
#define GPIO_PIN1_5                (13 << GPIO_PIN_SHIFT)
#define GPIO_PIN14                 (14 << GPIO_PIN_SHIFT)
#define GPIO_PIN1_6                (14 << GPIO_PIN_SHIFT)
#define GPIO_PIN15                 (15 << GPIO_PIN_SHIFT)
#define GPIO_PIN1_7                (15 << GPIO_PIN_SHIFT)
#define GPIO_PIN16                 (16 << GPIO_PIN_SHIFT)
#define GPIO_PIN2_0                (16 << GPIO_PIN_SHIFT)
#define GPIO_PIN17                 (17 << GPIO_PIN_SHIFT)
#define GPIO_PIN2_1                (17 << GPIO_PIN_SHIFT)
#define GPIO_PIN18                 (18 << GPIO_PIN_SHIFT)
#define GPIO_PIN2_2                (18 << GPIO_PIN_SHIFT)
#define GPIO_PIN19                 (19 << GPIO_PIN_SHIFT)
#define GPIO_PIN2_3                (19 << GPIO_PIN_SHIFT)
#define GPIO_PIN20                 (20 << GPIO_PIN_SHIFT)
#define GPIO_PIN2_4                (20 << GPIO_PIN_SHIFT)
#define GPIO_PIN21                 (21 << GPIO_PIN_SHIFT)
#define GPIO_PIN2_5                (21 << GPIO_PIN_SHIFT)
#define GPIO_PIN22                 (22 << GPIO_PIN_SHIFT)
#define GPIO_PIN2_6                (22 << GPIO_PIN_SHIFT)
#define GPIO_PIN23                 (23 << GPIO_PIN_SHIFT)
#define GPIO_PIN2_7                (23 << GPIO_PIN_SHIFT)
#define GPIO_PIN24                 (24 << GPIO_PIN_SHIFT)
#define GPIO_PIN3_0                (24 << GPIO_PIN_SHIFT)
#define GPIO_PIN25                 (25 << GPIO_PIN_SHIFT)
#define GPIO_PIN3_1                (25 << GPIO_PIN_SHIFT)
#define GPIO_PIN26                 (26 << GPIO_PIN_SHIFT)
#define GPIO_PIN3_2                (26 << GPIO_PIN_SHIFT)
#define GPIO_PIN27                 (27 << GPIO_PIN_SHIFT)
#define GPIO_PIN3_3                (27 << GPIO_PIN_SHIFT)
#define GPIO_PIN28                 (28 << GPIO_PIN_SHIFT)
#define GPIO_PIN3_4                (28 << GPIO_PIN_SHIFT)
#define GPIO_PIN29                 (29 << GPIO_PIN_SHIFT)
#define GPIO_PIN3_5                (29 << GPIO_PIN_SHIFT)
#define GPIO_PIN30                 (30 << GPIO_PIN_SHIFT)
#define GPIO_PIN3_6                (30 << GPIO_PIN_SHIFT)
#define GPIO_PIN31                 (31 << GPIO_PIN_SHIFT)
#define GPIO_PIN3_7                (31 << GPIO_PIN_SHIFT)
#define GPIO_PIN32                 (32  << GPIO_PIN_SHIFT)
#define GPIO_PIN4_0                (32  << GPIO_PIN_SHIFT)
#define GPIO_PIN33                 (33  << GPIO_PIN_SHIFT)
#define GPIO_PIN4_1                (33  << GPIO_PIN_SHIFT)
#define GPIO_PIN34                 (34  << GPIO_PIN_SHIFT)
#define GPIO_PIN4_2                (34  << GPIO_PIN_SHIFT)
#define GPIO_PIN35                 (35  << GPIO_PIN_SHIFT)
#define GPIO_PIN4_3                (35  << GPIO_PIN_SHIFT)
#define GPIO_PIN36                 (36  << GPIO_PIN_SHIFT)
#define GPIO_PIN4_4                (36  << GPIO_PIN_SHIFT)
#define GPIO_PIN37                 (37  << GPIO_PIN_SHIFT)
#define GPIO_PIN4_5                (37  << GPIO_PIN_SHIFT)
#define GPIO_PIN38                 (38  << GPIO_PIN_SHIFT)
#define GPIO_PIN4_6                (38  << GPIO_PIN_SHIFT)
#define GPIO_PIN39                 (39  << GPIO_PIN_SHIFT)
#define GPIO_PIN4_7                (39  << GPIO_PIN_SHIFT)
#define GPIO_PIN40                 (40 << GPIO_PIN_SHIFT)
#define GPIO_PIN5_0                (40 << GPIO_PIN_SHIFT)
#define GPIO_PIN41                 (41 << GPIO_PIN_SHIFT)
#define GPIO_PIN5_1                (41 << GPIO_PIN_SHIFT)
#define GPIO_PIN42                 (42  << GPIO_PIN_SHIFT)
#define GPIO_PIN5_2                (42  << GPIO_PIN_SHIFT)
#define GPIO_PIN43                 (43  << GPIO_PIN_SHIFT)
#define GPIO_PIN5_3                (43  << GPIO_PIN_SHIFT)
#define GPIO_PIN44                 (44  << GPIO_PIN_SHIFT)
#define GPIO_PIN5_4                (44  << GPIO_PIN_SHIFT)
#define GPIO_PIN45                 (45  << GPIO_PIN_SHIFT)
#define GPIO_PIN5_5                (45  << GPIO_PIN_SHIFT)
#define GPIO_PIN46                 (46  << GPIO_PIN_SHIFT)
#define GPIO_PIN5_6                (46  << GPIO_PIN_SHIFT)
#define GPIO_PIN47                 (47  << GPIO_PIN_SHIFT)
#define GPIO_PIN5_7                (47  << GPIO_PIN_SHIFT)
#define GPIO_PIN48                 (48  << GPIO_PIN_SHIFT)
#define GPIO_PIN6_0                (48  << GPIO_PIN_SHIFT)
#define GPIO_PIN49                 (49  << GPIO_PIN_SHIFT)
#define GPIO_PIN6_1                (49  << GPIO_PIN_SHIFT)
#define GPIO_PIN50                 (50 << GPIO_PIN_SHIFT)
#define GPIO_PIN6_2                (50 << GPIO_PIN_SHIFT)
#define GPIO_PIN51                 (51 << GPIO_PIN_SHIFT)
#define GPIO_PIN6_3                (51 << GPIO_PIN_SHIFT)
#define GPIO_PIN52                 (52  << GPIO_PIN_SHIFT)
#define GPIO_PIN6_4                (52  << GPIO_PIN_SHIFT)
#define GPIO_PIN53                 (53  << GPIO_PIN_SHIFT)
#define GPIO_PIN6_5                (53  << GPIO_PIN_SHIFT)
#define GPIO_PIN54                 (54  << GPIO_PIN_SHIFT)
#define GPIO_PIN6_6                (54  << GPIO_PIN_SHIFT)
#define GPIO_PIN55                 (55  << GPIO_PIN_SHIFT)
#define GPIO_PIN6_7                (55  << GPIO_PIN_SHIFT)
#define GPIO_PIN56                 (56  << GPIO_PIN_SHIFT)
#define GPIO_PIN7_0                (56  << GPIO_PIN_SHIFT)
#define GPIO_PIN57                 (57  << GPIO_PIN_SHIFT)
#define GPIO_PIN7_1                (57  << GPIO_PIN_SHIFT)
#define GPIO_PIN58                 (58  << GPIO_PIN_SHIFT)
#define GPIO_PIN7_2                (58  << GPIO_PIN_SHIFT)
#define GPIO_PIN59                 (59  << GPIO_PIN_SHIFT)
#define GPIO_PIN7_3                (59  << GPIO_PIN_SHIFT)
#define GPIO_PIN60                 (60 << GPIO_PIN_SHIFT)
#define GPIO_PIN7_4                (60 << GPIO_PIN_SHIFT)
#define GPIO_PIN61                 (61 << GPIO_PIN_SHIFT)
#define GPIO_PIN7_5                (61 << GPIO_PIN_SHIFT)
#define GPIO_PIN62                 (62  << GPIO_PIN_SHIFT)
#define GPIO_PIN7_6                (62  << GPIO_PIN_SHIFT)
#define GPIO_PIN63                 (63  << GPIO_PIN_SHIFT)
#define GPIO_PIN7_7                (63  << GPIO_PIN_SHIFT)
#define GPIO_PIN64                 (64  << GPIO_PIN_SHIFT)
#define GPIO_PIN8_0                (64  << GPIO_PIN_SHIFT)
#define GPIO_PIN65                 (65  << GPIO_PIN_SHIFT)
#define GPIO_PIN8_1                (65  << GPIO_PIN_SHIFT)
#define GPIO_PIN66                 (66  << GPIO_PIN_SHIFT)
#define GPIO_PIN8_2                (66  << GPIO_PIN_SHIFT)
#define GPIO_PIN67                 (67  << GPIO_PIN_SHIFT)
#define GPIO_PIN8_3                (67  << GPIO_PIN_SHIFT)
#define GPIO_PIN68                 (68  << GPIO_PIN_SHIFT)
#define GPIO_PIN8_4                (68  << GPIO_PIN_SHIFT)
#define GPIO_PIN69                 (69  << GPIO_PIN_SHIFT)
#define GPIO_PIN8_5                (69  << GPIO_PIN_SHIFT)
#define GPIO_PIN70                 (70 << GPIO_PIN_SHIFT)
#define GPIO_PIN8_6                (70 << GPIO_PIN_SHIFT)
#define GPIO_PIN71                 (71 << GPIO_PIN_SHIFT)
#define GPIO_PIN8_7                (71 << GPIO_PIN_SHIFT)
#define GPIO_PIN72                 (72  << GPIO_PIN_SHIFT)
#define GPIO_PIN9_0                (72  << GPIO_PIN_SHIFT)
#define GPIO_PIN73                 (73  << GPIO_PIN_SHIFT)
#define GPIO_PIN9_1                (73  << GPIO_PIN_SHIFT)
#define GPIO_PIN74                 (74  << GPIO_PIN_SHIFT)
#define GPIO_PIN9_2                (74  << GPIO_PIN_SHIFT)
#define GPIO_PIN75                 (75  << GPIO_PIN_SHIFT)
#define GPIO_PIN9_3                (75  << GPIO_PIN_SHIFT)
#define GPIO_PIN76                 (76  << GPIO_PIN_SHIFT)
#define GPIO_PIN9_4                (76  << GPIO_PIN_SHIFT)
#define GPIO_PIN77                 (77  << GPIO_PIN_SHIFT)
#define GPIO_PIN9_5                (77  << GPIO_PIN_SHIFT)
#define GPIO_PIN78                 (78  << GPIO_PIN_SHIFT)
#define GPIO_PIN9_6                (78  << GPIO_PIN_SHIFT)
#define GPIO_PIN79                 (79  << GPIO_PIN_SHIFT)
#define GPIO_PIN9_7                (79  << GPIO_PIN_SHIFT)
#define GPIO_PIN80                 (80  << GPIO_PIN_SHIFT)
#define GPIO_PIN10_0               (80  << GPIO_PIN_SHIFT)
#define GPIO_PIN81                 (81  << GPIO_PIN_SHIFT)
#define GPIO_PIN10_1               (81  << GPIO_PIN_SHIFT)
#define GPIO_PIN82                 (82  << GPIO_PIN_SHIFT)
#define GPIO_PIN10_2               (82  << GPIO_PIN_SHIFT)
#define GPIO_PIN83                 (83  << GPIO_PIN_SHIFT)
#define GPIO_PIN10_3               (83  << GPIO_PIN_SHIFT)
#define GPIO_PIN84                 (84  << GPIO_PIN_SHIFT)
#define GPIO_PIN10_4               (84  << GPIO_PIN_SHIFT)
#define GPIO_PIN85                 (85  << GPIO_PIN_SHIFT)
#define GPIO_PIN10_5               (85  << GPIO_PIN_SHIFT)
#define GPIO_PIN86                 (86 << GPIO_PIN_SHIFT)
#define GPIO_PIN10_6               (86 << GPIO_PIN_SHIFT)
#define GPIO_PIN87                 (87 << GPIO_PIN_SHIFT)
#define GPIO_PIN10_7               (87 << GPIO_PIN_SHIFT)
#define GPIO_PIN88                 (88  << GPIO_PIN_SHIFT)
#define GPIO_PIN11_0               (88  << GPIO_PIN_SHIFT)
#define GPIO_PIN89                 (89  << GPIO_PIN_SHIFT)
#define GPIO_PIN11_1               (89  << GPIO_PIN_SHIFT)
#define GPIO_PIN90                 (90  << GPIO_PIN_SHIFT)
#define GPIO_PIN11_2               (90  << GPIO_PIN_SHIFT)
#define GPIO_PIN91                 (91  << GPIO_PIN_SHIFT)
#define GPIO_PIN11_3               (91  << GPIO_PIN_SHIFT)
#define GPIO_PIN92                 (92  << GPIO_PIN_SHIFT)
#define GPIO_PIN11_4               (92  << GPIO_PIN_SHIFT)
#define GPIO_PIN93                 (93  << GPIO_PIN_SHIFT)
#define GPIO_PIN11_5               (93  << GPIO_PIN_SHIFT)
#define GPIO_PIN94                 (94  << GPIO_PIN_SHIFT)
#define GPIO_PIN11_6               (94  << GPIO_PIN_SHIFT)
#define GPIO_PIN95                 (95  << GPIO_PIN_SHIFT)
#define GPIO_PIN11_7               (95  << GPIO_PIN_SHIFT)

/* LED1/2/3 */
#define GPIO_PIN96                 (96 << GPIO_PIN_SHIFT)
#define GPIO_PIN97                 (97 << GPIO_PIN_SHIFT)
#define GPIO_PIN98                 (98 << GPIO_PIN_SHIFT)

/* PMU GPIO */
#define GPIO_PIN99                 (99 << GPIO_PIN_SHIFT)
#define GPIO_PIN100                 (100 << GPIO_PIN_SHIFT)
#define GPIO_PIN101                 (101 << GPIO_PIN_SHIFT)
#define GPIO_PIN102                 (102 << GPIO_PIN_SHIFT)
#define GPIO_PIN103                 (103 << GPIO_PIN_SHIFT)
#define GPIO_PIN104                 (104 << GPIO_PIN_SHIFT)
#define GPIO_PIN105                 (105 << GPIO_PIN_SHIFT)
#define GPIO_PIN106                 (106 << GPIO_PIN_SHIFT)
#define GPIO_PIN107                 (107 << GPIO_PIN_SHIFT)
#define GPIO_PIN108                 (108 << GPIO_PIN_SHIFT)
#define GPIO_PIN109                 (109 << GPIO_PIN_SHIFT)
#define GPIO_PIN110                 (110 << GPIO_PIN_SHIFT)
#define GPIO_PIN111                 (111 << GPIO_PIN_SHIFT)
#define GPIO_PIN112                 (112 << GPIO_PIN_SHIFT)
#define GPIO_PIN113                 (113 << GPIO_PIN_SHIFT)
#define GPIO_PIN114                 (114 << GPIO_PIN_SHIFT)
#define GPIO_PIN115                 (115 << GPIO_PIN_SHIFT)
#define GPIO_PIN116                 (116 << GPIO_PIN_SHIFT)
#define GPIO_PIN117                 (117 << GPIO_PIN_SHIFT)
#define GPIO_PIN118                 (118 << GPIO_PIN_SHIFT)
#define GPIO_PIN119                 (119 << GPIO_PIN_SHIFT)
#define GPIO_PIN120                 (120 << GPIO_PIN_SHIFT)
#define GPIO_PIN121                 (121 << GPIO_PIN_SHIFT)
#define GPIO_PIN122                 (122 << GPIO_PIN_SHIFT)
#define GPIO_PIN123                 (123 << GPIO_PIN_SHIFT)
#define GPIO_PIN124                 (124 << GPIO_PIN_SHIFT)
#define GPIO_PIN125                 (125 << GPIO_PIN_SHIFT)
#define GPIO_PIN126                 (126 << GPIO_PIN_SHIFT)
#define GPIO_PIN127                 (127 << GPIO_PIN_SHIFT)
#define GPIO_PIN128                 (128 << GPIO_PIN_SHIFT)
#define GPIO_PIN129                 (129 << GPIO_PIN_SHIFT)
#define GPIO_PIN130                 (130 << GPIO_PIN_SHIFT)
#define GPIO_PIN131                 (131 << GPIO_PIN_SHIFT)
#define GPIO_PIN132                 (132 << GPIO_PIN_SHIFT)
#define GPIO_PIN133                 (133 << GPIO_PIN_SHIFT)
#define GPIO_PIN134                 (134 << GPIO_PIN_SHIFT)
#define GPIO_PIN135                 (135 << GPIO_PIN_SHIFT)
#define GPIO_PIN136                 (136 << GPIO_PIN_SHIFT)
#define GPIO_PIN137                 (137 << GPIO_PIN_SHIFT)
#define GPIO_PIN138                 (138 << GPIO_PIN_SHIFT)
#define GPIO_PIN139                 (139 << GPIO_PIN_SHIFT)
#define GPIO_PIN140                 (140 << GPIO_PIN_SHIFT)
#define GPIO_PIN141                 (141 << GPIO_PIN_SHIFT)
#define GPIO_PIN142                 (142 << GPIO_PIN_SHIFT)
#define GPIO_PIN143                 (143 << GPIO_PIN_SHIFT)
#define GPIO_PIN144                 (144 << GPIO_PIN_SHIFT)
#define GPIO_PIN145                 (145 << GPIO_PIN_SHIFT)
#define GPIO_PIN146                 (146 << GPIO_PIN_SHIFT)
#define GPIO_PIN147                 (147 << GPIO_PIN_SHIFT)
#define GPIO_PIN148                 (148 << GPIO_PIN_SHIFT)
#define GPIO_PIN149                 (149 << GPIO_PIN_SHIFT)
#define GPIO_PIN150                 (150 << GPIO_PIN_SHIFT)
#define GPIO_PIN151                 (151 << GPIO_PIN_SHIFT)
#define GPIO_PIN152                 (152 << GPIO_PIN_SHIFT)
#define GPIO_PIN153                 (153 << GPIO_PIN_SHIFT)
#define GPIO_PIN154                 (154 << GPIO_PIN_SHIFT)
#define GPIO_PIN155                 (155 << GPIO_PIN_SHIFT)
#define GPIO_PIN156                 (156 << GPIO_PIN_SHIFT)
#define GPIO_PIN157                 (157 << GPIO_PIN_SHIFT)
#define GPIO_PIN158                 (158 << GPIO_PIN_SHIFT)
#define GPIO_PIN159                 (159 << GPIO_PIN_SHIFT)
#define GPIO_PIN160                 (160 << GPIO_PIN_SHIFT)
#define GPIO_PIN161                 (161 << GPIO_PIN_SHIFT)
#define GPIO_PIN162                 (162 << GPIO_PIN_SHIFT)
#define GPIO_PIN163                 (163 << GPIO_PIN_SHIFT)

#define PIN_LED1              GPIO_PIN96
#define PIN_LED2              GPIO_PIN97
#define PIN_LED3              GPIO_PIN98

#define PMU_PIN0_0          GPIO_PIN99
#define PMU_PIN0_1          GPIO_PIN100
#define PMU_PIN0_2          GPIO_PIN101
#define PMU_PIN0_3          GPIO_PIN102
#define PMU_PIN0_4          GPIO_PIN103
#define PMU_PIN0_5          GPIO_PIN104
#define PMU_PIN0_6          GPIO_PIN105
#define PMU_PIN0_7          GPIO_PIN106
#define PMU_PIN1_0          GPIO_PIN107
#define PMU_PIN1_1          GPIO_PIN108
#define PMU_PIN1_2          GPIO_PIN109
#define PMU_PIN1_3          GPIO_PIN110
#define PMU_PIN1_4          GPIO_PIN111
#define PMU_PIN1_5          GPIO_PIN112
#define PMU_PIN1_6          GPIO_PIN113
#define PMU_PIN1_7          GPIO_PIN114
#define PMU_PIN2_0          GPIO_PIN115
#define PMU_PIN2_1          GPIO_PIN116
#define PMU_PIN2_2          GPIO_PIN117
#define PMU_PIN2_3          GPIO_PIN118
#define PMU_PIN2_4          GPIO_PIN119
#define PMU_PIN2_5          GPIO_PIN120
#define PMU_PIN2_6          GPIO_PIN121
#define PMU_PIN2_7          GPIO_PIN122
#define PMU_PIN3_0          GPIO_PIN123
#define PMU_PIN3_1          GPIO_PIN124
#define PMU_PIN3_2          GPIO_PIN125
#define PMU_PIN3_3          GPIO_PIN126
#define PMU_PIN3_4          GPIO_PIN127
#define PMU_PIN3_5          GPIO_PIN128
#define PMU_PIN3_6          GPIO_PIN129
#define PMU_PIN3_7          GPIO_PIN130
#define PMU_PIN4_0          GPIO_PIN131
#define PMU_PIN4_1          GPIO_PIN132
#define PMU_PIN4_2          GPIO_PIN133
#define PMU_PIN4_3          GPIO_PIN134
#define PMU_PIN4_4          GPIO_PIN135
#define PMU_PIN4_5          GPIO_PIN136
#define PMU_PIN4_6          GPIO_PIN137
#define PMU_PIN4_7          GPIO_PIN138
#define PMU_PIN5_0          GPIO_PIN139
#define PMU_PIN5_1          GPIO_PIN140
#define PMU_PIN5_2          GPIO_PIN141
#define PMU_PIN5_3          GPIO_PIN142
#define PMU_PIN5_4          GPIO_PIN143
#define PMU_PIN5_5          GPIO_PIN144
#define PMU_PIN5_6          GPIO_PIN145
#define PMU_PIN5_7          GPIO_PIN146
#define PMU_PIN6_0          GPIO_PIN147
#define PMU_PIN6_1          GPIO_PIN148
#define PMU_PIN6_2          GPIO_PIN149
#define PMU_PIN6_3          GPIO_PIN150
#define PMU_PIN6_4          GPIO_PIN151
#define PMU_PIN6_5          GPIO_PIN152
#define PMU_PIN6_6          GPIO_PIN153
#define PMU_PIN6_7          GPIO_PIN154
#define PMU_PIN7_0          GPIO_PIN155
#define PMU_PIN7_1          GPIO_PIN156
#define PMU_PIN7_2          GPIO_PIN157
#define PMU_PIN7_3          GPIO_PIN158
#define PMU_PIN7_4          GPIO_PIN159
#define PMU_PIN7_5          GPIO_PIN160
#define PMU_PIN7_6          GPIO_PIN161
#define PMU_PIN7_7          GPIO_PIN162
#define PMU_PIN_VCHGR       GPIO_PIN163

/************************************************************************************
 * Public Types
 ************************************************************************************/



/************************************************************************************
 * Inline Functions
 ************************************************************************************/

#ifndef __ASSEMBLY__

/************************************************************************************
 * Public Data
 ************************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/************************************************************************************
 * Public Function Prototypes
 ************************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_BES_BES2001_GPIO_H */
