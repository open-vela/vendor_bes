/****************************************************************************
 * vendor/bes/boards/best1700_ep/include/board_bes1700_evb.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __BOARDS_BEST1700_EP_INCLUDE_BOARD_BES1700_EVB_H
#define __BOARDS_BEST1700_EP_INCLUDE_BOARD_BES1700_EVB_H

#define CFG_HW_HAVE_PWR_KEY 0
#define CFG_HW_PWL_NUM 0
#define CFG_HW_GPIOKEY_NUM 2
#define CFG_HW_ADCKEY_NUMBER 0
#define CFG_HW_ADCKEY_ADC_MAXVOLT 1000
#define CFG_HW_ADCKEY_ADC_MINVOLT 0
#define CFG_HW_ADCKEY_ADC_KEYVOLT_BASE 130

#include <nuttx/config.h>

//ref hal_iomux_1700.c
#define I2C0_IOMUX_INDEX    04 // hal_iomux_set_i2c0
#define I2C1_IOMUX_INDEX    94 // hal_iomux_set_i2c1

#if defined(CONFIG_BES_LPUART0) && defined(CONFIG_ARCH_CHIP_BES1700_BTH)
#ifndef CONFIG_BES1700_BTHCP
#define UART0_IOMUX_INDEX   04
#endif
#endif

#if (I2C0_IOMUX_INDEX == 04)
#ifdef UART0_IOMUX_INDEX
#undef UART0_IOMUX_INDEX
#endif
#define UART0_IOMUX_INDEX 100
#endif

/**
 * Board lcd Configuration
 */
#ifdef CONFIG_BOARD_DEF_LCD_RESOLUTION
#ifdef CONFIG_LCDC_PIXEL_MARGIN
#define BOARD_LCDC_WIDTH               (CONFIG_BOARD_LCD_X_RES + CONFIG_LCDC_PIXEL_MARGIN)
#else
#define BOARD_LCDC_WIDTH               CONFIG_BOARD_LCD_X_RES
#endif
#define BOARD_LCDC_HEIGHT              CONFIG_BOARD_LCD_Y_RES
#else
#if defined(CONFIG_BES_LCD_RM69330)
#define BOARD_LCDC_WIDTH               454
#define BOARD_LCDC_HEIGHT              454
#elif defined(CONFIG_BES_LCD_GC9503NP)
#define BOARD_LCDC_WIDTH               480
#define BOARD_LCDC_HEIGHT              800
#elif defined(CONFIG_VIDEO_FB)
#error "BOARD_LCDC_WIDTH/BOARD_LCDC_HEIGHT not defined"
#endif
#endif

#ifdef CONFIG_DEV_GPIO
#include <arch/chip/bes_gpio.h>
#endif

#ifndef __ASSEMBLY__
#include <stdint.h>
#include <stdbool.h>
#endif

#ifdef CONFIG_DEV_GPIO
/*
*  BUTTON configuration
*/
#define NUM_BUTTONS  2//(CFG_HW_ADCKEY_NUMBER+CFG_HW_GPIOKEY_NUM+1)   // ADCKEY + GPIOKEY + POWER KEY

/*
* User LED configuration
*/
#define NUM_GPIOLED                       2
#define PIN_LED1_BIT                      (1 << NUM_LEDPINLED)      /* bit in ledset */
#define PIN_LED2_BIT                      (1 << (NUM_LEDPINLED +1)  /* bit in ledset */

#define GPIOPIN_LED1                      PIN_LED1        /* pin 3_4 */
#define GPIOPIN_LED2                      PIN_LED2        /* pin 3_5 */

/*
*  RGB LED configuration
*/

#define CONFIG_RGBLED_RPWM_ID0            BES_HAL_LED_ID1
#define CONFIG_RGBLED_GPWM_ID1            BES_HAL_PWM_ID_2
#define CONFIG_RGBLED_BPWM_ID2            BES_HAL_PWM_ID_3
#define CONFIG_RRGBLED_RGPIO_ID           PIN_LED1
#define CONFIG_RRGBLED_GGPIO_ID           GPIO_PIN28   /* pin 3_4 */
#define CONFIG_RRGBLED_BGPIO_ID           GPIO_PIN29   /* pin 3_5 */

