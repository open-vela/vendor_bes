#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best1702_ep
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

    if [ "$1" = "ap" ]; then
        cmd=$cmd"CHIP_HAS_HIFI4=0 M55C1_AS_MAIN_MCU=1 CHIP_SUBSYS_M55C1=1 CHIP_DMA_CFG_IDX=1"
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
    build ap_rc07 $*


elif [ "$build_cmake" = "1" ]; then
    build ap $*

elif [ "$build_distclean" = "1" ]; then
    build ap distclean

else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services/out -rf;rm rtos/nuttx/config*

    build ap_rc07 $*
    build ap_rc07 distclean

fi

if [ "$build_cmake" = "1" ]; then
    mkdir -p $output
    find cmake_out/$build_chip/$PROJECT -path "*/out" -prune -o -name "nuttx_*.*" -type f -exec cp {} "$output/" \;
fi

echo "build $board_config done!!!"
