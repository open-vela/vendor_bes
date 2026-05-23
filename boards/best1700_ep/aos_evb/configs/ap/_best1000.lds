/***************************************************************************
 *
 * Copyright 2015-2019 BES.
 * All rights reserved. All unpublished rights reserved.
 *
 * No part of this work may be used or reproduced in any form or by any
 * means, or stored in a database or retrieval system, without prior written
 * permission of BES.
 *
 * Use of this work is governed by a license granted by BES.
 * This work contains confidential and proprietary information of
 * BES. which is protected by copyright, trade secret,
 * trademark and other intellectual property rights.
 *
 ****************************************************************************/
/***************************************************************************
 *
 * Copyright 2015-2020 BES.
 * All rights reserved. All unpublished rights reserved.
 *
 * No part of this work may be used or reproduced in any form or by any
 * means, or stored in a database or retrieval system, without prior written
 * permission of BES.
 *
 * Use of this work is governed by a license granted by BES.
 * This work contains confidential and proprietary information of
 * BES. which is protected by copyright, trade secret,
 * trademark and other intellectual property rights.
 *
 ****************************************************************************/
/***************************************************************************
 *
 * Copyright 2020-2022 BES.
 * All rights reserved. All unpublished rights reserved.
 *
 * No part of this work may be used or reproduced in any form or by any
 * means, or stored in a database or retrieval system, without prior written
 * permission of BES.
 *
 * Use of this work is governed by a license granted by BES.
 * This work contains confidential and proprietary information of
 * BES. which is protected by copyright, trade secret,
 * trademark and other intellectual property rights.
 *
 ****************************************************************************/
/* Hardware definitions */
/* M55 TCM CORE VIEW */
/* For MPC config */
/* M55 TCM AXI VIEW */
/* HIFI4 TCM CORE VIEW */
/* HIFI4 TCM AXI VIEW */
/* SYS RAM0/1/2/3 share with M55/HIFI4 I/DTCM */
/* For MPC config */
/* BTH AHB/APB */
/* BTH is always non-secured */
/* AON AHB */
/* SYS AXI/AHB/APB */
/* RAM config */
/***************************************************************************
 *
 * Copyright 2021-2023 BES.
 * All rights reserved. All unpublished rights reserved.
 *
 * No part of this work may be used or reproduced in any form or by any
 * means, or stored in a database or retrieval system, without prior written
 * permission of BES.
 *
 * Use of this work is governed by a license granted by BES.
 * This work contains confidential and proprietary information of
 * BES. which is protected by copyright, trade secret,
 * trademark and other intellectual property rights.
 *
 ****************************************************************************/
/* Avoid using M55C1/BTHC1 by default when SLEEP_PD_CURRENT_TEST=1 */
/*
#define WIFI_SHR_RAM_UPPER_ADDR
*/
/* RAM config */
/* Mailbox config */
/* RAM config checks (only check in lds file, the first compiled file during build) */
/* Self definition check */
/* Cross sys ram check */
/* Cross shared ram check */
/* Bth ram check */
/* Aon mbx internal check */
/* Chip subtype definitions */
/***************************************************************************
 *
 * Copyright 2020-2022 BES.
 * All rights reserved. All unpublished rights reserved.
 *
 * No part of this work may be used or reproduced in any form or by any
 * means, or stored in a database or retrieval system, without prior written
 * permission of BES.
 *
 * Use of this work is governed by a license granted by BES.
 * This work contains confidential and proprietary information of
 * BES. which is protected by copyright, trade secret,
 * trademark and other intellectual property rights.
 *
 ****************************************************************************/
/* Always reserve mailbox size for m55c1/dspc0 sleep ctrl */
/* To program SYS flash images */
/* Skip BTH cache by using BTH uncached address space of BTH flash */
/* DMA trigger timer is timer 1 sub id 1 */
/*
#define BTDUMP_BASE                             BTH_BTDUMP_BASE
*/
/*HIFI use SYS_DMA2_BASE */
/* For module features */
/* #define AHB_DMA_MULTI_MASTER */
/* #define AHB_DMA_WRITE_EARLY_RESP */
/* MPU table */
/* TODO: Generate mpu table for:
   (1) NO_MPU_DEFAULT_MAP
   (2) ARM_CMSE
   (3) ARM_CMNS
*/
/* For compatibility */
/* For linker scripts */
/* For module features */
/* #define CMU_FAST_TIMER_WITH_LOW_SYS_FREQ */
/* #define FLASH_CACHE_DOUBLE_LINEFILL */
/* #define PSRAM_CACHE_DOUBLE_LINEFILL */
/* LCDC features */
/* For boot struct version */
/* #define RSA_RAW_KEY_IN_ROM */
/* Since version G */
/* For ROM export functions */
/* 64M Bytes */
/* Common RAM config checks (only check in lds file, the first compiled file during build) */
/* Definitions for lds only */
/* Always define FLASH_REGION_BASE for subsys lds */
/* config.h -- Autogenerated! Do not edit. */
/* Used to represent the values of tristate options */
/* General Definitions ***********************************/
/* Sanity Checks *****************************************/
/* If the end of RAM is not specified then it is assumed to be
 * the beginning of RAM plus the RAM size.
 */
/* If the end of FLASH is not specified then it is assumed to be
 * the beginning of FLASH plus the FLASH size.
 */
