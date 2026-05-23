/************************************************************************************
 * arch/arm/src/bes/bes1305_gpio.h
 * General Purpose Input/Output (GPIO) definitions for the BES1305
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

#ifndef __ARCH_ARM_SRC_BES_BES1305_GPIO_H
#define __ARCH_ARM_SRC_BES_BES1305_GPIO_H

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
 *   OVV .AAA AAAA MMCC CIII BBBB BBBB
 */

/* If the pin is an GPIO output, then this identifies the initial output value:
 *
 *    .... .O.. .... .... .... .... .... ....
 */
#define GPIO_OUTPUT_SET            (1 << 26)    /* Bit 26: Initial value of output */
#define GPIO_OUTPUT_CLEAR          (0)

/* VOLTAGE_DOMAINS
*
*    .... ..VV .... .... .... .... .... ....
*/
#define GPIO_VOLD_SHIFT                24                         /* Bits 24-25: Alternate function */
#define GPIO_VOLD_MASK                 (3 << GPIO_VOLD_SHIFT)
#  define GPIO_VOLD(n)                 ((n) << GPIO_VOLD_SHIFT)
#  define GPIO_PIN_VOLTAGE_VIO         (0  << GPIO_VOLD_SHIFT) 
#  define GPIO_PIN_VOLTAGE_MEM         (1  << GPIO_VOLD_SHIFT)
#  define GPIO_PIN_VOLTAGE_VBAT        (2  << GPIO_VOLD_SHIFT)

/* supports up to 256 alternate functions per pin:
 *
 *    .... .... .AAA AAAA .... .... .... ....
 */

#define GPIO_ALT_SHIFT                16                         /* Bits 16-23: Alternate function */
#define GPIO_ALT_MASK                 (127 << GPIO_ALT_SHIFT)
#  define GPIO_ALT(n)                 ((n) << GPIO_ALT_SHIFT)
#  define GPIO_ALT_NONE               (0  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_GPIO               (1  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_AS_GPIO            (1  << GPIO_ALT_SHIFT) 
#  define GPIO_ALT_BT_UART_CTS        (2  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_RTS        (3  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_RX         (4  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_UART_TX         (5  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_BT_WIFI_SW         (6  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_32K_IN         (7  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_IN         (8  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_OUT        (9  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_OUT            (10  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_SCL            (11  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_SDA            (12  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S_MCLK           (13  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_TE             (14  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M0_SCL     (15  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M0_SDA     (16  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M1_SCL     (17  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M1_SDA     (18  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M2_SCL     (19  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M2_SDA     (20  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M3_SCL     (21  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M3_SDA     (22  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SCK       (23  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SDI0      (24  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SDI1      (25  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SDI2      (26  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SDI3      (27  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SDO       (28  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_WS        (29  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S1_SCK       (30  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S1_SDI0      (31  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S1_SDO       (32  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S1_WS        (33  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI0_CLK       (34  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI0_CS0       (35  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI0_CS1       (36  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI0_DI0       (37  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI0_DI1       (38  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI0_DIO       (39  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI1_CLK       (40  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI1_CS0       (41  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI1_DI0       (42  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI1_DIO       (43  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART0_RX       (44  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART0_TX       (45  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART1_CTS      (46  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART1_RTS      (47  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART1_RX       (48  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART1_TX       (49  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART2_RX       (50  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART2_TX       (51  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART2_CTS      (52  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART2_RTS      (53  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M4_SCL     (54  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M4_SDA     (55  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M5_SCL     (56  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M5_SDA     (57  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_CLK            (58  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_DI             (59  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_DO             (60  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_FSYNC          (61  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_CK            (62  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_D             (63  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_CK            (64  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_D             (65  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_CK            (66  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_D             (67  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM0               (68  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM1               (69  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM2               (70  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM3               (71  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM4               (72  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM5               (73  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM6               (74  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM7               (75  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_CLK          (76  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_CMD          (77  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA0        (78  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA1        (79  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA2        (80  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA3        (81  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA4        (82  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA5        (83  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA6        (84  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA7        (85  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPDIF0_DI          (86  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPDIF0_DO          (87  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_CLK      (88  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_CS       (89  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_D0       (90  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_D1       (91  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_D2       (92  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_QSPI_NAND_D3       (93  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S2_SCK       (94  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S2_SDI0      (95  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S2_SDO       (96  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S2_WS        (97  << GPIO_ALT_SHIFT)

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

/* This identifies the bit in the port:
 *
 *   .... .... ..BB BBBB
 */
// port 0   Gpio[31:0] 
#define GPIO_PIN_SHIFT             0           /* Bits 0-7: GPIO number: 0-31  with interrupt*/
#define GPIO_PIN_MASK              (0x3f << GPIO_PIN_SHIFT)
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
#define GPIO_PIN32                 (32  << GPIO_PIN_SHIFT)
#define GPIO_PIN33                 (33  << GPIO_PIN_SHIFT)
#define GPIO_PIN34                 (34  << GPIO_PIN_SHIFT)
#define GPIO_PIN35                 (35  << GPIO_PIN_SHIFT)
#define GPIO_PIN36                 (36  << GPIO_PIN_SHIFT)
#define GPIO_PIN37                 (37  << GPIO_PIN_SHIFT)
#define GPIO_PIN38                 (38  << GPIO_PIN_SHIFT)

#define PIN_LED1              GPIO_PIN37
#define PIN_LED2              GPIO_PIN38

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
#endif /* __ARCH_ARM_SRC_BES_BES1305_GPIO_H */
