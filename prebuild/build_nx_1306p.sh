#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best1306p_ep
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
        cmd=$cmd"PMU_NTC_MONITOR=0"

    elif [ "$1" = "ota" ]; then
        cmd=$cmd"PSRAM_POLLING=1 PMU_USB_PIN_CHECK=0"

    elif [ "$1" = "tee" ]; then
        cmd=$cmd"NORFLASH_API_ENABLE=1"

    elif [ "$1" = "apns" ]; then
        cmd=$cmd"NORFLASH_API_ENABLE=1"

    elif [ "$1" = "ap" ]; then
        cmd=$cmd"CP_SUBSYS_TRC_TO_MCU=1 AUDIO_SWITCH_ON=1 AUDIO_OUTPUT_DC_CALIB=0 CHIP_DMA_CFG_IDX=1 \
            FAST_XRAM_SECTION_SIZE=0x15000 PSRAM_POLLING=1 \
            DEFAULT_BSS_IN_PSRAM=1 DEFAULT_DATA_IN_PSRAM=1 PMU_USB_PIN_CHECK=0 UTILS_ESHELL_BTRF_TEST=1 \
            BQBTEST_ENABLE=1 AUDIO_DRC=1 AUDIO_LIMITER=1 SW_IIR_EQ_PROCESS=1 UART1_IOMUX_INDEX=20  \
            PMU_CLK_USE_EXT_CRYSTAL=1 SLEEP_STATS_TRACE=1 DEBUG_SLEEP_USER=1 FLASH_DEEP_SLEEP=1 \
            POWER_MODE=DIG_DCDC FORCE_FLASH1_SLEEP=1 MCU_I2C_SLAVE=0 CP_INTR_RELAY=1 CONFIG_PATH=/data/bt_config.conf"

    fi

    shift
    cmd=$cmd" "$*
    echo "$cmd"
    $cmd
    if [ $? -ne 0 ]; then
        exit 1
    fi
}

function build_cp()
{
    echo "$FUNCNAME $board_config"
    cd framework/services/
    rm -rf out/
    cmd="make T=cp_subsys -j8 CHIP=best1306p NOSTD=0 NO_TIMER=0 DEBUG=1 CP_SUBSYS_TRC_TO_MCU=1 \
        SUBSYS_IMAGE_SEGMENT=1 CONFIG_HAVE_CXX=1 OPENAMP_ENABLE=1 RPTUN_MCUC0_2_MCUC1=1 \
        SUBSYS_CACHE_ENABLE=1 MM_PROJECT=nuttx_1306p MM_PLATFORM=m33 MM_CORE=m33_cp \
        CHIP_DMA_CFG_IDX=1 CHIP_HAS_PSRAM=1 PSRAM_ENABLE=1 PSRAM_SIZE=0x00800000 \
        PSRAM_REGION_OFFSET=0x00600000 PSRAM_REGION_SIZE=0x00200000  DEFAULT_BSS_IN_PSRAM=1 \
        DEFAULT_DATA_IN_PSRAM=1 DEFAULT_CODE_IN_PSRAM=1 OS_DYNAMIC_MEM_SIZE=0x10000 SMF_PLAYER_EN=1 \
        SMF_ENABLE=1 MULTIMEDIA_DISABLE=0 AUDIO_COMMON=1 SW_IIR_EQ_PROCESS=1 AUDIO_DRC=1 AUDIO_LIMITER=1 \
        AUDIO_EQ=1 SPEECH_LIB=1 SLEEP_STATS_TRACE=1 DEBUG_SLEEP_USER=1 CONFIG_BES_RPTUN_RPMSG_SYSFREQ=y CP_INTR_RELAY=1 USE_ECMIC=1"
    echo "$cmd"
    $cmd
    if [ $? -ne 0 ]; then
        exit 1
    fi
    cp out/cp_subsys/cp_subsys.bin ../services/prebuild/cp_subsys.bin
    cp out/cp_subsys/cp_subsys.elf ../services/prebuild/cp_subsys.elf
    cp out/cp_subsys/cp_subsys.map ../services/prebuild/cp_subsys.map
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

elif [ "$1" = "ap" ]; then
    shift
    build ap $*

elif [ "$1" = "tee" ]; then
    shift
    build tee $*

elif [ "$1" = "apns" ]; then
    shift
    build apns $*

elif [ "$1" = "cp" ]; then
    build_cp

elif [ "$build_cmake" = "1" ]; then
    build bootloader $*
    build ota $*
    build ap $*

    if [ "$sdk_build" = "0" ]; then
        build_cp
    fi

elif [ "$build_distclean" = "1" ]; then
    build bootloader distclean
    build ota distclean
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

    if [ "$sdk_build" = "0" ]; then
        build_cp
    fi
fi

if [ "$build_cmake" = "1" ]; then
    mkdir -p $output
    find cmake_out/$build_chip/$PROJECT -path "*/out" -prune -o -name "nuttx_*.*" -type f -exec cp {} "$output/" \;
fi

cp framework/services/prebuild/cp_subsys.bin $output/nuttx_cp.bin
cp framework/services/prebuild/cp_subsys.elf $output/nuttx_cp.elf
cp framework/services/prebuild/cp_subsys.map $output/nuttx_cp.map

echo "build $board_config done!!!"