#define RGBLED_RPWM                       GPIO_ALT_GPIO
#define RGBLED_GPWM                       GPIO_ALT_PWM2
#define RGBLED_BPWM                       GPIO_ALT_PWM3


#ifndef CONFIG_RRGBLED_RGPIO_ID
   #error "Unknown gpio id for red led"
#else
   #define GPIO_RGBLED_RPINSET       CONFIG_RRGBLED_RGPIO_ID \
                                     |GPIO_OUTPUT|RGBLED_RPWM|GPIO_PIN_VOLTAGE_VIO
#endif

#ifndef CONFIG_RRGBLED_GGPIO_ID
   #error "Unknown gpio id for green led"
  #else
   #define GPIO_RGBLED_GPINSET      CONFIG_RRGBLED_GGPIO_ID \
                                    |GPIO_OUTPUT|RGBLED_GPWM|GPIO_PIN_VOLTAGE_VIO
#endif

#ifndef CONFIG_RRGBLED_BGPIO_ID
   #error "Unknown gpio id for blue led"
#else
   #define GPIO_RGBLED_BPINSET      CONFIG_RRGBLED_BGPIO_ID \
                                    |GPIO_OUTPUT|RGBLED_BPWM|GPIO_PIN_VOLTAGE_VIO
#endif

/*
*  IRC configuration
*/

/*irc transmiter use PWM  to  generate  ir signal*/
#ifndef CONFIG_BES_TX_PWM_ID
#define CONFIG_BES_TX_PWM_ID      2
#endif

#ifndef CONFIG_BES_IR_TX_PIN
#define CONFIG_BES_IR_TX_PIN      GPIO_PIN29    //pin 3_5
#endif

#define GPIO_IR_TX_PINCFG         CONFIG_BES_IR_TX_PIN \
                                  |GPIO_OUTPUT|GPIO_ALT_PWM5|GPIO_PIN_VOLTAGE_VIO

#define GPIO_IR_TX_PINCFG_GPIO    CONFIG_BES_IR_TX_PIN \
                                  |GPIO_OUTPUT|GPIO_ALT_GPIO|GPIO_PIN_VOLTAGE_VIO
/*irc receiver capture the ir sinale with gpio interrupt */
#ifndef CONFIG_IR_RX_PIN
#define CONFIG_IR_RX_PIN          GPIO_PIN28  //pin 3_4
#endif

#define GPIO_IR_RX_INT_PINCFG_FL  CONFIG_IR_RX_PIN|GPIO_INT_FALLING \
                                  |GPIO_CFG_PULLUP|GPIO_INPUT|GPIO_ALT_GPIO|GPIO_PIN_VOLTAGE_VIO

#define GPIO_IR_RX_INT_PINCFG_RH  CONFIG_IR_RX_PIN|GPIO_INT_RISING \
                                  |GPIO_CFG_PULLUP|GPIO_INPUT|GPIO_ALT_GPIO|GPIO_PIN_VOLTAGE_VIO


#ifndef CONFIG_IR_NEC_DECODER
#    define CONFIG_IR_NEC_DECODER     1
#endif
/*
*  gpio I2C configuration
*/
#  define GPIO_GPIO_SCL    (GPIO_CFG_PULLUP |GPIO_ALT_GPIO|GPIO_PIN6|GPIO_PIN_VOLTAGE_VIO)  /* pin 0_6 */
#  define GPIO_GPIO_SDA    (GPIO_CFG_PULLUP |GPIO_ALT_GPIO|GPIO_PIN7|GPIO_PIN_VOLTAGE_VIO)  /* pin 0_7 */

#if (CONFIG_INPUT_NT38350)
#define GPIO_TP_INT  GPIO_PIN36 /* pin 4_4 */
#define NT38350_I2C_ADDRESS          0x62
#endif