/* For FLASH image size check */
/* Linker script to configure memory regions. */
/* See plat_addr_map.h and common.mk for the macro definitions */
MEMORY
{
 ROM (rx) : ORIGIN = 0x04020000, LENGTH = 0x00018000
 FLASH (rx) : ORIGIN = (0x10000000 + 0x190000), LENGTH = (0x1000000 - ((0x10000000 + 0x190000) - 0x10000000))
 FLASH_NC (r) : ORIGIN = (((0x10000000 + 0x190000)) - 0x10000000 + 0x30000000), LENGTH = (0x1000000 - ((0x10000000 + 0x190000) - 0x10000000))
 RAM (rwx) : ORIGIN = (((0x21100000 - 0x21000000 + 0x20000000)) & ~0x04000000), LENGTH = ((((0x21100000 - 0x21000000 + 0x20000000)) & ~0x04000000) + (0x00200000 - (0 + 0 + 0x20)) - (((0x21100000 - 0x21000000 + 0x20000000)) & ~0x04000000))
 RAMX (rx) : ORIGIN = (((0x21900000 - (0x21800000 + ((0x0 + 0x00100000) - 0x0)) + (0x0 + 0x00100000))) & ~0x04000000), LENGTH = ((((0x21900000 - (0x21800000 + ((0x0 + 0x00100000) - 0x0)) + (0x0 + 0x00100000))) & ~0x04000000) + 0x00100000 - (((0x21900000 - (0x21800000 + ((0x0 + 0x00100000) - 0x0)) + (0x0 + 0x00100000))) & ~0x04000000))
 RAM_EXTRA0 (rw) : ORIGIN = 0x02500000, LENGTH = 0x00000000
 PSRAM (rwx) : ORIGIN = (0x18000000 + 0), LENGTH = 0x3700000
 PSRAM_NC (rwx) : ORIGIN = (((0x18000000 + 0)) - 0x18000000 + 0x38000000), LENGTH = 0x3700000
 AON_MAILBOX (rw) : ORIGIN = 0x23C00000, LENGTH = (0x0000B000 - 0x20)
}
/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __export_fn_rom
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __free_ram
 *   __factory_start
 *   __factory_end
 *   __calib_start
 *   __calib_end
 *   __flash_start
 *   __flash_end
 *   __free_flash
 *   __flash1_start
 *   __flash1_end
 *   __free_flash1
 *   __boot_text_sram_start_flash__
 *   __boot_text_sram_end_flash__
 *   __boot_text_sram_start__
 *   __boot_text_sram_end__
 *   __boot_data_sram_start_flash__
 *   __boot_data_sram_end_flash__
 *   __boot_data_sram_start__
 *   __boot_data_sram_end__
 *   __boot_bss_sram_start__
 *   __boot_bss_sram_end__
 *   __sram_text_start_flash__
 *   __sram_data_end_flash__
 *   __fast_sram_text_data_start__
 *   __fast_sram_text_data_end__
 *   __fast_sram_text_start_flash__
 *   __fast_sram_text_end_flash__
 *   __sram_text_data_start__
 *   __sram_bss_start__
 *   __sram_bss_end__
 *   __overlay_text_start__
 *   __overlay_text_exec_start__
 *   __overlay_data_start__
 */
