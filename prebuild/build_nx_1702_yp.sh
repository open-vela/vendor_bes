#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best1702_ep
PROJECT=aos_evb_yp
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

AUDIO_PROCESS_CFG="SW_IIR_EQ_PROCESS=1 AUDIO_LIMITER=1 AUDIO_DRC=1 AUDIO_EQ=1"
HIFI_AUDIO_PROCESS_CFG="MULTIMEDIA_DISABLE=0 MM_AUDIO_PROCESS_ENABLED=1 MM_SPEECH_ENABLED=1 \
    AUDIO_COMMON=1 SPEECH_LIB=1 SPEECH_ALGO=1 SPEECH_HIFI_V1=1 $AUDIO_PROCESS_CFG "
DYN_LIB_CFG="UTILS_BES_DLL_ENABLE=1 SMF_DLL_ENABLE=1 "

if [ "$sdk_build" = "0" ]; then
    DYN_LIB_CFG=$DYN_LIB_CFG"DYN_LIB_LOADER_ENABLE=1"
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
        cmd=$cmd"NORFLASH_API_ENABLE=1 FLASH_DUAL_CHIP_INIT_ON=0 FLASH_SIZE=0x2000000 MEM_USE_BBPLL=1 UTILS_ESHELL_BTRF_TEST=1 \
        SCO_OVER_INTERSYS=1 SCO_INTERSYS_ID=3 AUDIO_SCO_BTPCM_CHANNEL=0 DSP_USE_SCO_INTERSYS=1 FACTORY_SECTION_ENABLE=1 \
        USERDATA_SECTION_ENABLE=1 NEW_NV_RECORD_ENABLED=1 DSP_HIFI4_TRC_TO_MCU=1 DSP_BOOT_FROM_PSRAM=0 DSP_BOOT_FROM_SRAM=1 \
        NN_KWS=1 CODEC_ADC2_DSF=1 CHIP_DMA_CFG_IDX=3 -j $DYN_LIB_CFG $AUDIO_PROCESS_ONLINE_CFG "

    elif [ "$1" = "apc1" ]; then
        cmd=$cmd"NO_CP=0"

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
    cmd="make T=best1702_dsp DMA_APPLIED_ON_HIFI=1 DSP_COMBINE_BIN=1 ALLOW_WARNING=1 HIFI4_MSG_TEST=0 XTENSA_CORE=hifi5s_bes_asic_call0_abi PSRAM_ENABLE=1 \
        MCU2DSP_HIFI4_MSG_TEST=0 DSP_DEEP_SLEEP=0 CORE_SLEEP_POWER_DOWN=0 RMT_TRACE=1 CHIP_DMA_CFG_IDX=3 -j8 \
        all lst MM_PROJECT=nuttx_1702yp MM_PLATFORM=hifi5s MM_CORE=hifi5s OPENAMP_ENABLE=1 RPTUN_M55C0_2_DSPC0=1 \
        SMF=1 DSP_LIB=1 FLASH_SIZE=0x200000 RPMSG_SYSFREQ=1 RPMSG_SYSFREQ_CLIENT=1 \
        $DYN_LIB_CFG $HIFI_AUDIO_PROCESS_CFG"
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
    build bootloader $*
    build ota $*
    build ap $*
    build apc1 $*

    if [ "$sdk_build" = "0" ]; then
        build_hifi
    fi

elif [ "$build_distclean" = "1" ]; then
    build bootloader distclean
    build ota distclean
    build ap distclean
    build apc1 distclean

else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services/out -rf;rm rtos/nuttx/config*

    build bootloader $*
    build bootloader distclean
    build ota $*
    build ota distclean
    build ap $*
    build ap distclean
    build apc1 $*
    build apc1 distclean

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
