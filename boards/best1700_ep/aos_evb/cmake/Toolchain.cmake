# ##############################################################################
# vendor/bes/boards/***/***/cmake/Toolchain.cmake
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

if(CONFIG_BES1700_AP_LIBRARY_MODE AND CONFIG_BES1700_AP)
  set(BES1700_AP_LIBRARY_MODE TRUE)
else()
  set(BES1700_AP_LIBRARY_MODE FALSE)
endif()

set(SPECIAL_FLAGS "-DCHIP_BEST1700 ")

# add BES SDK target
add_custom_target(BES_SDK_TARGET)

add_compile_options(-pipe)

# add BES int32_t compile option
add_compile_options(-U__INT32_TYPE__ -D__INT32_TYPE__=int -U__UINT32_TYPE__)

# set BES_SDK_FLAGS

if(NOT "${CONFIG_ARCH_BOARD_CUSTOM_NAME}" STREQUAL "audio")
  # link entry add
  add_link_options(-static -nostdlib -Wl,-X -Wl,--build-id)
  add_link_options(-Wl,--whole-archive)
  add_link_options(-Wl,--entry=Boot_Loader)

  # set BES_SDK_FLAGS(CFLAGS)list(APPEND BES_SDK_FLAGS -DCHIP_BEST***)
  list(APPEND BES_SDK_FLAGS ${SPECIAL_FLAGS})
  if(CONFIG_ARCH_TRUSTZONE_NONSECURE)
    list(APPEND BES_SDK_FLAGS -DARM_CMNS)
    nuttx_add_extra_library(${CMAKE_BINARY_DIR}/../tee/nuttx_tee.se)
  endif()
  if(CONFIG_ARCH_TRUSTZONE_SECURE)
    list(APPEND BES_SDK_FLAGS -DARM_CMSE)
    add_link_options(-Wl,--cmse-implib  -Wl,--out-implib=${CMAKE_BINARY_DIR}/nuttx_tee.se)
  endif()

else()
  # xtensa
  add_compile_options(-mlongcalls -Wno-atomic-alignment -Wno-absolute-value)
  add_link_options(-Wl,--entry=_ResetVector)
  add_link_options(-Wl,--whole-archive)

  if(CONFIG_HAVE_CXX)
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)
  endif()

  set(BES_SDK_FLAGS ${SPECIAL_FLAGS} -DCHIP_BES_HIFI4 -DCHIP_SUBSYS_DSP -DBTH_AS_MAIN_MCU)

  set(BES_SDK_BUILD_DIR ${NUTTX_DIR}/../vendor/bes/${CONFIG_BES_DDK_DIR})

  list(APPEND BES_SDK_INCDIR ${BES_SDK_BUILD_DIR}/platform/hal)

endif()


# generate board_cfg.cmake

set(MK_FILE ${NUTTX_BOARD_ABS_DIR}/board_cfg.mk)
set(OUT_CMAKE ${NUTTX_BOARD_ABS_DIR}/board_cfg.cmake)

# used to identify ENV params that need passing to bsp
set(ENV{CONFIG_START} 1)

set(BES_PREBUILD_DIR ${NUTTX_DIR}/../prebuild)
if(NOT EXISTS ${BES_PREBUILD_DIR}/mk2cmake.py)
  set(BES_PREBUILD_DIR ${NUTTX_DIR}/../../prebuild)
endif()

execute_process(
    COMMAND python3
            ${BES_PREBUILD_DIR}/mk2cmake.py
            ${MK_FILE}
            ${OUT_CMAKE}
    RESULT_VARIABLE ret
    ERROR_VARIABLE err
)

if(NOT ret EQUAL 0)
    message(FATAL_ERROR "mk2cmake failed:\n${err}")
endif()

include ("${NUTTX_BOARD_ABS_DIR}/board_cfg.cmake")

