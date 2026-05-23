#export JTAG_SENS := 1
#export JTAG_BTH := 1
#export MCU_HIGH_PERFORMANCE_MODE := 1

include config/nx_bestbsp_base/nuttx_cfg.mk

ifeq ($(CONFIG_BES_WITHOUT_SPEECH),y)
SPEECH_LIB := 0
endif

ifeq ($(CONFIG_FLASH_DUAL_CHIP),y)
export FLASH_DUAL_CHIP := 1
# close when bootloader
export FLASH_DUAL_CHIP_INIT_ON := 1
# close except bootloader
export OTA_BOOT_TO_DUAL_CHIP := 1
endif

ifeq ($(CONFIG_RECOVERY_SUPPORT),y)
# if FLASH_DUAL_CHIP
#bootloader must build with CONFIG_WITHOUT_OS and size fix to 0x40000
#bl2 may used and build with full OS
# else
#bootloader can build with full OS or WITHOUT_OS and size fix to 0x40000
# endif
ifeq ($(CONFIG_GEN_RECOVERY_BIN),y)
export OTA_CODE_OFFSET := $(CONFIG_RECOVERY_BIN_SIZE)
export OTA_BOOT_OFFSET := 0x40000
export OTA_BOOT_SIZE := $(CONFIG_BIN_FLASH_SIZE)
export OTA_BOOT_INFO_OFFSET := $(OTA_BOOT_OFFSET)+$(OTA_BOOT_SIZE)+$(OTA_BOOT_SIZE) # bootloader + ota + otabackup

export NO_CP := 1
export LARGE_RAM := 1
export AUDIO_PROCESS_IN_CP := 0
SPEECH_LIB  ?= 0
KBUILD_CPPFLAGS += -D__BES_OTA_MODE__=1
FLASH_REMAP ?= 1
KBUILD_CPPFLAGS += -D__BOOT_SELECT=1
EXT_SRC_DIR += rtos/nuttx/ota_boot_secboot/
ifneq ($(CONFIG_PSRAM_BUILD),y)
export BOOT_LOADER_PRE_INIT_HOOK := 1
endif
export OTA_BOOT_TO_DUAL_CHIP := 0
else  ## CONFIG_GEN_RECOVERY_BIN=
ifeq ($(CONFIG_GEN_BOOTLOADER_BIN),y)
export NO_REPO_INFO := 1
export WIFI_CALI_ENABLE := 0
export NO_BT_DRIVER := 1
KBUILD_CPPFLAGS += -DNO_BT_DRIVER
export OTA_BOOT_OFFSET := 0
export OTA_BOOT_SIZE := $(CONFIG_BIN_FLASH_SIZE)
export OTA_CODE_OFFSET := 0x40000
export LARGE_RAM := 1
export AUDIO_PROCESS_IN_CP := 0
export CALIB_SLOW_TIMER := 1
export RTC_CALENDAR := 0
export RTC_ENABLE := 1
KBUILD_CPPFLAGS += -D__BES_OTA_MODE__=1
SPEECH_LIB  ?= 0
export BT_RAMRUN := 0
export NO_CP := 1
export BOOT_CODE_IN_RAM := 1
export TRACE_CODE_IN_RAM := 1
KBUILD_CPPFLAGS += -D__BOOT_SELECT=1
ifeq ($(CONFIG_WITHOUT_OS),y)
FLASH_REMAP ?= 1
DEBUG_PORT := 1
export FLASH_DUAL_CHIP_INIT_ON := 0
export NORFLASH_API_FLUSH_IN_SLEEP_HOOK := 1
export OTA_BOOT_INFO_OFFSET := $(CONFIG_RECOVERY_BIN_SIZE)-0x10000
export OTA_BOOT_INFO_SECTION_SIZE := 0x10000
EXT_SRC_DIR += rtos/nuttx/ota_boot_secboot/
else
export OTA_CODE_OFFSET := $(CONFIG_RECOVERY_BIN_SIZE)
ifeq ($(CONFIG_FLASH_DUAL_CHIP),y)
export OTA_BOOT_OFFSET := 0x40000
export OTA_BOOT_TO_DUAL_CHIP := 0
endif
endif
else
export OTA_BOOT_TO_DUAL_CHIP := 0
export OTA_CODE_OFFSET := $(CONFIG_RECOVERY_BIN_SIZE)
endif ## CONFIG_GEN_BOOTLOADER_BIN=y
endif ## CONFIG_GEN_RECOVERY_BIN=y
endif ## CONFIG_RECOVERY_SUPPORT=y

