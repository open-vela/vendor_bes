# ##############################################################################
# vendor/bes/chips/bes/CMakeLists.txt
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

# CHIP_CSRCS config

if(BES1700_LIBRARY_MODE)
  set(CHIP_CSRCS)
else()

list(
  APPEND
  CHIP_CSRCS
  bes_stub.c
  bes_irq.c
  bes_serial.c
  bes_timer.c
  bes_timer_oneshot.c
  bes_tickless_systick.c
  bes_allocateheap.c )

if(${CONFIG_BES_OS_LAYER_V0})
  list(APPEND CHIP_CSRCS bes_boardctl_v0.c)
else()
  list(APPEND CHIP_CSRCS bes_boardctl.c)
  target_include_directories(arch PRIVATE ${NUTTX_DIR}/../apps/system/zlib/zlib)
endif()

if(${CONFIG_BES_LPUART0S} OR ${CONFIG_BES_LPUART1S} OR ${CONFIG_BES_LPUART2S} OR ${CONFIG_BES_LPUART3S})
  list(APPEND CHIP_CSRCS bes_serial_single_wire.c)
endif()

if(${CONFIG_ARCH_CHIP_BES1600_BTH})
  if(${CONFIG_ARCH_HAVE_SDIO})
    list(APPEND CHIP_CSRCS bes_best_sdio.c)
  endif()
endif()

if(${CONFIG_BES_EMMC})
  list(APPEND CHIP_CSRCS bes_best_emmc.c)
endif()

if(${CONFIG_RTC})
if(${CONFIG_BES_OS_LAYER_V0})
  list(APPEND CHIP_CSRCS bes_rtc_v0.c)
else()
  list(APPEND CHIP_CSRCS bes_rtc.c)
endif()
endif()

if(${CONFIG_GEN_CMCP_BIN})
  list(APPEND CHIP_CSRCS bes_start_cp.c)
else()
  if(${CONFIG_BES_BOARD_START_FILE_CHIP_START})
    list(APPEND CHIP_CSRCS bes_start.c)
  endif()
endif()

if(${CONFIG_BES_COMMON_RPTUN_FILE})

  if(${CONFIG_BES_DUALCORE_AMP})
    list(APPEND CHIP_CSRCS up_rptun_cmcp.c)
  endif()

  if(${CONFIG_ARCH_HAVE_TRUSTZONE})
    list(APPEND CHIP_CSRCS up_rptun_se.c)
  endif()

  if(${CONFIG_BES_RPTUN_AP2SENS})
    list(APPEND CHIP_CSRCS up_rptun_m552sens.c)
  endif()

  if(${CONFIG_BES_RPTUN_CP2SENS})
    list(APPEND CHIP_CSRCS up_rptun_bth2sens.c)
  endif()

  if(${CONFIG_BES_RPTUN_DSP2CP})
    list(APPEND CHIP_CSRCS up_rptun_hifi2bth.c)
  endif()

endif() # if(${CONFIG_BES_COMMON_RPTUN_FILE})

if(${CONFIG_I2C_DRIVER})
  list(APPEND CHIP_CSRCS bes_i2c.c)
endif()

if(${CONFIG_I3C_DRIVER})
  list(APPEND CHIP_CSRCS bes_i3c.c)
endif()

if(${CONFIG_MIPI_DSI})
  list(APPEND CHIP_CSRCS bes_mipidsi.c)
endif()

if(${CONFIG_I2C_RPMSG_SERVER})
  list(APPEND CHIP_CSRCS bes_rpmsg_i2c_svr.c)
endif()

if(${CONFIG_I2C0_RPMSG_SERVER})
  # for tp
  list(APPEND CHIP_CSRCS bes_rpmsg_i2c_svr.c)
endif()

if(${CONFIG_BES_HAVE_IRC})
  list(
    APPEND
    CHIP_CSRCS
    bes_ir.c
    bes_lirc_dev_rx.c
    bes_lirc_dev_tx.c
    pwm-ir-tx.c
    gpio-ir-recv.c
    ir-nec-decoder.c
    rc-ir-raw.c
    kfifo.c
    gpio-ir-tx.c)
endif()

if(${CONFIG_IOEXPANDER})
  list(
    APPEND
    CHIP_CSRCS
    bes_ioexpander.c
    bes_gpio.c
    bes_gpio_pwm.c
    bes_spi.c
    bes_batt_monitor.c
    bes_batt_charger.c)
endif()

if(${CONFIG_MTD})
  list(APPEND CHIP_CSRCS bes_flash.c bes_flash_sec.c)
endif()

if(${CONFIG_BES_MTDSDMMC})
  list(APPEND CHIP_CSRCS bes_sdmmc.c)
endif()

if(${CONFIG_BES_MTDSDMMC_EMMC})
  list(APPEND CHIP_CSRCS bes_sdmmc_emmc.c)
