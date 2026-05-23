/****************************************************************************
 * vendor/bes/boards/best1700_ep/include/board.h
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

#ifndef __BOARDS_BEST1700_EP_INCLUDE_BOARD_H
#define __BOARDS_BEST1700_EP_INCLUDE_BOARD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifndef __ASSEMBLY__
#  include <stdint.h>
#  include <stdbool.h>
extern uint32_t _nuttx_heap_end;
#endif

#undef CONFIG_RAM_END
#define CONFIG_RAM_END ((unsigned)&_nuttx_heap_end)

#define PERFORMANCE_DEBUG 0
#if !defined(CONFIG_BES_FLASH_SUSPEND)
//#define LARGE_ERASE_BLOCK
#endif

#define BES_FLASH_BASE FLASH_NC_BASE
#define BES_FLASH_SIZE CONFIG_CHIP_FLASH_SIZE

#ifdef CONFIG_FLASH_DUAL_CHIP
#define BES_FLASH_PAGESIZE (256 * 2)
#else
#define BES_FLASH_PAGESIZE (256)
#endif

#define KPAGES (1024/BES_FLASH_PAGESIZE)
#ifdef LARGE_ERASE_BLOCK
#define ERASE_PAGE   (32*KPAGES)
#define MTD_BES_RESERVED_PAGE   (64*KPAGES)
#else
#ifdef CONFIG_FLASH_DUAL_CHIP
#define ERASE_PAGE   (8*KPAGES)
#else
#define ERASE_PAGE   (4*KPAGES)
#endif
#define MTD_BES_RESERVED_PAGE   (112*KPAGES)
#endif

#define BES_FLASH_SEC_SIZE         0x400000
#define BES_FLASH_SEC_PAGESIZE     256
#define BES_FLASH_SEC_DATAEXT_SIZE 0x400000


#define FLASH_BL_SIZE   (256*1024)   // bl: bootloader 256K(0x40000)
//#define FLASH_BL2_SIZE  (512*1024)   // bl2 : bl2 (0x80000)

#ifndef FLASH_BL2_SIZE
#ifdef CONFIG_FLASH_DUAL_CHIP
#define FLASH_OTA_SIZE  (640*1024)   // ota : 640K(0xA0000)
#define FLASH_OTA_BACKUP_SIZE  (640*1024) // ota backup: 640K
#else
#define FLASH_OTA_SIZE  (608*1024)   // ota : 608K
#define FLASH_OTA_BACKUP_SIZE  (608*1024) // ota backup: 608K
#endif
#define FLASH_OTAINFO_SIZE  (64*1024) // ota info 64K(0x10000)
#endif

#define FLASH_TEE_SIZE  (1344*1024) // tee: 1344K
#define FLASH_SST_SIZE  (128*1024) // sst: 128K secure storage for tee
#define FLASH_APP_SIZE  (8256*1024) // ap: 9.5M
#define FLASH_APC1_SIZE  (5*512*1024) // apc1: 2.5M
#define FLASH_AUDIO_SIZE  (2368*1024)
#define FLASH_BTH_SIZE  (3*1024*1024)
#define FLASH_BTH_CP_SIZE  (764*1024)
#define FLASH_BTH_MISC_SIZE  (256*1024)
#define FLASH_BTH_FACTORY_SIZE  (4*1024)

#if defined(CONFIG_MTD)
#define FLASH_DATA_SIZE       (5*1024*1024) // data: 1M
#endif
#define FLASH_MISC_SIZE       (128 *1024) // misc: misc

#if defined(CONFIG_BES_CORE_BL) || defined(CONFIG_BES_CORE_BL2) || defined(CONFIG_BES_CORE_OTA) || defined(CONFIG_BES_CORE_AP)
#ifdef FLASH_BL2_SIZE
#if !defined(CONFIG_RECOVERY_SUPPORT) || (CONFIG_RECOVERY_BIN_SIZE < (FLASH_BL_SIZE+FLASH_BL2_SIZE))
#error "BL2 need CONFIG_RECOVERY_SUPPORT and CONFIG_RECOVERY_BIN_SIZE >= (FLASH_BL_SIZE+FLASH_BL2_SIZE)"
#endif
#else
#if defined(CONFIG_RECOVERY_SUPPORT) && (CONFIG_RECOVERY_BIN_SIZE < (FLASH_BL_SIZE+FLASH_OTA_SIZE+FLASH_OTA_BACKUP_SIZE+FLASH_OTAINFO_SIZE))
#error "CONFIG_RECOVERY_SUPPORT need CONFIG_RECOVERY_BIN_SIZE >=  (FLASH_BL_SIZE+FLASH_OTA_SIZE+FLASH_OTA_BACKUP_SIZE+FLASH_OTAINFO_SIZE)"
#endif
#if !defined(CONFIG_RECOVERY_SUPPORT) &&  (CONFIG_RECOVERY_BIN_SIZE != 0)
#error "CONFIG_RECOVERY_BIN_SIZE must set to 0"
#endif
#endif
#endif

#ifdef CONFIG_WITHOUT_OS
#ifdef CONFIG_FLASH_DUAL_CHIP
#if FLASH_BL_SIZE < 2*CONFIG_BIN_FLASH_SIZE
#error "FLASH_DUAL_CHIP FLASH_BL_SIZE >= 2*CONFIG_BIN_FLASH_SIZE"
#endif
#else
#if FLASH_BL_SIZE < CONFIG_BIN_FLASH_SIZE
#error "need FLASH_BL_SIZE >= CONFIG_BIN_FLASH_SIZE"
#endif
#endif
#endif


#ifdef LARGE_ERASE_BLOCK
#define BOARDMISC_OFFSET    (8*1024)
#else
#define BOARDMISC_OFFSET    (0*1024)
#endif

#ifndef BOARD_FLASH_PTABLE

#if defined(CONFIG_RECOVERY_SUPPORT)
#ifdef FLASH_BL2_SIZE
#define BOARD_FLASH_PTABLE_RECOVER_PART \
  {\
    .name       = "bl2",\
    .firstblock = (FLASH_BL_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_BL2_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\

#else
#define BOARD_FLASH_PTABLE_RECOVER_PART \
  {\
    .name       = "ota_b",\
    .firstblock = (FLASH_BL_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_OTA_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\
  {\
    .name       = "ota",\
    .firstblock = ((FLASH_BL_SIZE+FLASH_OTA_SIZE)/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_OTA_BACKUP_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\
  {\
    .name       = "ota_info",\
    .firstblock = ((FLASH_BL_SIZE+FLASH_OTA_SIZE+FLASH_OTA_BACKUP_SIZE)/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_OTAINFO_SIZE/2/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\
  {\
    .name       = "ota_flag",\
    .firstblock = ((FLASH_BL_SIZE+FLASH_OTA_SIZE+FLASH_OTA_BACKUP_SIZE+FLASH_OTAINFO_SIZE/2)/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_OTAINFO_SIZE/2/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\

#endif /* FLASH_BL2_SIZE */
#endif /* CONFIG_RECOVERY_SUPPORT */


