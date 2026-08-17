#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best3601p_ep
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
        cmd=$cmd"TRACE_BUF_SIZE=32768 CORE_SLEEP_POWER_DOWN=1 BT_DRV_RF_INIT=1 BT_DRV_HCI_INIT=0 BT_DRV_RF_REINIT=0 -j8"

    elif [ "$1" = "apc1" ]; then
        cmd=$cmd"SMF=1 MVCS_DUMP=1 CORE_SLEEP_POWER_DOWN=1 TRACE_BUF_SIZE=32768 -j8"

    elif [ "$1" = "sensor" ]; then
        cmd=$cmd"CORE_SLEEP_POWER_DOWN=1 BT_DRV_RF_INIT=0 BT_DRV_HCI_INIT=1 BT_DRV_RF_REINIT=1 -j8"

    fi

    shift
    cmd=$cmd" "$*
    echo "$cmd"
    $cmd
    if [ $? -ne 0 ]; then
        exit 1
    fi
}

function build_zsp()
{
    echo "$FUNCNAME $board_config"
    cd framework/services_zsp/
    rm -rf out/
    cmd="make -j32 T=best3601p_dsp CHIP=best3601p ALLOW_WARNING=1 DEBUG=1 ZSP_TRC_TO_MCU=1 \
        OPENAMP_ENABLE=1 RPTUN_M55C0_2_ZSPC0=1 RPTUN_M55C1_2_ZSPC0=1 SMF=1 MM_PLATFORM=zsp \
        MM_CORE=zsp MM_PROJECT=nuttx_3601p NO_RETARGET_GCC=1 OS_HAVE_POSIX=1 NO_SLEEP=0 \
        PSRAM_SIZE=0x4000000 PSRAM_REGION_OFFSET=0x3000000 PSRAM_REGION_SIZE=0x300000 \
        OS_HEAP_IN_PSRAM=1 configTOTAL_HEAP_SIZE=200*1024 CORE_SLEEP_POWER_DOWN=1 \
        DYN_LIB_LOADER_ENABLE=1 UTILS_BES_DLL_ENABLE=1 SMF_DLL_ENABLE=1"
    $cmd
    if [ $? -ne 0 ]; then
        exit 1
    fi
    cp out/best3601p_dsp/best3601p_dsp.bin ../services/prebuild/nuttx_audio_$PROJECT.bin
    cp out/best3601p_dsp/best3601p_dsp.elf ../services/prebuild/nuttx_audio_$PROJECT.elf
    cp out/best3601p_dsp/best3601p_dsp.map ../services/prebuild/nuttx_audio_$PROJECT.map
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

if [ "$1" = "ap" ]; then
    shift
    build ap $*

elif [ "$1" = "apc1" ]; then
    shift
    build apc1 $*

elif [ "$1" = "sensor" ]; then
    shift
    build sensor $*

elif [ "$1" = "zsp" ]; then
    build_zsp

elif [ "$build_cmake" = "1" ]; then
    build ap $*

    if [ "$sdk_build" = "0" ]; then
        build apc1 $*
        build sensor $*
        build_zsp
    fi

elif [ "$build_distclean" = "1" ]; then
    build ap distclean
    if [ "$sdk_build" = "0" ]; then
        build apc1 distclean
        build sensor distclean
    fi
else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services_zsp/out -rf;rm rtos/nuttx/config*

    build ap $*
    build ap distclean

    if [ "$sdk_build" = "0" ]; then
        build apc1 $*
        build apc1 distclean
        build sensor $*
        build sensor distclean
        build_zsp
    fi

fi

if [ "$build_cmake" = "1" ]; then
    mkdir -p $output
    find cmake_out/$build_chip/$PROJECT -path "*/out" -prune -o -name "nuttx_*.*" -type f -exec cp {} "$output/" \;
fi

cp framework/services/prebuild/nuttx_audio_$PROJECT.bin $output/nuttx_zsp.bin
cp framework/services/prebuild/nuttx_audio_$PROJECT.elf $output/nuttx_zsp.elf
cp framework/services/prebuild/nuttx_audio_$PROJECT.map $output/nuttx_zsp.map

echo "build $board_config done!!!"
