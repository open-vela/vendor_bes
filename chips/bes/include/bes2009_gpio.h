/************************************************************************************
 * rtos/nuttx/include/arch/chip/bes2009_gpio.h
 * General Purpose Input/Output (GPIO) definitions for the BES2001
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

#ifndef __ARCH_ARM_SRC_BES_BES2009_GPIO_H
#define __ARCH_ARM_SRC_BES_BES2009_GPIO_H

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
#define GPIO_VOLD_SHIFT                25                         /* Bits 25-26: Alternate function */
#define GPIO_VOLD_MASK                 (3 << GPIO_VOLD_SHIFT)
#  define GPIO_VOLD(n)                 ((n) << GPIO_VOLD_SHIFT)
#  define GPIO_PIN_VOLTAGE_VIO         (0  << GPIO_VOLD_SHIFT)
#  define GPIO_PIN_VOLTAGE_MEM         (1  << GPIO_VOLD_SHIFT)
#  define GPIO_PIN_VOLTAGE_VBAT        (2  << GPIO_VOLD_SHIFT)

/* supports up to 128 alternate functions per pin:
 *
 *    .... .... .... AAAA .... .... .... ....
 */

#define GPIO_ALT_SHIFT                      16                         /* Bits 16-24: Alternate function */
#define GPIO_ALT_MASK                       (255 << GPIO_ALT_SHIFT)
#  define GPIO_ALT(n)                       ((n) << GPIO_ALT_SHIFT)
#  define GPIO_ALT_NONE                     (0  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_GPIO                     (1  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_AS_GPIO                  (1  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_CTS              (2  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_RTS              (3  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_RX               (4  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_TX               (5  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_32K_IN               (6  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_IN               (7  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_OUT              (8  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_OUT                  (9  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M0_SCL               (10  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M0_SDA               (11  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M1_SCL               (12  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M2_SCL               (13  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M2_SDA               (14  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M1_SDA               (15  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S_MCLK                 (16  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SCK                 (17  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDI0                (18  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDI1                (19  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDI2                (20  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDI3                (21  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDO0                (22  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDO1                (23  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDO2                (24  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDO3                (25  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_WS                  (26  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SCK                 (27  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDI0                (28  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDI1                (29  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDI2                (30  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDI3                (31  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDO0                (32  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDO1                (33  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDO2                (34  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDO3                (35  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_WS                  (36  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_CLK                  (37  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_DI                   (38  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_DO                   (39  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_FSYNC                (40  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_CK                  (41  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_D                   (42  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_CK                  (43  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_D                   (44  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_CK                  (45  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_D                   (46  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM0                     (47  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM1                     (48  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM2                     (49  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM3                     (50  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM4                     (51  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM5                     (52  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM6                     (53  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM7                     (54  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC0_CLK               (55  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC0_CMD               (56  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC0_DATA0             (57  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC0_DATA1             (58  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC0_DATA2             (59  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC0_DATA3             (60  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC0_DATA4             (61  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC0_DATA5             (62  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC0_DATA6             (63  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC0_DATA7             (64  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPDIF0_DI                (65  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPDIF0_DO                (66  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_CLK             (67  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_CS0             (68  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_CS1             (69  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_CS2             (70  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_CS3             (71  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_DCN             (72  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_DI0             (73  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_DI1             (74  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_DI2             (75  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_DI3             (76  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI0_DIO             (77  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPILCD_CLK           (78  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPILCD_CS0           (79  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPILCD_CS1           (80  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPILCD_DI0           (81  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPILCD_DI1           (82  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPILCD_DIO           (83  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI2_CLK             (84  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI2_CS0             (85  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI2_CS1             (86  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI2_DI0             (87  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI2_DI1             (88  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI2_DIO             (89  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI3_CLK             (90  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI3_CS0             (91  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI3_CS1             (92  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI3_DI0             (93  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI3_DI1             (94  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI3_DIO             (95  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C_M0_SCL           (96  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C_M0_SDA           (97  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C_M1_SCL           (98  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C_M1_SDA           (99  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_CLK            (100  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_CS             (101  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_D0             (102  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_D1             (103  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_D2             (104  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_D3             (105  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART0_RX                 (106  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART0_TX                 (107  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART1_CTS                (108  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART1_RTS                (109  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART1_RX                 (110  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART1_TX                 (111  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART2_RX                 (112  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART2_TX                 (113  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART2_CTS                (114  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART2_RTS                (115  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART3_RX                 (116  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART3_TX                 (117  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART3_CTS                (118  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART3_RTS                (119  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_CTS              (120  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_RTS              (121  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_RX               (122  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_TX               (123  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL0             (124  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL2             (125  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL3             (126  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL4             (127  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL5             (128  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL6             (129  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL7             (130  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL8             (131  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL9             (132  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_CLK              (133  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_CMD              (134  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_DATA0            (135  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_DATA1            (136  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_DATA2            (137  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_DATA3            (138  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_WAKE_HOST             (139  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_TXON                  (140  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_TE               (141  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_BL_PWM           (142  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_BL_EN            (143  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_CLK          (144  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_CS           (145  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_DIO          (146  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_DO1_DCN      (147  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_DO2          (148  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_DO3          (149  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_DI           (150  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_IR_RX                    (151  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_IR_TX                    (152  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_RXD              (153  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_TXD              (154  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_SWRX                  (155  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_SWTX                  (156  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_WF_SW                 (157  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_PRIO                  (158  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_ACTIVE                (159  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_FREQ                  (160  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM8                     (161  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM9                     (162  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM10                    (163  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM11                    (164  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM12                    (165  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM13                    (166  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM14                    (167  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM15                    (168  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_0                 (169  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_1                 (170  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_2                 (171  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_3                 (172  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_4                 (173  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_5                 (174  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_6                 (175  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_7                 (176  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_8                 (177  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_9                 (178  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_10                (179  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_11                (180  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_12                (181  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_13                (182  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_14                (183  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM_IN_15                (184  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPDIF_RX                 (185  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPDIF_TX                 (186  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_CLK             (187  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_CS0             (188  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_CS1             (189  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_DI0             (190  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_DI1             (191  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI1_DIO             (192  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI_SLV_CLK          (193  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI_SLV_CS           (194  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI_SLV_DIO          (195  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SPI_SLV_DO           (196  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SCI_CLK              (197  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SCI_RST              (198  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_SCI_IO               (199  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART0_CTS            (200  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART0_RTS            (201  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART0_RXD            (202  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART0_TXD            (203  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART1_CTS            (204  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART1_RTS            (205  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART1_RXD            (206  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART1_TXD            (207  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART2_CTS            (208  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART2_RTS            (209  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART2_RXD            (210  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART2_TXD            (211  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART3_CTS            (212  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART3_RTS            (213  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART3_RXD            (214  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART3_TXD            (215  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART4_CTS            (216  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART4_RTS            (217  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART4_RXD            (218  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART4_TXD            (219  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C0_SCK             (220  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C0_SDA             (221  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C1_SCK             (222  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C1_SDA             (223  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C0_SCK             (224  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C0_SDA             (225  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C1_SCK             (226  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C1_SDA             (227  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C2_SCK             (228  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C2_SDA             (229  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C3_SCK             (230  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C3_SDA             (231  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C4_SCK             (232  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C4_SDA             (233  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C5_SCK             (234  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C5_SDA             (235  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C6_SCK             (236  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C6_SDA             (237  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C7_SCK             (238  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2C7_SDA             (239  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SCK             (240  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_WS              (241  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDI0            (242  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDI1            (243  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDI2            (244  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDI3            (245  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDO0            (246  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDO1            (247  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDO2            (248  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDO3            (249  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDO4            (250  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDO5            (251  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDO6            (252  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S0_SDO7            (253  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SCK             (254  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_WS              (255  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDI0            (256  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDI1            (257  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDI2            (258  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDI3            (259  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDO0            (260  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDO1            (261  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDO2            (262  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDO3            (263  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDO4            (264  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDO5            (265  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDO6            (266  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S1_SDO7            (267  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SCK             (268  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_WS              (269  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDI0            (270  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDI1            (271  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDI2            (272  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDI3            (273  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDO0            (274  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDO1            (275  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDO2            (276  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDO3            (277  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDO4            (278  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDO5            (279  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDO6            (280  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S2_SDO7            (281  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SCK             (282  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_WS              (283  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDI0            (284  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDI1            (285  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDI2            (286  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDI3            (287  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDO0            (288  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDO1            (289  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDO2            (290  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDO3            (291  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDO4            (292  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDO5            (293  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDO6            (294  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S3_SDO7            (295  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S_MCLK_IN          (296  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I2S_MCLK_OUT         (297  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_SCK              (298  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_SDA              (299  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART_CTS             (300  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART_RTS             (301  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART_RXD             (302  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART_TXD             (303  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI_CLK              (304  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI_CS0              (305  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI_DI0              (306  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI_DIO              (307  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CODEC_PDM_CLK0           (308  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CODEC_PDM_DATA0          (309  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CODEC_PDM_CLK1           (310  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CODEC_PDM_DATA1          (311  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CODEC_PDM_CLK2           (312  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CODEC_PDM_DATA2          (313  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_LCDC_CLK            (314  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_LCDC_CS             (315  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_LCDC_D0             (316  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_LCDC_D1             (317  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_LCDC_D2             (318  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_LCDC_D3             (319  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_RXD              (320  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_TXD              (321  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_SW0               (322  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_SW1               (323  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_SW2               (324  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_SW3               (325  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_SW4               (326  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_SW5               (327  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_ACTIVE                (328  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDIO_DATA4               (329  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDIO_DATA5               (330  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDIO_DATA6               (331  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDIO_DATA7               (332  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_IR1_RX                   (333  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_IR1_TX                   (334  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_IR2_RX                   (335  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_IR2_TX                   (336  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_IR3_RX                   (337  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_IR3_TX                   (338  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_CLE       (339  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_ALE       (340  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_CE        (341  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_WE        (342  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_RE        (343  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_RB        (344  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_IO_0      (345  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_IO_1      (346  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_IO_2      (347  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_IO_3      (348  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_IO_4      (349  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_IO_5      (350  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_IO_6      (351  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SLC_NAND_FLASH_IO_7      (352  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_RXCLK              (353  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_TXCLK              (354  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_RXCTL              (355  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_TXCTL              (356  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_RXD_0              (357  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_TXD_0              (358  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_RXD_1              (359  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_TXD_1              (360  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_RXD_2              (361  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_TXD_2              (362  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_RXD_3              (363  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_TXD_3              (364  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_MDIO               (365  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_RGMII_MDC                (366  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_CLK                  (367  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_VSYNC                (368  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_VALID                (369  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_DATA0                (370  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_DATA1                (371  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_DATA2                (372  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_DATA3                (373  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_DATA4                (374  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_DATA5                (375  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_DATA6                (376  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_DATA7                (377  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_DATA8                (378  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DVP_DATA9                (379  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_CLK          (380  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_CTRL         (381  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_0       (382  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_1       (383  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_2       (384  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_3       (385  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_4       (386  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_5       (387  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_6       (388  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_7       (389  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_8       (390  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_9       (391  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_10      (392  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_11      (393  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_12      (394  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_13      (395  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_14      (396  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_15      (397  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_16      (398  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_17      (399  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_18      (400  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_19      (401  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_20      (402  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_21      (403  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_22      (404  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_23      (405  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_24      (406  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_25      (407  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_26      (408  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_27      (409  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_28      (410  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_29      (411  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_30      (412  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ACORE_TRACE_DATA_31      (413  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST0                (414  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST1                (415  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST2                (416  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST3                (417  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST4                (418  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST5                (419  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST6                (420  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST7                (421  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST8                (422  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST9                (423  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST10               (424  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST11               (425  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST12               (426  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST13               (427  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST14               (428  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST15               (429  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST16               (430  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST17               (431  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST18               (432  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST19               (433  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST20               (434  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST21               (435  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST22               (436  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST23               (437  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST24               (438  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST25               (439  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST26               (440  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_TEST27               (441  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDIO_CLK                 (442  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDIO_CMD                 (443  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDIO_DATA0               (444  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDIO_DATA1               (445  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDIO_DATA2               (446  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDIO_DATA3               (447  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PAT_ITF_WL_ACTIVE        (448  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PAT_ITF_BT_PRIORITY      (449  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PAT_ITF_BT_ACTIVE        (450  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PAT_ITF_BT_FREQ          (451  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTDI                     (452  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTDO                     (453  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTRST                    (454  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SMP_BT_PIN0              (455  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SMP_BT_PIN1              (456  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SMP_BT_VLD               (457  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DNTC_IN                  (458  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DNTC_OUT                 (459  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_RXD_WCI          (460  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_TXD_WCI          (461  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CANB_STB                 (462  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CANB_RX                  (463  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CANB_TX                  (464  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_VSYNC                (465  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_VIDEO_MODE_START_TRIG    (466  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ISP_EXTERNAL             (467  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANTENNA_SW               (468  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_FLG_EXC_GPIO_MCU         (469  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C0_SCL             (470  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_I3C1_SCL             (471  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_test28               (472  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_test29               (473  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANA_test30               (474  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART4_RST            (475  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTH_UART2_RST            (476  << GPIO_ALT_SHIFT)


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
#  define _GIO_INT_AIM             (1 << 10)   /* Bit 10: Additional Interrupt modes */
#  define _GPIO_INT_LEVEL          (1 << 9)    /* Bit 9: Level detection interrupt */
#  define _GPIO_INT_EDGE           (0)         /*        (vs. Edge detection interrupt) */
#  define _GPIO_INT_RH             (1 << 8)    /* Bit 9: Rising edge/High level detection interrupt */
#  define _GPIO_INT_FL             (0)         /*        (vs. Falling edge/Low level detection interrupt) */

