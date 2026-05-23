# ##############################################################################
# vendor/bes/boards/best1700_ep/aos_evb/CMakeLists.txt
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

set(BES_NUTTX_BOARD_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if((CONFIG_BES1700_AP_LIBRARY_MODE AND CONFIG_BES1700_AP) OR
   (CONFIG_BES1700_APC1_LIBRARY_MODE AND CONFIG_BES1700_APC1))
  set(BES1700_LIBRARY_MODE TRUE)
else()
  set(BES1700_LIBRARY_MODE FALSE)
endif()

if(BES1700_LIBRARY_MODE)
  message(STATUS "best1700 library mode enabled for ${CONFIG_ARCH_BOARD_CUSTOM_NAME}")
endif()

add_subdirectory(../../common common)
add_subdirectory(src)
add_subdirectory(configs/${CONFIG_ARCH_BOARD_CUSTOM_NAME})
add_subdirectory(${NUTTX_BOARD_ABS_DIR}/../../ EXCLUDE_FROM_ALL bes_board)
