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

#if defined(RPTUN_TRANSQ)
#  include "hal_transq.h"
#else
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

#define bes_rptun_transq_is_start   RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, is_start)
#define bes_rptun_transq_send       RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, send)
#define bes_rptun_transq_start      RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, start)
#define bes_rptun_transq_stop       RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, stop)

#define bes_rptun_transq_rx_handler RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, rx_handler)
#define bes_rptun_transq_tx_handler RPTUN_OPS_DECLARE(RPTUN_TUNNEL_NAME, tx_handler)

#define bes_rptun_initialize        RPTUN_INIT_DECLARE(RPTUN_TUNNEL_NAME)

/****************************************************************************
 * Prototype Declarations
 ****************************************************************************/
static int bes_rptun_transq_start(struct bes_rptun_phy_s *phy);
static int bes_rptun_transq_stop(struct bes_rptun_phy_s *phy);
static int bes_rptun_transq_send(struct bes_rptun_phy_s *phy, uint32_t data);
static bool bes_rptun_transq_is_start(struct bes_rptun_phy_s *phy);
static void bes_rptun_transq_rx_handler(enum HAL_TRANSQ_PRI_T prio);
static void bes_rptun_transq_tx_handler(enum HAL_TRANSQ_PRI_T prio, const uint8_t *data,
                                        unsigned int lens);

#if defined(RPTUN_INIT_WORK)
static void start_work(void *arg);
static void stop_work(void *arg);
static void start_work_hook(struct bes_rptun_dev_s *dev, uint32_t msg);
static void stop_work_hook(struct bes_rptun_dev_s *dev, uint32_t msg);
#endif

#if defined(RPTUN_MASTER)
extern void a7_dsp_boot(void);
extern void a7_dsp_stop(void);
extern int is_a7_boot_done(void);
extern uint32_t __resource_table_start__[];
extern uint32_t __resource_table_end__[];
#else
static int _get_resource_table(uint32_t *rsc_addr, uint32_t *rsc_size);
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
        .align      = RPTUN_ALIGN_BOUNDARY,
        .vring_num  = RPTUN_BUFFER_NUM,
        .vring_size = RPTUN_BUFFER_SIZE,
    },

    .phy = {
        .type = BES_RPTUN_PHY_TRANSQ,
        .transq = {
            .chan_id       = RPTUN_TRANSQ_ID,
            .cfg_prio      = RPTUN_TRANSQ_CFG_PRIO,
            .cfg_slot      = RPTUN_TRANSQ_CFG_SLOT,
            .msg_prio      = RPTUN_TRANSQ_MSG_PRIO,
            .msg_slot      = RPTUN_TRANSQ_MSG_SLOT,
            .rx_handler    = bes_rptun_transq_rx_handler,
            .tx_handler    = bes_rptun_transq_tx_handler,
#if !defined(RPTUN_MASTER)
            .resource_addr = 0,
            .resource_size = 0,
#endif
        },
    },

    .ops = {
        .is_start = bes_rptun_transq_is_start,
        .send     = bes_rptun_transq_send,
        .start    = bes_rptun_transq_start,
        .stop     = bes_rptun_transq_stop,
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

    dev->phy.transq.resource_addr = (uint32_t)__resource_table_start__,
    dev->phy.transq.resource_size =
        (uint32_t)__resource_table_end__ - (uint32_t)__resource_table_start__,
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
        return;
    } else {
        rp_info("rptun initialize done");
        dev->inited = true;
    }
