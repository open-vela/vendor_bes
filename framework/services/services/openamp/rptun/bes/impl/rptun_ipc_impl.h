/***************************************************************************
 *
 * Copyright 2015-2026 BES.
 * All rights reserved. All unpublished rights reserved.
 *
 * No part of this work may be used or reproduced in any form or by any
 * means, or stored in a database or retrieval system, without prior written
 * permission of BES.
 *
 * Use of this work is governed by a license granted by BES.
 * This work contains confidential and proprietary information of
 * BES. which is protected by copyright, trade secret,
 * trademark and other intellectual property rights.
 *
 ****************************************************************************/

#ifndef __RPTUN_IMPL_H__
#define __RPTUN_IMPL_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(__NuttX__)
#  include <nuttx/config.h>
#endif

#if defined(RPTUN_IPC_BT_HOST)
#  include "bt_host.h"
#elif defined(RPTUN_IPC_CP_SUBSYS)
#  include "cp_subsys.h"
#elif defined(RPTUN_IPC_CP_SUBSYS1)
#  include "cp_subsys1.h"
#elif defined(RPTUN_IPC_CP_SUBSYS2)
#  include "cp_subsys2.h"
#elif defined(RPTUN_IPC_DSP_HIFI4)
#  include "dsp_hifi4_ipc.h"
#  include "dsp_loader.h"
#elif defined(RPTUN_IPC_DSP_M55)
#  include "dsp_m55.h"
#elif defined(RPTUN_IPC_DSP_M55C1)
#  include "dsp_m55c1.h"
#elif defined(RPTUN_IPC_SENSOR_HUB)
#  include "sensor_hub.h"
#elif defined(RPTUN_IPC_ZSP_LOADER)
#  include "zsp_loader.h"
#elif defined(RPTUN_IPC_FW_LINUX)
#  include "fw_linux_loader.h"
#  define RPTUN_IPC_COMMON
#elif defined(RPTUN_IPC_CA_SUBSYS)
#  include "fw_linux_loader.h"
#  define RPTUN_IPC_COMMON
#elif !defined(RPTUN_IPC_COMMON)
#  error "unknow physical layer interface"
#endif

#include "hal_cmu.h"
#include "hal_rmt_ipc.h"
#include "hal_timer.h"
#include "plat_types.h"

#include "open-amp/rptun.h"

#include "bes_rptun_internal.h"

#if defined(RPTUN_INIT_WORK)
#  if defined(__NuttX__)
#    include <nuttx/wqueue.h>
#  else
#    include "wqueue.h"
#  endif
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define VRING_SIZE \
    RPTUN_VRING_TOTAL_SIZE(RPTUN_BUFFER_NUM, RPTUN_BUFFER_SIZE, RPTUN_ALIGN_BOUNDARY)

#define bes_rptun_vring             RPTUN_DECLARE(RPTUN_TUNNEL_NAME, vring)
#define bes_rptun_dev               RPTUN_DECLARE(RPTUN_TUNNEL_NAME, dev)
#define bes_rptun_rsc               RPTUN_DECLARE(RPTUN_TUNNEL_NAME, resource_table)

#define bes_rptun_ipc_is_start      RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, is_start)
#define bes_rptun_ipc_send          RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, send)
#define bes_rptun_ipc_start         RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, start)
#define bes_rptun_ipc_stop          RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, stop)

#define bes_rptun_ipc_rx_handler    RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, rx_handler)
#define bes_rptun_ipc_tx_handler    RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, tx_handler)

#define bes_rptun_initialize        RPTUN_INIT_DECLARE(RPTUN_TUNNEL_NAME)

/****************************************************************************
 * Prototype Declarations
 ****************************************************************************/
static int bes_rptun_ipc_start(struct bes_rptun_phy_s *phy);
static int bes_rptun_ipc_stop(struct bes_rptun_phy_s *phy);
static int bes_rptun_ipc_send(struct bes_rptun_phy_s *phy, uint32_t data);
static bool bes_rptun_ipc_is_start(struct bes_rptun_phy_s *phy);
static unsigned int bes_rptun_ipc_rx_handler(const void *data, unsigned int len);
static void bes_rptun_ipc_tx_handler(const void *data, unsigned int len);

