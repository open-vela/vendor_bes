#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best1700_ep
PROJECT=aos_evb_2800hp_ap_start_bth
ln -s $DIR/../boards/$build_chip/aos_evb_2800hp $DIR/../boards/$build_chip/$PROJECT
board_config=boards/$build_chip/$PROJECT/configs
output=rtos/nuttx
build_cmake=0
MM_PROJECT=nuttx_1700hp
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
        cmd=$cmd"WIFI_CALI_ENABLE=0"

    elif [ "$1" = "ota" ]; then
        cmd=$cmd"WIFI_CALI_ENABLE=0"

    elif [ "$1" = "bth_ramrun" ]; then
        cmd=$cmd"USE_OS_MAIN=1"

    elif [ "$1" = "apc1" ]; then
        cmd=$cmd"CFG_APP_DATAPATH_SERVER=0 ESHELL_ECHOBACK=0 \
            P2P_MODE_SUPPORT=0 USE_NTS_HEAP=0 WIFI_RF_SW_IO_SELECT=1 WIFI_ANA_YB_CFG=1 \
            RAMX_REGION_SIZE=0x80000 CHIP_DMA_CFG_IDX=3"

    elif [ "$1" = "ap_start_bth" ]; then
        cmd=$cmd"DSP_HIFI4_TRC_TO_MCU=1 CHIP_DMA_CFG_IDX=3 UTILS_ESHELL_BTRF_TEST=1 \
            ESHELL_ECHOBACK=0 P2P_MODE_SUPPORT=0 USE_NTS_HEAP=0 ONLY_BT_DRIVE_INIT=1"

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
    cmd="make T=best1700_watch CHIP=best1700 ALLOW_WARNING=1 USE_MEM_CFG=1 BTWATCH=1 MEM_CFG_OPT=OPT_HP \
        PSRAM_ENABLE=0 OSTICK_USE_FAST_TIMER=1 DSP_USE_SYS_PERIPH=1  CHIP_DMA_CFG_IDX=3 DEBUG=1 \
        DSP_HIFI4_TRC_TO_MCU=1 OPENAMP_ENABLE=1 RPTUN_M55C0_2_DSPC0=1 RPTUN_M55C1_2_DSPC0=0 \
        DMA_APPLIED_ON_HIFI=1 SMF=1 MM_PLATFORM=hifi4 MM_CORE=hifi4 MM_PROJECT=$MM_PROJECT \
        DYN_LIB_LOADER_ENABLE=1 HIFI_DSP_LIB=1 -j8"
    echo "$cmd"
    $cmd
    if [ $? -ne 0 ]; then
        exit 1
    fi
    cp out/best1700_watch/best1700_watch.bin ../services/prebuild/nuttx_audio_$PROJECT.bin
    cp out/best1700_watch/best1700_watch.elf ../services/prebuild/nuttx_audio_$PROJECT.elf
    cp out/best1700_watch/best1700_watch.map ../services/prebuild/nuttx_audio_$PROJECT.map
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
    build ap_start_bth $*

elif [ "$1" = "bth" ]; then
    shift
    build bth_ramrun $*

elif [ "$1" = "hifi" ]; then
    build_hifi

elif [ "$build_cmake" = "1" ]; then
    build bootloader $*
    build ota $*
    build ap_start_bth $*
    build apc1 $*
    build bth_ramrun $*

    if [ "$sdk_build" = "0" ]; then
        build_hifi
    fi

elif [ "$build_distclean" = "1" ]; then
    build bootloader distclean
    build ota distclean
    build ap_start_bth distclean
    build apc1 distclean
    build bth_ramrun distclean

else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services/out -rf;rm rtos/nuttx/config*

    build bootloader $*
    build bootloader distclean
    build ota $*
    build ota distclean
    build ap_start_bth $*
    build ap_start_bth distclean
    build apc1 $*
    build apc1 distclean
    build bth_ramrun $*
    build bth_ramrun distclean

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
