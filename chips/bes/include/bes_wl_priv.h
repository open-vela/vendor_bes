/***************************************************************************
 * rtos/nuttx/include/arch/chip/bes_wl_priv.h
 *
 * Copyright 2015-2025 BES.
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
#ifndef BES_WL_PRIV_H
#define BES_WL_PRIV_H
#include <net/if.h>

enum crash_lmac_ops
{
    CRASH_LMAC_OPS_ILLEGAL_ACCESS = 0,
    CRASH_LMAC_OPS_ASSERT,
    CRASH_LMAC_OPS_CMD_TIMEOUT,
};

enum bes_iw_priv_cmd_id
{
    BES_IW_PRIV_CMD_ID_GET_CONN_STATUS = 0,
    BES_IW_PRIV_CMD_ID_SET_LMAC_LOG_MODE,
    BES_IW_PRIV_CMD_ID_SET_LMAC_CRASH,

    BES_IW_PRIV_CMD_ID_MAX,
};

typedef enum
{
    WL_CONN_STATUS_DISCONNECTED,       /* Disconnected */
    WL_CONN_STATUS_SCAN_REQ_FAIL,      /* Scan request failed */
    WL_CONN_STATUS_SCAN_NO_AP,         /* No target AP found in scan */
    WL_CONN_STATUS_CONNECT_REQ_FAIL,   /* Connection request failed */
    WL_CONN_STATUS_AUTH_REJECT,        /* Authentication rejected */
    WL_CONN_STATUS_AUTH_TIMEOUT,       /* Authentication timeout */
    WL_CONN_STATUS_ASSOC_REJECT,       /* Association rejected */
    WL_CONN_STATUS_ASSOC_TIMEOUT,      /* Association timeout */
    WL_CONN_STATUS_HANDSHAKE_FAIL,     /* Handshake failed */
    WL_CONN_STATUS_DHCP_FAIL,          /* DHCP failed */
    WL_CONN_STATUS_CONNECTED,          /* Connected */
} wlan_conn_status;

typedef enum
{
    WL_CONN_STATE_INVALID,            /* Invalid state*/
    WL_CONN_STATE_SCANNING,           /* Scanning */
    WL_CONN_STATE_AUTHENTICATING,     /* Authentication start */
    WL_CONN_STATE_AUTH_REJECT,        /* Authentication rejected by AP */
    WL_CONN_STATE_AUTH_TIMEOUT,       /* Authentication timeout */
    WL_CONN_STATE_ASSOCIATING,        /* Association start */
    WL_CONN_STATE_ASSOC_REJECT,       /* Association request rejected by AP */
    WL_CONN_STATE_ASSOC_TIMEOUT,      /* Association timeout */
    WL_CONN_STATE_ASSOCIATED,         /* Associated to target AP */
    WL_CONN_STATE_4WAY_HANDSHAKE,     /* 4way-handshake start */
    WL_CONN_STATE_HANDSHAKE_FAIL,     /* 4way-handshake fail */
    WL_CONN_STATE_GROUP_HANDSHAKE,    /* Group handshake start */
    /* The above enumeration value should correspond to BWIFI_CONNECT_INTER_STATE */
    WL_CONN_STATE_CONNECTED,          /* Connected */
} wlan_conn_state;

#define BES_WL_USER_EVT_SIGNAL_BASE                                 (32)
#define BES_WL_USER_EVT_SIGNAL_STA_CONNECT                          (BES_WL_USER_EVT_SIGNAL_BASE + 0)
#define BES_WL_USER_EVT_SIGNAL_STA_AUTH_ASSOC_REJECT_STATUS_CODE    (BES_WL_USER_EVT_SIGNAL_BASE + 1)
#define BES_WL_USER_EVT_SIGNAL_STA_DISCONNECT                       (BES_WL_USER_EVT_SIGNAL_BASE + 2)
#define BES_WL_USER_EVT_SIGNAL_AP_ONOFF                             (BES_WL_USER_EVT_SIGNAL_BASE + 3)
#define BES_WL_USER_EVT_SIGNAL_AP_LINK_CHG                          (BES_WL_USER_EVT_SIGNAL_BASE + 4)
#define BES_WL_USER_EVT_SIGNAL_P2P                                  (BES_WL_USER_EVT_SIGNAL_BASE + 5)
#define BES_WL_USER_EVT_SIGNAL_MAX                                  (BES_WL_USER_EVT_SIGNAL_BASE + 6)

struct wdev_active_time
{
    struct timespec last_tx;
    struct timespec last_rx;
    struct timespec last_ioctl;
};

struct wifi_statistics
{
    int conn_status;                      /* Wi-Fi connect status */
    int scan_result_num;                  /* idle scan num */
    struct wdev_active_time active_time;  /* wireless device active time */
};

union iwreq_data_extended
{
    char name[IFNAMSIZ];                  /* Network interface name */
    struct wifi_statistics statistics;    /* Wi-Fi  statistics*/
    uint8_t lmac_log_mode;                /* lmac log mode */
    uint8_t crash_ops;                    /* lmac crash options */
};

struct iwreq_extended
{
    char ifr_name[IFNAMSIZ];              /* Interface name, e.g. "eth0" */
    uint8_t cmd_id;                       /* iw priv cmd id */
    union iwreq_data_extended u;          /* Data payload */
};

#endif//BES_WL_PRIV_H