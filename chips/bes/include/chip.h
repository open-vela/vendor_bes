/************************************************************************************
 * arch/arm/include/bes/chip.h
 *
 *   Copyright (C) 2019 Gregory Nutt. All rights reserved.
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

#ifndef __ARCH_ARM_INCLUDE_BES_CHIP_H
#define __ARCH_ARM_INCLUDE_BES_CHIP_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <arch/chip/irq.h>

#ifndef __ASSEMBLY__
typedef long long __s64;
typedef unsigned char __u8;
extern unsigned int __boot_data_sram_start__[];
extern unsigned int __boot_bss_sram_end__[];
extern unsigned int __sram_data_start__[];
extern unsigned int __sram_bss_end__[];
extern unsigned int __data_start__[];
extern unsigned int __StackLimit[];
#ifndef CONFIG_BOARD_MEMORY_RANGE
#define CONFIG_BOARD_MEMORY_RANGE {__boot_data_sram_start__,__boot_bss_sram_end__,0x6}, \
                                  {__sram_data_start__,__sram_bss_end__,0x6}, \
                                  {__data_start__,__StackLimit,0x6}, \
                                  {0,0,0}
#endif
#endif

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

#define ARMV6M_PERIPHERAL_INTERRUPTS (NR_IRQS-16)
#define ARMV7M_PERIPHERAL_INTERRUPTS (NR_IRQS-16)
#define ARMV8M_PERIPHERAL_INTERRUPTS (NR_IRQS-16)

/* NVIC priority levels *************************************************************/

/* Each priority field holds a priority value. The lower the value, the greater the
 * priority of the corresponding interrupt.
 */

#if defined(CONFIG_ARCH_CORTEXM4)
/* The Cortex-M4F core supports 16 programmable interrupt priority levels. */

#  define NVIC_SYSH_PRIORITY_MIN        0xf0 /* All bits[7:4] set is minimum priority */
#  define NVIC_SYSH_PRIORITY_DEFAULT    0x80 /* Midpoint is the default */
#  define NVIC_SYSH_PRIORITY_MAX        0x00 /* Zero is maximum priority */
#  define NVIC_SYSH_PRIORITY_STEP       0x10 /* Steps between priorities */

#elif defined(CONFIG_ARCH_CORTEXM33)
/* The Cortex-M0+ core supports 4 programmable interrupt priority levels. */

#  define NVIC_SYSH_PRIORITY_MIN        0xf0 /* All bits[7:4] set is minimum priority */
#  define NVIC_SYSH_PRIORITY_DEFAULT    0x80 /* Midpoint is the default */
#  define NVIC_SYSH_PRIORITY_MAX        0x00 /* Zero is maximum priority */
#  define NVIC_SYSH_PRIORITY_STEP       0x20 /* Steps between priorities */
#elif defined(CONFIG_ARCH_CORTEXM55)
/* The Cortex-M0+ core supports 4 programmable interrupt priority levels. */

#  define NVIC_SYSH_PRIORITY_MIN        0xf0 /* All bits[7:4] set is minimum priority */
#  define NVIC_SYSH_PRIORITY_DEFAULT    0x80 /* Midpoint is the default */
#  define NVIC_SYSH_PRIORITY_MAX        0x00 /* Zero is maximum priority */
#  define NVIC_SYSH_PRIORITY_STEP       0x20 /* Steps between priorities */

#elif defined(CONFIG_ARCH_CORTEXM0)
/* The Cortex-M0+ core supports 4 programmable interrupt priority levels. */

#  define NVIC_SYSH_PRIORITY_MIN        0xc0 /* All bits[7:4] set is minimum priority */
#  define NVIC_SYSH_PRIORITY_DEFAULT    0x80 /* Midpoint is the default */
#  define NVIC_SYSH_PRIORITY_MAX        0x00 /* Zero is maximum priority */
#  define NVIC_SYSH_PRIORITY_STEP       0x40 /* Steps between priorities */

#endif

/************************************************************************************
 * Public Types
 ************************************************************************************/
#ifndef M_PI
#define M_PI       3.1415926535897932384626433832795029
#endif
/************************************************************************************
 * Public Data
 ************************************************************************************/

/************************************************************************************
 * Public Functions
 ************************************************************************************/
#ifdef __ASSEMBLY__

/****************************************************************************
 * Name: setirqstack
 *
 * Description:
 *   Set the current stack pointer to the  -"top" of the IRQ interrupt
 *   stack for the current CPU.
 *
 ****************************************************************************/

#if defined(CONFIG_SMP) && CONFIG_ARCH_INTERRUPTSTACK > 7
  .macro  setintstack, tmp1, tmp2
  ldr  \tmp2, =SCB_ID_ADR
  ldr \tmp1, [\tmp2]
  and  \tmp1, \tmp1, #3          /* Bits 0-1=CPU ID */
  ldr  \tmp2, =g_cpu_intstack_top    /* tmp2=Array of IRQ stack pointers */
  lsls \tmp1, \tmp1, #2          /* tmp1=Array byte offset */
  add  \tmp2, \tmp2, \tmp1       /* tmp2=Offset address into array */
  ldr  \tmp1, [\tmp2, #0]        /* tmp1=Address in stack allocation */
  mov     sp, \tmp1                  /* Instantiate the aligned stack */
  sub  \tmp2, \tmp1, #CONFIG_ARCH_INTERRUPTSTACK       /* Reserve signal context */
  bic  \tmp2, \tmp2, #7              /* Get the stack pointer with 8-byte alignment */
#ifdef CONFIG_ARMV8M_STACKCHECK_HARDWARE
  msr     msplim, \tmp2
#endif
  .endm
#endif
#endif

#endif /* __ARCH_ARM_INCLUDE_BES_CHIP_H */