#if (CONFIG_ZINITIX)
#define GPIO_TP_INT  (GPIO_CFG_PULLUP|GPIO_ALT_GPIO|GPIO_PIN_VOLTAGE_VIO|GPIO_INPUT|GPIO_PIN23) /* pin 2_7 */
#define GPIO_TP_RST  (GPIO_CFG_PULLUP|GPIO_ALT_GPIO|GPIO_PIN_VOLTAGE_VIO|GPIO_OUTPUT|GPIO_PIN10) /* pin 1_2 */
#define ZINITIX_I2C_ADDRESS          0x20
#endif

#if (CONFIG_BES_TP_TMA525C)
#if CONFIG_BES1700_ZE7_EVB
    #define GPIO_TP_INT  (GPIO_CFG_PULLUP|GPIO_INT_FALLING|GPIO_ALT_GPIO|GPIO_PIN_VOLTAGE_VIO|GPIO_INPUT|GPIO_PIN10_4)
    #define GPIO_TP_RST  (GPIO_CFG_PULLUP|GPIO_ALT_GPIO|GPIO_PIN_VOLTAGE_VIO|GPIO_OUTPUT|GPIO_PIN10_3)
#else
    #define GPIO_TP_INT  (GPIO_CFG_PULLUP|GPIO_INT_FALLING|GPIO_ALT_GPIO|GPIO_PIN_VOLTAGE_VIO|GPIO_INPUT|GPIO_PIN33) /* pin 4_1 */
    #define GPIO_TP_RST  (GPIO_CFG_PULLUP|GPIO_ALT_GPIO|GPIO_PIN_VOLTAGE_VIO|GPIO_OUTPUT|GPIO_PIN35) /* pin 4_3 */
#endif
#define CONFIG_TMA525C_I2CDEV          0
#endif

#ifdef CONFIG_BES_ACCLIS2DH

#define acclis2dh_port   0        /* use i2c port 0     i2c = bes_i2cbus_initialize(0)*/
#define acclis2dh_addr   0x1d//0x18
#ifndef CONFIG_BES_HARDWARE_MIWARE_EN
#define ACCLIST_INT2_PINIDX       GPIO_PIN13
#define ACCLIST_INT2_PINCFG       GPIO_PIN13|GPIO_INT_FALLING|GPIO_CFG_PULLUP \
                                  |GPIO_INPUT|GPIO_ALT_GPIO|GPIO_PIN_VOLTAGE_VIO
#endif
#endif

