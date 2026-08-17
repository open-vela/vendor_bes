#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best1700_ep
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

WEBSVR_CFG="NET_MUSIC_SUPPORT=1 NET_MUSIC_BASE_SUPPORT=1 NET_MUSIC_SINK_SUPPORT=0 NET_MUSIC_CJSON_SUPPORT=0 \
            NET_WEBSVR_SUPPORT=1 WEBSVR_VERSION=v2 WEBSVR_FILE_SYS_SUPPORT=1"

AUDIO_PROCESS_CFG="SW_IIR_EQ_PROCESS=1 AUDIO_LIMITER=1 AUDIO_DRC=1"

AUDIO_PROCESS_ONLINE_CFG="$AUDIO_PROCESS_CFG NUTTX_AUDIO_PROCESS_ONLINE=1 PC_CMD_UART_ID=1 UART1_IOMUX_INDEX=10"

HIFI_AUDIO_PROCESS_CFG="$AUDIO_PROCESS_CFG MM_SPEECH_ENABLED=1 MM_AUDIO_PROCESS_ENABLED=1 AUDIO_COMMON=1"

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
        cmd=$cmd""

    elif [ "$1" = "bl2" ]; then
        cmd=$cmd""

    elif [ "$1" = "bth" ]; then
        cmd=$cmd""

    elif [ "$1" = "bthcp" ]; then
        cmd=$cmd""

    elif [ "$1" = "apc1" ]; then
        cmd=$cmd"CVSD_BYPASS=1 RF_TRACE_BY_SPRINTF=1"

    elif [ "$1" = "tee" ]; then
        cmd=$cmd""

    elif [ "$1" = "apns" ]; then
        cmd=$cmd"DSP_HIFI4_TRC_TO_MCU=1 CHIP_DMA_CFG_IDX=3 UTILS_ESHELL_BTRF_TEST=1 \
            ONLY_BT_DRIVE_INIT=1 $WEBSVR_CFG"

    elif [ "$1" = "ap" ]; then
        cmd=$cmd"DSP_HIFI4_TRC_TO_MCU=1 CHIP_DMA_CFG_IDX=3 UTILS_ESHELL_BTRF_TEST=1 \
            ONLY_BT_DRIVE_INIT=1 $WEBSVR_CFG"

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
    cmd="make -j8 T=best1700_watch USE_MEM_CFG=1 OSTICK_USE_FAST_TIMER=1 DEBUG=1 DEBUG_RPCHAN=0 \
        DSP_LOGIC_SROM_BASE_OFFSET=0xC00000 OPENAMP_ENABLE=1 USE_BES_RPCHAN=1 RPTUN_M55C0_2_DSPC0=1 \
        MM_ENABLED=1 MM_AUDIO_ENABLED=1 ALLOW_WARNING=1 DMA_APPLIED_ON_HIFI=1 CHIP_DMA_CFG_IDX=3 \
        DEBUG_PORT=2 TRACE_BUF_SIZE=0 DSP_HIFI4_TRC_TO_MCU=1 DSP_USE_SYS_PERIPH=0 TRACE_CPU_IMM_OUTPUT=0 \
        SMF=1 MM_PROJECT=$MM_PROJECT MM_PLATFORM=hifi4 MM_CORE=hifi4 BTWATCH=1 NO_SLEEP=1 \
        HIFI4_PSRAM_BASE=0x1BC00000 HIFI4_PSRAM_SIZE=0x400000 HIFI_DSP_LIB=1 PSRAM_ENABLE=1 \
        MEM_CFG_OPT=OPT_NUTTX"
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

elif [ "$1" = "bl2" ]; then
    shift
    build bl2 $*

elif [ "$1" = "apc1" ]; then
    shift
    build apc1 $*

elif [ "$1" = "ap" ]; then
    shift
    build ap $*

elif [ "$1" = "bth" ]; then
    shift
    build bth $*

elif [ "$1" = "bthcp" ]; then
    shift
    build bthcp $*

elif [ "$1" = "tee" ]; then
    shift
    build tee $*

elif [ "$1" = "apns" ]; then
    shift
    build apns $*

elif [ "$1" = "hifi" ]; then
    build_hifi

elif [ "$build_cmake" = "1" ]; then
    build bootloader $*
    build ota $*
    build bth $*
    build bthcp $*
    build apc1 $*
    build tee $*
    build apns $*

    if [ "$sdk_build" = "0" ]; then
        build_hifi
    fi

elif [ "$build_distclean" = "1" ]; then
    build bootloader distclean
    build ota distclean
    build bth distclean
    build bthcp distclean
    build apc1 distclean
    build ap distclean

else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services/out -rf;rm rtos/nuttx/config*

    build bootloader $*
    build bootloader distclean
    build ota $*
    build ota distclean
    build bth $*
    build bth distclean
    build bthcp $*
    build bthcp distclean
    build apc1 $*
    build apc1 distclean
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