#if defined(RPTUN_INIT_WORK)
static void start_work(void *arg);
static void stop_work(void *arg);
static void start_work_hook(struct bes_rptun_dev_s *dev, uint32_t msg);
static void stop_work_hook(struct bes_rptun_dev_s *dev, uint32_t msg);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/
static struct bes_rptun_dev_s bes_rptun_dev = {
    .attr = 0
#if !defined(RPTUN_DELAY_BOOT)
            | RPTUN_ATTR_AUTO_START
#endif
#if defined(RPTUN_MASTER)
            | RPTUN_ATTR_MASTER
#endif
#if defined(RPTUN_PRIMARY_CHANNEL)
            | RPTUN_ATTR_PRIMARY
#endif
#if defined(RPTUN_UNICTRL)
            | RPTUN_ATTR_UNICTRL
#endif
#if defined(RPTUN_INIT_WORK)
            | RPTUN_ATTR_INIT_WORK
#endif
            ,
    .inited    = false,
    .tunnel_id = RPTUN_TUNNEL_ID,
    .node = SYS_DLIST_STATIC_INIT(&bes_rptun_dev.node),

#if defined(RPTUN_RMT_NAME)
    .rmt_name = TO_STRING(RPTUN_RMT_NAME),
#else
#  if defined(RPTUN_MASTER)
    .rmt_name = "host",
#  else
    .rmt_name = "client",
#  endif
#endif

#if defined(RPTUN_LOCAL_NAME)
    .local_name = TO_STRING(RPTUN_LOCAL_NAME),
#else
    .local_name = "local",
#endif

    .rsc_addr = NULL,

    .vq = {
        .align        = RPTUN_ALIGN_BOUNDARY,
        .vring_num    = RPTUN_BUFFER_NUM,
        .vring_size   = RPTUN_BUFFER_SIZE,
    },

    .phy = {
        .type = BES_RPTUN_PHY_IPC,
        .ipc = {
            .local_id   = RPTUN_LOCAL_CORE_ID,
            .rmt_id     = RPTUN_RMT_CORE_ID,
            .chan_id    = RPTUN_IPC_CHAN,
            .rx_handler = bes_rptun_ipc_rx_handler,
            .tx_handler = bes_rptun_ipc_tx_handler,
        },
    },

    .ops = {
        .is_start = bes_rptun_ipc_is_start,
        .send     = bes_rptun_ipc_send,
        .start    = bes_rptun_ipc_start,
        .stop     = bes_rptun_ipc_stop,
    },

    .hook = {
#if defined(RPTUN_INIT_WORK)
        .start = start_work_hook,
        .stop  = stop_work_hook,
#else
        .start = bes_rptun_default_start_hook,
        .stop  = bes_rptun_default_stop_hook,
#endif
        .reset = bes_rptun_default_reset_hook,
        .panic = bes_rptun_default_panic_hook,
    },

    .rptun = {
        .ops = GET_RPTUN_OPS(),
    },
};

/****************************************************************************
 * Public Data
 ****************************************************************************/
RPTUN_BUFFER_LOC
uint32_t bes_rptun_vring[VRING_SIZE/sizeof(uint32_t)];

#if defined(RPTUN_MASTER)
RPTUN_RESOURCE_SECTION
struct bes_rptun_rsc_s bes_rptun_rsc =
{
    .bes_info = {
        .tunnel_id = RPTUN_TUNNEL_ID,
        .version   = ((RPTUN_MAJOR_VERSION << (24)) | \
                      (RPTUN_MINOR_VERSION << (16)) | \
                      (RPTUN_PATCH_VERSION << (8)) | \
                      (RPTUN_EXTEN_VERSION << (0))),
        .ready     = 0,
        .log_addr  = 0,
        .log_size  = 0,
    },

