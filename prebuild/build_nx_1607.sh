#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best1607_ep
PROJECT=aos_evb
board_config=boards/$build_chip/$PROJECT/configs
output=rtos/nuttx
build_cmake=0
MM_PROJECT=nuttx_1607
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

    elif [ "$1" = "apc1" ]; then
        cmd=$cmd" SUBSYS_INDEPENDENT_FREQ=1 BT_LOG_POWEROFF=1 CORE_SLEEP_POWER_DOWN=1 "

    elif [ ["$1" = "ap"]  || ["$1" = "aplp"]]; then
        cmd=$cmd" BT_VPA_CFG_TYPE=4 WIFI_RF_SW_IO_SELECT=2 SUBSYS_INDEPENDENT_FREQ=1 USE_NTS_HEAP=1 NET_HEAP_IN_PSRAM=0   WIFI_SLEEP_ENABLE=1 NET_BUF_IN_PSRAM=0 WIFI_PD_SLEEP=1 WIFI_SLEEP_ENABLE=1  SDMMC0_IOMUX_8WIRE=1 UART0_IOMUX_INDEX=44 BT_LOG_POWEROFF=1 CORE_SLEEP_POWER_DOWN=1 "

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
    cd framework/services/
    rm -rf out/
    cmd="make -j8 T=cp_subsys1 CHIP=best1607 CHIP_SUBSYS_M55C2=1 NO_SLEEP=1 OPENAMP_ENABLE=1 KERNEL=RTX5 RTOS=1 NOSTD=0 \
    RPTUN_M55C0_2_M55C2=1 CP_SUBSYS1_TEST=1 CP_SUBSYS1_TRC_TO_MCU=1 MM_PLATFORM=m55 MM_CORE=m55c2 MM_PROJECT=nuttx_1607 all \
    SMF_ENABLE=1 APSRAM_ENABLE=1 PSRAM_ENABLE=1 PSRAM_REGION_OFFSET=0x800000 PSRAM_REGION_SIZE=0x400000 DEFAULT_CODE_IN_APSRAM=1 \
    DEFAULT_DATA_IN_APSRAM=1 DEFAULT_BSS_IN_APSRAM=1 PSRAMCP_REGION_SIZE=0x400000 SMF_PLAYER_EN=1 MULTIMEDIA_DISABLE=1 AUDIO_COMMON=1 \
    SPEECH_LIB=1 CONFIG_HAVE_CXX=1  DEFAULT_CODE_IN_PSRAM=1 DEFAULT_DATA_IN_PSRAM=1 DEFAULT_BSS_IN_PSRAM=1 RTOS_IN_RAM=1 \
    OS_DYNAMIC_MEM_SIZE=0x10000 CHIP_DMA_CFG_IDX=0 SLEEP_STATS_TRACE=1 DEBUG_SLEEP_USER=1 RPMSG_SYSFREQ=1 SUBSYS_INDEPENDENT_FREQ=1 \
    RPMSG_SYSFREQ_CLIENT=1 SUBSYS_RMT_SYSFREQ_REQ=1 NOAPP=1 SLEEP_TEST=0 SUBSYS_CACHE_ENABLE=1"
    echo "$cmd"
    $cmd
    if [ $? -ne 0 ]; then
        exit 1
    fi
    cp out/cp_subsys1/cp_subsys1.bin ../services/prebuild/nuttx_audio_${build_chip}_$PROJECT.bin
    cp out/cp_subsys1/cp_subsys1.elf ../services/prebuild/nuttx_audio_${build_chip}_$PROJECT.elf
    cp out/cp_subsys1/cp_subsys1.map ../services/prebuild/nuttx_audio_${build_chip}_$PROJECT.map
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

elif [ "$1" = "aplp" ]; then
    shift
    build aplp $*

elif [ "$1" = "hifi" ]; then
    build_hifi

elif [ "$build_cmake" = "1" ]; then
    build bootloader $*
    build ota $*
    build apc1 $*
    build ap $*
    build aplp $*

    if [ "$sdk_build" = "0" ]; then
        build_hifi
    fi

elif [ "$build_distclean" = "1" ]; then
    build bootloader distclean
    build ota distclean
    build apc1 distclean
    build ap distclean
    build aplp distclean

else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services/out -rf;rm rtos/nuttx/config*

    build bootloader $*
    build bootloader distclean
    build ota $*
    build ota distclean
    build apc1 $*
    build apc1 distclean
    build ap $*
    build ap distclean
    build aplp $*
    build aplp distclean

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