$(info FLASH_DUAL_CHIP_INIT_ON = $(FLASH_DUAL_CHIP_INIT_ON))
$(info OTA_BOOT_TO_DUAL_CHIP = $(OTA_BOOT_TO_DUAL_CHIP))

ifeq ($(CONFIG_ARCH_HAVE_TRUSTZONE),y)
export RAM_S_SIZE ?= 0x1A0000
export FLASH_S_SIZE ?= 0x300000
export PSRAM_S_SIZE ?= 0x200000
export TZ_TRIGGER := 1
export BT_RAMRUN := 0
KBUILD_CPPFLAGS += -DFLASH_S_SIZE=$(FLASH_S_SIZE)
KBUILD_CPPFLAGS += -DPSRAM_S_SIZE=$(PSRAM_S_SIZE)
KBUILD_CPPFLAGS += -DRAM_S_SIZE=$(RAM_S_SIZE)

ifeq ($(CONFIG_ARCH_TRUSTZONE_SECURE),y)
export AUDIO_PROCESS_IN_CP := 0
export ARM_CMSE := 1
KBUILD_CPPFLAGS += -DCP_BUILD
EXT_SRC_DIR += platform/drivers/mpc/
ifneq ($(CONFIG_RECOVERY_BIN_SIZE),)
KBUILD_CPPFLAGS += -DFLASH_REGION_SIZE=$(FLASH_S_SIZE)-$(CONFIG_RECOVERY_BIN_SIZE)
else
KBUILD_CPPFLAGS += -DFLASH_REGION_SIZE=$(FLASH_S_SIZE)
endif
endif

ifeq ($(CONFIG_ARCH_TRUSTZONE_NONSECURE),y)
export OTA_CODE_OFFSET := $(FLASH_S_SIZE)
export ARM_CMNS := 1
KBUILD_CPPFLAGS += -DCP_BOOT
endif

else
export ARM_CMSE := 0
export ARM_CMNS := 0
export RAM_S_SIZE := 0
export FLASH_S_SIZE := 0
export PSRAM_S_SIZE := 0
endif


ifneq ($(OTA_CODE_OFFSET),)
KBUILD_CPPFLAGS += -DOTA_CODE_OFFSET=$(OTA_CODE_OFFSET)
endif

ifeq ($(CONFIG_BES_RPTUN_AP2SENS),y)
export SENSOR_HUB := 1
export SENSOR_HUB_TGT := vela_sensor
export SENS_TRC_TO_MCU := 1
else
export SENSOR_HUB := 0
endif

ifeq ($(CONFIG_BES_RPTUN_AP2DSP),y)
export DSP_BIN_BASE := $(CONFIG_DSP_BIN_ADDRESS)
ifeq ($(CONFIG_PSRAM_ENABLE),y)
export DSP_BOOT_FROM_PSRAM ?= 1
endif
endif

# if ap2sens not defined, app start sensor hub and ipc use core-brdige are an option
ifneq ($(CONFIG_BES_RPTUN_AP2SENS),y)
export APSENS_IPC_USE_COREBRIDGE ?= 1
endif

ifeq ($(CONFIG_BES_RPTUN_AP2SENS),y)
ifneq ($(CONFIG_SENS_BIN_ADDRESS),0)
export SENS_LOAD_FLASH_ADDR := $(CONFIG_SENS_BIN_ADDRESS)
export SENS_LOAD_FLASH_SIZE := $(CONFIG_SENS_BIN_SIZE)
endif
endif

ifeq ($(CONFIG_BES_RPTUN_AP2CP),y)
ifeq ($(CONFIG_BES_CP_BIN_FLASH_BOOT),y)
export BTH_FLASH_BOOT		:= 1
export SYS_USE_BTH_FLASH	:= 1
else
KBUILD_CPPFLAGS += -DBTH_LOAD_FLASH_ADDR=$(CONFIG_CP_SUBSYS_BIN_ADDRESS)
KBUILD_CPPFLAGS += -DBTH_LOAD_FLASH_SIZE=$(CONFIG_CP_SUBSYS_BIN_SIZE)
endif
EXT_SRC_DIR += platform/drivers/bt_host/
endif