# only for elf compile, don't need to set this when flat compile list(APPEND
# BES_SDK_FLAGS -pipe -fpic -msingle-pic-base -mpic-register=r10) set
# BES_SDK_BUILD_DIR, include BES_SDK .h
set(BES_SDK_BUILD_DIR ${NUTTX_DIR}/../vendor/bes/${CONFIG_BES_DDK_DIR})
list(
  APPEND
  BES_SDK_INCDIR
  ${BES_SDK_BUILD_DIR}/include
  ${BES_SDK_BUILD_DIR}/include/rtos/nuttx
  ${BES_SDK_BUILD_DIR}/multimedia/inc
  ${BES_SDK_BUILD_DIR}/multimedia/inc/audio/process
  ${BES_SDK_BUILD_DIR}/multimedia/inc/audio/process/filters/include
  ${BES_SDK_BUILD_DIR}/multimedia/inc/audio/process/drc/include
  ${BES_SDK_BUILD_DIR}/multimedia/inc/audio/process/limiter/include
  ${BES_SDK_BUILD_DIR}/multimedia/inc/speech/inc
  ${BES_SDK_BUILD_DIR}/net
  ${BES_SDK_BUILD_DIR}/net/utils
  ${BES_SDK_BUILD_DIR}/net/wifi
  ${BES_SDK_BUILD_DIR}/net/wifi/wifi_p2p
  ${BES_SDK_BUILD_DIR}/platform/hal
  ${BES_SDK_BUILD_DIR}/platform
  ${BES_SDK_BUILD_DIR}/platform/hal/best1700
  ${BES_SDK_BUILD_DIR}/platform/drivers/emmc/host/hci
  ${BES_SDK_BUILD_DIR}/platform/drivers/emmc/host/core
  ${BES_SDK_BUILD_DIR}/platform/drivers/emmc/host/card
  ${BES_SDK_BUILD_DIR}/platform/drivers/emmc/host/inc
  ${BES_SDK_BUILD_DIR}/platform/drivers/graphic/lcdc
  ${BES_SDK_BUILD_DIR}/platform/drivers/ana
  ${BES_SDK_BUILD_DIR}/platform/cmsis
  ${BES_SDK_BUILD_DIR}/platform/cmsis/inc
  ${BES_SDK_BUILD_DIR}/platform/drivers
  ${BES_SDK_BUILD_DIR}/platform/cmsis/inc
  ${BES_SDK_BUILD_DIR}/rtos/nuttx
  ${BES_SDK_BUILD_DIR}/services/nv_section/include
  ${BES_SDK_BUILD_DIR}/services/nv_section/aud_section
  ${BES_SDK_BUILD_DIR}/services/multimedia/inc
  ${BES_SDK_BUILD_DIR}/services/multimedia/audio/process
  ${BES_SDK_BUILD_DIR}/services/openamp/include
  ${BES_SDK_BUILD_DIR}/services/openamp/rptun/chips/utils
  ${BES_SDK_BUILD_DIR}/services/audioflinger
  ${BES_SDK_BUILD_DIR}/utils/heap
  ${BES_SDK_BUILD_DIR}/utils/kfifo
  ${BES_SDK_BUILD_DIR}/utils/hwtimer_list
  ${BES_SDK_BUILD_DIR}/utils/boot_struct)

set_property(
  TARGET BES_SDK_TARGET
  APPEND
  PROPERTY BES_SDK_INCLUDE_DIR ${BES_SDK_INCDIR})

set_property(
  TARGET BES_SDK_TARGET
  APPEND
  PROPERTY BES_SDK_COMPILE_OPTIONS ${BES_SDK_FLAGS})

set_property(
  TARGET BES_SDK_TARGET
  APPEND
  PROPERTY BES_SDK_BUILD_DIR ${BES_SDK_BUILD_DIR})

if(BES1700_AP_LIBRARY_MODE)
  set(PREBUILT_LIB_DIR ${NUTTX_BOARD_ABS_DIR}/configs/${CONFIG_ARCH_BOARD_CUSTOM_NAME})
  file(GLOB EXTRA_LIBS
       ${PREBUILT_LIB_DIR}/libbesboard_${CONFIG_ARCH_BOARD_CUSTOM_NAME}.a
       ${PREBUILT_LIB_DIR}/libbeschip_${CONFIG_ARCH_BOARD_CUSTOM_NAME}.a)
else()
  set(PREBUILT_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/../libs/${CONFIG_ARCH_BOARD_CUSTOM_NAME})
  file(GLOB EXTRA_LIBS ${PREBUILT_LIB_DIR}/*.a)
endif()

if(EXTRA_LIBS)
  nuttx_add_extra_library(${EXTRA_LIBS})
  message(STATUS "Prebuilt BSP libraries: ${EXTRA_LIBS}")
endif()

set_property(
  TARGET BES_SDK_TARGET
  APPEND
  PROPERTY NUTTX_ELF_MODULE_LINK_OPTIONS -r -e main -T
           $(BOARD_DIR)/scripts/gnu-elf.ld)

set_property(
  TARGET BES_SDK_TARGET
  APPEND
  PROPERTY SECURE_BOOT_TOOLS ${BES_SDK_BUILD_DIR}/utils/secure_boot/tools)