    .rptun_rsc = {
        .rsc_tbl_hdr = {
            .ver = 1,
#  if defined(CONFIG_BES_RPTUN_SYSLOG)
            .num = 2,
#  else
            .num = 1,
#  endif
            .reserved[0] = 0,
            .reserved[1] = 0,
        },

#  if defined(CONFIG_BES_RPTUN_SYSLOG)
        .offset[0] = offsetof(struct rptun_rsc_s, log_trace),
        .offset[1] = offsetof(struct rptun_rsc_s, rpmsg_vdev),

        .log_trace = {
            .type = RSC_TRACE,
            .da   = 0xFFFFFFFF,
            .len  = 0,
        },
#  else
        .offset[0] = offsetof(struct rptun_rsc_s, rpmsg_vdev),
#  endif

        .rpmsg_vdev = {
            .type      = RSC_VDEV,
            .id        = VIRTIO_ID_RPMSG,
            .dfeatures = 1 << VIRTIO_RPMSG_F_NS
                        | 1 << VIRTIO_RPMSG_F_ACK
                        | 1 << VIRTIO_RPMSG_F_BUFSZ
#if defined(VIRTIO_RPMSG_F_CPUNAME)
                        | 1 << VIRTIO_RPMSG_F_CPUNAME
#endif
#if defined(VIRTIO_RPMSG_F_BUFADDR)
                        | 1 << VIRTIO_RPMSG_F_BUFADDR
#endif
#if defined(RPTUN_MUST_NOTIFY)
                        | 1 << VIRTIO_RING_F_MUST_NOTIFY
#endif
                        ,
            .num_of_vrings = 2,
            .notifyid      = RSC_NOTIFY_ID_ANY,
            .config_len    = sizeof(struct fw_rsc_config),
        },

        .rpmsg_vring1 = {
            .num      = RPTUN_BUFFER_NUM,
            .align    = RPTUN_ALIGN_BOUNDARY,
            .notifyid = RSC_NOTIFY_ID_ANY,
        },

        .config = {
            .h2r_buf_size = RPTUN_BUFFER_SIZE,
#if defined(VIRTIO_RPMSG_F_CPUNAME)
#  if defined(RPTUN_LOCAL_NAME)
            .host_cpuname = TO_STRING(RPTUN_LOCAL_NAME),
#  elif defined(CONFIG_RPMSG_LOCAL_CPUNAME)
            .host_cpuname = CONFIG_RPMSG_LOCAL_CPUNAME,
#  else
            .host_cpuname = "local",
#  endif
#  if defined(RPTUN_RMT_NAME)
            .remote_cpuname = TO_STRING(RPTUN_RMT_NAME),
#  elif defined(RPTUN_MASTER)
            .remote_cpuname = "host",
#  else
            .remote_cpuname = "client",
#  endif
#endif
        },
    }
};
#else
struct bes_rptun_rsc_s *bes_rptun_rsc;
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/
static void _rptun_init_internal(struct bes_rptun_dev_s *dev)
{
    int status;
    uint32_t rsc_addr = 0;
    uint32_t rsc_size = 0;

#if defined(RPTUN_MASTER)
    dev->rsc_addr = &bes_rptun_rsc.rptun_rsc;
    bes_rptun_rsc.rptun_rsc.rpmsg_vring1.da = ROUND_UP((uint32_t)dev->vq.vring_buffer,
                                                    dev->vq.align);
#if defined(VIRTIO_RPMSG_F_BUFADDR)
    bes_rptun_rsc.rptun_rsc.config.h2r_buf_addr =
        bes_rptun_rsc.rptun_rsc.rpmsg_vring1.da +
        ROUND_UP(RPTUN_VRING_SIZE(dev->vq.vring_num, dev->vq.align),
                 dev->vq.align);
#endif

    status = rptun_initialize(&dev->rptun);
    if (status) {
        rp_err("rptun initialize failed, status/%d", status);
    } else {
        rp_info("rptun initialize done");
        dev->inited = true;
    }
#else
    status = hal_rmt_ipc_get_rsc_table(dev->phy.ipc.ep, &rsc_addr, &rsc_size);
    if (status) {
        rp_err("get %s's resource table failed, status/%d", dev->rmt_name, status);
        return;
    }

    rsc_addr = bes_rptun_get_rsc_table(dev->tunnel_id, rsc_addr, rsc_size);
    if (rsc_addr == 0) {
        rp_err("get tunnel/%d's resource table failed", dev->tunnel_id, status);
        return;
    }

    bes_rptun_rsc = (struct bes_rptun_rsc_s *)rsc_addr;

    status = bes_rptun_setup_rsc_table(&bes_rptun_dev, bes_rptun_rsc);
    if (status) {
        rp_err("setup resource table with %s failed, status/%d", dev->rmt_name, status);
        return;
    }

    dev->rsc_addr = &bes_rptun_rsc->rptun_rsc;

    if (dev->inited && BES_RPTUN_IS_AUTO_START(dev)) {
#  if defined(__NuttX__)
        status = rptun_boot(dev->rmt_name);
#  else
        status = rptun_boot_sync(dev->rmt_name);
#  endif
        if (status) {
            rp_err("rptun boot %s in re-init failed, status/%d",
                    dev->rmt_name, status);
            return;
        }
        rp_info("rptun boot %s in re-init done", dev->rmt_name);
    } else {
        status = rptun_initialize(&dev->rptun);
        if (status) {
            rp_err("rptun initialize failed, status/%d", status);
            return;
        }
        rp_info("rptun initialize done");

        dev->inited = true;
    }
#endif
    (void)rsc_addr;
    (void)rsc_size;
}