ifeq ($(CONFIG_POWERKEY_ONOFF),1)
KBUILD_CPPFLAGS += -DCHECK_PWRKEY_AT_BOOT -D__POWERKEY_CTRL_ONOFF_ONLY__
endif

ifeq ($(CONFIG_BES_RPTUN_RPMSG_PMU),y)
export RPMSG_PMU := 1
export RPMSG_PMU_SERVER := 1
endif

ifeq ($(CONFIG_BES_RPTUN_RPMSG_USBPHY),y)
export RPMSG_USBPHY := 1
export RPMSG_USBPHY_SERVER := 1
endif

ifeq ($(CONFIG_BES_RPTUN_RPMSG_BESPHY_RF),y)
export RPMSG_BESPHY_RF := 1
export RPMSG_BESPHY_RF_CLIENT := 1
export RPMSG_BESPHY_RF_SERVER_NAME := apc1
endif

ifeq ($(CONFIG_BES_RPTUN_RPMSG_SYSFREQ),y)
export RPMSG_SYSFREQ := 1
export RPMSG_SYSFREQ_SERVER := 1
endif

ifeq ($(CONFIG_BES_RPTUN_RPMSG_FACTORY),y)
export RPMSG_FACTORY := 1
export RPMSG_FACTORY_SERVER := 1
ifneq ($(filter 1,$(WIFI_APP_SUPPORT) $(WIFI_CONN_BESPHY_RF_CLIENT_SUPPORT)),)
export AIOT_FACTORY_EN := 1
ifeq (,$(filter services/aiot/factory/,$(core-y)))
EXT_SRC_DIR += services/aiot/factory/
endif
endif # WIFI_APP_SUPPORT
endif

ifeq ($(FACTORY_SECTION_ENABLE),1)
ifeq (,$(filter services/nv_section/,$(EXT_SRC_DIR)))
EXT_SRC_DIR += services/nv_section/
endif
endif

ifeq ($(CONFIG_BES_RPTUN_RPMSG_NVRECORD),y)
    export RPMSG_NVRECORD := 1
    export RPMSG_NVRECORD_SERVER := 1
endif

ifeq ($(CONFIG_PSRAM_BUILD),y)
    LDS_FILE := best1000_psram.lds
    export FLASH_REMAP := 0
    export NO_FLASH_DEFAULT_CALIB := 1
    # export FACTORY_SECTION_SIZE := 0x0
    export NO_PSRAM_INIT := 1
    export NO_APSRAM_INIT := 1
    export NO_NORFLASH_DRV := 1
    export NORFLASH_API_ENABLE := 0
    KBUILD_CPPFLAGS += -DPSRAM_FLASH_REGION_BASE=$(CONFIG_PSRAM_BUILD_BASE)
    KBUILD_CPPFLAGS += -DPSRAM_FLASH_REGION_SIZE=$(CONFIG_PSRAM_BUILD_SIZE)
endif

ifeq ($(CONFIG_BES_SECOND_FLASH),y)
export NO_FLASH_DEFAULT_CALIB := 1
endif

export WIFI_CALI_ENABLE ?= 1
ifeq ($(WIFI_CALI_ENABLE), 1)
export PMU_NTC_MONITOR := 1
endif
KBUILD_CPPFLAGS += -DWIFI_CALI=$(WIFI_CALI_ENABLE)

ifeq ($(CONFIG_BES_NAND_FLASH),y)
export MCU_HIGH_PERFORMANCE_MODE := 0
export NANDFLASH_ENABLE := 1
export ULTRA_LOW_POWER := 1
export OSC_26M_X4_AUD2BB := 1
export NAND_IOMUX_INDEX := 40
export FLASH_QSPI_ENABLE := 1
export FLASH_DMA ?= 0
#KBUILD_CPPFLAGS += -DNANDFLASH_HIGH_SPEED
EXT_SRC_DIR += platform/drivers/nandflash/
endif

