/***************************************************************************
 *
 * Copyright 2015-2019 BES.
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
#include <stdio.h>
#include <stdlib.h>

#include <nuttx/syslog/syslog_rpmsg.h>

#include "open-amp/rptun.h"

#define SET_VAL_TO_PTR(ptr, val)    \
    do {                            \
        if (ptr != NULL) {          \
            *ptr = val;             \
        }                           \
    } while(0)

int bes_global_shmem_get_tee_syslogbuffer(unsigned int *addr, unsigned int *len)
{
    int  status = 0;
#if defined(CONFIG_BES_RPTUN_NS2SE) || defined(CONFIG_BES_RPTUN_NS2SE_MASTER)
    bool local  = false;
    unsigned int buffer_addr = 0;
    unsigned int buffer_size = 0;

#if defined(CONFIG_BES1700_TEE)
    local = true;
#endif

    status = rptun_get_log_buffer(RPTUN_CHAN_M55NS_2_M55SE, local,
                (uint32_t *)&buffer_addr, (uint32_t *)&buffer_size);
    if (status != 0) {
        return status;
    }

    SET_VAL_TO_PTR(addr, buffer_addr);
    SET_VAL_TO_PTR(len, buffer_size);
#endif
    return status;
}

int bes_global_shmem_get_bth_syslogbuffer(unsigned int *addr, unsigned int *len)
{
    int  status = 0;
    bool local  = false;
    unsigned int buffer_addr = 0;
    unsigned int buffer_size = 0;

#if defined(CONFIG_BES1700_BTH) || defined(CONFIG_BES1700_CP)
    local = true;
#endif

    status = rptun_get_log_buffer(RPTUN_CHAN_M55C0_2_BTHC0, local,
                (uint32_t *)&buffer_addr, (uint32_t *)&buffer_size);
    if (status != 0) {
        return status;
    }

    SET_VAL_TO_PTR(addr, buffer_addr);
    SET_VAL_TO_PTR(len, buffer_size);

    return status;
}

int bes_global_shmem_get_cp_syslogbuffer(unsigned int *addr, unsigned int *len) {
    return bes_global_shmem_get_bth_syslogbuffer(addr, len);
}

int bes_global_shmem_get_apc1_syslogbuffer(unsigned int *addr, unsigned int *len)
{
    int  status = 0;
    bool local  = false;
    unsigned int buffer_addr = 0;
    unsigned int buffer_size = 0;

#if defined(CONFIG_BES1700_APC1)
    local = true;
#endif

    status = rptun_get_log_buffer(RPTUN_CHAN_M55C0_2_M55C1, local,
                (uint32_t *)&buffer_addr, (uint32_t *)&buffer_size);
    if (status != 0) {
        return status;
    }

    SET_VAL_TO_PTR(addr, buffer_addr);
    SET_VAL_TO_PTR(len, buffer_size);

    return status;
}

int bes_global_shmem_get_audio_syslogbuffer(unsigned int *addr, unsigned int *len)
{
    int  status = 0;
    bool local  = false;
    unsigned int buffer_addr = 0;
    unsigned int buffer_size = 0;

#if defined(CONFIG_BES1700_AUDIO)
    local = true;
#endif

    status = rptun_get_log_buffer(RPTUN_CHAN_M55C0_2_DSPC0, local,
                (uint32_t *)&buffer_addr, (uint32_t *)&buffer_size);
    if (status != 0) {
        return status;
    }

    SET_VAL_TO_PTR(addr, buffer_addr);
    SET_VAL_TO_PTR(len, buffer_size);

    return status;
}

int bes_global_shmem_get_bthcp_syslogbuffer(unsigned int *addr, unsigned int *len)
{
    int  status = 0;
    bool local  = false;
    unsigned int buffer_addr = 0;
    unsigned int buffer_size = 0;

#if defined(CONFIG_BES1700_BTHCP)
    local = true;
#endif

    status = rptun_get_log_buffer(RPTUN_CHAN_BTHC0_2_BTHC1, local,
                (uint32_t *)&buffer_addr, (uint32_t *)&buffer_size);
    if (status != 0) {
        return status;
    }

    SET_VAL_TO_PTR(addr, buffer_addr);
    SET_VAL_TO_PTR(len, buffer_size);

    return status;
}


int bes_global_shmem_setup_syslog_buffer(void)
{
#if defined(CONFIG_SYSLOG_RPMSG)
    unsigned int addr = 0;
    unsigned int len = 0;

#if defined(CONFIG_BES1700_BTH) || defined(CONFIG_BES1700_CP)
    bes_global_shmem_get_bth_syslogbuffer(&addr, &len);
#elif defined(CONFIG_BES1700_AUDIO)
    bes_global_shmem_get_audio_syslogbuffer(&addr, &len);
#elif defined(CONFIG_BES1700_APC1)
    bes_global_shmem_get_apc1_syslogbuffer(&addr, &len);
#elif defined(CONFIG_ARCH_TRUSTZONE_SECURE)
    bes_global_shmem_get_tee_syslogbuffer(&addr, &len);
#elif defined(CONFIG_BES1700_BTHCP)
    bes_global_shmem_get_bthcp_syslogbuffer(&addr, &len);
#endif

    syslog_rpmsg_init_early((void *)addr, len);
#endif

    return 0;
}

int bes_global_shmem_setup_ipc_buffer(void)
{
    return 0;
}