static void _rptun_deinit_internal(struct bes_rptun_dev_s *dev)
{
    int status;

    if (dev->inited && BES_RPTUN_IS_AUTO_START(dev)) {
#if defined(__NuttX__)
        status = rptun_poweroff(bes_rptun_dev.rmt_name);
#else
        status = rptun_close_sync(bes_rptun_dev.rmt_name);
#endif
        if (status) {
            rp_err("rptun stop %s in re-init failed, status/%d",
                    bes_rptun_dev.rmt_name, status);
            return;
        }
    }
}

#if defined(RPTUN_INIT_WORK)
static void start_work(void *arg)
{
    _rptun_init_internal(arg);
}

static void stop_work(void *arg)
{
    _rptun_deinit_internal(arg);
}

static void start_work_hook(struct bes_rptun_dev_s *dev, uint32_t msg)
{
    static struct work_s work;
    work_queue(HPWORK, &work, start_work, dev, 0);
}

static void stop_work_hook(struct bes_rptun_dev_s *dev, uint32_t msg)
{
    static struct work_s work;
    work_queue(HPWORK, &work, stop_work, dev, 0);
}
#endif

static unsigned int bes_rptun_ipc_rx_handler(const void *data, unsigned int len)
{
    uint32_t msg = (uint32_t)data;

    switch(msg & (RPTUN_MSG_MASK | (0xF) << RPTUN_MSG_SHIFT)) {
    case RPTUN_MSG_START:
        if (bes_rptun_dev.hook.start) {
            bes_rptun_dev.hook.start(&bes_rptun_dev, msg);
        } else {
            rp_warn("Got start msg/0x%x but notregister hook", msg);
        }
        break;
    case RPTUN_MSG_STOP:
        if (bes_rptun_dev.hook.stop) {
            bes_rptun_dev.hook.stop(&bes_rptun_dev, msg);
        } else {
            rp_warn("Got stop msg/0x%x but notregister hook", msg);
        }
        break;
    case RPTUN_MSG_PANIC:
        if (bes_rptun_dev.hook.panic) {
            bes_rptun_dev.hook.panic(&bes_rptun_dev, msg);
        } else {
            rp_warn("Got panic msg/0x%x but notregister hook", msg);
        }
        break;
    case RPTUN_MSG_RESET:
        if (bes_rptun_dev.hook.reset) {
            bes_rptun_dev.hook.reset(&bes_rptun_dev, msg);
        } else {
            rp_warn("Got reset msg/0x%x but notregister hook", msg);
        }
        break;
    default:
        if (bes_rptun_dev.callback) {
            rp_info("Got message/0x%x from %s", msg, bes_rptun_dev.rmt_name);
            bes_rptun_dev.callback(bes_rptun_dev.arg, (msg & (~ RPTUN_MSG_MASK)));
        } else {
            rp_warn("Got msg/0x%x from %s but callback not register", msg, bes_rptun_dev.rmt_name);
        }
    }

    return len;
}

static void bes_rptun_ipc_tx_handler(const void *data, unsigned int len)
{
    uint32_t msg = (uint32_t)data;

    switch(msg) {
    case RPTUN_MSG_PANIC:
        rp_info("Send panic msg/0x%x to %s done", msg, bes_rptun_dev.rmt_name);
        break;
    case RPTUN_MSG_START:
        rp_info("Send start msg/0x%x to %s done", msg, bes_rptun_dev.rmt_name);
        break;
    case RPTUN_MSG_RESET:
        rp_info("Send reset msg/0x%x to %s done", msg, bes_rptun_dev.rmt_name);
        break;
    case RPTUN_MSG_STOP:
        rp_info("Send close msg/0x%x to %s done", msg, bes_rptun_dev.rmt_name);
        break;
    default:
        rp_info("Send msg/0x%x done", msg);
    }
}