endif()

if(${CONFIG_BES_MMCSD_SPI})
  list(APPEND CHIP_CSRCS bes_mmcsd_spi.c)
endif()

if(${CONFIG_RPMSG_COMMON_MSG_SERVER})
  list(APPEND CHIP_CSRCS rpmsg_common.c rpmsg_common_cmd_table.c
       dev_common_cmd_table.c)
endif()

if(${CONFIG_RPMSG_COMMON_MSG_CLIENT})
  list(APPEND CHIP_CSRCS rpmsg_common.c rpmsg_common_cmd_table.c
       dev_common_cmd_table.c)
endif()

if(CONFIG_BES_AUDIO_LOCAL)
  list(APPEND CHIP_CSRCS bes_audio_local.c)
else()
  if(${CONFIG_AUDIO})

    if(NOT CONFIG_AUDIO_RPMSG_CLIENT)
      list(APPEND CHIP_CSRCS bes_audio.c)
    endif()

    if(${CONFIG_AUDIO_RPMSG_SERVER})
      list(APPEND CHIP_CSRCS bes_rpmsg_audio_svr.c)
    endif()

  endif() # if(${CONFIG_AUDIO})
endif()

if(CONFIG_BES_AUDIO_SERVER)
  list(APPEND CHIP_CSRCS bes_audio_server.c)
endif()

if(${CONFIG_BTSAK})
  list(APPEND CHIP_CSRCS bes_hciuart.c)
else()
  list(APPEND CHIP_CSRCS bes_serial_hci.c)
endif()

if(${CONFIG_SMP})
  list(APPEND CHIP_CSRCS bes_smp.c)
endif()

if(${CONFIG_ARCH_IDLE_CUSTOM})
if(${CONFIG_BES_OS_LAYER_V0})
  list(APPEND CHIP_CSRCS bes_idle_v0.c)
else()
  list(APPEND CHIP_CSRCS bes_idle.c)
endif()
endif()

if(${CONFIG_PM})
  list(APPEND CHIP_CSRCS bes_pm.c)
endif()

if(${CONFIG_RPTUN})
  list(APPEND CHIP_CSRCS up_rptun.c)
endif()

if(NOT CONFIG_FL3728)
  list(APPEND CHIP_CSRCS fl3728.c)
endif()

if(${CONFIG_ET6096})
  list(APPEND CHIP_CSRCS et6096.c)
endif()

if(${CONFIG_FL3236A})
  list(APPEND CHIP_CSRCS fl3236a.c)
endif()

if(${CONFIG_AW21024})
  list(APPEND CHIP_CSRCS aw21024.c)
endif()

if(${CONFIG_PSC2945})
  list(APPEND CHIP_CSRCS psc2945.c)
endif()

if(${CONFIG_BES_HW_VERSION})
  list(APPEND CHIP_CSRCS bes_hw_version.c)
endif()

if(${CONFIG_HX3203})
  list(APPEND CHIP_CSRCS hx3203.c)
endif()

if(${CONFIG_SENSORS_HX3203})
  list(APPEND CHIP_CSRCS hx3203_uorb.c)
endif()

if(${CONFIG_IEEE80211_BESTECHNIC_BES2300WP})
  list(APPEND CHIP_CSRCS besf_driver.c besf_netdev.c besf_wlan.c
       besf_net_arch.c)
endif()

if(${CONFIG_IEEE80211_BESTECHNIC_BES2003})
  list(APPEND CHIP_CSRCS besf_driver_2003.c besf_netdev_2003.c besf_wlan_2003.c
       besf_net_arch_2003.c)
  set_source_files_properties(besf_driver_2003.c PROPERTIES COMPILE_FLAGS "-fno-lto")
  set_source_files_properties(besf_netdev_2003.c PROPERTIES COMPILE_FLAGS "-fno-lto")
  set_source_files_properties(besf_wlan_2003.c PROPERTIES COMPILE_FLAGS "-fno-lto")
  set_source_files_properties(besf_net_arch_2003.c PROPERTIES COMPILE_FLAGS "-fno-lto")
  target_include_directories(arch PRIVATE ${NUTTX_APPS_DIR}/include)
endif()

if(${CONFIG_IEEE80211_BESTECHNIC_NETDEV_SDIO})
  list(APPEND CHIP_CSRCS bes_netdev_sdio_driver.c bes_netdev_sdio.c
       bes_netdev_sdio_wlan.c bes_netdev_sdio_arch.c)
endif()

if(${CONFIG_IEEE80211_BESTECHNIC_NETDEV_AX})
  list(APPEND CHIP_CSRCS bes_netdev_ax_driver.c bes_netdev_ax.c
       bes_netdev_ax_wlan.c bes_netdev_ax_arch.c bes_netdev_pm.c
       bes_netdev_notifier.c bes_netdev_rxf.c)

  if(${CONFIG_BES_EVENT_MONITOR})
    list(APPEND CHIP_CSRCS bes_netdev_event_monitor.c)
  endif()

  if(${CONFIG_BES_WL_HEAP})
    list(APPEND CHIP_CSRCS bes_netdev_heap.c)
  endif()

  target_include_directories(arch PRIVATE ${NUTTX_DIR}/../apps/include)
