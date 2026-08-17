#!/bin/bash
set -x

DATE=`date +%F | sed 's/-//g'`
commitid=`git rev-parse --short HEAD`

if [ "x$2" = "x" ]; then
    TARGET_NAME=bes-aos-nuttx
else
    TARGET_NAME=$2
fi

RELEASE_1306P=0
RELEASE_1502P=0
RELEASE_1502X=0
RELEASE_3601=0
RELEASE_2800BP=0
RELEASE_1605=0
RELEASE_1607=0
RELEASE_2800HP=0
RELEASE_2003=0
RELEASE_1702=0
RELEASE_1702YP=0
RELEASE_1702ZP=0
RELEASE_3601P=1


# repo forall -c "git clean -xfd -e .repo"

if [ $RELEASE_1306P == 1 ]; then
    ./prebuild/build_nx_1306p.sh cmake
fi

if [ $RELEASE_1502P == 1 ]; then
    ./prebuild/build_nx_1502p.sh cmake
fi

if [ $RELEASE_1502X == 1 ]; then
    ./prebuild/build_nx_1502x.sh
fi

if [ $RELEASE_1605 == 1 ]; then
    ./prebuild/build_nx_1605.sh cmake
fi

if [ $RELEASE_1607 == 1 ]; then
    ./prebuild/build_nx_1607.sh cmake
fi

if [ $RELEASE_3601 == 1 ]; then
    ./prebuild/build_nx_3601.sh
fi

if [ $RELEASE_2800BP == 1 ]; then
    ./prebuild/build_nx_2800bp.sh cmake
    ./prebuild/build_nx_2800bp_glass_demo.sh cmake
fi

if [ $RELEASE_2800HP == 1 ]; then
    ./prebuild/build_nx_2800hp.sh cmake
    ./prebuild/build_nx_2800hp_wifibtc0.sh cmake
    ./prebuild/build_nx_2800hp_wifibtc0_smfc1.sh cmake
    ./prebuild/build_nx_2800hp_with_bth.sh cmake
fi

if [ $RELEASE_2003 == 1 ]; then
    ./prebuild/build_nx_2003ax4d.sh cmake
    ./prebuild/build_nx_2003ax4f.sh cmake
    ./prebuild/build_nx_2003gx6d_m33_ui.sh cmake
    ./prebuild/build_nx_2003gx6d.sh cmake
fi

if [ $RELEASE_1702 == 1 ]; then
    ./prebuild/build_nx_1702.sh cmake
fi

if [ $RELEASE_1702YP == 1 ]; then
    ./prebuild/build_nx_1702_yp.sh cmake
fi

if [ $RELEASE_1702ZP == 1 ]; then
    ./prebuild/build_nx_1702_zp.sh cmake
fi

if [ $RELEASE_3601P == 1 ]; then
    ./prebuild/build_nx_3601p.sh cmake
fi

if [ $1 == 'WORKING' ]; then
    sed -i s/GEN_LIB/FORCE_TO_USE_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk
    cd framework/services
    ./tools/relsw_nx_all.sh bes-aos-ddk_`date +"%Y-%m-%d_%H-%M-%S"` $1
    cd ../../
    sed -i s/FORCE_TO_USE_LIB/GEN_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk

    mkdir -p $TARGET_NAME
    mv ./framework/services/bes-aos-ddk* ./$TARGET_NAME/
    cp prebuild/SDK_README.txt ./$TARGET_NAME/

    cd framework/services_hifi4
    ./tools/relsw_hifi4
    cd ../../
    mv ./framework/services_hifi4/hifi4_sdk* ./$TARGET_NAME/

    echo "$TARGET_NAME releasd done!"
fi