ENTRY(Boot_Loader)
SECTIONS
{
 __export_fn_rom = (ORIGIN(ROM) + LENGTH(ROM) - 40 - 128);
 .boot_struct (ORIGIN(FLASH)) :
 {
  __flash_start = .;
  KEEP(*(.boot_struct))
  . = ALIGN(4);
 } > FLASH
 . = ((.) - 0x10000000 + 0x10000000);
 .boot_text_flash (.) : AT (((ADDR(.boot_text_flash)) - 0x10000000 + 0x10000000))
 {
  __flashx_start_addr__ = .;
  *(.boot_loader)
  *(.boot_text_flash*)
  . = ALIGN(4);
 } > FLASH
 . = ((.) - 0x10000000 + 0x10000000);
 .boot_data_flash (.) :
 {
  *(.boot_rodata_flash*)
  . = ALIGN(4);
 } > FLASH
 .got_info (.) :
 {
  __got_info_start = .;
  __got_plt_start = .;
  *(.got.plt)
  __got_plt_end = .;
  __got_start = .;
  *(.got)
  __got_end = .;
  . = ALIGN(4);
 } > FLASH
 .vector_table (ORIGIN(RAM)) (NOLOAD) :
 {
  __vector_table_start = .;
  KEEP(*(.vector_table))
  . = 1024;
  . = ALIGN(4);
 } > RAM
 .reboot_param (NOLOAD) :
 {
  KEEP(*(.reboot_param*))
  . = 64;
  . = ALIGN(4);
 } > RAM
 .userdata_pool (NOLOAD) :
 {
  *(.userdata_pool)
  . = ALIGN(4);
 } > RAM
 __boot_text_sram_start_flash__ = LOADADDR(.got_info) + SIZEOF(.got_info);
 .boot_text_sram
  (ALIGN(ORIGIN(RAMX), 32))
  : AT (__boot_text_sram_start_flash__)
 {
  __boot_text_sram_start__ = .;
  _stext = __boot_text_sram_start__;
  /* memcpy.o/memcpy_move-kp.o or libc_nano.a(lib_a-memcpy.o/lib_a-memcpy-stub.o) */
  *:memcpy*.o(.text*)
  *:lib_a-memcpy*.o(.text*)
  *:libc_rom.o(.text*)
  *:libc_rom_mem.o(.text*)
  /* memset.o/memset-kp.o or libc_nano.a(lib_a-memset.o) */
  *:memset*.o(.text*)
  *:aeabi_memset.o(.text*)
  *:aeabi_memset-soft.o(.text*)
  *:lib_a-memset*.o(.text*)
  *:lib_memset*.o(.text*)
  *:*arch_mem*.o(.text*)
  *:*arch_str*.o(.text*)
  *:bin(.text*)
  *:irq_*.o(.text*)
  *:main_bl*.o(.text*)
  *:hook.o(.text*)
  *:hal_norflash*.o(.text*)
  *:norflash_*.o(EXCLUDE_FILE(*:norflash_api.o) .text*)
  *:hal_*cmu_*.o(.text*)
  *:stack_protector*.o(.text*)
  *:hal_iomux_*.o(.text*)
  *:hal_analogif_*.o(.text*)
  *:hal_phyif.o(.text*)
  *:hal_spi.o(.text*)
  *:hal_i2c.o(.text*)
  *:hal_timer.o(.text*)
  *:hal_sysfreq.o(.text*)
  *:hal_apsram*.o(.text*)
  *:apsram_*.o(.text*)
  *:hal_psram*.o(.text*)
  *:psram_drv*.o(.text*)
  *:psram_opi*.o(.text*)
  *:psram_xopi*.o(.text*)
  *:hal_trace*.o(.text*)
  *:pmu_*.o(.text*)
  *:hal_sleep.o(.text*)
  *(.boot_text_sram*)
  . = ALIGN(32);
  __boot_text_sram_end__ = .;
 } > RAMX
 __boot_text_data_sram_start__ = (__boot_text_sram_start__);
 __boot_text_sram_end_flash__ = __boot_text_sram_start_flash__ + SIZEOF(.boot_text_sram);
 __boot_data_sram_start_flash__ = __boot_text_sram_end_flash__;
 .boot_data_sram
  : AT (__boot_data_sram_start_flash__)
 {
  __boot_data_sram_start__ = .;
  *:hal_norflash*.o(.data* .rodata*)
  *:norflash_*.o(EXCLUDE_FILE(*:norflash_api.o) .data* EXCLUDE_FILE(*:norflash_api.o) .rodata*)
  *:libc_rom.o(.rodata*)
  *:libc_rom_mem.o(.rodata*)
  *:irq_*.o(.data* .rodata*)
  *:nx_start*.o(.data* .rodata*)
  *:bes_start*.o(.data* .rodata*)
  *:main_bl*.o(.data* .rodata*)
  *:hook.o(.data* .rodata*)
  *:hal_*cmu_*.o(.data* .rodata*)
  *:stack_protector*.o(.data* .rodata*)
  *:hal_iomux_*.o(.data* .rodata*)
  *:hal_analogif_*.o(.data* .rodata*)
  *:hal_phyif.o(.data* .rodata*)
  *:hal_spi.o(.data* .rodata*)
  *:hal_i2c.o(.data* .rodata*)
  *:hal_timer.o(.data* .rodata*)
  *:hal_sysfreq.o(.data* .rodata*)
  *:hal_apsram*.o(.data* .rodata*)
  *:apsram_*.o(.data* .rodata*)
  *:hal_psram*.o(.data* .rodata*)
  *:psram_drv*.o(.data* .rodata*)
  *:psram_opi*.o(.data* .rodata*)
  *:psram_xopi*.o(.data* .rodata*)
  *:hal_trace*.o(.data* .rodata*)
  *:pmu_*.o(.data* .rodata*)
  *:hal_sleep.o(.data* .rodata*)
  /* Stack protector instrumentation rodata for functions in special sections */
  *(.rodata.cst4)
  *(.boot_rodata_sram*)
  *(.boot_data*)
  . = ALIGN(4);
  __boot_data_sram_end__ = .;
 } > RAM
 __boot_data_sram_end_flash__ = __boot_data_sram_start_flash__ + SIZEOF(.boot_data_sram);
 .boot_bss_sram (.) (NOLOAD) : AT (ADDR(.boot_bss_sram))
 {
  __boot_bss_sram_start__ = .;
  *:hal_norflash*.o(.bss*)
  *:norflash_*.o(EXCLUDE_FILE(*:norflash_api.o) .bss*)
  *:arm_exception*.o(.bss*)
  *:irq_*.o(.bss*)
  *:nx_start*.o(.bss*)
  *:bes_start*.o(.bss*)
  *:main_bl*.o(.bss*)
  *:arm_initialize*.o(.bss*)
  *:hook.o(.bss*)
  *:hal_*cmu_*.o(.bss*)
  *:stack_protector*.o(.bss*)
  *:hal_iomux_*.o(.bss*)
  *:hal_analogif_*.o(.bss*)
  *:hal_phyif.o(.bss*)
  *:hal_spi.o(.bss*)
  *:hal_i2c.o(.bss*)
  *:hal_timer.o(.bss*)
  *:hal_sysfreq.o(.bss*)
  *:hal_apsram*.o(.bss*)
  *:apsram_*.o(.bss*)
  *:hal_psram*.o(.bss*)
  *:psram_drv*.o(.bss*)
  *:psram_opi*.o(.bss*)
  *:psram_xopi*.o(.bss*)
  *:hal_trace*.o(.bss*)
  *:pmu_*.o(.bss*)
  *:hal_sleep.o(.bss*)
  *(.boot_bss*)
  . = ALIGN(4);
  __boot_bss_sram_end__ = .;
 } > RAM
 __sram_nc_data_end_flash__ = __boot_data_sram_end_flash__;
 __ram_extra0_text_data_start_flash__ = __sram_nc_data_end_flash__;
 .ram_extra0_text_data : AT (__ram_extra0_text_data_start_flash__)
 {
  __ram_extra0_text_data_start__ = .;
  *(.ram_extra0_text*)
  . = ALIGN(4);
  *(.ram_extra0_rodata*)
  . = ALIGN(4);
  *(.ram_extra0_data*)
  . = ALIGN(4);
  __ram_extra0_text_data_end__ = .;
 } > RAM_EXTRA0
 __ram_extra0_text_data_end_flash__ = __ram_extra0_text_data_start_flash__ + SIZEOF(.ram_extra0_text_data);
 .ram_extra0_bss (NOLOAD) : AT (ADDR(.ram_extra0_bss))
 {
  __ram_extra0_bss_start__ = .;
  *(.ram_extra0_bss*)
  . = ALIGN(4);
  __ram_extra0_bss_end__ = .;
 } > RAM_EXTRA0
 __ram_extra0_top = ORIGIN(RAM_EXTRA0) + LENGTH(RAM_EXTRA0);
 __free_ram_extra0 = __ram_extra0_top - __ram_extra0_bss_end__;
 __ram_extra1_text_data_end_flash__ = __ram_extra0_text_data_end_flash__;
 __sram_text_start_flash__ = __ram_extra1_text_data_end_flash__;
 __sram_text_data_start__ = (ALIGN(__boot_text_sram_end__, 32));
 .sram_text ((__sram_text_data_start__)) : AT (__sram_text_start_flash__)
 {
  __sram_text_start__ = .;
  *:amr_common.o(.text*)
  *:bn_asm.o(.text*)
  *:ip*.o(.text*)
  *:udp*.o(.text*)
  *:iperf*.o(.text*)
  /* tcpip related files */
  *:recv.o(.text*)
  *:recvfrom.o(.text*)
  *:recvmsg.o(.text*)
  *:send.o(.text*)
  *:sendto.o(.text*)
  *:socket.o(.text*)
  *:net_sockets.o(.text*)
  *:net_sockif.o(.text*)
  *:net_poll.o(.text*)
  *:inet_sockif.o(.text*)
  *:netlink_sockif.o(.text*)
  *:tcp_recvfrom.o(.text*)
  *:tcp_send_buffered.o(.text*)
  *:arp_arpin.o(.text*)
  *:arp_out.o(.text*)
  *:arp_send.o(.text*)
  *:tcp_conn.o(.text*)
  *:tcp_send.o(.text*)
  *:tcp_input.o(.text*)
  *:tcp_appsend.o(.text*)
  *:tcp_monitor.o(.text*)
  *:tcp_callback.o(.text*)
  *:tcp_netpoll.o(.text*)
  *:tcp_wrbuffer.o(.text*)
  *:devif_callback.o(.text*)
  *:devif_iobsend.o(.text*)
  *:devif_poll.o(.text*)
  *:devif_loopback.o(.text*)
  *:devif_callback.o(.text*)
  *:tcp_devpoll.o(.text*)
  *:tcp_timer.o(.text*)
  *:tcp_seqno.o(.text*)
  *:tcp_recvwindow.o(.text*)
  *:tcp_ipselect.o(.text*)
  *:tcp_finddev.o(.text*)
  *:net_incr32.o(.text*)
  *:net_lock.o(.text*)
  *:net_tcpchksum.o(.text*)
  *:net_dev.o(.text*)
  *:icmp_*.o(.text*)
  /* iobuffer related files */
  *libmm.a:iob_*.o(.text*)
  *:mm_free.o(.text*)
  *:mm_malloc.o(.text*)
  *:hal_sdio*.o(.text*)
  *:wifi_sdio*.o(.text*)
  *:bes_netdev*.o(.text*)
  *:besf_driver_2003.o(.text*)
  *:besf_wlan_2003.o(.text*)
  *:besf_netdev_2003.o(.text*)
  *:besf_net_arch_2003.o(.text*)
  *:nuttx_net_v2.o(.text*)
  *:netdev_upperhalf.o(.text*)
  *:netdev_iob.o(.text*)
  *:netdev_input.c(.text*)
  *:ipv4_input.o(.text*)
  *:ipfrag.o(.text*)
  *:ipv4_frag.o(.text*)
  *:net_bufpool.o(.text*)
  *:net_chksum.o(.text*)
  *:net_incr32.o(.text*)
  *:net_ipchksum.o(.text*)
  *:net_tcpchksum.o(.text*)
  *:net_udpchksum.o(.text*)
  *:nuttx_os.o(.text*)
  *:lib_mutex.o(.text*)
  *:sem_*.o(.text*)
  *:event_*.o(.text*)
  /* iperf client and server */
  *:Client*.o(.text*)
  *:Server*.o(.text*)
  /* rpmsg host and its wrapper */
  *:rpmsg_host_adapter.o(.text*)
  *:wifi_host_rpmsg.o(.text*)
  *:wifi_hal_rpmsg.o(.text*)
  *:rpmsg_device_adapter.o(.text*)
  *:wifi_device_rpmsg.o(.text*)
  *:rpmsg.o(.text*)
  *:rpmsg_virtio.o(.text*)
  /* rptun and its wrapper */
  *:rptun.o(.text*)
  *:rptun_utils.o(.text*)
  *:rptun_m55c0_2*.o(.text*)
  /* wifi adapter */
  *:net_al.o(.text*)
  *:rtos_al.o(.text*)
  *:net_tasklet.o(.text*)
  *:net_timer.o(.text*)
  *:net_mutex.o(.text*)
  *:net_workqueue.o(.text*)
  *:net_memory.o(.text*)
  *:net_buf_mgt.o(.text*)
  *:mq_receive.o(.text*)
  /* wifi-stack v2 */
  *:rwnx_fdrv_perf.o(.text*)
  *:crypto_internal-modexp.o(.text*)
  *:bignum.o(.text*)
  *:libtommath.o(.text*)
  *:lv_disp.c.*graphics.lvgl.o(.text*)
  *:lv_event.c*graphics.lvgl.o(.text*)
  *:lv_group.c*graphics.lvgl.o(.text*)
  *:lv_indev_scroll.c*graphics.lvgl.o(.text*)
  *:lv_obj_class.c*graphics.lvgl.o(.text*)
  *:lv_obj_draw.c*graphics.lvgl.o(.text*)
  *:lv_obj_pos.c*graphics.lvgl.o(.text*)
  *:lv_obj_scroll.c*graphics.lvgl.o(.text*)
  *:lv_obj_style.c*graphics.lvgl.o(.text*)
  *:lv_obj_style_gen.c*graphics.lvgl.o(.text*)
  *:lv_obj_tree.c*graphics.lvgl.o(.text*)
  *:lv_theme.c*graphics.lvgl.o(.text*)
  *:lv_refr.c*graphics.lvgl.o(.text*)
  *:lv_indev.c*graphics.lvgl.o(.text*)
  *:lv_obj.c*graphics.lvgl.o(.text*)
  *:norflash_api.o(.text*)
  *(.sram_text*)
  /*
		   If you want protect one section by armv8's mpu, the section should
		   be aligned to 32bytes
		 */
  . = ALIGN(32);
  __sram_text_end__ = .;
 } > RAMX
 __sram_text_end_flash__ = __sram_text_start_flash__ + SIZEOF(.sram_text);
 __sram_data_start_flash__ = __sram_text_end_flash__;
 .sram_data
  : AT (__sram_data_start_flash__)
 {
  __sram_data_start__ = .;
  *:amr_common.o(.data* .rodata*)
  *:utils.o(.data* .rodata*)
  *:cqueue.o(.data* .rodata*)
  *:iir_process.o(.data* .rodata*)
  *:kfifo.o(.data* .rodata*)
  *:sbcplc.o(.data* .rodata*)
  *:sbc.o(.data* .rodata*)
  *:sbc_math.o(.data* .rodata*)
  *:sbc_api.o(.data* .rodata*)
  *:aac_api.o(.data* .rodata*)
  *:crossover_filter.o(.data* .rodata*)
  *:exp_func_tables.o(.data* .rodata*)
  *:sbcplc.o(.data* .rodata*)
  *:norflash_api.o(.rodata*)
  *:lc3_com.o(.data* .rodata*)
  *:lc3_dec.o(.data* .rodata*)
  *:lc3_enc.o(.data* .rodata*)
  *(.sram_rodata*)
  *(.sram_data*)
  *(.cp_data*)
  . = ALIGN(4);
  __sram_data_end__ = .;
 } > RAM
 __sram_data_end_flash__ = __sram_data_start_flash__ + SIZEOF(.sram_data);
 .sram_bss (.) (NOLOAD) : AT (ADDR(.sram_bss))
 {
  __sram_bss_start__ = .;
  *:utils.o(.bss*)
  *(.sram_bss*)
  *(.cp_bss*)
  *:rpc_bth_dsp.o(.bss*)
  . = ALIGN(32);
  __sram_bss_end__ = .;
 } > RAM
 __fast_sram_text_start_flash__ = __sram_data_end_flash__;
 .fast_text_sram : AT (__fast_sram_text_start_flash__)
 {
  __fast_sram_text_exec_start__ = .;
  /* memmove.o or libc_nano.a(lib_a-memmove.o) */
  *:memmove*.o(.text*)
  *:lib_a-memmove.o(.text*)
  *:utils.o(.text*)
  *:cqueue.o(.text*)
  *:kfifo.o(.text*)
  *:audio_resample_ex.o(.text*)
  *:sbc.o(.text*.sbc_is_stream_info_valid)
  *:sbc.o(.text*.sbc_frame_length_get)
  *:sbc.o(.text*.sbc_4bit_crc_calc)
  *:sbc.o(.text*.sbc_bits_for_mono_alloc)
  *:sbc.o(.text*.sbc_bits_for_stereo_alloc)
  *:sbc.o(.text*.sbc_header_process)
  *:sbc.o(.text*.sbc_factors_process)
  *:sbc.o(.text*.sbc_sample_extract)
  *:sbc.o(.text*.sbc_sbsamples_make)
  *:sbc.o(.text*.sbc_joint_process)
  *:sbc.o(.text*.sbc_4band_synth_filter)
  *:sbc.o(.text*.sbc_8band_synth_filter)
  *:sbc.o(.text*.sbc_decoder_state_reset)
  *:sbc.o(.text*.sbc_frame_mute)
  *:sbc.o(.text*.sbc_frames_decode)
  *:sbc.o(.text*.sbc_frames_decode_do)
  *:sbc.o(.text*.sbc_frames_decode_select_channel)
  *:sbc.o(.text*.sbc_frames_decode)
  *:sbc.o(.text*.sbc_samples_quant)
  *:sbc.o(.text*.sbc_decoder_init)
  *:sbc.o(.text*.sbc_encoder_init)
  *:sbc.o(.text*.sbc_frames_encode)
  *:sbc_math.o(.text*)
  *:sbc_api.o(.text*)
  *:aac_api.o(.text*)
  *:crossover_filter.o(.text*)
  *:data_compressor.o(.text*)
  *:drc.o(.text*)
  *:limiter.o(.text*)
  :audio_prompt_sbc.o(.text*)
  *:sbcplc.o(.text*)
  *:iirfilt.o(.text*)
  *:lc3_com.o(.text*)
  *:lc3_dec.o(.text*)
  *:lc3_enc.o(.text*)
  *(.fast_text_sram*)
  *(.cp_text_sram*)
  /*
		   If you want protect one section by armv8's mpu, the section should
		   be aligned to 32bytes
		 */
  . = ALIGN(32);
  __fast_sram_text_exec_end__ = .;
 } > RAMX
 __fast_sram_text_end_flash__ = __fast_sram_text_start_flash__ + SIZEOF(.fast_text_sram);
 __fast_sram_text_data_start__ = (__fast_sram_text_exec_start__);
 __fast_sram_text_data_end__ = (__fast_sram_text_exec_end__);
 __overlay_text_start_flash__ = __fast_sram_text_end_flash__;
 __overlay_text_start__ = ALIGN(__fast_sram_text_data_end__, 32);
 __overlay_text_exec_start__ = (__overlay_text_start__);
 OVERLAY (__overlay_text_exec_start__) : NOCROSSREFS AT (__overlay_text_start_flash__)
 {
  .overlay_text_last
  {
   LONG(0);
   . = ALIGN(4);
  }
 } > RAMX
 .dummy_overlay_text_end (.) (NOLOAD) : AT (ADDR(.dummy_overlay_text_end))
 {
  __overlay_text_exec_end__ = .;
 } > RAMX
 __fast_sram_end__ = (__overlay_text_exec_end__);
 __ramx_end = __fast_sram_end__;
 __ramx_top = ORIGIN(RAMX) + LENGTH(RAMX);
 __free_ramx = __ramx_top - __ramx_end;
 __overlay_data_start__ = __sram_bss_end__;
 OVERLAY (__overlay_data_start__) : NOCROSSREFS AT (__load_stop_overlay_text_last)
 {
  .overlay_data_last
  {
   LONG(0);
   . = ALIGN(4);
  }
 } > RAM
 .dummy_overlay_data_end (.) (NOLOAD) : AT (ADDR(.dummy_overlay_data_end))
 {
  __overlay_data_end__ = .;
 } > RAM
 ASSERT(__overlay_data_end__ - __overlay_data_start__ <= 0x10000, "overlay data sections too large")
  __apsram_nc_data_end_flash__ = __load_stop_overlay_data_last;
 __psram_text_data_start__ = ORIGIN(PSRAM);
 __psram_text_data_start_flash__ = __apsram_nc_data_end_flash__;
 .psram_text (((__psram_text_data_start__) - 0x18000000 + 0x18000000)) : AT (__psram_text_data_start_flash__)
 {
  __psramx_text_start__ = .;
  *(.psram_text*)
  . = ALIGN(32);
  __psramx_text_end__ = .;
 } > PSRAM
 .psram_data (__psram_text_data_start__ + SIZEOF(.psram_text)) :
    AT (__psram_text_data_start_flash__ + SIZEOF(.psram_text))
 {
  __psram_data_start__ = .;
  *(.psram_rodata*)
  *(.psram_data*)
  *(.data*)
  __psram_data_end__ = .;
  . = ALIGN(32);
 } > PSRAM
 __psram_text_data_end_flash__ = __psram_text_data_start_flash__ + SIZEOF(.psram_text)+ SIZEOF(.psram_data);
 .psram_bss (.) (NOLOAD) : AT (ADDR(.psram_bss))
 {
  __psram_bss_start__ = .;
  *:*ffmpeg*.o(COMMON)
  *(.psram_bss*)
  *(.bss*)
  . = ALIGN(32);
  __psram_bss_end__ = .;
 } > PSRAM
 __psram_nc_data_start_flash__ = __psram_text_data_end_flash__;
 .psram_nc_data (((.) - 0x18000000 + 0x38000000)) : AT (__psram_nc_data_start_flash__)
 {
  __psram_nc_data_start__ = .;
  *(.psram_nc_rodata*)
  . = ALIGN(32);
  *(.psram_nc_data*)
  . = ALIGN(32);
  __psram_nc_data_end__ = .;
 } > PSRAM_NC
 __psram_nc_data_end_flash__ = __psram_nc_data_start_flash__ + SIZEOF(.psram_nc_data);
 .psram_nc_bss (.) (NOLOAD) : AT (ADDR(.psram_nc_bss))
 {
  __psram_nc_bss_start__ = .;
  *(.psram_nc_bss*)
  *(.sync_flags_psram*)
  . = ALIGN(32);
  __psram_nc_bss_end__ = .;
 } > PSRAM_NC
 .psram_nc_noinit (.) (NOLOAD) : AT (ADDR(.psram_nc_noinit))
 {
  __psram_nc_noinit_start__ = .;
  __ram_log_start__ = .;
  *(.ram_log*)
  __ram_log_end__ = .;
  . = ALIGN(32);
  __psram_nc_noinit_end__ = .;
 } > PSRAM_NC
 .psram_heap_bss (((.) - 0x38000000 + 0x18000000)) (NOLOAD) : AT (ADDR(.psram_heap_bss))
 {
  __psram_reserved_start__ = .;
  *(.psram_reserved*)
  __psram_reserved_end__ = .;
  *(.psram_noinit*)
  . = ALIGN(32);
  _nuttx_heap_start = .;
  _nuttx_heap_end = ABSOLUTE((0x18000000 + 0) + 0x3700000);
 } > PSRAM
 __psramuhs_nc_data_end_flash__ = __psram_nc_data_end_flash__;
 __ddr_data_end_flash__ = __psramuhs_nc_data_end_flash__;
 __flash_text_data_start__ = __ddr_data_end_flash__;
 .text (((__flash_text_data_start__) - 0x10000000 + 0x10000000)) : AT (((ADDR(.text)) - 0x10000000 + 0x10000000))
 {
  *(.text*)
  *(.flash_text*)
  KEEP(*(.init))
  KEEP(*(.fini))
 } > FLASH
 .ARM.extab (.) : AT (((ADDR(.ARM.extab)) - 0x10000000 + 0x10000000))
 {
  *(.ARM.extab* .gnu.linkonce.armextab.*)
 } > FLASH
 /* .ARM.exidx contains R_ARM_PREL31 (+-0x40000000) offset to functions, which means
	 * the session location cannot be too far away from the function addresses */
 .ARM.exidx (.) : AT (((ADDR(.ARM.exidx)) - 0x10000000 + 0x10000000))
 {
  __exidx_start = .;
  *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  __exidx_end = .;
 } > FLASH
 .flashx_text_end_dummy (.) (NOLOAD) : AT (((ADDR(.flashx_text_end_dummy)) - 0x10000000 + 0x10000000))
 {
  __flashx_text_end__ = .;
 } > FLASH
 . = ((.) - 0x10000000 + 0x10000000);
 .rodata_nc (((.) - 0x10000000 + 0x30000000)) : AT (((ADDR(.rodata_nc)) - 0x30000000 + 0x10000000))
 {
  *(.rodata_nc*)
  *(.flash_nc_rodata*)
  . = ALIGN(4);
 } > FLASH_NC
 . = ((.) - 0x30000000 + 0x10000000);
 .rodata (.) :
 {
  *(.rodata*)
  *(.flash_rodata*)
  *(.constdata)
  /* C++ Static constructors/destructors (eabi) */
  . = ALIGN(4);
  _sinit = ABSOLUTE(.);
  /* preinit data */
  PROVIDE_HIDDEN (__preinit_array_start = .);
  KEEP(*(.preinit_array))
  PROVIDE_HIDDEN (__preinit_array_end = .);
  . = ALIGN(4);
  /* init data */
  PROVIDE_HIDDEN (__init_array_start = .);
  KEEP(*(SORT(.init_array.*)))
  KEEP(*(.init_array))
  PROVIDE_HIDDEN (__init_array_end = .);
  /* .ctors */
  *crtbegin.o(.ctors)
  *crtbegin?.o(.ctors)
  *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
  *(SORT(.ctors.*))
  *(.ctors)
  _einit = ABSOLUTE(.);
  /* .dtors */
  . = ALIGN(4);
  /* finit data */
  PROVIDE_HIDDEN (__fini_array_start = .);
  KEEP(*(SORT(.fini_array.*)))
  KEEP(*(.fini_array))
  PROVIDE_HIDDEN (__fini_array_end = .);
  *crtbegin.o(.dtors)
  *crtbegin?.o(.dtors)
  *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
  *(SORT(.dtors.*))
  *(.dtors)
  . = ALIGN(4);
  __cust_cmd_hdlr_tbl_start = .;
  KEEP(*(.cust_cmd_hdlr_tbl))
  __cust_cmd_hdlr_tbl_end = .;
  . = ALIGN(4);
  __ai_gatt_server_table_start = .;
  KEEP(*(.ai_gatt_server_table))
  __ai_gatt_server_table_end = .;
  . = ALIGN(4);
  __ai_ble_handler_table_start = .;
  KEEP(*(.ai_ble_handler_table))
  __ai_ble_handler_table_end = .;
  . = ALIGN(4);
  __ai_spp_register_table_start = .;
  KEEP(*(.ai_spp_register_table))
  __ai_spp_register_table_end = .;
  . = ALIGN(4);
  __tota_handler_table_start = .;
  KEEP(*(.tota_handler_table))
  __tota_handler_table_end = .;
  . = ALIGN(4);
  __sound_init_table_start = .;
  KEEP(*(.sound_init_table))
  __sound_init_table_end = .;
  . = ALIGN(4);
  __ai_handler_function_table_start = .;
  KEEP(*(.ai_handler_function_table))
  __ai_handler_function_table_end = .;
  . = ALIGN(4);
  __custom_handler_table_start = .;
  KEEP(*(.custom_handler_table))
  __custom_handler_table_end = .;
  . = ALIGN(4);
  __mesh_custom_handler_table_start = .;
  KEEP(*(.mesh_custom_handler_table))
  __mesh_custom_handler_table_end = .;
  . = ALIGN(4);
  __mixprompt_property_table_start = .;
  KEEP(*(.mixprompt_property_table))
  __mixprompt_property_table_end = .;
  . = ALIGN(4);
  __core_bridge_task_cmd_table_start = .;
  KEEP(*(.core_bridge_task_cmd_table))
  __core_bridge_task_cmd_table_end = .;
  . = ALIGN(4);
  __core_bridge_instant_cmd_table_start = .;
  KEEP(*(.core_bridge_instant_cmd_table))
  __core_bridge_instant_cmd_table_end = .;
  . = ALIGN(4);
  __rpc_bth_dsp_cmd_table_start = .;
  KEEP(*(.rpc_bth_dsp_cmd_table))
  __rpc_bth_dsp_cmd_table_end = .;
  . = ALIGN(4);
  __rpc_m55_dsp_cmd_table_start = .;
  KEEP(*(.rpc_m55_dsp_cmd_table))
  __rpc_m55_dsp_cmd_table_end = .;
  . = ALIGN(4);
  __rpc_mcu_cp_cmd_table_start = .;
  KEEP(*(.rpc_mcu_cp_cmd_table))
  __rpc_mcu_cp_cmd_table_end = .;
  . = ALIGN(4);
  __uart_bridge_task_cmd_table_start = .;
  KEEP(*(.uart_bridge_task_cmd_table))
  __uart_bridge_task_cmd_table_end = .;
  . = ALIGN(4);
  __uart_bridge_instant_cmd_table_start = .;
  KEEP(*(.uart_bridge_instant_cmd_table))
  __uart_bridge_instant_cmd_table_end = .;
  . = ALIGN(4);
  __eshell_command_table_start = .;
  KEEP(*(.eshell_command_table))
  __eshell_command_table_end = .;
  . = ALIGN(4);
  __app_bt_sync_command_handler_table_start = .;
  KEEP(*(.app_bt_sync_command_handler_table))
  __app_bt_sync_command_handler_table_end = .;
  . = ALIGN(4);
  __custom_apps_message_handler_table_start = .;
  KEEP(*(.custom_apps_message_handler_table))
  __custom_apps_message_handler_table_end = .;
  . = ALIGN(4);
  . = ALIGN(4);
  KEEP(*(.eh_frame*))
  PROVIDE(gnu_build_id_begin = .);
  *(.note.gnu.build-id)
  . = ALIGN(4);
  _etext = .;
 } > FLASH
 /* To copy multiple FLASH to RAM sections,
	 * uncomment .copy.table section and,
	 * define __STARTUP_COPY_MULTIPLE in startup_ARMCMx.S */
 /*
	.copy.table (.) :
	{
		. = ALIGN(4);
		__copy_table_start__ = .;
		LONG (__etext)
		LONG (__data_start__)
		LONG (__data_end__ - __data_start__)
		LONG (__etext2)
		LONG (__data2_start__)
		LONG (__data2_end__ - __data2_start__)
		__copy_table_end__ = .;
	} > FLASH
	*/
 /* To clear multiple BSS sections,
	 * uncomment .zero.table section and,
	 * define __STARTUP_CLEAR_BSS_MULTIPLE in startup_ARMCMx.S */
 /*
	.zero.table (.) :
	{
		. = ALIGN(4);
		__zero_table_start__ = .;
		LONG (__bss_start__)
		LONG (__bss_end__ - __bss_start__)
		LONG (__bss2_start__)
		LONG (__bss2_end__ - __bss2_start__)
		__zero_table_end__ = .;
	} > FLASH
	*/
 /* Location counter can end up 2byte aligned with narrow Thumb code but
	   __etext is assumed by startup code to be the LMA of a section in RAM
	   which must be 4byte aligned */
 __etext = ALIGN(4);
 /* The VMA is either the end of overlay_data or the end of sram bss */
 .data : AT (__etext)
 {
  __data_start__ = .;
  _sdata = .;
  *(vtable)
  . = ALIGN(4);
  *(.data*)
  *(.z_devstate*)
  *(.z_init*)
  KEEP(*(.jcr*))
  __shell_root_cmds_start = .;
  KEEP(*(SORT(.shell_root_cmd_*)));
  __shell_root_cmds_end = .;
  /* All data end */
  . = ALIGN(4);
  __data_end__ = .;
  _edata = .;
 } > RAM
 .bss (.) (NOLOAD) : AT (ADDR(.bss))
 {
  . = ALIGN(4);
  __bss_start__ = .;
  _sbss = .;
  *(.bss*)
  *(COMMON)
  . = ALIGN(4);
  __bss_end__ = .;
  _ebss = .;
 } > RAM
 .noinit (.) (NOLOAD) :
 {
  *(.noinit* .*_noinit*)
  . = ALIGN(4);
  KEEP(*(.reboot_custom_param*))
  . = ALIGN(4);
  __ram_log_start__ = .;
  *(.ram_log*)
  __ram_log_end__ = .;
 } > RAM
 .framebuffer (.) (NOLOAD) :
 {
  . = ALIGN(64);
  KEEP(*(.framebuffer))
 } > RAM
 .heap (.) (NOLOAD) :
 {
  . = ALIGN(8);
  __HeapBase = .;
  __end__ = .;
  end = __end__;
  . += 0x32;
  . = ALIGN(8);
  __HeapLimit = .;
 } > RAM
 /* .stack_dummy section doesn't contains any symbols. It is only
	 * used for linker to calculate size of stack sections, and assign
	 * values to stack symbols later */
 .stack_dummy (.) (COPY) :
 {
  . = 3072;
  . = ALIGN(8);
 } > RAM
 /* Set stack top to end of RAM, and stack limit move down by
	 * size of stack_dummy section */
 __StackTop = ORIGIN(RAM) + LENGTH(RAM);
 __StackLimit = __StackTop - SIZEOF(.stack_dummy);
 PROVIDE(__stack = __StackTop);
 /* Check if data + heap + stack exceeds RAM limit */
 ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
 __free_ram = __StackLimit - __HeapLimit;
 __mem_pool_start__ = __HeapLimit;
 __mem_pool_end__ = __StackLimit;
 __aon_mbx_data_start_load__ = __etext + SIZEOF(.data);
 .aon_mbx_data (ORIGIN(AON_MAILBOX)) : AT (__aon_mbx_data_start_load__)
 {
  __aon_mbx_data_start__ = .;
  *(.aon_mbx_data*)
  . = ALIGN(4);
/*openamp resource table */
  . = ALIGN(8);
  __resource_table_start__ = .;
  KEEP(*(.resource_table*))
  __resource_table_end__ = .;
  __aon_mbx_data_end__ = .;
 } > AON_MAILBOX
 __aon_mbx_data_end_load__ = __aon_mbx_data_start_load__ + SIZEOF(.aon_mbx_data);
 .aon_mbx_bss (.) (NOLOAD) :
 {
  __aon_mbx_bss_start__ = .;
  *(.aon_mbx_bss*)
  . = ALIGN(4);
  __aon_mbx_bss_end__ = .;
  *(.aon_mbx_buf*);
  . = ALIGN(4);
 } > AON_MAILBOX
 __aon_mbx_heap_start__ = .;
 __aon_mbx_heap_end__ = ORIGIN(AON_MAILBOX) + LENGTH(AON_MAILBOX);
 __aon_mbx_heap_size__ = __aon_mbx_heap_end__ - __aon_mbx_heap_start__;
 . = __aon_mbx_data_end_load__;
 . = ((.) - 0x10000000 + 0x30000000);
/***************************************************************************
 *
 * Copyright 2023-2024 BES.
 * All rights reserved. All unpublished rights reserved.
 *
 * No part of this work may be used or reproduced in any form or by any
 * means, or stored in a database or retrieval system, without prior written
 * permission of BES.
 *
 * Use of this work is governed by a license granted by BES.
 * This work contains confidential and proprietary information of
 * BES. which is protected by copyright, trade secret,
 * trademark and other intellectual property rights.
 *
 ****************************************************************************/
 .repo_delimiter0 (.) : AT (((ADDR(.repo_delimiter0)) - 0x30000000 + 0x10000000))
 {
  LONG(0);
  . = ALIGN(4);
 } > FLASH_NC = 0x00000000
 .repo_manifest (.) : AT (((ADDR(.repo_manifest)) - 0x30000000 + 0x10000000))
 {
  KEEP(*(.repo_manifest))
  . = ALIGN(4);
 } > FLASH_NC = 0x00000000
 .repo_delimiter1 (.) : AT (((ADDR(.repo_delimiter1)) - 0x30000000 + 0x10000000))
 {
  LONG(0);
  . = ALIGN(4);
 } > FLASH_NC = 0x00000000
 .repo_revison (.) : AT (((ADDR(.repo_revison)) - 0x30000000 + 0x10000000))
 {
  KEEP(*(.repo_revision))
  . = ALIGN(4);
 } > FLASH_NC = 0x00000000
 .repo_delimiter2 (.) : AT (((ADDR(.repo_delimiter2)) - 0x30000000 + 0x10000000))
 {
  LONG(0);
  . = ALIGN(4);
 } > FLASH_NC = 0x00000000
 .build_info (.) : AT (((ADDR(.build_info)) - 0x30000000 + 0x10000000))
 {
  KEEP(*(.build_info))
  . = ALIGN(4);
 } > FLASH_NC = 0x00000000
 __boot_struct_build_info = ADDR(.build_info);
 . = ((.) - 0x30000000 + 0x10000000);
 /* The following section MUST be the last loaded section */
 .code_start_addr (.) :
 {
  LONG(0xBE57341D);
  LONG(((ABSOLUTE(__flash_start)) - 0x10000000 + 0x30000000));
 } > FLASH
 __flash_end = .;
 ASSERT(__flash_end <= __flash_start + 0x980000, "flash code size too large (should <= FLASH_IMAGE_SIZE)")
/***************************************************************************
 *
 * Copyright 2015-2022 BES.
 * All rights reserved. All unpublished rights reserved.
 *
 * No part of this work may be used or reproduced in any form or by any
 * means, or stored in a database or retrieval system, without prior written
 * permission of BES.
 *
 * Use of this work is governed by a license granted by BES.
 * This work contains confidential and proprietary information of
 * BES. which is protected by copyright, trade secret,
 * trademark and other intellectual property rights.
 *
 ****************************************************************************/
 __flash_tail_sec_start = ORIGIN(FLASH_NC) + LENGTH(FLASH_NC) -
       ((0x4000 + 8K - 1) & ~(8K - 1)) -
       ((0x2000 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       ((0x2000 + 8K - 1) & ~(8K - 1)) * 2 -
       ((0 + 8K - 1) & ~(8K - 1)) * 2 -
       ((0x2000 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       ((0x0 + 8K - 1) & ~(8K - 1)) -
       ((0x0 + 8K - 1) & ~(8K - 1)) -
       ((0 + 8K - 1) & ~(8K - 1)) -
       (( + 8K - 1) & ~(8K - 1)) -
       0;
 .dummy_flash_tail (__flash_tail_sec_start - 16) (NOLOAD) : AT (ADDR(.dummy_flash_tail))
 {
  __dummy_flash_tail_start = .;
   . = ALIGN(8K);
  __dummy_flash_tail_end = .;
 } > FLASH_NC
 ASSERT(__flash_tail_sec_start == __dummy_flash_tail_end, "Bad dummy_flash_tail")
 .findmy_info_section (NOLOAD):
 {
  __findmy_info_start = .;
  . = (( + 8K - 1) & ~(8K - 1));
  __findmy_info_end = .;
 } > FLASH_NC
 .combo (NOLOAD):
 {
  __combo_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __combo_end = .;
 } > FLASH_NC
 .prompt (NOLOAD):
 {
  __prompt_start = .;
  . = ((0x0 + 8K - 1) & ~(8K - 1));
  __prompt_end = .;
 } > FLASH_NC
 .hotword_model (NOLOAD):
 {
  __hotword_model_start = .;
  . = ((0x0 + 8K - 1) & ~(8K - 1));
  __hotword_model_end = .;
 } > FLASH_NC
 .ramdump_section (NOLOAD) :
 {
  __ramdump_section_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __ramdump_section_end = .;
 } > FLASH_NC
 .bt_controller_ramdump_section (NOLOAD) :
 {
  __bt_controller_ramdump_section_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __bt_controller_ramdump_section_end = .;
 } > FLASH_NC
 .coredump_section (NOLOAD) :
 {
  __coredump_section_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __coredump_section_end = .;
 } > FLASH_NC
 .ota_upgrade_log (NOLOAD) :
 {
  __ota_upgrade_log_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __ota_upgrade_log_end = .;
 } > FLASH_NC
 .log_dump (NOLOAD) :
 {
  __log_dump_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __log_dump_end = .;
 } > FLASH_NC
 .crash_dump (NOLOAD) :
 {
  __crash_dump_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __crash_dump_end = .;
 } > FLASH_NC
 .custom_parameter (NOLOAD) :
 {
  __custom_parameter_start = .;
  . = ((0x2000 + 8K - 1) & ~(8K - 1));
  __custom_parameter_end = .;
 } > FLASH_NC
 .lhdc_license (NOLOAD) :
 {
  __lhdc_license_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __lhdc_license_end = .;
 } > FLASH_NC
 .wifi_userdata (NOLOAD) :
 {
  __wifi_userdata_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1)) * 2;
  __wifi_userdata_end = .;
 } > FLASH_NC
 .userdata (NOLOAD) :
 {
  __userdata_start = .;
  . = ((0x2000 + 8K - 1) & ~(8K - 1)) * 2;
  __userdata_end = .;
 } > FLASH_NC
 .lte_nv (NOLOAD) :
 {
  __lte_nv_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __lte_nv_end = .;
 } > FLASH_NC
 .lte_calib (NOLOAD) :
 {
  __lte_calib_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __lte_calib_end = .;
 } > FLASH_NC
 .lte_rfdata (NOLOAD) :
 {
  __lte_rfdata_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __lte_rfdata_end = .;
 } > FLASH_NC
 .audio (NOLOAD) :
 {
  __aud_start = .;
  . = ((0 + 8K - 1) & ~(8K - 1));
  __aud_end = .;
 } > FLASH_NC
 .reserved (NOLOAD) :
 {
  __reserved_start = .;
  . = ((0x2000 + 8K - 1) & ~(8K - 1));
  __reserved_end = .;
 } > FLASH_NC
 .factory (NOLOAD) :
 {
  __factory_start = .;
  . = ((0x4000 + 8K - 1) & ~(8K - 1));
  __factory_end = .;
 } > FLASH_NC
 __tail_section_start = __flash_tail_sec_start;
 ASSERT(((__tail_section_start) - 0x30000000 + 0x10000000) >= __flash_end, "region FLASH overflowed")
 __free_flash = ((__tail_section_start) - 0x30000000 + 0x10000000) - __flash_end;
 ASSERT((__vector_table_start & (1K - 1)) == 0, "vector table alignment error")
 /DISCARD/ :
 {
  *(.interp)
  *(.hash)
  *(.dynsym)
  *(.dynstr)
  *(.gnu.version)
  *(.gnu.version_d)
  *(.gnu.version_r)
  *(.rela.plt)
  *(.rela.data.rel.ro*)
  *(.rela.gnu.linkonce.d.rel.ro*)
  *(.rela.*)
  *(.plt)
  *(.dynamic)
 }
}
