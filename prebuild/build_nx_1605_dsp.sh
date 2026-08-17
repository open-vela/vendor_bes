#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best1605_ep
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

    elif [ "$1" = "bl2" ]; then
        cmd=$cmd"SDMMC_DMA_DESC_CNT=64"

    elif [ "$1" = "ota" ]; then
        cmd=$cmd"SYS_USE_BTH_FLASH=1 FORCE_FLASH1_SLEEP=0"

    elif [ "$1" = "ota_psram_run" ]; then
        cmd=$cmd"NO_REPO_INFO=1 SYS_USE_BTH_FLASH=1 FORCE_FLASH1_SLEEP=0"

    elif [ "$1" = "ap" ]; then
        cmd=$cmd"DSP_HIFI4_TRC_TO_MCU=1 UTILS_ESHELL_BTRF_TEST=1 MM_PROJECT=nuttx_1605 CHIP_DMA_CFG_IDX=0"

    elif [ "$1" = "bth" ]; then
        cmd=$cmd"FLASH_NV_FACTORY=1 CVSD_BYPASS=1"

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
    cmd="make -j T=best1605_dsp BTH_AS_MAIN_MCU=0 DSP_HIFI4_TRC_TO_MCU=1 PSRAM_ENABLE=1 RMT_TRACE=1 FORCE_TRACE_UART1=1 APSRAM_ENABLE=1 \
         XTENSA_CORE=hifi4_bes_asic_call0_abi OPENAMP_ENABLE=1 USE_BES_RPCHAN=1 RPTUN_M55C0_2_DSPC0=1 \
         SMF=1 SMF_ENABLE=1 MM_PROJECT=nuttx_1605 MM_PLATFORM=hifi4 MM_CORE=hifi4 HIFI_DSP_LIB=1 ALLOW_WARNING=0 CHIP_DMA_CFG_IDX=2"
    echo "$cmd"
    $cmd
    if [ $? -ne 0 ]; then
        exit 1
    fi
    cp out/best1605_dsp/best1605_dsp.bin ../services/prebuild/nuttx_audio_${build_chip}_$PROJECT.bin
    cp out/best1605_dsp/best1605_dsp.elf ../services/prebuild/nuttx_audio_${build_chip}_$PROJECT.elf
    cp out/best1605_dsp/best1605_dsp.map ../services/prebuild/nuttx_audio_${build_chip}_$PROJECT.map
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

elif [ "$1" = "bl2" ]; then
    shift
    build bl2 $*

elif [ "$1" = "ota" ]; then
    shift
    build ota $*

elif [ "$1" = "ap" ]; then
    shift
    build ap $*

elif [ "$1" = "bth" ]; then
    shift
    build bth $*

elif [ "$1" = "ota_psram_run" ]; then
    build ota_psram_run $*

elif [ "$1" = "hifi" ]; then
    build_hifi

elif [ "$build_cmake" = "1" ]; then
    build bootloader $*
    build ota $*
    build bth $*
    build ap $*

    if [ "$sdk_build" = "0" ]; then
        build_hifi
    fi

elif [ "$build_distclean" = "1" ]; then
    build bootloader distclean
    build ota distclean
    build bth distclean
    build ap distclean

else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services/out -rf;rm rtos/nuttx/config*

    build bootloader $*
    build bootloader distclean
    build ota $*
    build ota distclean
    build ap $*
    build ap distclean
    build bth $*
    build bth distclean

    if [ "$sdk_build" = "0" ]; then
        build_hifi
    fi
fi

if [ "$build_cmake" = "1" ]; then
    mkdir -p $output
    find cmake_out/$build_chip/$PROJECT -path "*/out" -prune -o -name "nuttx_*.*" -type f -exec cp {} "$output/" \;
fi

cp framework/services/prebuild/nuttx_audio_${build_chip}_$PROJECT.bin $output/nuttx_hifi.bin
cp framework/services/prebuild/nuttx_audio_${build_chip}_$PROJECT.elf $output/nuttx_hifi.elf
cp framework/services/prebuild/nuttx_audio_${build_chip}_$PROJECT.map $output/nuttx_hifi.map

echo "build $board_config done!!!"
