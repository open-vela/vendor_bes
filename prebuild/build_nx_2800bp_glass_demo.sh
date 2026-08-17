#!/bin/bash

DIR=$(cd $(dirname $0); pwd)
build_chip=best1700_ep
PROJECT=glass_demo
board_config=boards/$build_chip/$PROJECT/configs
output=rtos/nuttx
build_cmake=0
MM_PROJECT=nuttx_1700_glass_demo
build_distclean=0
sdk_build=1
build_all=0

BUILD_BTH_LIB=${BUILD_BTH_LIB:-0}
build_exec=1

bes_sdk_build=$(repo list framework/services 2>/dev/null)
if [[ $bes_sdk_build = *"bes-aos/bsp-src"* ]]; then
    sdk_build=0
fi

WEBSVR_CFG="NET_MUSIC_SUPPORT=1 NET_MUSIC_BASE_SUPPORT=1 NET_MUSIC_SINK_SUPPORT=0 NET_MUSIC_CJSON_SUPPORT=0 \
            NET_WEBSVR_SUPPORT=1 WEBSVR_VERSION=v2 WEBSVR_FILE_SYS_SUPPORT=1"
DYN_LIB_CFG="UTILS_BES_DLL_ENABLE=1 SMF_DLL_ENABLE=1 "

if [ "$sdk_build" = "0" ]; then
    DYN_LIB_CFG=$DYN_LIB_CFG"DYN_LIB_LOADER_ENABLE=1"
fi

# global params check
for arg in $*
do
    if [ $arg = "cmake" ];then
        build_cmake=1
        shift
    fi
    if [ $arg = "distclean" ];then
        build_distclean=1
    fi
done

# Set output path for cmake mode
if [ "$build_cmake" = "1" ]; then
    output=cmake_out/$build_chip/$PROJECT/out
    mkdir -p $output
fi

