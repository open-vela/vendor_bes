obj-y :=

LIB_NAME := libnet
ifeq ($(WIFI_CONN),1)
LIB_NAME_WIFI_STACK := libwifistack_conn
else ifeq ($(FHOST_RPMSG_DEVICE),1)
LIB_NAME_WIFI_STACK := libwifistack_rpmsg
else
LIB_NAME_WIFI_STACK := libwifistack
endif

ifeq ($(P2P_MODE_SUPPORT),1)
LIB_NAME := $(LIB_NAME)_p2p
LIB_NAME_WIFI_STACK := $(LIB_NAME_WIFI_STACK)_p2p
endif

ifeq ($(USE_NTS_HEAP),1)
LIB_NAME := $(LIB_NAME)_nts
LIB_NAME_WIFI_STACK := $(LIB_NAME_WIFI_STACK)_nts
endif

ifneq ($(SDK), 1)
export NET_COMMIT_ID := $(shell cd $(dir $(lastword $(MAKEFILE_LIST))) && git rev-parse --short HEAD)$(shell cd $(dir $(lastword $(MAKEFILE_LIST))) && git diff --quiet || echo "-dirty")
export NET_BUILD_DATE := $(shell date "+%Y%m%d_%H:%M:%S")

src_obj += utils/
ifeq ($(CHIP_HAS_WIFI), 1)
ifeq ($(WIFI_ENABLE), 1)
ifeq ($(WIFI_STACK_VER), 1)
src_obj += security/
endif
endif
endif

ifeq ($(NET_TELNET_SERVER_SUPPORT),1)
src_obj += telnet/
endif

ifeq ($(NET_KCP_SUPPORT),1)
src_obj += kcp/
endif

ifeq ($(NET_JANSSSON_SUPPORT),1)
src_obj += jansson/
endif

ifeq ($(NET_JSMN_SUPPORT),1)
src_obj += jsmn/
endif

ifeq ($(NET_LIBRWS_SUPPORT),1)
src_obj += librws/
ifeq ($(NET_LIBRWS_SUPPORT),1)
KBUILD_CFLAGS += -DNET_LIBRWS_SUPPORT -DWEBSOCKET_SSL_ENABLE -DRWS_OS_CMSIS
ifeq ($(LIBRWS_USE_LIST),1)
ifneq ($(LIBRWS_MAX_SIZE),)
KBUILD_CFLAGS += -DLIBRWS_MAX_SIZE=$(LIBRWS_MAX_SIZE)
endif
KBUILD_CFLAGS += -DLIBRWS_USE_LIST
endif
endif
endif

ifeq ($(NET_NGHTTP2_SUPPORT),1)
src_obj += nghttp2/
endif

ifeq ($(SNIFFER_MODE_SUPPORT),1)
src_obj += sniffer/
endif

ifneq ($(NUTTX_BUILD),1)
ifeq ($(AP_MODE_SUPPORT),1)
src_obj += dhcpd/
endif
endif

ifeq ($(NET_RNDIS_SUPPORT),1)
src_obj += rndis/
endif

ifeq ($(LIVE555_SUPPORT),1)
src_obj += live555/
endif

ifeq ($(MIRACAST_SUPPORT),1)
src_obj += miracast/
endif

ifeq ($(NET_WAMP_SUPPORT),1)
src_obj += wamp/
endif

ifeq ($(VOWLAN_SUPPORT),1)
src_obj += vowlan/
endif

ifeq ($(IMS_SUPPORT),1)
src_obj += ims/
endif

ifeq ($(LTE_SUPPORT),1)
src_obj += lte/
endif

ifeq ($(IPSEC_SUPPORT),1)
src_obj += ipsec/
endif

$(LIB_NAME)-y := $(src_obj)

LIB_NAME_net_music := libnet_music
src_obj := net_music/
$(LIB_NAME_net_music)-y := $(src_obj)

LIB_NAME_websvr := libnet_websvr
src_obj := websvr/
$(LIB_NAME_websvr)-y := $(src_obj)

