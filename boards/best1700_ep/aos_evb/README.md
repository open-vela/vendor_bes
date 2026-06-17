# BEST1700 AOS EVB

[ English | [简体中文](README_zh-cn.md) ]

This board package provides the open-vela board support files for the
BEST1700 AOS EVB AP/APC1 library release.

## Supported Features

- Wi-Fi
- eMMC
- RM69330 DSI display
- TMA525C touch panel
- USB serial console

## Console

The serial console is exposed through the USB port.

Connect the board to the host over USB and open the enumerated serial device
with the console settings used by the target image.

## Configurations

This release branch supports library mode only.

Available board configurations:

- `configs/ap`
- `configs/apc1`

The AP configuration enables the released AP board wrapper and BSP archives.
The APC1 configuration enables the released APC1 board wrapper and BSP
archives.

## Library Payload

The board and chip implementation is provided mainly through prebuilt static
archives under the configuration directories:

- `configs/ap/libbesboard_ap.a`
- `configs/ap/libbeschip_ap.a`
- `configs/ap/libnx_bestbsp_ap.a`
- `configs/apc1/libbesboard_apc1.a`
- `configs/apc1/libbeschip_apc1.a`
- `configs/apc1/libnx_bestbsp_apc1.a`

The source files kept in this branch are limited to the AP/APC1 board entry
wrappers and build glue needed to consume those libraries.

## Third-Party Notices

The released static archives include third-party components. Distributions of
this board package should include:

- `THIRD_PARTY_NOTICES`

## Build

Use the normal open-vela build entry points for the corresponding AP/APC1
configuration.

Example AP build from the open-vela repository root:

```bash
./1700_ap.sh
```
