/************************************************************************************
 * rtos/nuttx/include/arch/chip/bes2005_gpio.h
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

#define GPIO_ALT_SHIFT                16                         /* Bits 16-24: Alternate function */
#define GPIO_ALT_MASK                 (255 << GPIO_ALT_SHIFT)
#  define GPIO_ALT(n)                 ((n) << GPIO_ALT_SHIFT)
#  define GPIO_ALT_NONE               (0  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_GPIO               (1  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_AS_GPIO            (1  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_CTS        (2  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_RTS        (3  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_RX         (4  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_TX         (5  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART1_RX        (6  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART1_TX        (7  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART1_CTS       (8  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART1_RTS       (9  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_32K_IN         (10  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_IN         (11  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_OUT        (12  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_OUT            (13  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M0_SCL         (14  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M0_SDA         (15  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M1_SCL         (16  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M2_SCL         (17  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M2_SDA         (18  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_M1_SDA         (19  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_MCLK          (20  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SCK           (21  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDI0          (22  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDI1          (23  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDI2          (24  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDI3          (25  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDO0          (26  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDO1          (27  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDO2          (28  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_SDO3          (29  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S0_WS            (30  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SCK           (31  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDI0          (32  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDI1          (33  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDI2          (34  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDI3          (35  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDO0          (36  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDO1          (37  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDO2          (38  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_SDO3          (39  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S1_WS            (40  << GPIO_ALT_SHIFT)

#  define GPIO_ALT_PCM_CLK            (41  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_DI             (42  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_DO             (43  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_FSYNC          (44  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_CK            (45  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_D             (46  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_CK            (47  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_D             (48  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_CK            (49  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_D             (50  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM0               (51  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM1               (52  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM2               (53  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM3               (54  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM4               (55  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM5               (56  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM6               (57  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM7               (58  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_CLK          (59  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_CMD          (60  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA0        (61  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA1        (62  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA2        (63  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA3        (64  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA4        (65  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA5        (66  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA6        (67  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA7        (68  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPDIF0_DI          (69  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPDIF0_DO          (70  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPI_CLK            (71  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPI_CS0            (72  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPI_CS1            (73  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPI_CS2            (74  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPI_CS3            (75  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPI_DCN            (76  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPI_DI0            (77  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPI_DI1            (78  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPI_DI2            (79  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPI_DI3            (80  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPI_DIO            (81  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPILCD_CLK         (82  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPILCD_CS0         (83  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPILCD_CS1         (84  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPILCD_CS2         (85  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPILCD_CS3         (86  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPILCD_DCN         (87  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPILCD_DI0         (88  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPILCD_DI1         (89  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPILCD_DI2         (90  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPILCD_DI3         (91  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPILCD_DIO         (92  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIS_CLK           (93  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIS_IN            (94  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIS_OUT           (95  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPIS_CS            (96  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART0_RX           (97  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART0_TX           (98  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART0_CTS          (99  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART0_RTS          (100  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART1_CTS          (101  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART1_RTS          (102  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART1_RX           (103  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART1_TX           (104  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART2_RX           (105  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART2_TX           (106  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART2_CTS          (107  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART2_RTS          (108  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART3_RX           (109  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART3_TX           (110  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART3_CTS          (111  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_UART3_RTS          (112  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_CTS        (113  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_RTS        (114  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_RX         (115  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_UART_TX         (116  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL0       (117  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL2       (118  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL3       (119  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL4       (120  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL5       (121  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL6       (122  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL7       (123  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL8       (124  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_FEM_CNTL9       (125  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_CLK        (126  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_CMD        (127  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_DATA0      (128  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_DATA1      (129  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_DATA2      (130  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_SDIO_DATA3      (131  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_WAKE_HOST       (132  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_TXON            (133  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_RXON            (134  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_WF_EPTA            (135  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_TE         (136  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_BL_PWM     (137  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_BL_EN      (138  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_CLK    (139  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_CS     (140  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_DIO    (141  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_DO1_DCN (142  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_DO2    (143  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_DO3    (144  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_DISPLAY_SPI_DI     (145  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_IR_RX              (146  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_IR_TX              (147  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TMS           (148  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDI           (149  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TDO           (150  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_TCLK          (151  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_JTAG_RESET         (152  << GPIO_ALT_SHIFT)

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
#endif /* __ARCH_ARM_SRC_BES_BES2001_GPIO_H */
