#!/bin/bash
set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "$0")"; pwd)
cd "$SCRIPT_DIR"

# Disable ccache so build_info.o is always freshly compiled.
export CCACHE_DISABLE=1

LEGACY_BUILD_DIR="cmake_out/aos_evb_ap"
RELEASE_STYLE_ROOT="cmake_out/best1700_ep/aos_evb"
RELEASE_STYLE_AP_DIR="$RELEASE_STYLE_ROOT/ap"
RELEASE_STYLE_OUT_DIR="$RELEASE_STYLE_ROOT/out"
BOARD_CONFIG="vendor/bes/boards/best1700_ep/aos_evb/configs/ap"
DEFCONFIG_FILE="$BOARD_CONFIG/defconfig"
INIT_SCRIPT_FILE="vendor/bes/boards/best1700_ep/aos_evb/src/etc/init.d/rc.sysinit.ap"
CONFIG_STAMP_FILE="$LEGACY_BUILD_DIR/.ap_build_inputs.sha256"

current_build_inputs_hash=$(
    sha256sum "$DEFCONFIG_FILE" "$INIT_SCRIPT_FILE" | sha256sum | awk '{print $1}'
)
previous_build_inputs_hash=""

if [ -f "$CONFIG_STAMP_FILE" ]; then
    previous_build_inputs_hash=$(cat "$CONFIG_STAMP_FILE")
fi

if [ "$current_build_inputs_hash" != "$previous_build_inputs_hash" ]; then
    echo "AP build inputs changed, forcing clean reconfigure"
    for build_dir in "$LEGACY_BUILD_DIR" "$RELEASE_STYLE_AP_DIR" "$RELEASE_STYLE_OUT_DIR"; do
        if [ -d "$build_dir" ]; then
            echo "Removing build dir: $build_dir"
            rm -rf "$build_dir"
        fi
    done
fi

WEBSVR_CFG=(
    NET_MUSIC_SUPPORT=1
    NET_MUSIC_BASE_SUPPORT=1
    NET_MUSIC_SINK_SUPPORT=0
    NET_MUSIC_CJSON_SUPPORT=0
    NET_WEBSVR_SUPPORT=1
    WEBSVR_VERSION=v2
    WEBSVR_FILE_SYS_SUPPORT=1
)

AP_FLAGS=(
    DSP_HIFI4_TRC_TO_MCU=1
    CHIP_DMA_CFG_IDX=3
    UTILS_ESHELL_BTRF_TEST=1
    ONLY_BT_DRIVE_INIT=1
)
AP_FLAGS+=("${WEBSVR_CFG[@]}")

./build.sh "$BOARD_CONFIG" --cmake -j8 "${AP_FLAGS[@]}" "$@"

mkdir -p "$LEGACY_BUILD_DIR"
printf '%s\n' "$current_build_inputs_hash" > "$CONFIG_STAMP_FILE"

mkdir -p "$RELEASE_STYLE_AP_DIR" "$RELEASE_STYLE_OUT_DIR"
for artifact in \
    nuttx.bin \
    nuttx.map \
    System.map \
    nuttx_ap.bin \
    nuttx_ap.map \
    nuttx_ap.elf

do
    if [ -f "$LEGACY_BUILD_DIR/$artifact" ]; then
        cp "$LEGACY_BUILD_DIR/$artifact" "$RELEASE_STYLE_AP_DIR/"
        cp "$LEGACY_BUILD_DIR/$artifact" "$RELEASE_STYLE_OUT_DIR/"
    fi
done

hifi_prefix="vendor/bes/framework/services/prebuild/nuttx_audio_best1700_ep_aos_evb"
if [ -f "$hifi_prefix.bin" ]; then
    cp "$hifi_prefix.bin" "$RELEASE_STYLE_OUT_DIR/nuttx_hifi.bin"
fi
if [ -f "$hifi_prefix.elf" ]; then
    cp "$hifi_prefix.elf" "$RELEASE_STYLE_OUT_DIR/nuttx_hifi.elf"
fi
if [ -f "$hifi_prefix.map" ]; then
    cp "$hifi_prefix.map" "$RELEASE_STYLE_OUT_DIR/nuttx_hifi.map"
fi
