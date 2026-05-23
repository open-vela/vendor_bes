/************************************************************************************
 * bes1702_gpio.h
 * General Purpose Input/Output (GPIO) definitions for the BES1700
 *
 *   Copyright (C) 2009-2015, 2013 Gregory Nutt. All rights reserved.
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

#ifndef __ARCH_ARM_SRC_BES_BES1702_GPIO_H
#define __ARCH_ARM_SRC_BES_BES1702_GPIO_H

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

/* VOLTAGE_DOMAINS*/
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
#  define GPIO_ALT_BTC_SYNC_PMIC          (8 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_32K_OUT            (9 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_OUT                (10 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_IN             (11 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_OUT            (12 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_SCL                (13 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_SDA                (14 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_RST               (15 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TCK               (16 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDI               (17 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDO               (18 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TMS               (19 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_RST1              (20 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TCK1              (21 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDI1              (22 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDO1              (23 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TMS1              (24 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_PWM                (25 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_TE0                (26 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_TE1                (27 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_TRIG               (28 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_VSYNC              (29 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_CK                (30 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_D                 (31 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_CK                (32 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_D                 (33 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_CK                (34 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_D                 (35 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM3_CK                (36 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM3_D                 (37 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM4_CK                (38 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM4_D                 (39 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PU_OSC                 (40 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PU_RC                  (41 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_CS0           (42 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_CLK           (43 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO0          (44 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO1          (45 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO2          (46 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO3          (47 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_CS0           (48 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_CLK           (49 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO0          (50 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO1          (51 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO2          (52 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO3          (53 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_DNTC_IN            (54 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_DNTC_OUT           (55 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M0_SCL         (56 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M0_SDA         (57 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M1_SCL         (58 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M1_SDA         (59 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M2_SCL         (60 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M2_SDA         (61 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M3_SCL         (62 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M3_SDA         (63 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M4_SCL         (64 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M4_SDA         (65 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_MCLK          (66 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_MCLK_IN       (67 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SCK           (68 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDI0          (69 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDO0          (70 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDI1          (71 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDO1          (72 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDI2          (73 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDO2          (74 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDI3          (75 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDO3          (76 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_WS            (77 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_MCLK          (78 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_MCLK_IN       (79 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SCK           (80 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDI0          (81 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDO0          (82 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDI1          (83 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDO1          (84 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDI2          (85 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDO2          (86 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDI3          (87 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDO3          (88 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_WS            (89 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I3C_M0_SCL         (90 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I3C_M0_SDA         (91 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM0               (92 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM1               (93 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM2               (94 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM3               (95 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SCI_RESET          (96 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SCI_CLK            (97 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SCI_DIO            (98 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_CLK         (99 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_CMD         (100 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA0       (101 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA1       (102 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA2       (103 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA3       (104 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA4       (105 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA5       (106 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA6       (107 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA7       (108 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPDIF0_DI          (109 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPDIF0_DO          (110 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DCN           (111 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CLK           (112 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CS0           (113 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CS1           (114 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CS2           (115 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DI0           (116 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DI1           (117 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DI2           (118 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DIO           (119 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DCN           (120 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CLK           (121 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CS0           (122 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CS1           (123 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CS2           (124 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DI0           (125 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DI1           (126 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DI2           (127 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DIO           (128 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI2_DCN           (129 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI2_CLK           (130 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI2_CS0           (131 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI2_CS1           (132 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI2_CS2           (133 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI2_DI0           (134 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI2_DI1           (135 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI2_DI2           (136 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI2_DIO           (137 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI3_DCN           (138 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI3_CLK           (139 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI3_CS0           (140 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI3_CS1           (141 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI3_CS2           (142 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI3_DI0           (143 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI3_DI1           (144 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI3_DI2           (145 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI3_DIO           (146 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_CLK         (147 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_CS          (148 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_DIO         (149 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_DO          (150 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART0_CTS          (151 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART0_RTS          (152 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART0_RX           (153 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART0_TX           (154 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_CTS          (155 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_RTS          (156 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_RX           (157 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_TX           (158 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_CTS          (159 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_RTS          (160 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_RX           (161 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_TX           (162 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART3_CTS          (163 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART3_RTS          (164 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART3_RX           (165 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART3_TX           (166 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SOUNDWIRE_SLV_CLK  (167 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SOUNDWIRE_SLV_D    (168 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SOUNDWIRE_MST_CLK  (169 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SOUNDWIRE_MST_D    (170 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_MCLK        (171 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_PCLK        (172 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_D0          (173 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_D1          (174 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_D2          (175 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_D3          (176 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDIO_SLV_CLK       (177 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDIO_SLV_CMD       (178 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDIO_SLV_DATA0     (179 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDIO_SLV_DATA1     (180 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDIO_SLV_DATA2     (181 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDIO_SLV_DATA3     (182 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_QSPI_NAND_CLK      (183 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_QSPI_NAND_CS       (184 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_QSPI_NAND_D0       (185 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_QSPI_NAND_D0       (186 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_QSPI_NAND_D0       (187 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_QSPI_NAND_D0       (188 << GPIO_ALT_SHIFT)


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