ifeq ($(CHIP_HAS_WIFI), 1)
ifeq ($(WIFI_ENABLE), 1)
$(LIB_NAME_WIFI_STACK)-y += wifi_stack/v$(WIFI_STACK_VER)/
endif
endif

endif

obj-y += $(LIB_NAME).a
ifeq ($(CHIP_HAS_WIFI), 1)
ifeq ($(WIFI_ENABLE), 1)
obj-y += $(LIB_NAME_WIFI_STACK).a
endif
endif

ifeq ($(NET_MUSIC_SUPPORT), 1)
obj-y += $(LIB_NAME_net_music).a
endif

ifeq ($(NET_WEBSVR_SUPPORT),1)
obj-y += $(LIB_NAME_websvr).a
endif

ifeq ($(NET_LWIP_SUPPORT),1)
ifeq ($(NET_LWIP_EXTERN),0)
obj-y += $(LWIP_VER)/
endif
endif

ifeq ($(WIFI_IPERF_SUPPORT),1)
obj-y += iperf/
endif

ifeq ($(NET_OPENSSL_SUPPORT),1)
export NET_OPENSSL_VER ?= openssl-1.1.1i
obj-y += $(NET_OPENSSL_VER)/
endif

ifeq ($(NET_PING_SUPPORT),1)
obj-y += ping/
endif

ifeq ($(WIFI_CONN),1)
obj-y += ../platform/drivers/conn/
ifeq ($(WIFI_BT_COEX_SUPPORT),1)
obj-y += ../platform/drivers/coex/
endif
else
ifneq ($(WIFI_RF_TEST_ONLY),1)
obj-y += wifi/
endif
endif

ifeq ($(NET_LIBCURL_SUPPORT),1)
obj-y += libcurl/
endif

ifeq ($(NET_MBEDTLS_SUPPORT),1)
obj-y += mbedtls/
endif

ifeq ($(NET_FTP_CLIENT_SUPPORT),1)
obj-y += ftp_client/
endif

ifeq ($(NET_FTPD_SUPPORT),1)
obj-y += ftpd/
endif

ifeq ($(NET_MBEDTLS_CLIENT_SUPPORT),1)
obj-y += mbedtls_client/
endif

ifeq ($(NET_CJSON_SUPPORT),1)
obj-y += cJSON/
endif

ifeq ($(NET_COZE_SUPPORT),1)
obj-y += coze/
endif

ifeq ($(NET_ERPC_SUPPORT),1)
obj-y += erpc/
endif

ifeq ($(SDIO_WIFI_HOST),1)
obj-y += ../platform/drivers/conn/
subdir-ccflags-y += -Iplatform/drivers/conn -Iplatform/drivers/conn/rtos_host
endif

ifeq ($(FHOST_SDIO_DEVICE),1)
obj-y += ../platform/drivers/conn/
subdir-ccflags-y += -Iplatform/drivers/conn -Iplatform/drivers/conn/rtos_device
endif

obj-y += net_main.o
obj-y += rwnx_control_compat.o

subdir-ccflags-y +=\
    -Inet\
    -Inet/wifi\
    -Inet/wifi/wifi_rpmsg\
    -Inet/net_os\
    -Inet/utils\
    -Inet/include/os/\
    -Iservices/nvrecord/\
    -Iservices/cp_boot/ \
    -Iservices/aiot/factory/fhost_device/$(CHIP) \
    -Iservices/aiot/net_debug/ \
    -Iservices/nv_section/factory_section \
    -Iplatform/drivers/ana \
    -Iplatform/drivers/wifi/$(CHIP) \
    -Iutils/heap/ \
    -Iservices/aiot/factory/

ifeq ($(NET_LWIP_SUPPORT),1)
subdir-ccflags-y +=\
    -I$(LWIP_ROOT)/src/include \
    -I$(LWIP_ROOT)/src/include/$(POSIX_PATH) \
    -I$(LWIP_ROOT)/src/include/lwip/arch \
    -I$(LWIP_ROOT)/src/include/ipv4/