static int bes_rptun_ipc_start(struct bes_rptun_phy_s *phy)
{
    int ret;

    rp_assert(phy, "invalid bes rptun physical tunnel");
    rp_assert(phy->type == BES_RPTUN_PHY_IPC, "invalid bes rptun physical tunnel type");

#if defined(RPTUN_IPC_FW_LINUX)
    ret = fw_linux_main();
    if (ret) {
        rp_err("fw_linux_main() return/%d", ret);
        ret = 200;
        goto _exit;
    }
    rp_info("fw_linux_main() return/%d", ret);
#elif defined(RPTUN_IPC_CA_SUBSYS)
    ret = ap_subsys_open(AP_SUBSYS_USER_CPU);
    if (ret) {
        rp_err("ap_subsys_open(%d) return/%d", AP_SUBSYS_USER_CPU, ret);
        ret = 200;
        goto _exit;
    }
    rp_info("ap_subsys_open(%d) return/%d", AP_SUBSYS_USER_CPU, ret);

    ret = ap_cpu_open(AP_OP_AUTO_TRIGGER);
    if (ret) {
        rp_err("ap_cpu_open(%d) return/%d", AP_OP_AUTO_TRIGGER, ret);
        ret = 201;
        goto _exit;
    }
    rp_info("ap_cpu_open(%d) return/%d", AP_OP_AUTO_TRIGGER, ret);
#elif defined (RPTUN_IPC_BT_HOST)
    ret = bt_host_open(bes_rptun_ipc_rx_handler, bes_rptun_ipc_tx_handler);
    if (ret) {
        rp_err("bt_host_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
               bes_rptun_ipc_tx_handler, ret);
        ret = 200;
        goto _exit;
    }
    rp_info("bt_host_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
            bes_rptun_ipc_tx_handler, ret);
#elif defined(RPTUN_IPC_CP_SUBSYS)
    ret = cp_subsys_open(bes_rptun_ipc_rx_handler, bes_rptun_ipc_tx_handler);
    if (ret) {
        rp_err("cp_subsys_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
               bes_rptun_ipc_tx_handler, ret);
        ret = 200;
        goto _exit;
    }
    rp_info("cp_subsys_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
            bes_rptun_ipc_tx_handler, ret);
#elif defined(RPTUN_IPC_CP_SUBSYS1)
    ret = cp_subsys1_open(bes_rptun_ipc_rx_handler, bes_rptun_ipc_tx_handler);
    if (ret) {
        rp_err("cp_subsys1_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
               bes_rptun_ipc_tx_handler, ret);
        ret = 200;
        goto _exit;
    }
    rp_info("cp_subsys1_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
            bes_rptun_ipc_tx_handler, ret);
#elif defined(RPTUN_IPC_CP_SUBSYS2)
    ret = cp_subsys2_open(bes_rptun_ipc_rx_handler, bes_rptun_ipc_tx_handler);
    if (ret) {
        rp_err("cp_subsys2_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
               bes_rptun_ipc_tx_handler, ret);
        ret = 200;
        goto _exit;
    }
    rp_info("cp_subsys2_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
            bes_rptun_ipc_tx_handler, ret);
#elif defined(RPTUN_IPC_DSP_HIFI4)
    ret = dsp_open();
    if (ret) {
        rp_err("dsp_open() return/%d", ret);
        ret = 200;
        goto _exit;
    }

    ret = dsp_hifi4_ipc_open(bes_rptun_ipc_rx_handler, bes_rptun_ipc_tx_handler);
    if (ret) {
        rp_err("dsp_hifi4_ipc_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
               bes_rptun_ipc_tx_handler, ret);
        ret = 201;
        goto _exit;
    }
    rp_info("dsp_hifi4_ipc_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
            bes_rptun_ipc_tx_handler, ret);
#elif defined(RPTUN_IPC_DSP_M55)
    ret = dsp_m55_open(bes_rptun_ipc_rx_handler, bes_rptun_ipc_tx_handler);
    if (ret) {
        rp_err("dsp_m55_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
               bes_rptun_ipc_tx_handler, ret);
        ret = 200;
        goto _exit;
    }
    rp_info("dsp_m55_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
            bes_rptun_ipc_tx_handler, ret);
#elif defined(RPTUN_IPC_DSP_M55C1)
    ret = dsp_m55c1_open(bes_rptun_ipc_rx_handler, bes_rptun_ipc_tx_handler);
    if (ret) {
        rp_err("dsp_m55c1_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
               bes_rptun_ipc_tx_handler, ret);
        ret = 200;
        goto _exit;
    }
    rp_info("dsp_m55c1_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
            bes_rptun_ipc_tx_handler, ret);
#elif defined(RPTUN_IPC_SENSOR_HUB)
    ret = sensor_hub_open(bes_rptun_ipc_rx_handler, bes_rptun_ipc_tx_handler);
    if (ret) {
        rp_err("sensor_hub_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
               bes_rptun_ipc_tx_handler, ret);
        ret = 200;
        goto _exit;
    }
    rp_info("sensor_hub_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
            bes_rptun_ipc_tx_handler, ret);
#elif defined(RPTUN_IPC_ZSP_LOADER)
    ret = zsp_open(bes_rptun_ipc_rx_handler, bes_rptun_ipc_tx_handler);
    if (ret) {
        rp_err("zsp_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
               bes_rptun_ipc_tx_handler, ret);
        ret = 200;
        goto _exit;
    }
    rp_info("zsp_open(%p, %p) return/%d", bes_rptun_ipc_rx_handler,
            bes_rptun_ipc_tx_handler, ret);
#endif

#if defined(RPTUN_IPC_COMMON)
    if (1)
#else
    ret = hal_rmt_ipc_get_ep(RPTUN_RMT_CORE_ID, RPTUN_IPC_CHAN, &phy->ipc.ep);
    if (ret) {
        rp_err("hal_rmt_ipc_get_ep(%d, %d, %p) return/%d", RPTUN_RMT_CORE_ID,
               RPTUN_IPC_CHAN, &phy->ipc.ep, ret);
        ret = 202;
        goto _exit;
    }
    rp_info("hal_rmt_ipc_get_ep(%d, %d, %p) return/%d", RPTUN_RMT_CORE_ID,
            RPTUN_IPC_CHAN, &phy->ipc.ep, ret);

    if (!hal_rmt_ipc_opened(phy->ipc.ep))
#endif
    {
        ret = hal_rmt_ipc_open(RPTUN_RMT_CORE_ID, RPTUN_IPC_CHAN, bes_rptun_ipc_rx_handler,
                            bes_rptun_ipc_tx_handler, false, &phy->ipc.ep);
        if (ret) {
            rp_err("hal_rmt_ipc_open(%d, %d, %p, %p, %s, %p) return/%d", RPTUN_RMT_CORE_ID,
                RPTUN_IPC_CHAN, bes_rptun_ipc_rx_handler, bes_rptun_ipc_tx_handler,
                "false", &phy->ipc.ep, ret);
            ret = 203;
            goto _exit;
        }
        rp_info("hal_rmt_ipc_open(%d, %d, %p, %p, %s, %p) return/%d", RPTUN_RMT_CORE_ID,
                RPTUN_IPC_CHAN, bes_rptun_ipc_rx_handler, bes_rptun_ipc_tx_handler,
                "false", &phy->ipc.ep, ret);

        ret = hal_rmt_ipc_start_recv(phy->ipc.ep);
        if (ret) {
            rp_err("hal_rmt_ipc_start_recv(%p) return/%d", phy->ipc.ep, ret);
            ret = 204;
            goto _exit;
        }
        rp_info("hal_rmt_ipc_start_recv(%p) return/%d", phy->ipc.ep, ret);
    }

_exit:
    return ret;
}