/* LED1/2/3 */
#define GPIO_PIN64                 (64 << GPIO_PIN_SHIFT)
#define GPIO_PIN65                 (65 << GPIO_PIN_SHIFT)
#define GPIO_PIN66                 (66 << GPIO_PIN_SHIFT)

/* PMU GPIO */
#define GPIO_PIN67                 (67 << GPIO_PIN_SHIFT)
#define GPIO_PIN68                 (68 << GPIO_PIN_SHIFT)
#define GPIO_PIN69                 (69 << GPIO_PIN_SHIFT)
#define GPIO_PIN70                 (70 << GPIO_PIN_SHIFT)
#define GPIO_PIN71                 (71 << GPIO_PIN_SHIFT)
#define GPIO_PIN72                 (72 << GPIO_PIN_SHIFT)
#define GPIO_PIN73                 (73 << GPIO_PIN_SHIFT)
#define GPIO_PIN74                 (74 << GPIO_PIN_SHIFT)
#define GPIO_PIN75                 (75 << GPIO_PIN_SHIFT)
#define GPIO_PIN76                 (76 << GPIO_PIN_SHIFT)
#define GPIO_PIN77                 (77 << GPIO_PIN_SHIFT)
#define GPIO_PIN78                 (78 << GPIO_PIN_SHIFT)
#define GPIO_PIN79                 (79 << GPIO_PIN_SHIFT)
#define GPIO_PIN80                 (80 << GPIO_PIN_SHIFT)
#define GPIO_PIN81                 (81 << GPIO_PIN_SHIFT)
#define GPIO_PIN82                 (82 << GPIO_PIN_SHIFT)
#define GPIO_PIN83                 (83 << GPIO_PIN_SHIFT)
#define GPIO_PIN84                 (84 << GPIO_PIN_SHIFT)
#define GPIO_PIN85                 (85 << GPIO_PIN_SHIFT)
#define GPIO_PIN86                 (86 << GPIO_PIN_SHIFT)
#define GPIO_PIN87                 (87 << GPIO_PIN_SHIFT)
#define GPIO_PIN88                 (88 << GPIO_PIN_SHIFT)
#define GPIO_PIN89                 (89 << GPIO_PIN_SHIFT)
#define GPIO_PIN90                 (90 << GPIO_PIN_SHIFT)
#define GPIO_PIN91                 (91 << GPIO_PIN_SHIFT)
#define GPIO_PIN92                 (92 << GPIO_PIN_SHIFT)
#define GPIO_PIN93                 (93 << GPIO_PIN_SHIFT)
#define GPIO_PIN94                 (94 << GPIO_PIN_SHIFT)
#define GPIO_PIN95                 (95 << GPIO_PIN_SHIFT)
#define GPIO_PIN96                 (96 << GPIO_PIN_SHIFT)
#define GPIO_PIN97                 (97 << GPIO_PIN_SHIFT)
#define GPIO_PIN98                 (98 << GPIO_PIN_SHIFT)
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

