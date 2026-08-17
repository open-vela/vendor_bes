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

./build.sh boards/best1600_ep/aos_evb/configs/ap -j \
&& ./build.sh boards/best1600_ep/aos_evb/configs/cp -j \
&& ./build.sh boards/best1600_ep/aos_evb/configs/sensor/ -j NO_SUBSYS_RAM=1
if [ $? -ne 0 ]; then
	exit 1
fi

sed -i s/GEN_LIB/SDK/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk

cd framework/services
./tools/relsw_nx_1600.sh WORKING bes-aos-ddk
cd ../../

sed -i s/SDK/GEN_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk

mkdir -p $TARGET_NAME
mv ./framework/services/bes-aos-ddk* ./$TARGET_NAME/
mv ./$TARGET_NAME*tar.gz ./$TARGET_NAME/
cp prebuild/SDK_README.txt ./$TARGET_NAME/

echo "$TARGET_NAME releasd done!"