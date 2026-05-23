# ##############################################################################
# vendor/bes/boards/CMakeLists.txt
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

target_include_directories(board PRIVATE ${NUTTX_DIR}/include)

target_include_directories(board SYSTEM PRIVATE ${CMAKE_BINARY_DIR}/include/arch/chip)

# target_include_directories( board PRIVATE ${NUTTX_DIR}/include/nuttx)

get_target_property(BES_SDK_BUILD_DIR BES_SDK_TARGET BES_SDK_BUILD_DIR)
get_target_property(CONFIG_ARCH_BOARD BES_SDK_TARGET CONFIG_ARCH_BOARD)
get_target_property(LD_SCRIPT_FILE BES_SDK_TARGET LD_SCRIPT_FILE)

target_include_directories(
  board
  PRIVATE $<GENEX_EVAL:$<TARGET_PROPERTY:BES_SDK_TARGET,BES_SDK_INCLUDE_DIR>>)

target_compile_options(
  board
  PRIVATE
    $<GENEX_EVAL:$<TARGET_PROPERTY:BES_SDK_TARGET,BES_SDK_COMPILE_OPTIONS>>)

if(BES1700_LIBRARY_MODE)
  set(PREBUILT_BES_SDK_DIR
      ${NUTTX_BOARD_ABS_DIR}/configs/${CONFIG_ARCH_BOARD_CUSTOM_NAME})
  set(PREBUILT_BES_SDK_LIB
      ${PREBUILT_BES_SDK_DIR}/lib${CONFIG_ARCH_BOARD}.a)
  set(PREBUILT_LD_SCRIPT
      ${PREBUILT_BES_SDK_DIR}/${LD_SCRIPT_FILE})

  if(NOT EXISTS ${PREBUILT_BES_SDK_LIB})
    message(FATAL_ERROR
            "best1700 library mode is enabled, but ${PREBUILT_BES_SDK_LIB} is missing")
  endif()

  if(NOT EXISTS ${PREBUILT_LD_SCRIPT})
    message(FATAL_ERROR
            "best1700 library mode is enabled, but ${PREBUILT_LD_SCRIPT} is missing")
  endif()

  set_property(GLOBAL PROPERTY LD_SCRIPT ${PREBUILT_LD_SCRIPT})
else()
  if(NOT EXISTS ${LD_SCRIPT_FILE})
    set_property(
      GLOBAL
      PROPERTY
        LD_SCRIPT
        "${CMAKE_CURRENT_BINARY_DIR}/out/${CONFIG_ARCH_BOARD}/${LD_SCRIPT_FILE}")
  else()
    set_property(GLOBAL PROPERTY LD_SCRIPT ${LD_SCRIPT_FILE})
  endif()
endif()

# link lib

# nuttx/vela cmake has been loaded the .a, so rm

# execute_process( COMMAND readlink -f
# ${NUTTX_BOARD_ABS_DIR}/libs/${CONFIG_ARCH_BOARD_CUSTOM_NAME}
# OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LINK_PATH_ABS
# WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}) file(GLOB ALL_LIBRARIES
# "${LINK_PATH_ABS}/*.a") target_link_libraries(board ${ALL_LIBRARIES})

if(BES1700_LIBRARY_MODE)
  message(STATUS "Using prebuilt best1700 ${CONFIG_ARCH_BOARD_CUSTOM_NAME} BSP archive: ${PREBUILT_BES_SDK_LIB}")

  add_library(BES_SDK_LIB STATIC IMPORTED GLOBAL)
  set_target_properties(
    BES_SDK_LIB
    PROPERTIES
      IMPORTED_LOCATION ${PREBUILT_BES_SDK_LIB})
else()
  # call external module for exter build
  set(CUST_BUILD_PARAMS $ENV{CUST_BUILD_PARAMS})
  message(STATUS "CUST_BUILD_PARAMS=${CUST_BUILD_PARAMS}")

  # pack all env params to bsp
  execute_process(
      COMMAND env
      OUTPUT_VARIABLE _env_output
  )

  string(REPLACE "\n" ";" _env_lines "${_env_output}")

  set(_env_args "CONFIG_ARCH_BOARD=${CONFIG_ARCH_BOARD}")
  set(_found FALSE)

  foreach(line IN LISTS _env_lines)
      if(NOT _found)
          if(line MATCHES "^CONFIG_START=")
              set(_found TRUE)
          endif()
      else()
          if(line MATCHES "^[^=]+=")
              list(APPEND _env_args "${line}")
          endif()
      endif()
  endforeach()
  message(STATUS "_env_args=${_env_args}")

  ExternalProject_Add(
    BES_SDK_TARGET_out_tree
    SOURCE_DIR "${BES_SDK_BUILD_DIR}"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND
      ${CMAKE_COMMAND} -E env ${_env_args} bash -c
      "make -C ${BES_SDK_BUILD_DIR} lib${CONFIG_ARCH_BOARD}.a NUTTX_BUILD_ROOT=${CMAKE_BINARY_DIR} TOPDIR=${NUTTX_DIR} BES_NUTTX_BOARD_DIR=${BES_NUTTX_BOARD_DIR} O=${CMAKE_CURRENT_BINARY_DIR}/out ${CUST_BUILD_PARAMS}"
    INSTALL_COMMAND ""
    BUILD_ALWAYS TRUE)

  # imported target need a generate rule

  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/out/${CONFIG_ARCH_BOARD}/lib${CONFIG_ARCH_BOARD}.a
      ${CMAKE_CURRENT_BINARY_DIR}/out/${CONFIG_ARCH_BOARD}/${LD_SCRIPT_FILE}
    COMMAND
      ${CMAKE_COMMAND} -E touch
      ${CMAKE_CURRENT_BINARY_DIR}/out/${CONFIG_ARCH_BOARD}/lib${CONFIG_ARCH_BOARD}.a
    COMMENT "Generating lib${CONFIG_ARCH_BOARD}.a"
    DEPENDS BES_SDK_TARGET_out_tree)

  # create a virtual intermediate dependency target

  add_custom_target(
    BES_SDK_bin ALL
    DEPENDS
      ${CMAKE_CURRENT_BINARY_DIR}/out/${CONFIG_ARCH_BOARD}/lib${CONFIG_ARCH_BOARD}.a
  )

  # define IMPORTED target and its relation chain

  add_library(BES_SDK_LIB STATIC IMPORTED GLOBAL)
  add_dependencies(BES_SDK_LIB BES_SDK_bin)
  add_dependencies(board BES_SDK_LIB)
  set_target_properties(
    BES_SDK_LIB
    PROPERTIES
      IMPORTED_LOCATION
      ${CMAKE_CURRENT_BINARY_DIR}/out/${CONFIG_ARCH_BOARD}/lib${CONFIG_ARCH_BOARD}.a
  )
endif()

set_property(GLOBAL APPEND PROPERTY NUTTX_SYSTEM_LIBRARIES BES_SDK_LIB)