#define PIN_LED1              GPIO_PIN64
#define PIN_LED2              GPIO_PIN65
#define PIN_LED3              GPIO_PIN66

#define PMU_PIN0_0          GPIO_PIN67
#define PMU_PIN0_1          GPIO_PIN68
#define PMU_PIN0_2          GPIO_PIN69
#define PMU_PIN0_3          GPIO_PIN70
#define PMU_PIN0_4          GPIO_PIN71
#define PMU_PIN0_5          GPIO_PIN72
#define PMU_PIN0_6          GPIO_PIN73
#define PMU_PIN0_7          GPIO_PIN74
#define PMU_PIN1_0          GPIO_PIN75
#define PMU_PIN1_1          GPIO_PIN76
#define PMU_PIN1_2          GPIO_PIN77
#define PMU_PIN1_3          GPIO_PIN78
#define PMU_PIN1_4          GPIO_PIN79
#define PMU_PIN1_5          GPIO_PIN80
#define PMU_PIN1_6          GPIO_PIN81
#define PMU_PIN1_7          GPIO_PIN82
#define PMU_PIN2_0          GPIO_PIN83
#define PMU_PIN2_1          GPIO_PIN84
#define PMU_PIN2_2          GPIO_PIN85
#define PMU_PIN2_3          GPIO_PIN86
#define PMU_PIN2_4          GPIO_PIN87
#define PMU_PIN2_5          GPIO_PIN88
#define PMU_PIN2_6          GPIO_PIN89
#define PMU_PIN2_7          GPIO_PIN90
#define PMU_PIN3_0          GPIO_PIN91
#define PMU_PIN3_1          GPIO_PIN92
#define PMU_PIN3_2          GPIO_PIN93
#define PMU_PIN3_3          GPIO_PIN94
#define PMU_PIN3_4          GPIO_PIN95
#define PMU_PIN3_5          GPIO_PIN96
#define PMU_PIN3_6          GPIO_PIN97
#define PMU_PIN3_7          GPIO_PIN98
#define PMU_PIN4_0          GPIO_PIN99
#define PMU_PIN4_1          GPIO_PIN100
#define PMU_PIN4_2          GPIO_PIN101
#define PMU_PIN4_3          GPIO_PIN102
#define PMU_PIN4_4          GPIO_PIN103
#define PMU_PIN4_5          GPIO_PIN104
#define PMU_PIN4_6          GPIO_PIN105
#define PMU_PIN4_7          GPIO_PIN106
#define PMU_PIN5_0          GPIO_PIN107
#define PMU_PIN5_1          GPIO_PIN108
#define PMU_PIN5_2          GPIO_PIN109
#define PMU_PIN5_3          GPIO_PIN110
#define PMU_PIN5_4          GPIO_PIN111
#define PMU_PIN5_5          GPIO_PIN112
#define PMU_PIN5_6          GPIO_PIN113
#define PMU_PIN5_7          GPIO_PIN114
#define PMU_PIN6_0          GPIO_PIN115
#define PMU_PIN6_1          GPIO_PIN116
#define PMU_PIN6_2          GPIO_PIN117
#define PMU_PIN6_3          GPIO_PIN118
#define PMU_PIN6_4          GPIO_PIN119
#define PMU_PIN6_5          GPIO_PIN120
#define PMU_PIN6_6          GPIO_PIN121
#define PMU_PIN6_7          GPIO_PIN122
#define PMU_PIN7_0          GPIO_PIN123
#define PMU_PIN7_1          GPIO_PIN124
#define PMU_PIN7_2          GPIO_PIN125
#define PMU_PIN7_3          GPIO_PIN126
#define PMU_PIN7_4          GPIO_PIN127
#define PMU_PIN7_5          GPIO_PIN128
#define PMU_PIN7_6          GPIO_PIN129
#define PMU_PIN7_7          GPIO_PIN130

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