/* External Panel Pins */
#if !defined(CONFIG_BES1700_ZE7_EVB)
#if defined(CONFIG_BES_LCD_GC9503NP)
#define GPIO_PANEL_RST  (GPIO_CFG_PULLUP|GPIO_OUTPUT |GPIO_ALT_GPIO|PMU_PIN1_3|GPIO_PIN_VOLTAGE_VIO) // pmu 1_3
#else
#define GPIO_PANEL_RST  (GPIO_CFG_PULLUP|GPIO_OUTPUT |GPIO_ALT_GPIO|GPIO_PIN34|GPIO_PIN_VOLTAGE_VIO)  // pin 4_2
#endif
#define GPIO_PANEL_1V8  (GPIO_CFG_PULLUP|GPIO_OUTPUT |GPIO_ALT_GPIO|PMU_PIN2_1|GPIO_PIN_VOLTAGE_VIO) // pin 2_1
#define GPIO_PANEL_2V8  (GPIO_CFG_PULLUP|GPIO_OUTPUT |GPIO_ALT_GPIO|PMU_PIN2_2|GPIO_PIN_VOLTAGE_VIO) // pin 2_2
#define GPIO_PANEL_3V3  (GPIO_CFG_PULLUP|GPIO_OUTPUT |GPIO_ALT_GPIO|PMU_PIN2_3|GPIO_PIN_VOLTAGE_VIO) // pin 2_3
#else
#define GPIO_PANEL_RST   (GPIO_CFG_PULLUP|GPIO_OUTPUT |GPIO_ALT_GPIO|GPIO_PIN58|GPIO_PIN_VOLTAGE_VIO)  // pin 7_2
#define GPIO_PANEL_RST2  (GPIO_CFG_PULLUP|GPIO_OUTPUT |GPIO_ALT_GPIO|GPIO_PIN89|GPIO_PIN_VOLTAGE_VIO)  // pin 11_1
#define GPIO_PANEL_1V8  (GPIO_CFG_PULLUP|GPIO_OUTPUT |GPIO_ALT_GPIO|GPIO_PIN26|GPIO_PIN_VOLTAGE_VIO) // pin 3_2
#define GPIO_PANEL_2V8  (GPIO_CFG_PULLUP|GPIO_OUTPUT |GPIO_ALT_GPIO|GPIO_PIN27|GPIO_PIN_VOLTAGE_VIO) // pin 3_3
#define GPIO_PANEL_3V3  (GPIO_CFG_PULLUP|GPIO_OUTPUT |GPIO_ALT_GPIO|GPIO_PIN13|GPIO_PIN_VOLTAGE_VIO) // pin 1_5
#endif
/*
* SPI device configuration,1700 default use spi1
*/
#ifdef CONFIG_BES_MODEM
#define CONFIG_SPI1_MODEM
#define SPILCD_IOMUX_4WIRE
#define SPILCD_IOMUX_CLK_INDEX        90
#define GPIO_MODEM_CS    GPIO_PIN73  // HAL_GPIO_PIN_P9_1
#define GPIO_MODEM_HRDY  GPIO_PIN61  // HAL_GPIO_PIN_P7_5
#define GPIO_MODEM_DRDY  GPIO_PIN62  // HAL_GPIO_PIN_P7_6
#define GPIO_MODEM_DINT  GPIO_PIN63  // HAL_GPIO_PIN_P7_7
#define GPIO_MODEM_DIRE  GPIO_PIN64  // HAL_GPIO_PIN_P8_0
#endif

/*
* EMMC PIN
*/
#ifndef EMMC_EXTENDED_USE
#define EMMC_EXTENDED_USE
#endif
#ifdef EMMC_EXTENDED_USE                    // default use
#define EMMC_DEV_RST_PIN  GPIO_PIN30        // HAL_IOMUX_PIN_P3_6
// #define EMMC_DEV_3V3_PIN  GPIO_PIN28        // HAL_IOMUX_PIN_P3_4
// #define EMMC_DEV_1V8_PIN  GPIO_PIN64        // HAL_IOMUX_PIN_P8_0
#else
#define EMMC_DEV_RST_PIN  GPIO_PIN30        // HAL_IOMUX_PIN_P3_6
// #define EMMC_DEV_3V3_PIN  GPIO_PIN118       // HAL_IOMUX_PIN_PMU2_3
// #define EMMC_DEV_1V8_PIN  GPIO_PIN116       // HAL_IOMUX_PIN_PMU2_1
#endif

/* SPI0 */
#   define GPIO_SPI0_CLK  (GPIO_CFG_NOPULL |GPIO_ALT_SYS_SPI0_CLK|GPIO_PIN32|GPIO_PIN_VOLTAGE_VIO)   /* pin 4_0 */
#   define GPIO_SPI0_CS0  (GPIO_CFG_NOPULL |GPIO_ALT_SYS_SPI0_CS0|GPIO_PIN33|GPIO_PIN_VOLTAGE_VIO)   /* pin 4_1 */
#   define GPIO_SPI0_DIO  (GPIO_CFG_NOPULL |GPIO_ALT_SYS_SPI0_DIO|GPIO_PIN35|GPIO_PIN_VOLTAGE_VIO)   /* pin 4_3 */
#   define GPIO_SPI0_DI0  (GPIO_CFG_NOPULL |GPIO_ALT_SYS_SPI0_DI0|GPIO_PIN34|GPIO_PIN_VOLTAGE_VIO)   /* pin 4_4  4 wire only*/

/* SPI1/SPILCD */

