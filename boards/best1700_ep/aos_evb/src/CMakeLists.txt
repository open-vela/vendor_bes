# ##############################################################################
# vendor/bes/boards/best1700_ep/aos_evb/src/CMakeLists.txt
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

# This release branch is library-mode-only apart from the released AP/APC1
# board entry wrappers kept in source form.

# add RCSRCS and RCRAWS

add_board_rcsrcs(${CMAKE_CURRENT_SOURCE_DIR}/etc/init.d/rcS
                 ${CMAKE_CURRENT_SOURCE_DIR}/etc/init.d/rc.sysinit)

if(${CONFIG_BES1700_AP})
  if(${CONFIG_ARCH_BOARD_CUSTOM_BES1700_EVB})
    add_board_rcraws(${CMAKE_CURRENT_SOURCE_DIR}/etc/build.prop)
  endif()
endif()

if(${CONFIG_BES1700_OTA})
  add_board_rcraws(${CMAKE_CURRENT_SOURCE_DIR}/etc/key.avb)
endif()

if(CONFIG_TXTABLE_DEFAULT_PARTITION EQUAL 1)
  add_board_rcsrcs(${CMAKE_CURRENT_SOURCE_DIR}/etc/txtable.txt)
endif()

if(${CONFIG_MEDIA_SERVER})
  add_board_rcraws(${CMAKE_CURRENT_SOURCE_DIR}/etc/media/graph.conf)
endif()

if(${CONFIG_LIB_PFW})
  add_board_rcraws(${CMAKE_CURRENT_SOURCE_DIR}/etc/media/criteria.txt)
  add_board_rcraws(${CMAKE_CURRENT_SOURCE_DIR}/etc/media/settings.pfw)
endif()

if(${CONFIG_MEDIA_FOCUS})
  add_board_rcraws(${CMAKE_CURRENT_SOURCE_DIR}/etc/media/media_focus.conf)
endif()

# INCLUDE

set_property(
  TARGET nuttx
  APPEND
  PROPERTY NUTTX_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR})

# target_link_options(nuttx PRIVATE
#   "LINKER:--verbose"
# )
