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
boards/best1600_ep/aos_evb
boards/best1600_ep/common
boards/best1600_ep/scripts

boards/best1306_ep/aos_evb
boards/best1306_ep/common
boards/best1306_ep/scripts

boards/best1501p_ep/tws_evb
boards/best1501p_ep/common
boards/best1501p_ep/scripts

boards/best1502x_ep/evb
boards/best1502x_ep/tws_evb
boards/best1502x_ep/common
boards/best1502x_ep/scripts

boards/best2001_ep/evb
boards/best2001_ep/common
boards/best2001_ep/scripts

boards/best2003_ep/aos_evb
boards/best2003_ep/aos_evb_ax4d
boards/best2003_ep/aos_evb_ax4d_gc9503
boards/best2003_ep/common
boards/best2003_ep/scripts

rtos/external
EOF
`
"

#rtos/external/Submake.mk
#rtos/external/ffmpeg
#rtos/external/zblue
#rtos/external/zlib
#rtos/external/libpng
#rtos/external/iperf2
#rtos/external/curl
#rtos/external/libssh
#rtos/external/libtar
#rtos/external/libjpeg-turbo
#rtos/external/bsdiff
#rtos/external/lc3
#rtos/external/unqlite
#rtos/external/protobuf-c

EXCLUDE_FILE_DIR="$EXCLUDE_FILE_DIR
`cat <<-EOF

EOF
`
"
. `dirname $0`/relsw_base_nx_bsp

./build.sh boards/best1600_ep/aos_evb/configs/ap -j \
&& ./build.sh boards/best1600_ep/aos_evb/configs/cp -j \
&& ./build.sh boards/best1600_ep/aos_evb/configs/sensor/ -j
if [ $? -ne 0 ]; then
	exit 1
fi

./build.sh boards/best1306_ep/aos_evb/configs/ap -j \
&& ./build.sh boards/best1306_ep/aos_evb/configs/ap_smp -j
if [ $? -ne 0 ]; then
	exit 1
fi

./build.sh boards/best1501p_ep/tws_evb/configs/ap -j \
&& ./build.sh boards/best1501p_ep/tws_evb/configs/sensor -j
if [ $? -ne 0 ]; then
	exit 1
fi

./build.sh boards/best1502x_ep/evb/configs/ap -j \
&& ./build.sh boards/best1502x_ep/evb/configs/sensor -j \
&& ./build.sh boards/best1502x_ep/evb/configs/ap_smp -j \
&& ./build.sh boards/best1502x_ep/evb/configs/ap_only -j
if [ $? -ne 0 ]; then
	exit 1
fi

./build.sh boards/best2003_ep/aos_evb_ax4f/configs/ap -j
if [ $? -ne 0 ]; then
	exit 1
fi

sed -i s/GEN_LIB/FORCE_TO_USE_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk

cd framework/services
./tools/relsw_nx_all.sh WORKING bes-aos-ddk
cd ../../

sed -i s/FORCE_TO_USE_LIB/GEN_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk

mkdir -p $TARGET_NAME
mv ./framework/services/bes-aos-ddk* ./$TARGET_NAME/
mv ./$TARGET_NAME*tar.gz ./$TARGET_NAME/
cp prebuild/SDK_README.txt ./$TARGET_NAME/

echo "$TARGET_NAME releasd done!"