endif()

if(${CONFIG_BES_HAVE_DVFS})
  list(APPEND CHIP_CSRCS bes_dvfs.c)
  if(${CONFIG_FS_PROCFS})
    list(APPEND CHIP_CSRCS procfs_dvfs.c)
  endif()
endif()

if(${CONFIG_BES_HAVE_CPUFREQ})
  list(APPEND CHIP_CSRCS bes_cpufreq.c)
endif()

if(${CONFIG_WATCHDOG})
  list(APPEND CHIP_CSRCS bes_wdt.c)
endif()

if(${CONFIG_INPUT_BUTTONS})
  list(APPEND CHIP_CSRCS bes_buttons.c)
endif()

if(${CONFIG_BES_TRNG})
  list(APPEND CHIP_CSRCS bes_trng.c)
endif()

if(${CONFIG_BES_NAND_FLASH})
  list(APPEND CHIP_CSRCS bes_nand.c)
endif()

if(${CONFIG_BES_MODEM})
  list(APPEND CHIP_CSRCS besf_modem.c bes_tty_mdm.c fifo.c)
endif()

if(${CONFIG_BES_SPI})
  list(APPEND CHIP_CSRCS bes_spi_slave.c bes_spi_dbgslave.c)
endif()

if(${CONFIG_BES_OTGHS})
  list(APPEND CHIP_CSRCS bes_otghshost.c bes_otghshost_modem.c)
endif()

if(${CONFIG_BES_HAVE_USB})
  list(APPEND CHIP_CSRCS bes_usbdev.c)
endif()

if(${CONFIG_CRYPTO_CRYPTODEV_HARDWARE})
  list(APPEND CHIP_CSRCS bes_crypto.c)
endif()

endif()

target_sources(arch PRIVATE ${CHIP_CSRCS})


# filter-out some files
get_target_property(filter_sources arch SOURCES)
list(FILTER filter_sources EXCLUDE REGEX ".*arm_allocateheap\\.c$")
if(CONFIG_BES_ONESHOT_SYSTICK)
  list(FILTER filter_sources EXCLUDE REGEX ".*arm_systick\\.c$")
endif()
if(CONFIG_WITHOUT_OS)
  list(FILTER filter_sources EXCLUDE REGEX ".*arm_vectors\\.c$")
endif()
if(
    (CONFIG_LPUART0_SERIAL_CONSOLE AND (CONFIG_LPUART0_TXDMA OR CONFIG_LPUART0_RXDMA)) OR
    (CONFIG_LPUART1_SERIAL_CONSOLE AND (CONFIG_LPUART1_TXDMA OR CONFIG_LPUART1_RXDMA)) OR
    (CONFIG_LPUART2_SERIAL_CONSOLE AND (CONFIG_LPUART2_TXDMA OR CONFIG_LPUART2_RXDMA))
)
  list(FILTER filter_sources EXCLUDE REGEX ".*arm_nputs\\.c$")
endif()
set_target_properties(arch PROPERTIES SOURCES "${filter_sources}")
# filter-out some files end

# include and options

target_include_directories(
  arch
  PRIVATE $<GENEX_EVAL:$<TARGET_PROPERTY:BES_SDK_TARGET,BES_SDK_INCLUDE_DIR>>)

target_include_directories(arch PRIVATE ${NUTTX_DIR}/../vendor/bes/boards/common/src)

target_compile_options(
  arch
  PRIVATE
    $<GENEX_EVAL:$<TARGET_PROPERTY:BES_SDK_TARGET,BES_SDK_COMPILE_OPTIONS>>)

if(${CONFIG_SPECIFIC_DRIVERS})
  target_include_directories(arch PRIVATE ${NUTTX_DIR}/drivers/platform/include)
endif()

target_include_directories(arch SYSTEM PRIVATE ${CMAKE_BINARY_DIR}/include/arch/chip)

target_compile_options(
  arch
  PRIVATE -Wno-unused-function
          -Wno-unused-const-variable
          -Wno-unused-but-set-variable
          -Wno-return-type
          -Wno-pointer-sign
          -Wno-format
          -Wno-unused-variable
          -Wno-parentheses
          -Wno-implicit-function-declaration
          -Wno-strict-prototypes
          -Wno-int-conversion
          -Wno-implicit-int
          -Wno-incompatible-pointer-types
          -Wno-maybe-uninitialized
          -Wno-discarded-qualifiers
          -Wno-shadow
          -Wno-unused-label
          -Wno-comment)