static int bes_rptun_ipc_stop(struct bes_rptun_phy_s *phy)
{
    int ret;
    struct fw_rsc_vdev_vring *rpmsg_vring0;

    rp_assert(phy, "invalid bes rptun physical tunnel");
    rp_assert(phy->type == BES_RPTUN_PHY_IPC, "invalid bes rptun physical tunnel type");
    rp_assert(phy->ipc.ep, "invalid bes rptun physical tunnel");

#if defined(RPTUN_IPC_FW_LINUX) || defined(RPTUN_IPC_CA_SUBSYS)
    ret = ap_cpu_close();
    if (ret) {
        rp_err("ap_cpu_close() return/%d", ret);
        ret = 210;
        goto _exit;
    }
    rp_info("ap_cpu_close() return/%d", ret);

    ret = ap_subsys_close(AP_SUBSYS_USER_CPU);
    if (ret) {
        rp_err("ap_subsys_close(%d) return/%d", AP_SUBSYS_USER_CPU, ret);
        ret = 211;
        goto _exit;
    }
    rp_info("ap_subsys_close(%d) return/%d", AP_SUBSYS_USER_CPU, ret);
#elif defined (RPTUN_IPC_BT_HOST)
    ret = bt_host_close();
    if (ret) {
        rp_err("bt_host_close() return/%d", ret);
        ret = 210;
        goto _exit;
    }
    rp_info("bt_host_close() return/%d", ret);
#elif defined(RPTUN_IPC_CP_SUBSYS)
    ret = cp_subsys_close();
    if (ret) {
        rp_err("cp_subsys_close() return/%d", ret);
        ret = 210;
        goto _exit;
    }
    rp_info("cp_subsys_close() return/%d", ret);
#elif defined(RPTUN_IPC_CP_SUBSYS1)
    ret = cp_subsys1_close();
    if (ret) {
        rp_err("cp_subsys1_close() return/%d", ret);
        ret = 210;
        goto _exit;
    }
    rp_info("cp_subsys1_close() return/%d", ret);
#elif defined(RPTUN_IPC_CP_SUBSYS2)
    ret = cp_subsys2_close();
    if (ret) {
        rp_err("cp_subsys2_close() return/%d", ret);
        ret = 210;
        goto _exit;
    }
    rp_info("cp_subsys2_close() return/%d", ret);
#elif defined(RPTUN_IPC_DSP_HIFI4)
    ret = dsp_hifi4_ipc_close();
    if (ret) {
        rp_err("dsp_hifi4_ipc_close() return/%d", ret);
        ret = 210;
        goto _exit;
    }
    rp_info("dsp_hifi4_ipc_close() return/%d", ret);

    ret = dsp_close();
    if (ret) {
        rp_err("dsp_close() return/%d", ret);
        ret = 211;
        goto _exit;
    }
    rp_info("dsp_close() return/%d", ret);
#elif defined (RPTUN_IPC_DSP_M55)
    ret = dsp_m55_close();
    if (ret) {
        rp_err("dsp_m55_close() return/%d", ret);
        ret = 210;
        goto _exit;
    }
    rp_info("dsp_m55_close() return/%d", ret);
#elif defined (RPTUN_IPC_DSP_M55C1)
    ret = dsp_m55c1_close();
    if (ret) {
        rp_err("dsp_m55c1_close() return/%d", ret);
        ret = 210;
        goto _exit;
    }
    rp_info("dsp_m55c1_close() return/%d", ret);
#elif defined(RPTUN_IPC_SENSOR_HUB)
    ret = sensor_hub_close();
    if (ret) {
        rp_err("sensor_hub_close() return/%d", ret);
        ret = 210;
        goto _exit;
    }
    rp_info("sensor_hub_close() return/%d", ret);
#elif defined(RPTUN_IPC_ZSP_LOADER)
    ret = zsp_close();
    if (ret) {
        rp_err("zsp_close() return/%d", ret);
        ret = 210;
        goto _exit;
    }
    rp_info("zsp_close() return/%d", ret);
#endif

#if defined(RPTUN_IPC_COMMON)
    if (1)
#else
    if (hal_rmt_ipc_opened(phy->ipc.ep))
#endif
    {
        ret = hal_rmt_ipc_close(phy->ipc.ep);
        if (ret) {
            rp_err("hal_rmt_ipc_close(%p) return/%d", phy->ipc.ep, ret);
            ret = 212;
            goto _exit;
        }
        rp_info("hal_rmt_ipc_close(%p) return/%d", phy->ipc.ep, ret);
    }

#if defined(RPTUN_MASTER)
    rpmsg_vring0 = &bes_rptun_rsc.rptun_rsc.rpmsg_vring0;
    memset(rpmsg_vring0, 0, sizeof(*rpmsg_vring0));
#else
    (void)(rpmsg_vring0);
#endif

_exit:
    return ret;
}

