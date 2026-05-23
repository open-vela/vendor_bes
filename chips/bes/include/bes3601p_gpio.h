/************************************************************************************
 * bes3601p_gpio.h
 * General Purpose Input/Output (GPIO) definitions for the BES3601P
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

#ifndef __ARCH_ARM_SRC_BES_BES3601P_GPIO_H
#define __ARCH_ARM_SRC_BES_BES3601P_GPIO_H

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
 *  .... ..DD AAAA AAAA MMCC CIII BBBB BBBB
 */

/* VOLTAGE_DOMAINS
 *
 *  .... ..DD .... .... .... .... .... ....
 */
#define GPIO_VOLD_SHIFT                24                         /* Bits 24-25: Alternate function */
#define GPIO_VOLD_MASK                 (3 << GPIO_VOLD_SHIFT)
#  define GPIO_VOLD(n)                 ((n) << GPIO_VOLD_SHIFT)
#  define GPIO_PIN_VOLTAGE_VIO         (0  << GPIO_VOLD_SHIFT) 
#  define GPIO_PIN_VOLTAGE_MEM         (1  << GPIO_VOLD_SHIFT)
#  define GPIO_PIN_VOLTAGE_VBAT        (2  << GPIO_VOLD_SHIFT)

/* supports up to 128 alternate functions per pin:
 *
 *  .... .... AAAA AAAA .... .... .... ....
 */
#define GPIO_ALT_SHIFT                    16                         /* Bits 16-23: Alternate function */
#define GPIO_ALT_MASK                     (255 << GPIO_ALT_SHIFT)
#  define GPIO_ALT(n)                     ((n) << GPIO_ALT_SHIFT)
#  define GPIO_ALT_NONE                   (0  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_GPIO                   (1  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_AS_GPIO                (1  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_CTS           (2  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_RTS           (3  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_RX            (4  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_TX            (5  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_WCI_RX        (6  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_UART_WCI_TX        (7  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_JTAG_TCK           (8  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BTC_JTAG_TMS           (9  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_ACTIVE              (10 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_PRO                 (11 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_FREQ                (12 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_WIFI_SW             (13 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_SMP_PIN1            (14 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_SMP_PIN0            (15 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_SMP_VLD             (16 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_PTA_IO_FREQ         (17 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_SWRX                (18 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_SWTX                (19 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_32K_OUT            (20 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_OUT                (21 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_IN             (22 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_OUT            (23 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_SCL                (24 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_SDA                (25 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_RST               (26 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TCK               (27 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDI               (28 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDO               (29 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TMS               (30 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_RST1              (31 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TCK1              (32 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDI1              (33 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDO1              (34 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TMS1              (35 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_PWM                (36 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_TE0                (37 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_TE1                (38 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_TRIG               (39 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_VSYNC              (40 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_CK                (41 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_D                 (42 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_CK                (43 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_D                 (44 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_CK                (45 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_D                 (46 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PU_OSC                 (47 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PU_RC                  (48 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_CS0           (49 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_CLK           (50 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO0          (51 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO1          (52 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO2          (53 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD0_DIO3          (54 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_CS0           (55 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_CLK           (56 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO0          (57 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO1          (58 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO2          (59 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPILCD1_DIO3          (60 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_PCLK              (61 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_VSYNC             (62 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_HSYNC             (63 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATAEN            (64 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA0             (65 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA1             (66 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA2             (67 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA3             (68 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA4             (69 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA5             (70 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA6             (71 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA7             (72 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA8             (73 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA9             (74 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA10            (75 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA11            (76 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA12            (77 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA13            (78 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA14            (79 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA15            (80 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA16            (81 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA17            (82 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA18            (83 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA19            (84 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA20            (85 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA21            (86 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA22            (87 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD0_DATA23            (88 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_SCLK0        (89 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_SCLK1        (90 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_CS0          (91 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_CS1          (92 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_SIO0         (93 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_SIO1         (94 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_SIO2         (95 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_SIO3         (96 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_SIO4         (97 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_SIO5         (98 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_SIO6         (99 << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIFLASH2_SIO7         (100<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_PIO_DRAM0_SCAN_IN      (101<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_PIO_DRAM0_SCLK         (102<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_PIO_DRAM0_XWEB         (103<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_PIO_DRAM0_SCAN_OUT     (104<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_PIO_DRAM1_SCAN_IN      (105<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_PIO_DRAM1_SCLK         (106<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_PIO_DRAM1_XWEB         (107<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_PIO_DRAM1_SCAN_OUT     (108<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_RFFE_SCL               (109<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_RFFE_SDA               (110<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_PSRAM0_LPBK_PASS       (111<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_PSRAM0_LPBK_FAIL       (112<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_PSRAM0_LPBK_DONE       (113<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_ANTENNA_SW             (114<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_DNTC_IN            (115<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_DNTC_OUT           (116<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M0_SCL         (117<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M0_SDA         (118<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M1_SCL         (119<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M1_SDA         (120<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M2_SCL         (121<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M2_SDA         (122<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M3_SCL         (123<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M3_SDA         (124<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M4_SCL         (125<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2C_M4_SDA         (126<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_MCLK          (127<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_MCLK_IN       (128<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SCK           (129<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDI0          (130<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_SDO           (131<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S0_WS            (132<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_MCLK          (133<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_MCLK_IN       (134<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SCK           (135<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDI0          (136<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_SDO           (137<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I2S1_WS            (138<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I3C_M0_SCL         (139<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_I3C_M0_SDA         (140<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM0               (141<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM1               (142<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM2               (143<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_PWM3               (144<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SCI_RESET          (145<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SCI_CLK            (146<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SCI_DIO            (147<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_CLK         (148<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_CMD         (149<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA0       (150<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA1       (151<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA2       (152<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA3       (153<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA4       (154<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA5       (155<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA6       (156<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SDMMC0_DATA7       (157<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPDIF0_DI          (158<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPDIF0_DO          (159<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DCN           (160<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CLK           (161<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CS0           (162<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CS1           (163<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_CS2           (164<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DI0           (165<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DI1           (166<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DI2           (167<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI0_DIO           (168<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DCN           (169<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CLK           (170<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CS0           (171<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CS1           (172<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_CS2           (173<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DI0           (174<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DI1           (175<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DI2           (176<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPI1_DIO           (177<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_CLK         (178<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_CS          (179<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_DIO         (180<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPISLV_DO          (181<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART0_RX           (182<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART0_TX           (183<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_CTS          (184<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_RTS          (185<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_RX           (186<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART1_TX           (187<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_CTS          (188<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_RTS          (189<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_RX           (190<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_UART2_TX           (191<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CANB_STB           (192<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CANB_RX            (193<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CANB_TX            (194<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_MCLK        (195<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_PCLK        (196<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_D0          (197<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_D1          (198<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_D2          (199<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_SPICAM_D3          (200<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CAM_DVP_CLK        (201<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CAM_DVP_VSYNC      (202<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CAM_DVP_HSYNC      (203<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CAM_DVP_D0         (204<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CAM_DVP_D1         (205<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CAM_DVP_D2         (206<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CAM_DVP_D3         (207<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CAM_DVP_D4         (208<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CAM_DVP_D5         (209<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CAM_DVP_D6         (210<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_CAM_DVP_D7         (211<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TMS1          (212<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TCK1          (213<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TMS0          (214<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TCK0          (215<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TMS2          (216<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TCK2          (217<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TMS3          (218<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TCK3          (219<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TDI2          (220<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TDO2          (221<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_RST2          (222<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TDI3          (223<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_TDO3          (224<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_SYS_JTAG_RST3          (225<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_UART0_CTS          (226<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_UART0_RTS          (227<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_UART0_TX           (228<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_UART0_RX           (229<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_UART1_CTS          (230<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_UART1_RTS          (231<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_UART1_TX           (232<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_UART1_RX           (233<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_RFON               (234<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_TXON               (235<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_SCI_RST            (236<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_SCI_CLK            (237<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_SCI_IO             (238<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_WCI_UART_RX        (239<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_WCI_UART_TX        (240<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_SPISLV_CLK         (241<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_SPISLV_CS          (242<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_SPISLV_DIO         (243<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_SPISLV_DO          (244<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_JTAG_TCK0          (245<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_JTAG_TMS0          (246<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_JTAG_TCK1          (247<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_JTAG_TMS1          (248<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_JTAG_TDI1          (249<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_JTAG_TDO1          (250<< GPIO_ALT_SHIFT)
#  define GPIO_ALT_LTE_JTAG_RST1          (251<< GPIO_ALT_SHIFT)