ifeq ($(CONFIG_ARCH_CHIP_BES1600),y)
export DSIPLL_MHZ := 480
export BBPLL_MHZ := 400
export RTC_ENABLE := 1
KBUILD_CPPFLAGS += -DRTC_ENABLE
ifeq ($(CONFIG_BES1600_OTA),y)
include config/nx_best1600_ota/target.mk
endif
ifeq ($(CONFIG_BES1600_AP),y)
export SENS_TRC_TO_MCU := 0
include config/nx_bestbsp_base/nx_best1600_m55xip/target.mk
endif
ifeq ($(CONFIG_BES1600_TEE),y)
include config/nx_best1600_tee/target.mk
endif
endif

ifeq ($(CONFIG_BES_WIFI_RPMSG_APC0C1),y)
export WIFI_HOST_RPMSG := 1
KBUILD_CPPFLAGS += -DWIFI_HOST_RPMSG=$(WIFI_HOST_RPMSG)
endif

ifeq ($(CONFIG_ARCH_CHIP_BES1605),y)
export DSIPLL_MHZ := 384
export LCDCPIX_MHZ := 24
export BBPLL_MHZ := 384
export RTC_CALENDAR := 1
export RTC_ENABLE := 0
export CHIP_HAS_JPEG := 1
export SERVICE_OVERLAY := 0

include config/best1605/bt_config.mk

ifeq ($(CONFIG_BES_RPTUN_AP2DSP_MASTER), y)
    export CHIP_HAS_HIFI4 := 1
    export DSP_BIN_BASE := $(CONFIG_DSP_BIN_ADDRESS)
    export DSP_HIFI4_TRC_TO_MCU := 1
else
    export CHIP_HAS_HIFI4 := 0
    export DSP_HIFI4_TRC_TO_MCU ?= 0
endif

ifeq ($(CONFIG_BES_RPTUN_AP2BTH_MASTER), y)
    export BT_HOST := 1
    export BTH_FLASH_BOOT := 1
else
    export BT_HOST := 0
endif
include config/nx_bestbsp_base/nx_best1605_base/target.mk
endif # CONFIG_ARCH_CHIP_BES1605

ifeq ($(CONFIG_ARCH_CHIP_BES1702),y)
export RTC_ENABLE := 0
export RTC_CALENDAR := 1

ifeq ($(CONFIG_OTA_SERVER),y)
export NUTTX_BLE_OTA ?= 1
KBUILD_CPPFLAGS += -DNUTTX_BLE_OTA
endif

include config/best1702/mem_cfg.mk
include config/nx_bestbsp_base/nx_best1702_base/target.mk
    include config/best1702/bt_config.mk

endif

ifeq ($(CONFIG_ARCH_CHIP_BES1607),y)
    export RTC_ENABLE := 0
    export RTC_CALENDAR := 1
    export CHIP_HAS_EMMC := 0

    ifeq ($(CONFIG_OTA_SERVER),y)
        export NUTTX_BLE_OTA ?= 1
        KBUILD_CPPFLAGS += -DNUTTX_BLE_OTA
    endif

    ifeq ($(CONFIG_BLUETOOTH_TOTA),y)
        export NUTTX_BLUETOOTH_TOTA ?= 1
        KBUILD_CPPFLAGS += -DNUTTX_BLUETOOTH_TOTA
    endif

    include config/best1607/mem_cfg.mk
    include config/nx_bestbsp_base/nx_best1607_m55xip/target.mk
    include config/nx_bestbsp_base/nx_best1607_base/target.mk
    include config/best1607/bt_config.mk

    ifeq ($(WIFI_APP_SUPPORT),1)
        export WIFI_BT_COEX_SUPPORT ?= 1
        export WIFI_BT_COEX_VER ?= 2
        include config/wifi6/wifi_bt_coex.mk
    endif
endif

ifeq ($(CONFIG_ARCH_CHIP_BES1700),y)
export DSIPLL_MHZ := 400
export SYS_USE_BBPLL := 0
export RTC_CALENDAR ?= 1
export RTC_ENABLE ?= 0
export ISPI_ACCESS_IN_SAME_SUBSYS := 1

ifeq ($(CONFIG_BES_PMU_WIFI_RF_POWER),y)
export PMU_WIFI_BUILD ?= 1
endif

