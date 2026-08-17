#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best1701_ep
PROJECT=aos_evb
board_config=boards/$build_chip/$PROJECT/configs
output=rtos/nuttx
build_cmake=0
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

    if [ "$1" = "bootloader" ]; then
        cmd=$cmd""

    elif [ "$1" = "ota" ]; then
        cmd=$cmd""

    elif [ "$1" = "ap" ]; then
        cmd=$cmd"CONFIG_BES_CHIP_SIMU=y AP_BOOTLOADER_IN_EMMC=1 APSRAM_ENABLE=1 APSRAM_DEBUG=1
            PSRAM_SPEED=24 APSRAM_32M_MODE=1 APSRAM_SPEED=24 APSRAM_2X64_MODE=1 AP_APSRAM_ENABLE=1
            PSRAM_ENABLE=1  APSRAM_SIZE=0x40000000 AP_EXEC_IN_APSRAM=1 SECURE_BOOT_VER=5"

    elif [ "$1" = "casys-a32" ]; then
        if [ "$build_cmake" != "1" ]; then
            cmd=$cmd"-e -DFPGA "
        fi
        cmd=$cmd"DSIPLL_MHZ=1000 OSC_26M_X4_AUD2BB=1 FPGA=1 ALGORITHMS_ENABLE=0 DDR_ENABLE=0 DDR_SIZE=0x4000000"
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

if [ "$1" = "bootloader" ]; then
    shift
    build bootloader $*

elif [ "$1" = "ota" ]; then
    shift
    build ota $*

elif [ "$1" = "ap" ]; then
    shift
    build ap $*

elif [ "$1" = "casys-a32" ]; then
    shift
    build casys-a32 $*

elif [ "$build_cmake" = "1" ]; then
    build ap $*
    build casys-a32 $*


elif [ "$build_distclean" = "1" ]; then
    build ap distclean
    build casys-a32 distclean

else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services/out -rf;rm rtos/nuttx/config*

    build ap $*
    build ap distclean
    build casys-a32 $*
    build casys-a32 distclean

fi

if [ "$build_cmake" = "1" ]; then
    mkdir -p $output
    find cmake_out/$build_chip/$PROJECT -path "*/out" -prune -o \
        -type f \( -name "nuttx_*.bin*" -o -name "nuttx_*.elf" -o -name "nuttx_*.map" \
            -o -name "nuttx-*.bin*" -o -name "nuttx-*.elf" -o -name "nuttx-*.map" \) \
        -exec cp {} "$output/" \;
fi

echo "build $board_config done!!!"