static int bes_rptun_ipc_send(struct bes_rptun_phy_s *phy, uint32_t data)
{
    int ret;

    rp_assert(phy, "invalid bes rptun physical tunnel");
    rp_assert(phy->type == BES_RPTUN_PHY_IPC, "invalid bes rptun physical tunnel type");

    ret = hal_rmt_ipc_send(phy->ipc.ep, (const void *)data, 0);
    if (ret) {
        rp_err("hal_rmt_ipc_send(%p, 0x%x, 0) return/%d", phy->ipc.ep, data, ret);
        ret = 220;
        goto _exit;
    }
    rp_info("hal_rmt_ipc_send(%p, 0x%x, 0) return/%d", phy->ipc.ep, data, ret);
#if defined(RPTUN_IPC_CP_SUBSYS)
    if (data == RPTUN_MSG_PANIC) {
        hal_sys_timer_delay(MS_TO_TICKS(10));
        hal_cmu_cp_subsys_wakeup_safe();
    }
#elif defined(RPTUN_IPC_CP_SUBSYS1)
    if (data == RPTUN_MSG_PANIC) {
        hal_sys_timer_delay(MS_TO_TICKS(10));
        hal_cmu_cp_subsys1_wakeup_safe();
    }
#elif defined(RPTUN_IPC_CP_SUBSYS2)
    if (data == RPTUN_MSG_PANIC) {
        hal_sys_timer_delay(MS_TO_TICKS(10));
        hal_cmu_cp_subsys2_wakeup_safe();
    }
#elif defined(RPTUN_IPC_DSP_HIFI4)
    if (data == RPTUN_MSG_PANIC) {
        hal_sys_timer_delay(MS_TO_TICKS(10));
        hal_cmu_hifi4_wakeup_safe();
    }
#elif defined(RPTUN_IPC_ZSP_LOADER)
    if (data == RPTUN_MSG_PANIC) {
        hal_sys_timer_delay(MS_TO_TICKS(10));
        hal_cmu_zsp_wakeup_safe();
    }
#endif

_exit:
    return ret;
}