ifeq ($(WIFI_APP_SUPPORT),1)
export WIFI_BT_COEX_SUPPORT ?= 1
export WIFI_BT_COEX_VER ?= 2
include config/wifi6/wifi_bt_coex.mk
endif

ifeq ($(CONFIG_OTA_SERVER),y)
export NUTTX_BLE_OTA ?= 1
KBUILD_CPPFLAGS += -DNUTTX_BLE_OTA
endif

ifeq ($(CONFIG_BLUETOOTH_TOTA),y)
export NUTTX_BLUETOOTH_TOTA ?= 1
KBUILD_CPPFLAGS += -DNUTTX_BLUETOOTH_TOTA
endif

# ========
# MEM_CFG
# ========
ifeq ($(CONFIG_BES1700_A9_EVB), y)
    export MEM_CFG_OPT := OPT_HP
else
    export MEM_CFG_OPT := OPT_NUTTX
endif
include config/best1700/mem_cfg_watch.mk

ifeq ($(CONFIG_PSRAM_ENABLE), y)
    export PSRAM_1V2_ENABLE ?= 1
endif

include config/best1700/bt_config.mk
include config/nx_bestbsp_base/nx_best1700_m55/target.mk
export NO_BT_DRIVER := 1
ifeq ($(CONFIG_LCDC_USE_QSPI),y)
export QSPILCD0_IOMUX_INDEX := 60
endif
endif

ifeq ($(CONFIG_ARCH_CHIP_BES3601),y)
export DSIPLL_MHZ := 400
export SYS_USE_BBPLL := 0
export RTC_CALENDAR ?= 1
export RTC_ENABLE ?= 0

include config/nx_bestbsp_base/nx_best3601_m52xip/target.mk

ifeq ($(CONFIG_LCDC_USE_QSPI),y)
export QSPILCD0_IOMUX_INDEX := 60
endif

endif # CONFIG_ARCH_CHIP_BES3601

ifeq ($(CONFIG_ARCH_CHIP_BES3601P),y)
export RTC_CALENDAR := 1
export RTC_ENABLE := 0
    include config/nx_bestbsp_base/nx_best3601p_base/target.mk
endif # CONFIG_ARCH_CHIP_BES3601P

ifeq ($(CONFIG_ARCH_CHIP_BES1502X),y)
export RTC_ENABLE := 1
KBUILD_CPPFLAGS += -DRTC_ENABLE
ifeq ($(CONFIG_ARCH_BOARD_CUSTOM_BES1502X_TWS_EVB),y)
include config/best1502x_ibrt_anc/target.mk
else
export FLASH_SIZE := 0x800000
ifeq ($(CONFIG_BES_RPTUN_AP2SENS),y)
export SENS_FLASH_BOOT := 1
else
ifeq ($(CHIP),best1503)
export RAM_SIZE := 0x140000
else
export RAM_SIZE := 0x200000
endif
endif
export USE_DSI_PLL := 1
ifeq ($(CONFIG_DSIPHY_OUTFMT_RGB565),y)
export DSIPLL_MHZ := 320
export BBPLL_MHZ := 384
endif
ifeq ($(CONFIG_BES_RPTUN_AP2DSP),y)
export CHIP_HAS_CP  := 1
export CP_AS_SUBSYS := 1
export CP_SUBSYS_TRC_TO_MCU := 1
KBUILD_CPPFLAGS += -DCP_SUBSYS_TRC_TO_MCU
export CP_SUBSYS_LOAD_FLASH_ADDR := $(CONFIG_DSP_BIN_ADDRESS)
export CP_SUBSYS_LOAD_FLASH_SIZE := $(CONFIG_DSP_BIN_SIZE)
endif
include config/best1502x_ibrt/target.mk
endif
endif

