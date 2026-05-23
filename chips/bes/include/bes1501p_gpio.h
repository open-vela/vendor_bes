/************************************************************************************
 * arch/arm/src/bes/bes1501P_gpio.h
 * General Purpose Input/Output (GPIO) definitions for the BES1501P
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

#ifndef __ARCH_ARM_SRC_BES_BES1501P_GPIO_H
#define __ARCH_ARM_SRC_BES_BES1501P_GPIO_H

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
#  define GPIO_ALT_CLK_32K_IN         (6  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_IN         (7  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_REQ_OUT        (8  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_CLK_OUT            (9  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_SCL            (10  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2C_SDA            (11  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_I2S_MCLK           (12  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_LCD_TE             (13  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M0_SCL     (14  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M0_SDA     (15  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M1_SCL     (16  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2C_M1_SDA     (17  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SCK       (18  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SDI0      (19  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SDI1      (20  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SDI2      (21  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SDI3      (22  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_SDO       (23  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S0_WS        (24  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S1_SCK       (25  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S1_SDI0      (26  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S1_SDO       (27  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_I2S1_WS        (28  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI_CLK        (29  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI_CS0        (30  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI_CS1        (31  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI_CS2        (32  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI_CS3        (33  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI_DCN        (34  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI_DI0        (35  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI_DI1        (36  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI_DI2        (37  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI_DI3        (38  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_SPI_DIO        (39  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART0_RX       (40  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART0_TX       (41  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART1_CTS      (42  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART1_RTS      (43  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART1_RX       (44  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART1_TX       (45  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART2_RX       (46  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_MCU_UART2_TX       (47  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_CLK            (48  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_DI             (49  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_DO             (50  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PCM_FSYNC          (51  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_CK            (52  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM0_D             (53  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_CK            (54  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM1_D             (55  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_CK            (56  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PDM2_D             (57  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM0               (58  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM1               (59  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM2               (60  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_PWM3               (61  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_CLK          (62  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_CMD          (63  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA0        (64  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA1        (65  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA2        (66  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA3        (67  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA4        (68  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA5        (69  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA6        (70  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SDMMC_DATA7        (71  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2C_M0_SCL    (72  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2C_M0_SDA    (73  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2C_M1_SCL    (74  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2C_M1_SDA    (75  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2C_M2_SCL    (76  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2C_M2_SDA    (77  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2C_M3_SCL    (78  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2C_M3_SDA    (79  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2S0_SCK      (80  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2S0_SDI0     (81  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2S0_SDI1     (82  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2S0_SDI2     (83  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2S0_SDI3     (84  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2S0_SDO      (85  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_I2S0_WS       (86  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPI_CLK       (87  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPI_CS0       (88  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPI_CS1       (89  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPI_CS2       (90  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPI_CS3       (91  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPI_DCN       (92  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPI_DI0       (93  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPI_DI1       (94  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPI_DI2       (95  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPI_DI3       (96  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPI_DIO       (97  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPILCD_CLK    (98  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPILCD_CS0    (99  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPILCD_CS1    (100  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPILCD_CS2    (101  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPILCD_CS3    (102  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPILCD_DCN    (103  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPILCD_DI0    (104  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPILCD_DI1    (105  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPILCD_DI2    (106  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPILCD_DI3    (107  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_SPILCD_DIO    (108  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_UART0_RX      (109  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_UART0_TX      (110  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_UART1_CTS     (111  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_UART1_RTS     (112  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_UART1_RX      (113  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SENS_UART1_TX      (114  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPDIF0_DI          (115  << GPIO_ALT_SHIFT)
#  define GPIO_ALT_SPDIF0_DO          (116  << GPIO_ALT_SHIFT)

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
 *   .... .... BBBB BBBB
 */
