/****************************************************************************
 * vendor/bes/boards/best1700_ep/src/audio.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#ifdef CONFIG_BES1700_AUDIO

#include <nuttx/cache.h>
#include <nuttx/serial/uart_rpmsg.h>
#include <nuttx/power/pm.h>
#include "hwtimer_list.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_late_initialize
 *
 * Description:
 *   If CONFIG_BOARD_LATE_INITIALIZE is selected, then an additional
 *   initialization call will be performed in the boot-up sequence to a
 *   function called board_late_initialize().  board_late_initialize() will
 *   be called immediately after up_initialize() is called and just before
 *   the initial application is started.  This additional initialization
 *   phase may be used, for example, to initialize board-specific device
 *   drivers.
 *
 ****************************************************************************/

#ifdef CONFIG_BOARD_LATE_INITIALIZE
void board_late_initialize(void)
{
  /* Perform board-specific initialization */
#ifdef CONFIG_RPTUN
#if defined(CONFIG_BES_RPTUN_AP2DSP)
  extern int up_rptun_init_ap2dsp(void);
  up_rptun_init_ap2dsp();
#endif
#if defined(CONFIG_BES_RPTUN_APC12DSP)
  extern int up_rptun_init_apc12dsp(void);
  up_rptun_init_apc12dsp();
#endif
#endif

#ifdef CONFIG_AUDIO
  extern uint32_t af_open(void);
  af_open();
#endif
}
#endif /* CONFIG_BOARD_LATE_INITIALIZE */

#ifdef CONFIG_RPMSG_UART
void rpmsg_serialinit(void)
{
#ifdef CONFIG_BES_RPTUN_AP2DSP
#ifdef CONFIG_BES_GEN_HIFI_BIN
    uart_rpmsg_init("ap", "AUDIO", 4096, true);
#else
    uart_rpmsg_init("audio", "AUDIO", 4096, false);
#endif
#endif
}
#endif

int board_app_initialize(uintptr_t arg)
{
  return 0;
}

#ifdef CONFIG_BOARDCTL_FINALINIT
int board_app_finalinitialize(uintptr_t arg)
{
#if defined(CONFIG_BES_AUDIO_RAW_DATA_DUMP) && defined(CONFIG_AUDIO_RPMSG_CLIENT)
  extern void dump_init(void);
  dump_init();
#endif
  return 0;
}
#endif

#ifdef CONFIG_BOARD_EARLY_INITIALIZE
void board_early_initialize()
{
#if !defined(CONFIG_DISABLE_ENVIRON) && defined(CONFIG_SYSLOG_TIMESTAMP_LOCALTIME)
  setenv("TZ", CONFIG_TZ_INITIAL, 1);
#endif
#if defined(CONFIG_CALIB_SLOW_TIMER)
  extern void hal_sys_timer_calib(void);
  hal_sys_timer_calib();
#endif
#if !defined(CONFIG_USE_SLOW_TIMER)
  hwtimer_init();
#endif
#ifdef CONFIG_XTENSA_ICACHE
  up_enable_icache();
#endif
#ifdef CONFIG_XTENSA_DCACHE
  up_enable_dcache();
#endif
  extern int bes_xtansa_mpu_init(void);
  //bes_xtansa_mpu_init();

#if defined(CONFIG_AUDIO_RPMSG_CLIENT)
  extern int rpmsg_audio_initialize(int minor);
  rpmsg_audio_initialize(0);
#endif

#ifdef CONFIG_BES_AUDIO_CLIENT
  extern int bes_audio_client_initialize(void);
  bes_audio_client_initialize();
#endif

#if defined(CONFIG_WATCHDOG)
  extern int bes_wdt_initialize(void);
  bes_wdt_initialize();
#endif
}
#endif

#endif /* CONFIG_BES1700_AUDIO */