ifeq ($(CONFIG_ARCH_CHIP_BES1502P),y)
    export UTILS_HWTIMER_LIST_ENABLE := 1
    export UTILS_HEAP_ENABLE := 1
    export UTILS_CRC_ENABLE := 1
    export UTILS_KFIFO_ENABLE := 1

    ifeq ($(CONFIG_OTA_SERVER),y)
        export NUTTX_BLE_OTA ?= 1
        KBUILD_CPPFLAGS += -DNUTTX_BLE_OTA
    endif

    ifeq ($(CONFIG_BES_RPTUN_AP2SENS_MASTER),y)
        export SENSOR_HUB := 1
        export SENS_TRC_TO_MCU := 0
        ifeq ($(CONFIG_BES_SENS_BIN_FLASH_BOOT),y)
            export SENS_FLASH_BOOT := 1
            export SENS_FLASH_BOOT_STRUCT_ADDR := $(CONFIG_SENS_BIN_ADDRESS)
        else
            export SENS_LOAD_FLASH_ADDR := $(CONFIG_SENS_BIN_ADDRESS)
            export SENS_LOAD_FLASH_SIZE := $(CONFIG_SENS_BIN_SIZE)
        endif
    endif

    ifeq ($(CONFIG_BES_RPTUN_AP2DSP_MASTER),y)
        export CHIP_HAS_CP := 1
        export CP_AS_SUBSYS := 1
        export CP_SUBSYS_TRC_TO_MCU := 1
        export CP_SUBSYS_LOAD_FLASH_ADDR := $(CONFIG_DSP_BIN_ADDRESS)
        export CP_SUBSYS_LOAD_FLASH_SIZE := $(CONFIG_DSP_BIN_SIZE)
        ifneq ($(RAM_REGION_OFFSET),)
            KBUILD_CPPFLAGS += -DRAM_REGION_OFFSET=$(RAM_REGION_OFFSET)
        endif
    endif

    export RTC_CALENDAR := 1
    export RTC_ENABLE := 0
    export UTILS_CQUEUE_EN ?= 1
    export DSIPLL_MHZ ?= 480
    export PSRAM_ENABLE ?=1
    export PSRAM_SIZE := 0x2000000
    export PSRAM_CLASSIFY ?= XOPI
    export PSRAM_SPEED ?= 200
    export PSRAM_X8_MODE ?= 1
    export FAST_XRAM_SECTION_SIZE := 0x1000
    export NO_BT_DRIVER ?=1
    export NO_SLEEP ?=1
    export BT_LOG_POWEROFF ?=0
    export BT_SOURCE ?= 0
    include config/nx_bestbsp_base/nx_best1502p_base/target.mk
endif

ifeq ($(CONFIG_ARCH_CHIP_BES1503),y)
export PSRAM_ENABLE ?= 1
export PSRAM_SIZE ?= 0x1000000
export PSRAM_SPEED ?= 200
export PSRAM_XCCELA_MODE := 1
export UTILS_HWTIMER_LIST_ENABLE := 1
export USERDATA_SECTION_ENABLE ?= 1
export FACTORY_SECTION_ENABLE  ?= 1
export UTILS_CRC_ENABLE          ?= 1
export UTILS_HEAP_ENABLE        ?= 1

ifeq ($(CONFIG_OTA_SERVER),y)
export NUTTX_BLE_OTA ?= 1
KBUILD_CPPFLAGS += -DNUTTX_BLE_OTA
endif

include config/nx_bestbsp_base/nx_best1503_base/target.mk
export FAST_XRAM_SECTION_SIZE := 0x15000
ifeq ($(CONFIG_BES_RPTUN_AP2DSP_MASTER),y)
override export RAMCP_SIZE   :=
override export RAMCPX_SIZE  :=
export CHIP_HAS_CP  := 1
export CP_AS_SUBSYS := 1
ifeq ($(CONFIG_DSP_BIN_ADDRESS), 0x0)
export INCLUDE_CP_SUBSYS_BIN := 1
else
export CP_SUBSYS_LOAD_FLASH_ADDR := $(CONFIG_DSP_BIN_ADDRESS)
export CP_SUBSYS_LOAD_FLASH_SIZE := $(CONFIG_DSP_BIN_SIZE)
endif
endif

endif

ifeq ($(CONFIG_ARCH_CHIP_BES1503P),y)
export PSRAM_ENABLE ?= 1
export PSRAM_SIZE ?= 0x1000000
export PSRAM_SPEED ?= 200
export PSRAM_XCCELA_MODE := 1
include config/best1503p_ibrt/target.mk
ifeq ($(CONFIG_BES_RPTUN_AP2DSP_MASTER),y)
export CHIP_HAS_CP  := 1
export CP_AS_SUBSYS := 1
export CP_SUBSYS_LOAD_FLASH_ADDR := $(CONFIG_DSP_BIN_ADDRESS)
export CP_SUBSYS_LOAD_FLASH_SIZE := $(CONFIG_DSP_BIN_SIZE)
endif
endif