#  define GPIO_INT_HIGHLEVEL       (_GIO_INT_AIM | _GPIO_INT_LEVEL | _GPIO_INT_RH)
#  define GPIO_INT_LOWLEVEL        (_GIO_INT_AIM | _GPIO_INT_LEVEL | _GPIO_INT_FL)
#  define GPIO_INT_RISING          (_GIO_INT_AIM | _GPIO_INT_EDGE  | _GPIO_INT_RH)
#  define GPIO_INT_FALLING         (_GIO_INT_AIM | _GPIO_INT_EDGE  | _GPIO_INT_FL)
#  define GPIO_INT_BOTHEDGES       (0)

/* If the pin is an GPIO output, then this identifies the initial output value:
 *
 *   .... .... V... ....
 */

#define GPIO_OUTPUT_SET            (1 << 7)    /* Bit 7: Initial value of output */
#define GPIO_OUTPUT_CLEAR          (0)

/* This identifies the GPIO port:
 *
 *   .... .... .PP. ....
 */

#define GPIO_PORT_SHIFT            (5)         /* Bit 5-6:  Port number */
#define GPIO_PORT_MASK             (3 << GPIO_PORT_SHIFT)
#  define GPIO_PORT_GPIO0           (0 << GPIO_PORT_SHIFT)
#  define GPIO_PORT_GPIO1           (1 << GPIO_PORT_SHIFT)

