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

./build.sh boards/best2003_ep/aos_evb_ax4d/configs/bootloader -j && \
./build.sh boards/best2003_ep/aos_evb_ax4d/configs/ota -j && \
./build.sh boards/best2003_ep/aos_evb_ax4d/configs/audio -j && \
./build.sh boards/best2003_ep/aos_evb_ax4d/configs/ap -j && \
./build.sh boards/best2003_ep/aos_evb_ax4f/configs/ap -j && \
./build.sh boards/best2003_ep/aos_evb_ax4f/configs/audio -j
if [ $? -ne 0 ]; then
	exit 1
fi

sed -i s/GEN_LIB/FORCE_TO_USE_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk

cd framework/services
./tools/relsw_nx_2003.sh WORKING bes-aos-ddk
cd ../../

sed -i s/FORCE_TO_USE_LIB/GEN_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk

mkdir -p $TARGET_NAME
mv ./framework/services/bes-aos-ddk* ./$TARGET_NAME/
mv ./$TARGET_NAME*tar.gz ./$TARGET_NAME/
cp prebuild/SDK_README.txt ./$TARGET_NAME/

echo "$TARGET_NAME releasd done!"