function build()
{
    if [ $# -eq 0 ]; then
        echo "need param!"
        exit 1
    fi

    # Save first input param
    module_name=$1

    cmd="./build.sh $board_config/$1 "
    if [ "$build_cmake" = "1" ]; then
        cmd=$cmd"--cmake "
    fi
    cmd=$cmd" -j8 "

    # echo "DEBUG: BUILD_BTH_LIB = $BUILD_BTH_LIB"
    if [ "$1" = "bootloader" ]; then
        cmd=$cmd"WIFI_CALI_ENABLE=0 PMU_CLK_USE_EXT_CRYSTAL=0 "

    elif [ "$1" = "ota" ]; then
        cmd=$cmd"PMU_CLK_USE_EXT_CRYSTAL=0 "

    elif [ "$1" = "bth" ]; then
        common_cmd="$DYN_LIB_CFG FAST_TIMER_COMPENSATE=1 PMU_CLK_USE_EXT_CRYSTAL=1 NO_SLEEP=1 BT_LOG_POWEROFF=0 MM_PROJECT=$MM_PROJECT NN_KWS=1 HAL_CMU_FREQ_MAX=HAL_CMU_FREQ_104M "
        cmd="$cmd $common_cmd"

        if [ "$BUILD_BTH_LIB" -eq 1 ]; then
            extra_cmd=" MULTIMEDIA_DISABLE=0 AUDIO_COMMON=1 SPEECH_LIB=1 MM_SPEECH_ENABLED=1"
            cmd="$cmd $extra_cmd"
        fi

    # elif [ "$1" = "bthcp" ]; then
    #     cmd=$cmd"MM_PROJECT=$MM_PROJECT "

    elif [ "$1" = "apc1" ]; then
        cmd=$cmd"CHIP_DMA_CFG_IDX=3 NO_SLEEP=0 BT_LOG_POWEROFF=0 UTILS_ESHELL_BTRF_TEST=1 WIFI_5G_RF_USE_EXTLNA=1 MM_PROJECT=$MM_PROJECT SCO_FORCE_CVSD=1 CVSD_BYPASS=1 SCO_OVER_INTERSYS=1 SCO_INTERSYS_ID=3 AUDIO_SCO_BTPCM_CHANNEL=0 "

    elif [ "$1" = "ap" ]; then
        cmd=$cmd"DSP_HIFI4_TRC_TO_MCU=1 ONLY_BT_DRIVE_INIT=1 CHIP_DMA_CFG_IDX=3 UTILS_ESHELL_BTRF_TEST=1 BTHC0_USE_ADC2=1 CODEC_CLK_SEL_BTH=1 \
        CODEC_ADC2_DSF=1 CODEC_ADC3_DSF=1 FAST_TIMER_COMPENSATE=1 PMU_CLK_USE_EXT_CRYSTAL=1 MM_PROJECT=$MM_PROJECT $WEBSVR_CFG BT_PAN_SUPPORT=1 SCO_OVER_INTERSYS=1 SCO_INTERSYS_ID=3 AUDIO_SCO_BTPCM_CHANNEL=0 "
    fi

    shift
    cmd=$cmd" "$*

    # check input parameters whether it includes menuconfig or distclean
    for param in "$@"; do
        if [ "$param" = "menuconfig" ] || [ "$param" = "distclean" ]; then
            build_exec=0
            break
        fi
    done

    if [ $build_exec -ne 1 ]; then
        $cmd
        echo "cmd:" $cmd
        return 0
    fi

    # Create log directory if not exists
    log_dir="build_logs"
    mkdir -p $log_dir

    # Generate log file name with timestamp and module name
    date_str=$(date +%Y%m%d_%H%M%S)
    log_file="$log_dir/build_${module_name}_${date_str}.log"

    # Log the build command
    echo "=== Build Command ===" | tee $log_file
    echo "$cmd" | tee -a $log_file
    echo "===================" | tee -a $log_file
    echo "" | tee -a $log_file

    # Execute command and redirect output to log file
    $cmd 2>&1 | tee -a $log_file

    # Check build result
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
        echo "" | tee -a $log_file
        echo "=== Build Failed ===" | tee -a $log_file
        echo "Log file: $log_file" | tee -a $log_file
        exit 1
    else
        echo "" | tee -a $log_file
        echo "=== Build Success ===" | tee -a $log_file
        echo "Log file: $log_file" | tee -a $log_file
    fi
}

function build_hifi()
{
    echo "$FUNCNAME $board_config"
    cd framework/services_hifi4/
    # rm -rf out/
    cmd="make -j8 T=best1700_watch USE_MEM_CFG=1 OSTICK_USE_FAST_TIMER=1 DEBUG=1 DEBUG_RPCHAN=0 \
        DSP_LOGIC_SROM_BASE_OFFSET=0xC00000 OPENAMP_ENABLE=1 USE_BES_RPCHAN=1 RPTUN_M55C0_2_DSPC0=1 \
        MM_ENABLED=1 MM_AUDIO_ENABLED=1 ALLOW_WARNING=1 DMA_APPLIED_ON_HIFI=1 CHIP_DMA_CFG_IDX=3 \
        DEBUG_PORT=2 TRACE_BUF_SIZE=0 DSP_HIFI4_TRC_TO_MCU=1 DSP_USE_SYS_PERIPH=0 TRACE_CPU_IMM_OUTPUT=0 \
        SMF=1 MM_PROJECT=$MM_PROJECT MM_PLATFORM=hifi4 MM_CORE=hifi4 BTWATCH=1 NO_SLEEP=1 \
        HIFI4_PSRAM_BASE=0x1BC00000 HIFI4_PSRAM_SIZE=0x400000 HIFI_DSP_LIB=1 PSRAM_ENABLE=1 \
        MEM_CFG_OPT=OPT_NUTTX RPTUN_M55C1_2_DSPC0=1 $DYN_LIB_CFG "
    echo "$cmd"
    $cmd
    if [ $? -ne 0 ]; then
        exit 1
    fi
    # for release hifi image
    cp out/best1700_watch/best1700_watch.bin                ../services/prebuild/nuttx_audio_$PROJECT.bin
    cp out/best1700_watch/best1700_watch.elf                ../services/prebuild/nuttx_audio_$PROJECT.elf
    cp out/best1700_watch/best1700_watch.map                ../services/prebuild/nuttx_audio_$PROJECT.map
    cp multimedia/smf/projects/$MM_PROJECT/json/smf.json    ../services/prebuild/smf_$PROJECT.json
    # for debug usage
    DIR_TOP=../..
    cp out/best1700_watch/best1700_watch.bin                ${DIR_TOP}/$output/nuttx_hifi.bin
    cp out/best1700_watch/best1700_watch.elf                ${DIR_TOP}/$output/nuttx_hifi.elf
    cp out/best1700_watch/best1700_watch.map                ${DIR_TOP}/$output/nuttx_hifi.map
    cp multimedia/smf/projects/$MM_PROJECT/json/smf.json    ${DIR_TOP}/$output/smf.json
    # copy *.dll files
    find "out/best1700_watch" -type f -name "*.dll" -exec cp {} "${DIR_TOP}/$output/" \;
    cd ${DIR_TOP}
}


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

elif [ "$1" = "bth" ]; then
    shift
    build bth $*

# elif [ "$1" = "bthcp" ]; then
#    shift
#     build bthcp $*

elif [ "$1" = "hifi" ]; then
    build_hifi

elif [ "$build_cmake" = "1" ]; then
    build bootloader $*
    build ota $*
    build bth $*
    # build bthcp $*
    build apc1 $*
    build ap $*

    if [ "$sdk_build" = "0" ]; then
        build_hifi
    fi

elif [ "$build_distclean" = "1" ]; then
    build bootloader distclean
    build ota distclean
    build bth distclean
    # build bthcp distclean
    build apc1 distclean
    build ap distclean

else
    build_all=1
    rm rtos/nuttx/.config;rm rtos/nuttx/Make.defs;rm framework/services/out -rf;rm rtos/nuttx/.config*

    build bootloader $*
    build bootloader distclean
    build ota $*
    build ota distclean
    build bth $*
    build bth distclean
    # build bthcp $*
    # build bthcp distclean
    build apc1 $*
    build apc1 distclean
    build ap $*
    build ap distclean

    if [ "$sdk_build" = "0" ]; then
        build_hifi
    fi
fi

if [ $build_exec = 1 ]; then
    if [ "$build_cmake" = "1" ]; then
        find cmake_out/$build_chip/$PROJECT -path "*/out" -prune -o -name "nuttx_*.*" -type f -exec cp {} "$output/" \;
        # copy *.dll files
        find "cmake_out/$build_chip/$PROJECT" -type f -name "*.dll" -exec cp {} "$output/" \; || { echo "WARNING: copy dll files failure!"; }
    else
        # copy *.dll files
        find "framework/services/out" -type f -name "*.dll" -exec cp {} "$output/" \; || { echo "WARNING: copy dll files failure!"; }
        find "framework/services_hifi4/out" -type f -name "*.dll" -exec cp {} "$output/" \; || { echo "WARNING: copy dll files failure!"; }
    fi
fi

echo "build $board_config done!!!"