ifeq ($(CONFIG_ARCH_CHIP_BES1501P),y)
include config/best1501p_ibrt/target.mk
endif

ifeq ($(CONFIG_ARCH_CHIP_BES1306),y)
export USE_BASIC_THREADS := 0
include config/best1306_ibrt/target.mk
endif

ifeq ($(CONFIG_ARCH_CHIP_BES1306P),y)
export PSRAM_ENABLE ?= 0
export PSRAM_SIZE ?= 0x800000
export PSRAM_SPEED ?= 200
export PSRAM_CLASSIFY := OPI
export USE_BASIC_THREADS := 0
export RTC_CALENDAR := 1
export RTC_ENABLE := 0

ifeq ($(CONFIG_OTA_SERVER),y)
export NUTTX_BLE_OTA ?= 1
KBUILD_CPPFLAGS += -DNUTTX_BLE_OTA
endif

include config/nx_bestbsp_base/nx_best1306p_base/target.mk
export FAST_XRAM_SECTION_SIZE ?= 0x1000
ifeq ($(CONFIG_BES_RPTUN_AP2DSP_MASTER),y)
override export RAMCP_SIZE   :=
override export RAMCPX_SIZE  :=
export CHIP_HAS_CP  := 1
export CP_AS_SUBSYS := 1
ifeq ($(CONFIG_DSP_BIN_ADDRESS), 0x0)
export INCLUDE_CP_SUBSYS_BIN := 1
else
export CP_SUBSYS_LOAD_FLASH_ADDR := $(CONFIG_DSP_BIN_ADDRESS)
export CP_SUBSYS_LOAD_FLASH_SIZE := $(CONFIG_DSP_BIN_SIZE)
endif
endif

ifeq ($(CONFIG_WITHOUT_OS),y)
export AUDIO_OUTPUT_DC_AUTO_CALIB := 0
endif

export UTILS_INTERSYSHCI_ENABLE  := 0
export UTILS_HEAP_ENABLE         ?= 1
export UTILS_CQUEUE_ENABLE       ?= 1
export UTILS_CRC_ENABLE          ?= 1
export UTILS_KFIFO_ENABLE        ?= 1
ifneq ($(CONFIG_WITHOUT_OS),y)
export UTILS_LIST_ENABLE         ?= 1
endif
export UTILS_HWTIMER_LIST_ENABLE ?= 1
export UTILS_HEXDUMP_ENABLE      ?= 1

export FACTORY_SECTION_ENABLE ?= 1
export USERDATA_SECTION_ENABLE ?= 1

endif

ifeq ($(CONFIG_ARCH_CHIP_BES2009),y)
export LOAD_LINUX := 1
export DDRPLL_MHZ := 800
export DDR_BOOT_INIT := 0
export AP_BOOTLOADER_IN_FLASH := 1
export AP_BOOTLOADER_IN_EMMC  := 0
ifeq ($(CONFIG_JTAG_ENABLE),y)
export JTAG_ENABLE := 1
export JTAG_TDI_TDO_PIN := 1
export JTAG_RESET_PIN := 1
export SYS_USE_SDMMC_DEVICE := 0
export JTAG_TO_AP := 1
else
export SYS_USE_SDMMC_DEVICE := 1
endif
ifeq ($(CONFIG_USBDEV),y)
export SYS_USE_USB_DEVICE := 0
endif
export PDC_DRV := 0
export NET_HEAP_IN_PSRAM := 0
export SW_IIR_EQ_PROCESS := 0
export RTC_ENABLE := 1
ifeq ($(RTC_ENABLE),y)
KBUILD_CPPFLAGS += -DRTC_ENABLE
endif
export CHIP_HAS_EMMC := 1
include config/best2009_ep/target.mk
ifeq ($(CONFIG_USE_BES_BT_STACK),y)

else
export FAST_XRAM_SECTION_SIZE := 0x13000
endif
endif

########CONFIG_BES_CORE_AP-1701########
ifeq ($(CONFIG_ARCH_CHIP_BES1701),y)
    export RTC_ENABLE := 1
    export CHIP_HAS_DDR := 1
    export DDR_ENABLE := 1
    include config/nx_bestbsp_base/nx_best1701_base/target.mk