/* This identifies the bit in the port:
 *
 *   .... .... ...B BBBB
 */
// port 0   Gpio[31:0]
#define GPIO_PIN_SHIFT             0           /* Bits 0-4: GPIO number: 0-31  with interrupt*/
#define GPIO_PIN_MASK              (31 << GPIO_PIN_SHIFT)
#define GPIO_PIN0                  (0  << GPIO_PIN_SHIFT)
#define GPIO_PIN1                  (1  << GPIO_PIN_SHIFT)
#define GPIO_PIN2                  (2  << GPIO_PIN_SHIFT)
#define GPIO_PIN3                  (3  << GPIO_PIN_SHIFT)
#define GPIO_PIN4                  (4  << GPIO_PIN_SHIFT)
#define GPIO_PIN5                  (5  << GPIO_PIN_SHIFT)
#define GPIO_PIN6                  (6  << GPIO_PIN_SHIFT)
#define GPIO_PIN7                  (7  << GPIO_PIN_SHIFT)
#define GPIO_PIN8                  (8  << GPIO_PIN_SHIFT)
#define GPIO_PIN9                  (9  << GPIO_PIN_SHIFT)
#define GPIO_PIN10                 (10 << GPIO_PIN_SHIFT)
#define GPIO_PIN11                 (11 << GPIO_PIN_SHIFT)
#define GPIO_PIN12                 (12 << GPIO_PIN_SHIFT)
#define GPIO_PIN13                 (13 << GPIO_PIN_SHIFT)
#define GPIO_PIN14                 (14 << GPIO_PIN_SHIFT)
#define GPIO_PIN15                 (15 << GPIO_PIN_SHIFT)
#define GPIO_PIN16                 (16 << GPIO_PIN_SHIFT)
#define GPIO_PIN17                 (17 << GPIO_PIN_SHIFT)
#define GPIO_PIN18                 (18 << GPIO_PIN_SHIFT)
#define GPIO_PIN19                 (19 << GPIO_PIN_SHIFT)
#define GPIO_PIN20                 (20 << GPIO_PIN_SHIFT)
#define GPIO_PIN21                 (21 << GPIO_PIN_SHIFT)
#define GPIO_PIN22                 (22 << GPIO_PIN_SHIFT)
#define GPIO_PIN23                 (23 << GPIO_PIN_SHIFT)
#define GPIO_PIN24                 (24 << GPIO_PIN_SHIFT)
#define GPIO_PIN25                 (25 << GPIO_PIN_SHIFT)
#define GPIO_PIN26                 (26 << GPIO_PIN_SHIFT)
#define GPIO_PIN27                 (27 << GPIO_PIN_SHIFT)
#define GPIO_PIN28                 (28 << GPIO_PIN_SHIFT)
#define GPIO_PIN29                 (29 << GPIO_PIN_SHIFT)
#define GPIO_PIN30                 (30 << GPIO_PIN_SHIFT)
#define GPIO_PIN31                 (31 << GPIO_PIN_SHIFT)

//port 1 Gpio[39:32]   /*no interrupt*/
#define GPIO_PIN32                  (32  << GPIO_PIN_SHIFT)
#define GPIO_PIN33                  (33  << GPIO_PIN_SHIFT)
#define GPIO_PIN34                  (34  << GPIO_PIN_SHIFT)
#define GPIO_PIN35                  (35  << GPIO_PIN_SHIFT)
#define GPIO_PIN36                  (36  << GPIO_PIN_SHIFT)
#define GPIO_PIN37                  (37  << GPIO_PIN_SHIFT)
#define GPIO_PIN38                  (38  << GPIO_PIN_SHIFT)
#define GPIO_PIN39                  (39  << GPIO_PIN_SHIFT)



#define PIN_LED1              GPIO_PIN32
#define PIN_LED2              GPIO_PIN33


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
#endif /* __ARCH_ARM_SRC_BES_BES2009_GPIO_H */