#else
    status = _get_resource_table(&rsc_addr, &rsc_size);
    if (status) {
        rp_err("get %s's resource table failed, status/%d",
               dev->rmt_name, status);
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

#if !defined(RPTUN_MASTER)
static int _get_resource_table(uint32_t *rsc_addr, uint32_t *rsc_size)
{
    int times = 0;
    struct bes_rptun_phy_s *phy = NULL;

    phy = &bes_rptun_dev.phy;

    for (; times < 100; times++) {
        if (phy->transq.resource_addr == 0 || phy->transq.resource_size == 0) {
            osDelay(10);
            continue;
        }

        *rsc_addr = phy->transq.resource_addr;
        *rsc_size = phy->transq.resource_size;
        break;
    }

    if (times == 100) {
        rp_err("get resource table timeout");
        return 1;
    }

    return 0;
}

static int _update_resource_info(enum HAL_TRANSQ_PRI_T prio)
{
    int status = 0;
    uint32_t lens = 0;
    const uint8_t *data = NULL;
    enum HAL_TRANSQ_RET_T ret = 0;
    struct bes_rptun_phy_s *phy = NULL;

    phy = &bes_rptun_dev.phy;

    status = hal_transq_rx_first(phy->transq.chan_id, prio, &data, &lens);
    rp_assert(status == HAL_TRANSQ_RET_OK, "unexpected status");
    rp_assert(phy->transq.resource_addr == 0 && phy->transq.resource_size == 0,
              "transq has invalid resource info");

    rp_info("hal_transq_rx_first(%d, %p, %p) return/%d", phy->transq.chan_id,
            prio, &data, &lens, status);

    phy->transq.resource_addr = (uint32_t)data;
    phy->transq.resource_size = (uint32_t)lens;

    status = hal_transq_rx_next(phy->transq.chan_id, prio, &data, &lens);
    rp_assert(status == HAL_TRANSQ_RET_RX_EMPTY, "unexpected status");

    return status;
}
#endif

static void inline _process_message(uint32_t msg)
{
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
}

static void bes_rptun_transq_rx_handler(enum HAL_TRANSQ_PRI_T prio)
{
    uint32_t lens = 0;
    const uint8_t *data = NULL;
    enum HAL_TRANSQ_RET_T status = 0;
    struct bes_rptun_phy_s *phy = &bes_rptun_dev.phy;

    if (prio == phy->transq.cfg_prio) {
#if defined(RPTUN_MASTER)
        rp_assert(false, "get unexpected message");
#else
        _update_resource_info(prio);
#endif
        goto _exit;
    }

    status = hal_transq_rx_first(phy->transq.chan_id, prio, &data, &lens);
    rp_assert(status == HAL_TRANSQ_RET_OK, "unexpected status");

    for (;;) {
        _process_message((uint32_t)data);

        status = hal_transq_rx_next(phy->transq.chan_id, prio, &data, &lens);
        if (status == HAL_TRANSQ_RET_RX_EMPTY) {
            break;
        }
    }

_exit:
    return;
}

static void bes_rptun_transq_tx_handler(enum HAL_TRANSQ_PRI_T prio, const uint8_t *data,
                                        unsigned int lens)
{
    uint32_t msg = (uint32_t)data;
    struct bes_rptun_phy_s *phy = &bes_rptun_dev.phy;

    if (prio == phy->transq.cfg_prio) {
#if defined(RPTUN_MASTER)
        rp_assert((uint32_t)data == phy->transq.resource_addr, "unexpected message done");
        rp_info("notify resource info done");
#else
        rp_assert(false, "unexpected message done");
#endif
    } else if (prio == phy->transq.msg_prio) {
        rp_assert(lens == 0, "unexpected message length done");

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
}

static int bes_rptun_transq_start(struct bes_rptun_phy_s *phy)
{
    int ret = 0;
    enum HAL_TRANSQ_RET_T status = HAL_TRANSQ_RET_OK;
    struct HAL_TRANSQ_CFG_T transq_cfg = {
        .rx_irq_count = 0,
        .rx_handler   = bes_rptun_transq_rx_handler,
        .tx_handler   = bes_rptun_transq_tx_handler,
    };

    transq_cfg.slot.rx_num[phy->transq.msg_prio] = phy->transq.msg_slot;
    transq_cfg.slot.tx_num[phy->transq.msg_prio] = phy->transq.msg_slot;
    transq_cfg.slot.rx_num[phy->transq.cfg_prio] = phy->transq.cfg_slot;
    transq_cfg.slot.tx_num[phy->transq.cfg_prio] = phy->transq.cfg_slot;

    rp_assert(phy, "invalid bes rptun physical tunnel");
    rp_assert(phy->type == BES_RPTUN_PHY_TRANSQ, "invalid bes rptun physical tunnel type");

#if defined(RPTUN_MASTER)
    rp_info("a7_dsp_boot() ing");

    a7_dsp_boot();

    rp_info("a7_dsp_boot() done");
#endif

    status = hal_transq_open(phy->transq.chan_id, &transq_cfg);
    if (status != HAL_TRANSQ_RET_OK) {
        rp_err("hal_transq_open(%d, %p) return/%d", phy->transq.chan_id, &transq_cfg, status);
        ret = 200;
        goto _exit;
    }
    rp_info("hal_transq_open(%d, %p) return/%d", phy->transq.chan_id, &transq_cfg, status);

#if defined(RPTUN_MASTER)
    status = hal_transq_tx(phy->transq.chan_id, phy->transq.cfg_prio,
                           (void *)phy->transq.resource_addr, phy->transq.resource_size);
    if (status != HAL_TRANSQ_RET_OK) {
        rp_err("hal_transq_tx(%d, %d, 0x%x, 0x%x) return/%d", phy->transq.chan_id,
               phy->transq.cfg_prio, phy->transq.resource_addr, phy->transq.resource_size, status);
        ret = 201;
        goto _exit;
    }
    rp_info("hal_transq_tx(%d, %d, 0x%x, 0x%x) return/%d", phy->transq.chan_id,
            phy->transq.cfg_prio, phy->transq.resource_addr, phy->transq.resource_size, status);
#endif

_exit:
    rp_info("LOW_RPTUN: bes_rptun_initialize exit ret=%d rmt=%s", ret, bes_rptun_dev.rmt_name);
    return ret;
}

static int bes_rptun_transq_stop(struct bes_rptun_phy_s *phy)
{
    int ret = 0;
    enum HAL_TRANSQ_RET_T status = HAL_TRANSQ_RET_OK;
    struct fw_rsc_vdev_vring *rpmsg_vring0 = NULL;

    rp_assert(phy, "invalid bes rptun physical tunnel");
    rp_assert(phy->type == BES_RPTUN_PHY_TRANSQ, "invalid bes rptun physical tunnel type");

    status = hal_transq_flush(phy->transq.chan_id);
    if (status != HAL_TRANSQ_RET_OK) {
        rp_err("hal_transq_flush(%d) return/%d", phy->transq.chan_id, status);
        ret = 210;
        goto _exit;
    }
    rp_info("hal_transq_flush(%d) return/%d", phy->transq.chan_id, status);

    status = hal_transq_close(phy->transq.chan_id);
    if (status != HAL_TRANSQ_RET_OK) {
        rp_err("hal_transq_close(%d) return/%d", phy->transq.chan_id, status);
        ret = 211;
        goto _exit;
    }
    rp_info("hal_transq_close(%d) return/%d", phy->transq.chan_id, status);

#if defined(RPTUN_MASTER)
    rp_info("a7_dsp_stop() ing");

    a7_dsp_stop();

    rp_info("a7_dsp_stop() done");
#endif

#if defined(RPTUN_MASTER)
    rpmsg_vring0 = &bes_rptun_rsc.rptun_rsc.rpmsg_vring0;
    memset(rpmsg_vring0, 0, sizeof(*rpmsg_vring0));
#else
    (void)(rpmsg_vring0);
#endif

_exit:
    return ret;
}

static int bes_rptun_transq_send(struct bes_rptun_phy_s *phy, uint32_t data)
{
    int ret = 0;
    enum HAL_TRANSQ_RET_T status = HAL_TRANSQ_RET_OK;

    rp_assert(phy, "invalid bes rptun physical tunnel");
    rp_assert(phy->type == BES_RPTUN_PHY_TRANSQ, "invalid bes rptun physical tunnel type");

    status = hal_transq_tx(phy->transq.chan_id, phy->transq.msg_prio, (void *)data, 0);
    if (status != HAL_TRANSQ_RET_OK) {
        rp_err("hal_transq_tx(%d, %d, %p, 0x%x) return/%d", phy->transq.chan_id,
               phy->transq.msg_prio, (void *)data, 0, status);
        ret = 220;
        goto _exit;
    }
    rp_info("hal_transq_tx(%d, %d, %p, 0x%x) return/%d", phy->transq.chan_id,
            phy->transq.msg_prio, (void *)data, 0, status);

_exit:
    return ret;
}

static bool bes_rptun_transq_is_start(struct bes_rptun_phy_s *phy)
{
    int is_start = false;

    rp_assert(phy, "invalid bes rptun physical tunnel");
    rp_assert(phy->type == BES_RPTUN_PHY_TRANSQ, "invalid bes rptun physical tunnel type");

#if defined(RPTUN_MASTER)
    is_start = is_a7_boot_done();
#else
    is_start = hal_transq_is_opened(phy->transq.msg_prio);
#endif

    rp_info("tunnel %s", is_start ? "started" : "not start");

    return !!is_start;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/
int bes_rptun_initialize(void)
{
    rp_info("LOW_RPTUN: bes_rptun_initialize inited=%d tunnel_id=%d rmt=%s",
            bes_rptun_dev.inited, bes_rptun_dev.tunnel_id, bes_rptun_dev.rmt_name);
    int ret = 0;
    int status = 0;

    if (bes_rptun_dev.inited) {
        rp_info("LOW_RPTUN: reinit path for %s", bes_rptun_dev.rmt_name);
        _rptun_deinit_internal(&bes_rptun_dev);
    } else {
        rp_info("LOW_RPTUN: first init path for %s", bes_rptun_dev.rmt_name);
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

    rp_info("LOW_RPTUN: start phy for %s", bes_rptun_dev.rmt_name);
    status = bes_rptun_dev.ops.start(&bes_rptun_dev.phy);
    rp_info("LOW_RPTUN: start phy ret=%d for %s", status, bes_rptun_dev.rmt_name);
    if (status) {
        rp_err("start tunnel with %s failed, status/%d", bes_rptun_dev.rmt_name, status);
        ret = 101;
        goto _exit;
    }
#endif

_exit:
    return ret;
}

#endif /* __RPTUN_IMPL_H__ */
