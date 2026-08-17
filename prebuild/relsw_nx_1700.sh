#!/bin/bash

DATE=`date +%F | sed 's/-//g'`
commitid=`git rev-parse --short HEAD`

if [ "x$2" = "x" ]; then
	TARGET_NAME=bes-aos-nuttx
else
	TARGET_NAME=$2
fi

EXPORT_LIB="$EXPORT_LIB
`cat <<-EOF
EOF
`
"
EXPORT_FILE_DIR="$EXPORT_FILE_DIR
`cat <<-EOF
boards/best1700_ep/aos_evb
boards/best1700_ep/common
boards/best1700_ep/scripts

rtos
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

## clean all the generated files
./build.sh boards/best1700_ep/aos_evb/configs/ap -j8 CP_SUBSYS_TRC_TO_MCU=1 BTH_IF_COMM_RPC_EN=1 distclean

. `dirname $0`/relsw_base_nx_bsp WORKING

cd framework/services
./tools/build_1700_watch.sh -b m55c1 DEBUG=1 GEN_LIB=1
if [ $? -ne 0 ]; then
	exit 1
fi

./tools/build_1700_watch.sh -b m33c0 DEBUG=1 GEN_LIB=1
if [ $? -ne 0 ]; then
	exit 1
fi

cd -

sed -i s/GEN_LIB/FORCE_TO_USE_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk

cd framework/services
./tools/relsw_1700_watch_nuttx.sh WORKING bes-aos-ddk
cd ../../

sed -i s/FORCE_TO_USE_LIB/GEN_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk

mkdir -p $TARGET_NAME
mv ./framework/services/bes-aos-ddk* ./$TARGET_NAME/
mv ./$TARGET_NAME*tar.gz ./$TARGET_NAME/
cp prebuild/SDK_README.txt ./$TARGET_NAME/

echo "$TARGET_NAME releasd done!"