#   define GPIO_SPILCD_CLK  (GPIO_CFG_NOPULL |GPIO_ALT_SYS_SPI1_CLK|GPIO_PIN72|GPIO_PIN_VOLTAGE_VIO)   /* pin 9_0 */
#   define GPIO_SPILCD_CS0  (GPIO_CFG_NOPULL |GPIO_ALT_SYS_SPI1_CS0|GPIO_PIN73|GPIO_PIN_VOLTAGE_VIO)   /* pin 9_1 */
#   define GPIO_SPILCD_DIO  (GPIO_CFG_NOPULL |GPIO_ALT_SYS_SPI1_DIO|GPIO_PIN75|GPIO_PIN_VOLTAGE_VIO)  /* pin 9_3 */
#   define GPIO_SPILCD_DI0  (GPIO_CFG_NOPULL |GPIO_ALT_SYS_SPI1_DI0|GPIO_PIN74|GPIO_PIN_VOLTAGE_VIO)   /* pin 9_2 4 wire only*/
#   define GPIO_SPILCD_CS1  (GPIO_CFG_NOPULL |GPIO_ALT_SYS_SPI_CS1|GPIO_PIN10|GPIO_PIN_VOLTAGE_VIO)   /* pin 1_2 */
#   define GPIO_SPILCD_DI1  (GPIO_CFG_NOPULL |GPIO_ALT_SYS_SPI_DI1|GPIO_PIN22|GPIO_PIN_VOLTAGE_VIO)   /* pin 2_6 4 wire only*/


/*
*  gpio set exported to user space
*/

#define NUM_OUTPUT_EXPGPIO         0
#define NUM_INPUT_EXPGPIO          0
#define NUM_LEVELINT_EXPGPIO       0
#define NUM_EDGEINT_EXPGPIO        0


/*
*  speaker external PA enable pin
*/
#define  SPEAKER_EXT_PAEN_PINSET   GPIO_PIN18|GPIO_OUTPUT|GPIO_ALT_GPIO|GPIO_PIN_VOLTAGE_VIO  /* pin 2_2*/
#endif


/*
* battery and charger
*/

#define GPADC_CHAN_BATTERY   1
#define GPADC_ATP_ONESHOT   -1
#define GPADC_BAD_VALUE  0xFFFF

#define BES_BATTERY_LEVEL_MIN     0
#define BES_BATTERY_LEVEL_MAX     100
#define BES_BATTERY_STABLE_COUNT  5
#define BES_BATTERY_MONITOR_PERIODIC_US  1000000
#define BES_BATTERY_MEASURE_PERIODIC_NORMAL_MS   1000
#define BES_BATTERY_MIN_MV (3200)
#define BES_BATTERY_PD_MV   (3100)
#define BES_BATTERY_MAX_MV (4300)
#define BES_BATTERY_MV_BASE ((BES_BATTERY_MAX_MV-BES_BATTERY_PD_MV)/(100))

#define BES_BATT_OV_DELAY_1S   1000000
#define BES_BATT_OV_DELAY_2S   2000000
#define BES_BATT_OV_DELAY_3S   3000000
#define BES_BATT_OV_DELAY_4S   4000000
#define BES_BATT_OV_DELAY_8S   8000000


#define BES_BATT_UV_DELAY_1S   1000000
#define BES_BATT_UV_DELAY_2S   2000000
#define BES_BATT_UV_DELAY_3S   3000000
#define BES_BATT_UV_DELAY_4S   4000000
#define BES_BATT_UV_DELAY_8S   8000000
#define BES_BATT_UV_DELAY_16S  16000000


