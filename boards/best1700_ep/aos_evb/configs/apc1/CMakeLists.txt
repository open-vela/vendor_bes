# ##############################################################################
# vendor/bes/boards/best1700_ep/aos_evb/configs/apc1/CMakeLists.txt
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
set(CONFIG_ARCH_BOARD "nx_bestbsp_apc1")
if(CONFIG_BES_APC1_BIN_FLASH_BOOT)
  set(LD_SCRIPT_FILE _best1000.lds)
else()
  set(LD_SCRIPT_FILE _subsys.lds)
  target_link_options(nuttx PRIVATE -Wl,--entry=Reset_Handler)
endif()

set_property(
  TARGET BES_SDK_TARGET
  APPEND
  PROPERTY BES_SDK_COMPILE_OPTIONS -DCHIP_BEST1700 -DCHIP_SUBSYS_M55C1)

set_property(
  TARGET BES_SDK_TARGET
  APPEND
  PROPERTY CONFIG_ARCH_BOARD ${CONFIG_ARCH_BOARD})

set_property(
  TARGET BES_SDK_TARGET
  APPEND
  PROPERTY LD_SCRIPT_FILE ${LD_SCRIPT_FILE})

# POSTBUILD
add_custom_target(
  nuttx_post_build
  DEPENDS nuttx
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Generating: nuttx_apc1.bin"
  COMMAND ${CMAKE_COMMAND} -E copy nuttx nuttx_apc1.elf
  COMMAND ${CMAKE_COMMAND} -E copy nuttx.bin nuttx_apc1.bin
  COMMAND ${CMAKE_COMMAND} -E copy nuttx.map nuttx_apc1.map)
