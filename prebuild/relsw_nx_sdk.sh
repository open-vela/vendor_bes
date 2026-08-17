#!/bin/bash
set -x

DATE=`date +%F | sed 's/-//g'`
commitid=`git rev-parse --short HEAD`

if [ "x$2" = "x" ]; then
    TARGET_NAME=bes-aos-nuttx
else
    TARGET_NAME=$2
fi

repo forall -c "git clean -xfd -e .repo"

EXPORT_LIB="$EXPORT_LIB
`cat <<-EOF
EOF
`
"

EXPORT_FILE_DIR="$EXPORT_FILE_DIR
`cat <<-EOF
boards/best1306p_ep/aos_evb
boards/best1306p_ep/common
boards/best1306p_ep/scripts

boards/best1502x_ep/evb
boards/best1502x_ep/evb_8x5
boards/best1502x_ep/common
boards/best1502x_ep/scripts

boards/best2003_ep/aos_evb
boards/best2003_ep/aos_evb_ax4d
boards/best2003_ep/aos_evb_ax4d_m33_ui
boards/best2003_ep/aos_evb_gx6d_m33_ui
boards/best2003_ep/common
boards/best2003_ep/scripts

rtos/external

EOF
`
"

EXCLUDE_FILE_DIR="$EXCLUDE_FILE_DIR
`cat <<-EOF
EOF
`
"

. `dirname $0`/relsw_base_nx_bsp

./build.sh boards/best1306p_ep/aos_evb/configs/ap -j
if [ $? -ne 0 ]; then
    exit 1
fi
cp -r framework/services/lib/bes framework/services/lib/bes_1306p_aos_evb

./build.sh boards/best1502x_ep/evb_8x5/configs/bootloader -j && \
./build.sh boards/best1502x_ep/evb_8x5/configs/ota -j && \
./build.sh boards/best1502x_ep/evb_8x5/configs/sensor -j && \
./build.sh boards/best1502x_ep/evb_8x5/configs/ap SENS_FLASH_BOOT=0 -j
if [ $? -ne 0 ]; then
    exit 1
fi
cp -r framework/services/lib/bes framework/services/lib/bes_1502x_evb_8x5

./build.sh boards/best2003_ep/aos_evb_ax4f/configs/bootloader -j && \
./build.sh boards/best2003_ep/aos_evb_ax4f/configs/ota -j && \
./build.sh boards/best2003_ep/aos_evb_ax4f/configs/audio A7_GPIO_IRQ_MAP=0x800000 A7_PROJECT=dummy -j && \
./build.sh boards/best2003_ep/aos_evb_ax4f/configs/ap A7_GPIO_IRQ_MAP=0x800000 A7_PROJECT=dummy -j USB_HOST=1 USB_DISK_TEST=1
if [ $? -ne 0 ]; then
    exit 1
fi
cp -r framework/services/lib/bes framework/services/lib/bes_2003_aos_evb

./build.sh boards/best2003_ep/aos_evb_ax4d/configs/bootloader -j && \
./build.sh boards/best2003_ep/aos_evb_ax4d/configs/ota -j && \
./build.sh boards/best2003_ep/aos_evb_ax4d/configs/audio A7_GPIO_IRQ_MAP=0x800000 A7_PROJECT=dummy -j && \
./build.sh boards/best2003_ep/aos_evb_ax4d/configs/ap A7_GPIO_IRQ_MAP=0x800000 A7_PROJECT=dummy -j USB_HOST=1 USB_DISK_TEST=1
if [ $? -ne 0 ]; then
    exit 1
fi
cp -r framework/services/lib/bes framework/services/lib/bes_2003_aos_evb_ax4d

./build.sh boards/best2003_ep/aos_evb_gx6d_m33_ui/configs/bootloader -j && \
./build.sh boards/best2003_ep/aos_evb_gx6d_m33_ui/configs/ota -j && \
./build.sh boards/best2003_ep/aos_evb_gx6d_m33_ui/configs/audio A7_PROJECT=aispeech -j && \
./build.sh boards/best2003_ep/aos_evb_gx6d_m33_ui/configs/ap A7_PROJECT=aispeech -j UTILS_ESHELL_EN=1 IBRT=1 USB_HOST=1 USB_DISK_TEST=1
if [ $? -ne 0 ]; then
    exit 1
fi
cp -r framework/services/lib/bes framework/services/lib/bes_2003_aos_evb_gx6d_m33_ui

./build.sh boards/best2003_ep/aos_evb_ax4d_m33_ui/configs/bootloader -j && \
./build.sh boards/best2003_ep/aos_evb_ax4d_m33_ui/configs/ota -j && \
./build.sh boards/best2003_ep/aos_evb_ax4d_m33_ui/configs/audio A7_PROJECT=aispeech -j && \
./build.sh boards/best2003_ep/aos_evb_ax4d_m33_ui/configs/ap A7_PROJECT=aispeech -j WIFI_BT_COEX_FDD=1
mkdir framework/services/lib/bes/libwifistack_FDD
cp framework/services/lib/bes/libnet.a framework/services/lib/bes/libwifistack_FDD
cp framework/services/lib/bes/libwifistack.a framework/services/lib/bes/libwifistack_FDD
./build.sh boards/best2003_ep/aos_evb_ax4d_m33_ui/configs/ap A7_PROJECT=aispeech -j WIFI_BT_COEX_FDD=1 WIFI_BT_COEX_HYBRID=1
mkdir framework/services/lib/bes/libwifistack_FDD_HYBRID
cp framework/services/lib/bes/libnet.a framework/services/lib/bes/libwifistack_FDD_HYBRID
cp framework/services/lib/bes/libwifistack.a framework/services/lib/bes/libwifistack_FDD_HYBRID
./build.sh boards/best2003_ep/aos_evb_ax4d_m33_ui/configs/ap A7_PROJECT=aispeech -j USB_HOST=1 USB_DISK_TEST=1
mkdir framework/services/lib/bes/libwifistack_TDD
cp framework/services/lib/bes/libnet.a framework/services/lib/bes/libwifistack_TDD
cp framework/services/lib/bes/libwifistack.a framework/services/lib/bes/libwifistack_TDD
if [ $? -ne 0 ]; then
    exit 1
fi
cp -r framework/services/lib/bes framework/services/lib/bes_2003_aos_evb_ax4d_m33_ui

sed -i s/GEN_LIB/FORCE_TO_USE_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk
cd framework/services
./tools/relsw_nx_sdk.sh WORKING bes-aos-ddk
cd ../../
sed -i s/FORCE_TO_USE_LIB/GEN_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk

mkdir -p $TARGET_NAME
mv ./framework/services/bes-aos-ddk* ./$TARGET_NAME/
mv ./$TARGET_NAME*tar.gz ./$TARGET_NAME/
cp prebuild/SDK_README.txt ./$TARGET_NAME/

echo "$TARGET_NAME releasd done!"
