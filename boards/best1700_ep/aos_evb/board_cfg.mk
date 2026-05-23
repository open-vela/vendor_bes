#board_cfg.mk
#configs will shared with every core or subsys

export CHIP_HAS_WIFI       := 0
export NEW_NV_RECORD_ENABLED := 1

ifeq ($(CONFIG_TZ_ENABLE),y)
export RAM_S_SIZE := 0x20000
export FLASH_S_SIZE := 0x300000
export PSRAM_S_SIZE := 0x200000
endif

#SRAM mem layout

#PSRAM mem layout
ifeq ($(CONFIG_BES1700_ZE7_EVB),y)
export PSRAM_SIZE := 0x4000000
else
export PSRAM_SIZE := 0x2000000
endif

#($(HIFI4_PSRAM_SIZE)+$(CONFIG_PSRAM_OFFSET)+$(CONFIG_PSRAM_SIZE) <= $(PSRAM_SIZE))
export HIFI4_PSRAM_SIZE := 0x400000
export HIFI4_PSRAM_BASE := SYS_PSRAM0_BASE+PSRAM_SIZE-HIFI4_PSRAM_SIZE

#SHARED mem layout

#GPIO layout

#cflags for nuttx code
