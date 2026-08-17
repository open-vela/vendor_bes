#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best1700_ep
PROJECT=aos_evb_2800hp_wifibtc0_smfc1
ln -s $DIR/../boards/$build_chip/aos_evb_2800hp $DIR/../boards/$build_chip/$PROJECT
board_config=boards/$build_chip/$PROJECT/configs
output=rtos/nuttx
build_cmake=0
MM_PROJECT=nuttx_1700hp_rec_c1
build_distclean=0
sdk_build=1
build_all=0

bes_sdk_build=$(repo list framework/services 2>/dev/null)
if [[ $bes_sdk_build = *"bes-aos/bsp-src"* ]]; then
    sdk_build=0
fi

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
        cmd=$cmd"WIFI_CALI_ENABLE=0 MEM_CFG_OPT=OPT_HP_C0C1"

    elif [ "$1" = "ota" ]; then
        cmd=$cmd"WIFI_CALI_ENABLE=0 MEM_CFG_OPT=OPT_HP_C0C1"

    elif [ "$1" = "apc1_wifibtc0_smfc1" ]; then
        cmd=$cmd"CFG_APP_DATAPATH_SERVER=0 ESHELL_ECHOBACK=0 \
            CHIP_DMA_CFG_IDX=3 MM_PROJECT=$MM_PROJECT MM_PLATFORM=m55 MM_CORE=m55c1 MEM_CFG_OPT=OPT_HP_C0C1\
            NO_SLEEP=1 BT_LOG_POWEROFF=0 $DYN_LIB_CFG "

    elif [ "$1" = "ap_wifibtc0_smfc1" ]; then
        cmd=$cmd"DSP_HIFI4_TRC_TO_MCU=1 UTILS_ESHELL_BTRF_TEST=1 WIFI_ANA_YB_CFG=1 CHIP_DMA_CFG_IDX=3 \
            MM_PROJECT=$MM_PROJECT CODEC_ADC2_DSF=1 SMF_SINGLE_PIPELINE=1 MEM_CFG_OPT=OPT_HP_C0C1\
            WIFI_RF_SW_IO_SELECT=1 ESHELL_ECHOBACK=0 USE_NTS_HEAP=0 "

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

elif [ "$1" = "apc1" ]; then
    shift
    build apc1_wifibtc0_smfc1 $*

elif [ "$1" = "ap" ]; then
    shift
    build ap_wifibtc0_smfc1 $*

elif [ "$build_cmake" = "1" ]; then
    build bootloader $*
    build ota $*
    build apc1_wifibtc0_smfc1 $*
    build ap_wifibtc0_smfc1 $*

elif [ "$build_distclean" = "1" ]; then
    build bootloader distclean
    build ota distclean
    build apc1_wifibtc0_smfc1 distclean
    build ap_wifibtc0_smfc1 distclean

else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services/out -rf;rm rtos/nuttx/config*

    build bootloader $*
    build bootloader distclean
    build ota $*
    build ota distclean
    build apc1_wifibtc0_smfc1 $*
    build apc1_wifibtc0_smfc1 distclean
    build ap_wifibtc0_smfc1 $*
    build ap_wifibtc0_smfc1 distclean

fi

if [ "$build_cmake" = "1" ]; then
    mkdir -p $output
    find cmake_out/$build_chip/$PROJECT -path "*/out" -prune -o -name "nuttx_*.*" -type f -exec cp {} "$output/" \;
fi

echo "build $board_config done!!!"