// port 0   Gpio[31:0] 
#define GPIO_PIN_SHIFT             0           /* Bits 0-7: GPIO number: 0-31  with interrupt*/
#define GPIO_PIN_MASK              (255 << GPIO_PIN_SHIFT)
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
#define GPIO_PIN39                 (39  << GPIO_PIN_SHIFT)
#define GPIO_PIN40                 (40 << GPIO_PIN_SHIFT)
#define GPIO_PIN41                 (41 << GPIO_PIN_SHIFT)
#define GPIO_PIN42                 (42  << GPIO_PIN_SHIFT)
#define GPIO_PIN43                 (43  << GPIO_PIN_SHIFT)
#define GPIO_PIN44                 (44  << GPIO_PIN_SHIFT)
#define GPIO_PIN45                 (45  << GPIO_PIN_SHIFT)
#define GPIO_PIN46                 (46  << GPIO_PIN_SHIFT)
#define GPIO_PIN47                 (47  << GPIO_PIN_SHIFT)
#define GPIO_PIN48                 (48  << GPIO_PIN_SHIFT)
#define GPIO_PIN49                 (49  << GPIO_PIN_SHIFT)
#define GPIO_PIN50                 (50 << GPIO_PIN_SHIFT)
#define GPIO_PIN51                 (51 << GPIO_PIN_SHIFT)
#define GPIO_PIN52                 (52  << GPIO_PIN_SHIFT)
#define GPIO_PIN53                 (53  << GPIO_PIN_SHIFT)
#define GPIO_PIN54                 (54  << GPIO_PIN_SHIFT)
#define GPIO_PIN55                 (55  << GPIO_PIN_SHIFT)
#define GPIO_PIN56                 (56  << GPIO_PIN_SHIFT)
#define GPIO_PIN57                 (57  << GPIO_PIN_SHIFT)
#define GPIO_PIN58                 (58  << GPIO_PIN_SHIFT)
#define GPIO_PIN59                 (59  << GPIO_PIN_SHIFT)
#define GPIO_PIN60                 (60 << GPIO_PIN_SHIFT)
#define GPIO_PIN61                 (61 << GPIO_PIN_SHIFT)
#define GPIO_PIN62                 (62  << GPIO_PIN_SHIFT)
#define GPIO_PIN63                 (63  << GPIO_PIN_SHIFT)
#define GPIO_PIN64                 (64  << GPIO_PIN_SHIFT)
#define GPIO_PIN65                 (65  << GPIO_PIN_SHIFT)
#define GPIO_PIN66                 (66  << GPIO_PIN_SHIFT)
#define GPIO_PIN67                 (67  << GPIO_PIN_SHIFT)
#define GPIO_PIN68                 (68  << GPIO_PIN_SHIFT)
#define GPIO_PIN69                 (69  << GPIO_PIN_SHIFT)
#define GPIO_PIN70                 (70 << GPIO_PIN_SHIFT)
#define GPIO_PIN71                 (71 << GPIO_PIN_SHIFT)
#define GPIO_PIN72                 (72  << GPIO_PIN_SHIFT)
#define GPIO_PIN73                 (73  << GPIO_PIN_SHIFT)
#define GPIO_PIN74                 (74  << GPIO_PIN_SHIFT)
#define GPIO_PIN75                 (75  << GPIO_PIN_SHIFT)
#define GPIO_PIN76                 (76  << GPIO_PIN_SHIFT)
#define GPIO_PIN77                 (77  << GPIO_PIN_SHIFT)
#define GPIO_PIN78                 (78  << GPIO_PIN_SHIFT)
#define GPIO_PIN79                 (79  << GPIO_PIN_SHIFT)
#define GPIO_PIN80                 (80 << GPIO_PIN_SHIFT)
#define GPIO_PIN81                 (81 << GPIO_PIN_SHIFT)

#define PIN_LED1              GPIO_PIN80
#define PIN_LED2              GPIO_PIN81

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
#endif /* __ARCH_ARM_SRC_BES_BES1501P_GPIO_H */