static bool bes_rptun_ipc_is_start(struct bes_rptun_phy_s *phy)
{
    int is_start;
    rp_assert(phy, "invalid bes rptun physical tunnel");
    rp_assert(phy->type == BES_RPTUN_PHY_IPC, "invalid bes rptun physical tunnel type");

    is_start = hal_rmt_ipc_opened(phy->ipc.ep);

    rp_info("tunnel %s", is_start ? "started" : "not start");

    return !!is_start;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/
int bes_rptun_initialize(void)
{
    int ret = 0;
    int status = 0;

    if (bes_rptun_dev.inited) {
        _rptun_deinit_internal(&bes_rptun_dev);
    } else {
#if defined(CONFIG_BES_RPCHAN)
        extern int rpchan_register(struct bes_rptun_dev_s *, RPCHAN_CORE_ID_T);
        status = rpchan_register(&bes_rptun_dev, RPCHAN_REMOTE_ID);
        if (status) {
            rp_err("register rp tunnel to rpchan failed, status/%d", status);
            ret = 100;
            goto _exit;
        }
#endif
        bes_rptun_register_dev(&bes_rptun_dev);
    }

    bes_rptun_dev.vq.vring_buffer =
        ADDR_CPU_TO_DEV(ROUND_UP((uint32_t)bes_rptun_vring, RPTUN_ALIGN_BOUNDARY));

#if defined(RPTUN_MASTER)
    _rptun_init_internal(&bes_rptun_dev);
#else
    rptun_pm_lock(bes_rptun_dev.tunnel_id);

    status = bes_rptun_dev.ops.start(&bes_rptun_dev.phy);
    if (status) {
        rp_err("start tunnel with %s failed, status/%d", bes_rptun_dev.rmt_name, status);
        ret = 101;
        goto _exit;
    }

    if (!BES_RPTUN_IS_INIT_WORK(&bes_rptun_dev)) {
        _rptun_init_internal(&bes_rptun_dev);
    }
#endif

_exit:
    return ret;
}

#endif /* __RPTUN_IMPL_H__ */