#define BES_BATTERY_CHARGE_OFFSET_MV  (20)
#define BES_CHARGER_PLUGINOUT_DEBOUNCE_MS   (50)
#define BES_BATTERY_CHARGING_SLOPE_TABLE_COUNT  (6)
#define BES_CHARGER_PLUGINOUT_DEBOUNCE_CNT (3)
#define BES_BATTERY_CHARGING_PERIODIC_MS (BES_BATTERY_MEASURE_PERIODIC_NORMAL_MS)
#define BES_BATTERY_CHARGING_EXTPIN_MEASURE_CNT (BES_BATTERY_CHARGING_PERIODIC_MS<2*1000?2*1000/BES_BATTERY_CHARGING_PERIODIC_MS:1)
#define BES_BATTERY_CHARGING_EXTPIN_DEDOUNCE_CNT (6)
#define BES_BATTERY_CHARGING_OVERVOLT_MEASURE_CNT (BES_BATTERY_CHARGING_PERIODIC_MS<2*1000?2*1000/BES_BATTERY_CHARGING_PERIODIC_MS:1)
#define BES_BATTERY_CHARGING_OVERVOLT_DEDOUNCE_CNT (3)
#define BES_BATTERY_CHARGING_SLOPE_MEASURE_CNT (BES_BATTERY_CHARGING_PERIODIC_MS<20*1000?20*1000/BES_BATTERY_CHARGING_PERIODIC_MS:1)
#define BES_BATTERY_CHARGE_TIMEOUT_MIN   (90)

#define BES_BATTERY_OPEN_MODE_CHARGING  1
#define BES_BATTERY_OPEN_MODE_NORMAL    0


/*
*   dvfs
*/

#define UP_THRESHOLD 20
#define DN_THRESHOLD 60
#define NUM_SYS_FREQ_POINTS   9

#define FREQ_MAXID 0
#define FREQ_MINID 8

#define FREQ_IDLE    208000
#define FREQ_NORMAL  208000
#define FREQ_STANDBY 208000
#define FREQ_DSLEEP  32  //32

#ifndef __ASSEMBLY__
enum SYSFREQ_USER_T {
    SYSFREQ_USER_IDLE,
    SYSFREQ_USER_CPUFREQ,
    SYSFREQ_USER_AUD_REC_1,
    SYSFREQ_USER_AUD_PLAY_2,
    SYSFREQ_USER_BT_IF_3,
    SYSFREQ_USER_WIFI_IF_4,
    SYSFREQ_USER_FLASH_IO_5,
    SYSFREQ_USER_QTY
};
#endif

#define DVFS_AUTO_USER 9

#define CODEC_SADC_VOL (5)
#ifdef CONFIG_AISPEECH_ALG
#define CODEC_MIC_CH0_SADC_VOL              5
#define CODEC_MIC_CH1_SADC_VOL              11
#define CODEC_MIC_CH2_SADC_VOL              11
#else
#ifdef CONFIG_ARCH_BOARD_CUSTOM_XIAOMI_M01
#define CODEC_MIC_CH0_SADC_VOL              3
#define CODEC_MIC_CH1_SADC_VOL              3
#define CODEC_MIC_CH2_SADC_VOL              0
#else
#define CODEC_MIC_CH0_SADC_VOL              1
#define CODEC_MIC_CH1_SADC_VOL              3
#define CODEC_MIC_CH2_SADC_VOL              3
#endif
#endif

#define CFG_HW_AUD_INPUT_PATH_NUM           (1)
#define AUD_INPUT_VMIC_CFG                  (AUD_VMIC_MAP_VMIC1)

#define SW_VOLUME_LEVEL_COUNT               (100)
#define TGT_VOLUME_LEVEL_COUNT              (TGT_VOLUME_LEVEL_QTY+SW_VOLUME_LEVEL_COUNT-16)

//config codec iir.
#define EQ_HW_DAC_IIR_LIST_NUM              1
#define EQ_HW_ADC_IIR_LIST_NUM              1
#define EQ_HW_IIR_LIST_NUM                  1
#define EQ_SW_IIR_LIST_NUM                  1
#define EQ_HW_FIR_LIST_NUM                  3

//#define CFG_HW_AUD_OUTPUT_POP_SWITCH (enum HAL_IOMUX_PIN_T)(((CONFIG_AUDIO_PA_SWITCH_GPIO/10)<<3)|(CONFIG_AUDIO_PA_SWITCH_GPIO%10))

#ifndef __ASSEMBLY__
int bes_enable_mic_regulator(bool flag);
#endif

#endif  /* __BOARDS_BEST1700_EP_INCLUDE_BOARD_BES1700_EVB_H */
