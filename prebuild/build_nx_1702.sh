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
        cmd=$cmd"NORFLASH_API_ENABLE=1 FLASH_DUAL_CHIP_INIT_ON=0 FLASH_SIZE=0x1000000 MEM_USE_BBPLL=1 \
        FACTORY_SECTION_ENABLE=1 USERDATA_SECTION_ENABLE=1 NEW_NV_RECORD_ENABLED=1  APSRAM_ENABLE=1 \
        DSP_HIFI4_TRC_TO_MCU=1 DSP_BOOT_FROM_PSRAM=0 USB_HIGH_SPEED=0 "

    fi

    shift
    cmd=$cmd" "$*
    echo "$cmd"
    $cmd
    if [ $? -ne 0 ]; then
        exit 1
    fi
}

function build_hifi()
{
    echo "$FUNCNAME $board_config"
    cd framework/services_hifi4/
    rm -rf out/
    cmd="make T=best1702_dsp DMA_APPLIED_ON_HIFI=1 DSP_COMBINE_BIN=1 ALLOW_WARNING=0 HIFI4_MSG_TEST=0 \
        MCU2DSP_HIFI4_MSG_TEST=0 DSP_DEEP_SLEEP=0 CORE_SLEEP_POWER_DOWN=0 RMT_TRACE=1 CHIP_DMA_CFG_IDX=3 -j8 all lst "
    echo "$cmd"
    $cmd
    if [ $? -ne 0 ]; then
        exit 1
    fi
    cp out/best1702_dsp/best1702_dsp.bin ../services/prebuild/nuttx_audio_$PROJECT.bin
    cp out/best1702_dsp/best1702_dsp.elf ../services/prebuild/nuttx_audio_$PROJECT.elf
    cp out/best1702_dsp/best1702_dsp.map ../services/prebuild/nuttx_audio_$PROJECT.map
    cd ../../
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

elif [ "$1" = "apc1" ]; then
    shift
    build apc1 $*

elif [ "$1" = "ap" ]; then
    shift
    build ap $*

elif [ "$1" = "hifi" ]; then
    build_hifi

elif [ "$build_cmake" = "1" ]; then
    build ap $*

    if [ "$sdk_build" = "0" ]; then
        build_hifi
    fi

elif [ "$build_distclean" = "1" ]; then
    build ap distclean

else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services/out -rf;rm rtos/nuttx/config*

    build ap $*
    build ap distclean

    if [ "$sdk_build" = "0" ]; then
        build_hifi
    fi
fi

if [ "$build_cmake" = "1" ]; then
    mkdir -p $output
    find cmake_out/$build_chip/$PROJECT -path "*/out" -prune -o -name "nuttx_*.*" -type f -exec cp {} "$output/" \;
fi

cp framework/services/prebuild/nuttx_audio_$PROJECT.bin $output/nuttx_hifi.bin
cp framework/services/prebuild/nuttx_audio_$PROJECT.elf $output/nuttx_hifi.elf
cp framework/services/prebuild/nuttx_audio_$PROJECT.map $output/nuttx_hifi.map

echo "build $board_config done!!!"