/* Input/Output mode:
 *
 *  .... .... .... .... MM.. .... .... ....
 */

#define GPIO_MODE_SHIFT            (14)        /* Bits 14-15: GPIO mode */
#define GPIO_MODE_MASK             (3 << GPIO_MODE_SHIFT)
#  define GPIO_INPUT               (0 << GPIO_MODE_SHIFT) /* Input */
#  define GPIO_OUTPUT              (1 << GPIO_MODE_SHIFT) /* Output */
#  define GPIO_PERIPHA             (2 << GPIO_MODE_SHIFT) /* Controlled by periph A signal */
#  define GPIO_PERIPHB             (3 << GPIO_MODE_SHIFT) /* Controlled by periph B signal */

/* These bits set the configuration of the pin:
 *
 *  .... .... .... .... ..CC C... .... ....
 */

#define GPIO_CFG_SHIFT             (11)        /* Bits 11-13: GPIO configuration bits */
#define GPIO_CFG_MASK              (7 << GPIO_CFG_SHIFT)

#  define GPIO_CFG_NOPULL          (0 << GPIO_CFG_SHIFT) /* Default, no pull */
#  define GPIO_CFG_PULLUP          (1 << GPIO_CFG_SHIFT) /* Bit 11: Internal pull-up */
#  define GPIO_CFG_PULLDOWN        (2 << GPIO_CFG_SHIFT) /* Bit 12: Internal pull-down */

/* Additional interrupt modes:
 *
 *  .... .... .... .... .... .III .... ....
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
 *  .... .... .... .... .... .... BBBB BBBB
 */
// port 0   Gpio[31:0] 
#define GPIO_PIN_SHIFT             0           /* Bits 0-7: GPIO number: 0-31  with interrupt*/
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

/* LED1/2 */
#define GPIO_PIN96                 (96 << GPIO_PIN_SHIFT)
#define GPIO_PIN97                 (97 << GPIO_PIN_SHIFT)

#define PIN_LED1                    GPIO_PIN96
#define PIN_LED2                    GPIO_PIN97

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
#endif /* __ARCH_ARM_SRC_BES_BES3601P_GPIO_H */
