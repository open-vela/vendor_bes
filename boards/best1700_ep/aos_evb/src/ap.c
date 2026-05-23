/****************************************************************************
 * vendor/bes/boards/best1700_ep/src/ap.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <arch/board/board.h>
#include <assert.h>
#include <debug.h>
#include <errno.h>
#include <nuttx/arch.h>
#include <nuttx/board.h>
#include <nuttx/config.h>
#include <nuttx/fs/partition.h>
#include <nuttx/lcd/lcd.h>
#include <nuttx/lcd/st7735.h>
#include <nuttx/mmcsd.h>
#include <nuttx/sdio.h>

#ifdef CONFIG_BES1700_AP

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void emmc_partition_options(FAR char *part)
{
}

void emmc_init_before_partition(FAR struct sdio_dev_s *dev, FAR char *path)
{
}

void emmc_init_after_partition(FAR struct sdio_dev_s *dev, FAR char *path)
{
#ifdef CONFIG_BOARD_COREDUMP_BLKDEV
    char *devpath = CONFIG_BOARD_COREDUMP_DEVPATH; // for example: /dev/mmcsd0core
    char cmd[64]; // such as: mkgpt write /dev/mmcsd0 mmcsd0fs:3335M mmcsd0core:64M
    snprintf(cmd, sizeof(cmd), "mkgpt write %s %sfs:%dM %s:%dM", path, &path[5], 3335, &devpath[5], 64);

    system(cmd);
#endif
}

#endif /* CONFIG_BES1700_AP */