endif

#WiFi common feature
#subdir-ccflags-y += -DCUSTOM_FEATURE
subdir-ccflags-y += -Wno-array-bounds

ifeq ($(WIFI_HIGH_PERFORMANCE_MODE), 1)
ifneq ($(filter best2001 best2003 best2005,$(CHIP)),)
subdir-ccflags-y += -DNET_HIGHEST_FREQ=HAL_CMU_FREQ_390M
else
subdir-ccflags-y += -DNET_HIGHEST_FREQ=HAL_CMU_FREQ_208M
endif
else
subdir-ccflags-y += -DNET_HIGHEST_FREQ=HAL_CMU_FREQ_104M
endif

ifeq ($(WIFI_STACK_VER), 1)
#subdir-ccflags-y += -DBES_SOFT_AGC_ANTI_NOISE
#subdir-ccflags-y += -DKEY_FRAME_SW_RETRY
#build lwip need.
subdir-ccflags-y += -Inet/wifi_stack/v1/lwip
endif

ifeq ($(SDIO_WIFI_HOST),1)
subdir-ccflags-y += -Inet/wifi_stack/v1/lwip
else
ifeq ($(WIFI_STACK_VER),2)
#adapt lwip.
subdir-ccflags-y += -Inet/wifi_stack/v2/net_al
ifeq ($(NUTTX_BUILD), 1)
subdir-ccflags-y += -Inet/wifi_stack/v2/net_al/nuttx
else
subdir-ccflags-y += -Inet/wifi_stack/v2/net_al/lwip
endif # NUTTX_BUILD
else
subdir-ccflags-y += -Inet/wifi_stack/v1/net_al
subdir-ccflags-y += -Inet/wifi_stack/v1/net_al/lwip
endif
endif

ifeq ($(P2P_SERVICE_SUPPORT),1)
subdir-ccflags-y += -Inet/wifi/p2p_services
endif

ifeq ($(SDIO_WIFI_HOST),1)
subdir-ccflags-y += -Inet/wifi/wifi_host_sdio
endif

ifeq ($(NTS_HEAP_OVERLAY_WFCALI),1)
subdir-ccflags-y += -DNTS_HEAP_OVERLAY_WFCALI
subdir-ccflags-y += -DNET_HEAP_START=$(RAM_SIZE)+$(BT_RAMRUN_SIZE) -DNET_HEAP_END=$(RAM_SIZE)+$(BT_RAMRUN_SIZE)+$(RAM_RSV_SIZE)
endif

ifeq ($(WIFI_BT_COEX_SERVICE),1)
subdir-ccflags-y += -Iservices/aiot/coex/
endif

ifeq ($(NET_HEAP_IN_PSRAM),1)
subdir-ccflags-y += -DNET_HEAP_IN_PSRAM
endif

ifeq ($(NET_BUF_IN_PSRAM),1)
subdir-ccflags-y += -DNET_BUF_IN_PSRAM
endif

ifeq ($(BEST2002_BOOT_FOR_DPD),1)
subdir-ccflags-y += -DBEST2002_BOOT_FOR_DPD
endif

ifeq ($(OWE_SUPPORT),1)
subdir-ccflags-y += -DCONFIG_SHRINK_EVP
endif

ifeq ($(NETWORK_AGENT_SUPPORT),1)
subdir-ccflags-y += -Inet/wifi_stack/v2/net_agent/
endif

ifeq ($(WIFI_RM_EXTEND_SUPPORT),1)
subdir-ccflags-y += -D__WIFI_RM_EXTEND__
endif

ifeq ($(WIFI_SOFTAP_RECOVERY_SUPPORT),1)
subdir-ccflags-y += -D__WIFI_SOFTAP_RECOVERY__
endif

ifeq ($(DEFAULT_BSS_IN_PSRAM),1)
subdir-ccflags-y += -DDEFAULT_BSS_IN_PSRAM
endif