#if defined(CONFIG_BES_CORE_OTA) || defined(CONFIG_ARCH_TRUSTZONE_SECURE)

#define BOARD_FLASH_PTABLE_FIRST \
  {\
    .name       = "tee",\
    .firstblock = (CONFIG_RECOVERY_BIN_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_TEE_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\
  {\
    .name       = "sst",\
    .firstblock = ((CONFIG_RECOVERY_BIN_SIZE+FLASH_TEE_SIZE)/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_SST_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\

#endif

#define BOARD_FLASH_PTABLE \
  {\
    .name       = "ap",\
    .firstblock = ((CONFIG_RECOVERY_BIN_SIZE+FLASH_TEE_SIZE+FLASH_SST_SIZE)/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_APP_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\
  {\
    .name       = "apc1",\
    .firstblock = ((CONFIG_RECOVERY_BIN_SIZE+FLASH_TEE_SIZE+FLASH_SST_SIZE+FLASH_APP_SIZE)/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_APC1_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\
  {\
    .name       = "hifi",\
    .firstblock = ((CONFIG_RECOVERY_BIN_SIZE+FLASH_TEE_SIZE+FLASH_SST_SIZE+FLASH_APP_SIZE+FLASH_APC1_SIZE)/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_AUDIO_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\

#define BOARD_FLASH_PTABLE_REMAIN \
  /* the last 128K is used for other  partition*/ \
  {\
    .name       = "misc", /*now misc is fixed at offset 120 or 128 to compatible with DVT1 machine*/ \
    .firstblock = (BES_FLASH_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE - MTD_BES_RESERVED_PAGE - ERASE_PAGE - ERASE_PAGE, \
    .nblocks    = ERASE_PAGE,\
  },\
  {\
    .name       = "bootinfo",\
    .firstblock = (BES_FLASH_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE - MTD_BES_RESERVED_PAGE - ERASE_PAGE,\
    .nblocks    = ERASE_PAGE,\
  },\
  {\
    .name       = "bes_reserved",\
    .firstblock = (BES_FLASH_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE - MTD_BES_RESERVED_PAGE,\
    .nblocks    = MTD_BES_RESERVED_PAGE - ERASE_PAGE,\
  },\
  {\
    .name       = "factory",\
    .firstblock = (BES_FLASH_SIZE/BES_FLASH_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE - ERASE_PAGE,\
    .nblocks    = ERASE_PAGE,\
  },\

#ifndef BOARD_FLASH_SECOND_PTABLE
#define BOARD_FLASH_SECOND_PTABLE \
  {\
    .name       = "bth",\
    .firstblock = 0, \
    .nblocks    = (FLASH_BTH_SIZE/BES_FLASH_SEC_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\
  {\
    .name       = "bthcp",\
    .firstblock = (FLASH_BTH_SIZE/BES_FLASH_SEC_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_BTH_CP_SIZE/BES_FLASH_SEC_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\
  {\
    .name       = "bth_misc",\
    .firstblock = ((FLASH_BTH_SIZE+FLASH_BTH_CP_SIZE)/BES_FLASH_SEC_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_BTH_MISC_SIZE/BES_FLASH_SEC_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\
  {\
    .name       = "bth_factory",\
    .firstblock = ((FLASH_BTH_SIZE+FLASH_BTH_CP_SIZE+FLASH_BTH_MISC_SIZE)/BES_FLASH_SEC_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
    .nblocks    = (FLASH_BTH_FACTORY_SIZE/BES_FLASH_SEC_PAGESIZE + ERASE_PAGE - 1)/ERASE_PAGE*ERASE_PAGE,\
  },\

#endif /* BOARD_FLASH_SECOND_PTABLE */
#endif /* BOARD_FLASH_PTABLE */

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clocking *****************************************************************/

/* The BES1700 is fitted with a 16384 Crystal */

#define BOARD_XTAL_FREQUENCY 16384

#ifdef CONFIG_BES1700_AUDIO
#  define BOARD_CLOCK_FREQUENCY CONFIG_HIFI4_CLOCK_FREQUENCY
#endif

/* If CONFIG_ARCH_LEDs is defined, then NuttX will control the LEDs on board
 * the BES1302EVB.  The following definitions describe how NuttX controls the
 * LEDs:
 *
 *   SYMBOL                Meaning                      LED state
 *                                                      RED   GREEN  BLUE
 *   -------------------  ----------------------------  -----------------
 */

#define LED_STARTED       1 /* NuttX has been started    OFF   OFF    OFF */
#define LED_HEAPALLOCATE  2 /* Heap has been allocated   OFF   OFF    ON  */
#define LED_IRQSENABLED   0 /* Interrupts enabled        OFF   OFF    ON  */
#define LED_STACKCREATED  3 /* Idle stack created        OFF   ON     OFF */
#define LED_INIRQ         0 /* In an interrupt          (no change)       */
#define LED_SIGNAL        0 /* In a signal handler      (no change)       */
#define LED_ASSERTION     0 /* An assertion failed      (no change)       */
#define LED_PANIC         4 /* The system has crashed    FLASH OFF    OFF */
#undef  LED_IDLE            /* BES1302EVB in sleep mode (Not used)        */


/* Alternate function pin selections ****************************************/

/* By default, the serial console will be provided on the OpenSDA VCOM port:
 *
 *   OpenSDA UART TX  PTC7 (LPUART1_TX)
 *   OpenSDA UART RX  PTC6 (LPUART1_RX)
 */

#define PIN_LPUART1_RX    PIN_LPUART1_RX_1  /* PTC6 */
#define PIN_LPUART1_TX    PIN_LPUART1_TX_1  /* PTC7 */

/*
*   System Power Control definitions
*   XXX_PDOMAIN - module power domain index
*   XXX_ACTIVITY_PRIORITY - act power priority, range from 0 to 9,
*                           larger number means higher priority
*/

#define ADC_BUTTON_PDOMAIN                0
#define ADC_BUTTON_ACTIVITY_PRIORITY      9

#define GPIO_BUTTON_PDOMAIN               0
#define GPIO_BUTTON_ACTIVITY_PRIORITY     9

#define GPIO_IR_PDOMAIN                   0
#define GPIO_IR_ACTIVITY_PRIORITY         8


#define CONSOLE_IO_PDOMAIN                0
#define CONSOLE_IO_ACTIVITY_PRIORITY      9


#define FLASH_IO_PDOMAIN                  0
#define FLASH_IO_ACTIVITY_PRIORITY        2

#define CPULOAD_TIMER_PDOMAIN             0
#define CPULOAD_TIMER_ACTIVITY_PRIORITY   2

#define RPMSG_IO_PDOMAIN                  0
#define RPMSG_IO_ACTIVITY_PRIORITY        2


#define I2C_IO_PDOMAIN                    0
#define I2C_IO_ACTIVITY_PRIORITY          2


#define SPI_IO_PDOMAIN                    0
#define SPI_IO_ACTIVITY_PRIORITY          2


#define UART_IO_PDOMAIN                   0
#define UART_IO_ACTIVITY_PRIORITY         2


#define WIFI_IO_PDOMAIN                   0
#define WIFI_IO_ACTIVITY_PRIORITY         8


#define BT_IO_PDOMAIN                     0
#define BT_IO_ACTIVITY_PRIORITY           8

#ifdef CONFIG_DSI_VIDEO_MODE
#define BOARD_LCDC_HFP                  80
#define BOARD_LCDC_HBP                  80
#define BOARD_LCDC_VFP                  24
#define BOARD_LCDC_VBP                  24
#define BOARD_LCDC_HSYNC                1
#define BOARD_LCDC_VSYNC                1
#else
#define BOARD_LCDC_HFP                  12
#define BOARD_LCDC_HBP                  10
#define BOARD_LCDC_VFP                  10
#define BOARD_LCDC_VBP                  10
#define BOARD_LCDC_HSYNC                10
#define BOARD_LCDC_VSYNC                2
#endif
#define BOARD_LCDC_GCR_DEN              1
#define BOARD_LCDC_GCR_DBW              5
#define BOARD_LCDC_GCR_DGW              6
#define BOARD_LCDC_GCR_DRW              5

#if defined(CONFIG_ARCH_BOARD_CUSTOM_BES1700_EVB)
#include <arch/board/board_bes1700_evb.h>
#endif

#if defined(CONFIG_LV_USE_GPU_INTERFACE) && ((BOARD_LCDC_WIDTH*BOARD_LCDC_HEIGHT%16) != 0)
#define CONFIG_ZOOM_TO_SCREEN
#undef BOARD_LCDC_HEIGHT
#undef BOARD_LCDC_WIDTH
#ifdef CONFIG_LCD_RM69330
#define BOARD_LCDC_HEIGHT           454
#define BOARD_LCDC_WIDTH            454
#else
#define BOARD_LCDC_HEIGHT           480
#define BOARD_LCDC_WIDTH            480
#endif
#endif

#endif  /* __BOARDS_BEST1700_EP_INCLUDE_BOARD_H */
