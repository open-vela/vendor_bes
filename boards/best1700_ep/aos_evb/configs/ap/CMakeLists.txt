# ##############################################################################
# vendor/bes/boards/best1700_ep/aos_evb/configs/ap/CMakeLists.txt
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

# set target var:
set(CONFIG_ARCH_BOARD "nx_bestbsp_ap")
set(LD_SCRIPT_FILE _best1000.lds)

list(APPEND BES_SDK_FLAGS -DMPU_DEFAULTMAP_DISABLE)

set_property(
  TARGET BES_SDK_TARGET
  APPEND
  PROPERTY CONFIG_ARCH_BOARD ${CONFIG_ARCH_BOARD})

set_property(
  TARGET BES_SDK_TARGET
  APPEND
  PROPERTY LD_SCRIPT_FILE ${LD_SCRIPT_FILE})

if(USE_TRACE_ID STREQUAL "1")
  list(APPEND OBJCOPYARGS -R .trc_str)
  list(APPEND BES_SDK_FLAGS -DUSE_TRACE_ID)

  # POSTBUILD
  add_custom_target(
    nuttx_post_build
    DEPENDS nuttx
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating: nuttx_ap.bin"
    COMMAND ${OBJCOPY} ${OBJCOPYARGS} -O binary nuttx nuttx.bin
    COMMAND ${CMAKE_COMMAND} -E copy nuttx nuttx_ap.elf
    COMMAND ${CMAKE_COMMAND} -E copy nuttx.bin nuttx_ap.bin
    COMMAND ${CMAKE_COMMAND} -E copy nuttx.map nuttx_ap.map
    COMMAND ${BES_SDK_BUILD_DIR}/tools/gen_str_bin.pl nuttx_ap.elf nuttx_ap
    COMMAND ${CMAKE_COMMAND} -E rm nuttx_ap
    COMMAND ${BES_SDK_BUILD_DIR}/tools/fill_sec_base.pl nuttx_ap.elf nuttx.bin nuttx_ap.bin)

else()

  # POSTBUILD
  add_custom_target(
    nuttx_post_build
    DEPENDS nuttx
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating: nuttx_ap.bin"
    COMMAND ${CMAKE_COMMAND} -E copy nuttx nuttx_ap.elf
    COMMAND ${CMAKE_COMMAND} -E copy nuttx.bin nuttx_ap.bin
    COMMAND ${CMAKE_COMMAND} -E copy nuttx.map nuttx_ap.map
    COMMAND ${BES_SDK_BUILD_DIR}/tools/fill_sec_base.pl nuttx_ap.elf nuttx.bin nuttx_ap.bin)

endif()
