#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best3601_ep
PROJECT=aos_evb
board_config=boards/$build_chip/$PROJECT/configs
output=rtos/nuttx
build_cmake=0
MM_PROJECT=nuttx_1700
build_distclean=0
sdk_build=1
build_all=0

bes_sdk_build=$(repo list framework/services 2>/dev/null)
if [[ $bes_sdk_build = *"bes-aos/bsp-src"* ]]; then
    sdk_build=0
fi

function build()
{
    if [ $# -eq 0 ]; then
        echo "need param!"
        exit 1
    fi

    cmd="./build.sh $board_config/$1 "
    if [ "$build_cmake" = "1" ]; then
        cmd=$cmd"--cmake "
    fi
    cmd=$cmd"-j8 "

    if [ "$1" = "ap" ]; then
        cmd=$cmd"FLASH_SIZE=0x800000 VUSB_ON=1 IDLE_MIN_SYS_FREQ_MHZ=208 PSRAM_SIZE=0x2000000 \
            PSRAM_X16_MODE=1 PSRAM_SPEED=200 UART0_IOMUX_INDEX=96 SMF=1 DEFAULT_CODE_IN_PSRAM=1
            FLASH_HIGH_SPEED=1 PSRAM_ENABLE=1 APSRAM_ENABLE=1 NO_SLEEP=1"

    elif [ "$1" = "ap_mini3d" ]; then
        cmd=$cmd"FLASH_SIZE=0x800000 VUSB_ON=1 IDLE_MIN_SYS_FREQ_MHZ=208 PSRAM_SIZE=0x2000000 \
            PSRAM_X16_MODE=1 PSRAM_SPEED=200 UART0_IOMUX_INDEX=96 SMF=1 DEFAULT_CODE_IN_PSRAM=1 \
            FLASH_HIGH_SPEED=1 PSRAM_ENABLE=1 APSRAM_ENABLE=1 NO_SLEEP=1 NO_CP=1 INCLUDE_ZSP_BIN=0 \
            LTE_NV_SECTION_ENABLE=0 SPEECH_LIB=0 GCV_BUILD_LIBS=1"

    fi

    shift
    cmd=$cmd" "$*
    echo "$cmd"
    $cmd
    if [ $? -ne 0 ]; then
        exit 1
    fi
}

# global params check

for arg in $*
do
    if [ $arg = "cmake" ];then
        build_cmake=1
        output=cmake_out/$build_chip/$PROJECT/out
        shift
    fi
    if [ $arg = "distclean" ];then
        build_distclean=1
    fi
done


# build config check

if [ "$1" = "ap" ]; then
    shift
    build ap $*

elif [ "$1" = "ap_mini3d" ]; then
    shift
    build ap_mini3d $*

elif [ "$build_cmake" = "1" ]; then
    build ap $*
    build ap_mini3d $*

elif [ "$build_distclean" = "1" ]; then
    build ap distclean
    build ap_mini3d distclean

else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services/out -rf;rm rtos/nuttx/config*

    build ap $*
    build ap distclean
    build ap_mini3d $*
    build ap_mini3d distclean
fi

if [ "$build_cmake" = "1" ]; then
    mkdir -p $output
    find cmake_out/$build_chip/$PROJECT -path "*/out" -prune -o -name "nuttx_*.*" -type f -exec cp {} "$output/" \;
fi

echo "build $board_config done!!!"
