# ##############################################################################
# boards/common/src/CMakeLists.txt
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

set(SRCS)

if(BES1700_AP_LIBRARY_MODE)
  set(SRCS)
else()

if(${CONFIG_ARCH_LEDS})
  # list(APPEND SRCS bes_autoleds.c)
elseif(${CONFIG_USERLED})
  list(APPEND SRCS bes_userleds.c)
endif()

if(${CONFIG_PWM})
  list(APPEND SRCS bes_pwm.c)
endif()

if(${CONFIG_BES_ACCLIS2DH})
  list(APPEND SRCS bes_acclis2dh.c)
endif()

if(${CONFIG_BES_SPI})
  list(APPEND SRCS bes_spi.c)
  list(APPEND SRCS bes_board_spi_slave.c)
  list(APPEND SRCS bes_board_spi_dbgslave.c)
endif()

if(${CONFIG_VIDEO})
  list(APPEND SRCS bes_camera_common.c)
  if(${CONFIG_BES_CAMSPI})
    list(APPEND SRCS bes_camspi_common.c)
    if(${CONFIG_BES_CAMERA_GC032A})
      list(APPEND SRCS bes_camspi_gc032a.c)
    endif()
  endif()
  if(${CONFIG_BES_CAMCSI})
    list(APPEND SRCS bes_camcsi_common.c)
    if(${CONFIG_BES_CAMERA_GC2145})
      list(APPEND SRCS bes_camcsi_gc2145.c)
    endif()
  endif()
  if(${CONFIG_BES_CAMUVC})
    list(APPEND SRCS bes_camusb_uvc.c)
  endif()
endif()

if(${CONFIG_POWER})
  list(APPEND SRCS bes_power.c)
endif()

if(${CONFIG_BES_ADC})
  list(APPEND SRCS bes_adc.c)
endif()

if(${CONFIG_BES_BAT_VOLTAGE})
  list(APPEND SRCS bes_bat_voltage.c)
endif()

if(${CONFIG_RPMSG_GPIO_CLIENT})
  list(APPEND SRCS ioe_rpmsg.c)
endif()

if(${CONFIG_I2C_RPMSG_CLIENT})
  list(APPEND SRCS bes_rpmsg_i2c.c)
endif()

if(${CONFIG_AUDIO_RPMSG_CLIENT})
  if(NOT CONFIG_ARCH_CHIP_BESHIFI4)
    list(APPEND SRCS rpmsg_audio.c)
  endif()
endif()

if(${CONFIG_BOARDCTL})
  # list(APPEND SRCS bes_appinit.c)
endif()

if(${CONFIG_BES_HAVE_RGBLED})
  list(APPEND SRCS bes_rgbled.c)
endif()

if(${CONFIG_BES_TP_TMA525C})
  list(APPEND SRCS tma525c.c)
  list(APPEND SRCS bes_tp_tma525c.c)
endif()

if(${CONFIG_BES_TP_CHSC6540})
  list(APPEND SRCS bes_tp_chsc6540.c)
  list(APPEND SRCS bes_rpmsg_i2c.c)
endif()

if(${CONFIG_BES_TP_CST3240})
  list(APPEND SRCS bes_tp_cst3240.c)
  list(APPEND SRCS tp_cst3240.c)
endif()

if(${CONFIG_VIDEO_FB})
  list(APPEND SRCS bes_lcdc.c)
  list(APPEND SRCS bes_lcdc_cmds.c)
  list(APPEND SRCS bes_lcdc_rotate.c)
endif()

if(${CONFIG_BES_LCD_JD9165A})
  list(APPEND SRCS board_lcd_jd9165a.c)
  list(APPEND SRCS bes_lcdc_jd9165a.c)
  if(${CONFIG_BES_TP_IST415X})
    list(APPEND SRCS bes_tp_ist415x.c)
    list(APPEND SRCS tp_ist415x.c)
  endif()
endif()

if(${CONFIG_BES_LCD_RM69090})
  list(APPEND SRCS board_lcd_rm69090.c)
  list(APPEND SRCS bes_lcdc_rm69090.c)
endif()

if(${CONFIG_BES_LCD_RM69330})
  list(APPEND SRCS board_lcd_rm69330.c)
  list(APPEND SRCS bes_lcdc_rm69330.c)
