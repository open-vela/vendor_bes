#!/bin/bash
set -x

DATE=`date +%F | sed 's/-//g'`
commitid=`git rev-parse --short HEAD`

if [ "x$2" = "x" ]; then
    TARGET_NAME=bes-aos-nuttx
else
    TARGET_NAME=$2
fi

RELEASE_1702=1

# repo forall -c "git clean -xfd -e .repo"

if [ $RELEASE_1702 == 1 ]; then
    CHIPID=1702
    # ./prebuild/build_nx_1702_rc07.sh
fi

if [ $1 == 'WORKING' ]; then
    sed -i s/GEN_LIB/FORCE_TO_USE_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk
    cd framework/services
    ./tools/relsw_nx_all.sh
    cd ../../
    sed -i s/FORCE_TO_USE_LIB/GEN_LIB/g framework/services/config/nx_bestbsp_base/nuttx_cfg.mk

    mkdir -p $TARGET_NAME
    mv ./framework/services/bes-nuttx-rc07-bsp.tar.gz ./$TARGET_NAME/
    cp prebuild/SDK_README.txt ./$TARGET_NAME/

    echo "$TARGET_NAME releasd done!"
fi