endif

ifeq ($(CONFIG_ARCH_CHIP_BES2005),y)
export NET_HEAP_IN_PSRAM := 0
export SW_IIR_EQ_PROCESS := 0
include config/best2005_ep/target.mk
ifeq ($(CONFIG_USE_BES_BT_STACK),y)
else
export FAST_XRAM_SECTION_SIZE := 0x13000
endif
endif

ifeq ($(CONFIG_ARCH_CHIP_BES2003),y)
export TX_PULLING_CAL := 0
ifeq ($(CONFIG_USE_BES_BT_STACK),y)
export NET_HEAP_IN_PSRAM := 0
else
export FAST_XRAM_SECTION_SIZE := 0x13000
export NET_HEAP_IN_PSRAM := 1
endif
export SW_IIR_EQ_PROCESS := 1
export RTC_ENABLE := 1
KBUILD_CPPFLAGS += -DRTC_ENABLE
export RAMV_EN := 1


include config/best2003_ep/target.mk
ifeq ($(CONFIG_GEN_BOOTLOADER_BIN)-$(CONFIG_GEN_RECOVERY_BIN),-)
include config/best2003/wifi.mk
include config/best2003/wifi_bt_coex.mk
endif

export UTILS_INTERSYSHCI_ENABLE  := 0
export UTILS_HEAP_ENABLE         ?= 1
export UTILS_CQUEUE_ENABLE       ?= 1
export UTILS_CRC_ENABLE          ?= 1
export UTILS_KFIFO_ENABLE        ?= 1
ifneq ($(CONFIG_WITHOUT_OS),y)
export UTILS_LIST_ENABLE         ?= 1
endif
export UTILS_HWTIMER_LIST_ENABLE ?= 1
export UTILS_HEXDUMP_ENABLE      ?= 1

export FACTORY_SECTION_ENABLE ?= 1
export USERDATA_SECTION_ENABLE ?= 1

endif

ifeq ($(CONFIG_ARCH_CHIP_BES2001),y)
include config/best2001_ep/target.mk
endif

ifeq ($(FLASH_REMAP),1)
export OTA_REMAP_OFFSET ?= 0x80000
KBUILD_CPPFLAGS += -DOTA_REMAP_OFFSET=$(OTA_REMAP_OFFSET)
KBUILD_CPPFLAGS += -DOTA_BOOT_OFFSET=$(OTA_BOOT_OFFSET)
KBUILD_CPPFLAGS += -DFLASH_REMAP
endif

ifeq ($(CONFIG_BES_NO_CP),y)
export NO_CP := 1
endif

ifeq ($(CONFIG_BES_BQBTEST_ENABLE),y)
KBUILD_CPPFLAGS += -DBQBTEST_ENABLE
endif

export NET_COZE_SUPPORT ?= 0
ifeq ($(NET_COZE_SUPPORT),1)
export NET_MBEDTLS_CLIENT_SUPPORT := 1
export NET_LIBRWS_SUPPORT := 1
export LIBRWS_USE_LIST := 0
KBUILD_CPPFLAGS += -DNET_COZE_SUPPORT
export LIBRWS_MIN_RECV_SIZE ?= 0x200000
ifneq ($(LIBRWS_MIN_RECV_SIZE),)
KBUILD_CPPFLAGS += -DLIBRWS_MIN_RECV_SIZE=$(LIBRWS_MIN_RECV_SIZE)
endif
endif #NET_COZE_SUPPORT

ifeq ($(USB_HOST),1)
EXT_SRC_DIR += services/fs/plat_drv/usbhost_mass/
EXT_SRC_DIR += services/usb/usb_host/msd/
KBUILD_CPPFLAGS += -DFS_MOUNT_DIR=\"/usb\"
endif

ifeq ($(CONFIG_GRAPHICS_LVGL),y)
ifneq ($(wildcard thirdparty/lvgl/Makefile),)
EXT_SRC_DIR += thirdparty/lvgl/
endif
endif

core-y := $(filter-out $(EXT_SRC_DIR), $(core-y))
core-y += $(EXT_SRC_DIR)
EXT_SRC_DIR :=