endif()

if(${CONFIG_BES_LCD_A064})
  list(APPEND SRCS board_lcd_a064.c)
  list(APPEND SRCS bes_lcdc_a064.c)
  if(${CONFIG_BES_TP_A064_FTS})
    list(APPEND SRCS bes_tp_a064.c)
    list(APPEND SRCS tp_a064.c)
  endif()
endif()

if(${CONFIG_BES_LCD_HX8394})
  list(APPEND SRCS board_lcd_hx8394.c)
  list(APPEND SRCS bes_lcdc_hx8394.c)
endif()

if(${CONFIG_BES_LCD_ST7703})
  list(APPEND SRCS board_lcd_st7703.c)
  list(APPEND SRCS bes_lcdc_st7703.c)
endif()

if(${CONFIG_BES_LCD_ST7701S})
  list(APPEND SRCS board_lcd_st7701s.c)
  list(APPEND SRCS lcd_st7701s.c)
endif()

if(${CONFIG_BES_LCD_ST7796U})
  list(APPEND SRCS board_lcd_st7796u.c)
  list(APPEND SRCS lcd_st7796u.c)
endif()

if(${CONFIG_BES_LCD_ST7785M})
  list(APPEND SRCS board_lcd_st7785m.c)
  list(APPEND SRCS lcd_st7785m.c)
endif()

if(${CONFIG_BES_LCD_ST7797})
  list(APPEND SRCS board_lcd_st7797.c)
  list(APPEND SRCS lcd_st7797.c)
endif()

if(${CONFIG_BES_LCD_GC9503NP})
  list(APPEND SRCS board_lcd_gc9503np.c)
  if("${CONFIG_ARCH_BOARD_CUSTOM_PRODUCT_NAME}" STREQUAL "dx2")
    list(APPEND SRCS bes_lcdc_gc9503np_dx2.c)
  else()
    list(APPEND SRCS bes_lcdc_gc9503np.c)
  endif()
endif()

if(${CONFIG_BES_EMMC})
  list(APPEND SRCS board_bes_emmc.c)
endif()

if(${CONFIG_BES_EMMC_DEV})
  list(APPEND SRCS bes_emmcdev.c)
endif()

if(${CONFIG_IEEE80211_BROADCOM_BCM4301X})
  list(APPEND SRCS board_wlan_bcm4301x.c)
endif()

if(${CONFIG_BES_NAND_FLASH})
  list(APPEND SRCS board_bes_nand.c)
endif()

if(${CONFIG_RELAY_GPIO})
  list(APPEND SRCS board_relays_gpio.c)
endif()

if(NOT CONFIG_GEN_DSP_BIN)
  if(${CONFIG_BES_BOARD_START_FILE_CM})
    list(APPEND SRCS bes_start_cm.c)
  endif()

  if(${CONFIG_BES_BOARD_START_FILE_CA})
    list(APPEND SRCS bes_start_ca.c)
  endif()

  if(${CONFIG_BES_BOARD_START_FILE_CMCP})
    list(APPEND SRCS bes_start_cmcp.c)
  endif()

  if(${CONFIG_BES_BOARD_START_FILE_CHIP_START})
    # list(APPEND SRCS bes_start_cm.c)
  endif()
endif()

if(${CONFIG_USBDEV})
  list(APPEND SRCS bes_composite.c)
endif()

if(${CONFIG_BES_AUDIO_CLIENT})
  list(APPEND SRCS bes_audio_client.c)
endif()

endif()

target_sources(board PRIVATE ${SRCS})

# INCLUDE

set_property(
  TARGET nuttx
  APPEND
  PROPERTY NUTTX_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR})

set(INCDIR
    ${NUTTX_APPS_DIR}/vendor/bes/framework/services/platform/drivers/graphic/lcdc
    ${NUTTX_APPS_DIR}/vendor/bes/framework/services/platform/drivers/graphic/gpu
    ${NUTTX_APPS_DIR}/vendor/bes/framework/services/platform/drivers/graphic/gpu/drv/vglite/inc
    ${NUTTX_APPS_DIR}/apps/graphics/lvgl/lvgl
    ${NUTTX_DIR}/${CONFIG_ARCH_BOARD_CUSTOM_DIR}/include
    )

target_include_directories(board PRIVATE ${INCDIR})
