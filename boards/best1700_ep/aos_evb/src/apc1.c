/****************************************************************************
 * vendor/bes/boards/best1600_ep/src/ap.c
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

#ifdef CONFIG_BES1700_APC1
#include <stdint.h>
#include <assert.h>
#include <debug.h>
#include <ctype.h>

#include <nuttx/init.h>
#include <nuttx/timers/arch_rtc.h>
#include <nuttx/timers/rpmsg_rtc.h>
#include <nuttx/rptun/rptun.h>
#include <nuttx/serial/uart_rpmsg.h>
#include <nuttx/syslog/syslog_rpmsg.h>
#include <arch/board/board.h>
#include "nuttx/sched.h"
#include "sched/sched.h"
#include <sys/mount.h>
#include "arm_internal.h"
#include "nvic.h"
#include <sys/boardctl.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "bes_dvfs.h"
#include <stdio.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
extern void hal_sleep_start_stats(uint32_t stats_interval_ms, uint32_t trace_interval_ms);
extern void hal_trace_init_program_regions(void);
extern int bes_global_shmem_setup_syslog_buffer(void);
extern void hal_dma_open(void);
volatile bool btdrv_init_ok = true;
volatile bool wifidrv_init_ok = true;

void _start(void)
{
    //NVIC_UpdateVectors_cp((uint32_t)_vectors);
#if defined(CONFIG_BES_LPUART)
extern void hal_iomux_set_uart0(void);
extern void hal_iomux_set_uart1(void);
extern void hal_iomux_set_uart2(void);
#if defined(CONFIG_BES_LPUART0)
    hal_iomux_set_uart0();
    hal_trace_open(2);
#elif defined(CONFIG_BES_LPUART1)
    hal_iomux_set_uart1();
    hal_trace_open(3);
#elif defined(CONFIG_BES_LPUART2)
    hal_iomux_set_uart2();
    hal_trace_open(4);
#endif
    hal_trace_set_log_level(6);
    hal_trace_enable_log_module(0);
#endif

    bes_global_shmem_setup_syslog_buffer();

    nx_start();
    /* Shouldn't get here */
    for (; ; );
}


void bes_chip_init_early(void)
{
    hal_dma_open();
#if defined(CONFIG_ARCH_CHIP_DEBUG_H)
    hwtimer_init();
    extern void cp_subsys_trace_to_mcu(void);
    cp_subsys_trace_to_mcu();
#if !defined(CONFIG_BES_LPUART)
    hal_trace_open(0);
    hal_trace_set_log_level(6);
    hal_trace_enable_log_module(0);
#endif
#endif
    hal_sleep_start_stats(10000, 10000);
    hal_trace_init_program_regions();
}

#endif /* CONFIG_BES2003_CP */
