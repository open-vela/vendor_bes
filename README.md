# BES Chip Vendor Support for openvela

[ English | [简体中文](README_zh-cn.md) ]

## Introduction

This repository contains chip support, board configurations, and hardware drivers from BES Technology for the openvela operating system. BES Technology is a leading semiconductor company specializing in wireless connectivity and audio solutions for AIoT applications.

This solution is provided by **Fortune Technology**, offering complete hardware and software integration for wearable and IoT devices.

## Repository Structure

```
vendor/bes/
├── chips/           # BES chip support and hardware abstraction layer
│   ├── bes/        # BES chip series (Cortex-M based, e.g., BES2600)
│   └── besa7/      # BES A7 chip series (Cortex-A based, not covered here)
├── boards/          # Board-specific configurations
│   └── best2003_ep/ # BEST2003 Evaluation Platform (for BES2600 chip)
└── drivers/         # BES-specific device drivers
```

## Supported Hardware

### BES2600WM-AX4F

**BES2600WM-AX4F** is a highly integrated SoC designed for wearable and IoT devices, featuring:

- **Processor**: ARM Cortex-M architecture based
- **Wireless Connectivity**: Integrated Bluetooth support
- **Audio Processing**: Advanced audio subsystem with multiple interfaces
- **Display Support**: LCD controller with DSI interface
- **Power Management**: Low-power design optimized for wearables
- **Applications**: Smart watches, fitness bands, smart speakers, headphones, smart home devices, and robots

### Development Board

**BES2600WM MAIN BOARD V1.1**

The official BES2600WM evaluation board provides a complete development and evaluation environment.

#### Chip Compatibility

The development board supports multiple BES2600 series chip variants, selected via jumper caps:
- **AX4D & GX6D**: Select AX4D jumper
- **AX4F**: Select AX4F jumper (the variant supported by this repository)

#### Power System

- **USB Interfaces**:
  - Type-C programming and power interface (standard 5V/800mA or above)
  - Onboard DCDC converts to 3.6V power supply
  - Type-C USB interface (5V/800mA or above)
  
- **Power Selection**:
  - Select 5V (VBUS) or 3.6V (3V6) input via jumper cap
  - Default configuration: Type-C powered, jumper set to 3.6V

- **I/O Level Selection**:
  - Options: 3.3V, 2.8V, or 1.8V
  - Configured via jumper cap

- **Display Power**:
  - Options: VBAT or 3.6V
  - Default: VBAT

#### Audio System

- **Onboard Microphones**: 3 analog MICs
- **External Microphone Connector**: P2.54 pin header, supports external analog MIC and loopback circuit
- **Audio Amplifier**:
  - Model: Naxinwei NS4150C
  - Rated Output Power: 2.8W (5V/4Ω, THD=10%)
  - Output Connector: 2-pin PH2.0 specification
- **External Amplifier Connector**: P2.54 pin header, supports external amplifier via jumper wires

#### Display Interfaces

- **MIPI LCD**: 30-pin FPC connector, bottom contact, 0.5mm pitch
- **SPI LCD**: 25-pin FPC connector, flip-top, 0.3mm pitch

#### Camera Interface

- **MIPI Camera**: 24-pin FPC connector, bottom contact, 0.5mm pitch

#### Storage

- **TF Card Slot**: Micro-SD card slot with insertion detection
- **eMMC**: Reserved eMMC functionality

#### Buttons

- **SW1**: Power button
- **SW2**: Reset button
- **SW3-SW6**: Button array

#### Other Features

- **IR Transceiver**: Supports infrared communication
- **SPI to Ethernet**: Network expansion functionality
- **MFi Chip**: Supports Apple MFi certification
- **ADC Interface**: ADC connection terminals
- **GPIO Expansion**: Multiple GPIO pin headers for external applications via DuPont wires

#### Debug Interfaces

- **Programming Port**: External programming interface
- **Debug Port**: Debug interface

**Hardware Documentation**: [BES2600WM Main Board Hardware User Guide V1.0 (PDF)](https://www.fortune-co.com/Public/Uploads/ueditor/upload/file/20250801/1754019693187058.pdf)

## Core Features

### Wireless Connectivity
- **Bluetooth**: Native BT/BLE stack support
- **BLE Bridge Mode**: Optimized low-power Bluetooth operation

### Audio Subsystem
- **Multiple Audio Interfaces**:
  - I2S (Master/Slave modes)
  - PCM interfaces (CODEC, BTPCM)
  - Audio DMA (AUDMA) support
- **Smart Audio Amplifier Support**:
  - Awinic AW88266A
  - Cirrus Logic CS35L41B
  - Foursemi FS1818U
- **Audio Processing**:
  - Multi-channel playback and recording
  - HCI audio dump for debugging

### Display and Graphics
- **LCD Controller (LCDC)**:
  - Multi-layer support
  - DSI PHY interface (configurable single/dual lane)
  - Color formats: RGB565, RGB888, ARGB8888
  - DMA2D hardware acceleration
  - TE (Tearing Effect) synchronization
  - ULPS (Ultra Low Power State)

- **Supported LCD Controllers**:
  - RM69090, RM69330, GC9503NP
  - ST7703, ST7701S, ST7796U, ST7785M, ST7797
  - HX8394, A064, JD9165A, JT4007

- **Touch Panel Support**:
  - TMA525C, CHSC6540, CST3240
  - IST415X, Zinitix, FTS

### Sensors and Peripherals
- **I2C**: Multiple ports with configurable pins
- **SPI**: SPI interface
- **UART**: Configurable serial interfaces
- **GPIO**: Rich GPIO support with interrupts
- **ADC**: Battery monitoring, temperature sensors
- **Accelerometer**: LIS2DH sensor support
- **PWM**: RGB LED control
- **Buttons**: ADC-based button support

### Storage
- **Flash**: NAND/NOR Flash support
- **External Storage**: eMMC, SD/MMC (via SPI/SDIO)
- **PSRAM**: High-speed PSRAM support

### Camera
- **CAMSPI**: GC032A sensor
- **CAMCSI**: GC2145 sensor

### Power Management
- **DVFS**: Dynamic Voltage Frequency Scaling
- **RTC**: Real-time clock with calibration
- **Battery Management**: Charging control and monitoring
- **Low Power Modes**: Optimized for battery-powered devices

### Development and Debugging
- **JTAG/SWD**: Hardware debugging support
- **Backtrace**: Stack trace on crash
- **Crash Dump**: System crash analysis

## Integration with openvela

The openvela operating system is an embedded OS tailored for AIoT (Artificial Intelligence of Things) applications, widely used in:
- Smart watches and fitness bands
- Smart speakers
- Headphones
- Smart home devices
- Robots

openvela has been fully adapted for BES chips.

This chip vendor repository integrates seamlessly with openvela through:

1. **Kconfig Integration**: Chip and board configurations accessible via `menuconfig`
2. **Build System**: Integration with NuttX/openvela build infrastructure
3. **Device Drivers**: Standard NuttX driver interfaces
4. **RTOS Support**: Full POSIX compatibility

## Configuration

To configure a BES2600WM-based development board:

```bash
# Example: Configure for BEST2003 development board
./build.sh vendor/bes/boards/best2003_ep/aos_evb/<config_name>

# Or use board:config notation
./build.sh best2003_ep:aos_evb
```

## Hardware Purchase and Consultation

For hardware purchase and technical consultation, please contact Fortune Technology:
- **Email**:
  - branwang@fortune-co.com
  - petermao@fortune-co.com
  - ivanchen.kj@fortune-co.com

## License

```
Copyright 2015-2025 BES.
All rights reserved. All unpublished rights reserved.

No part of this work may be used or reproduced in any form or by any
means, or stored in a database or retrieval system, without prior written
permission of BES.

Use of this work is governed by a license granted by BES.
This work contains confidential and proprietary information of BES.
```

**Note**: This repository contains proprietary code from BES Technology. Please refer to the LICENSE file for complete licensing terms.

## Contributing

For chip vendor-specific changes, please follow BES Technology's internal development process. For openvela integration issues, please refer to the main [openvela Contributing Guide](../../docs/CONTRIBUTING.md).

## Support

- **Fortune Technology** (Hardware Support): Please use the email addresses listed above
- **BES Technology**: Contact your BES representative for chip-specific support
- **openvela Integration**: See [openvela Documentation](../../docs/) or community forums

## Related Resources

- [Fortune Technology - openvela+BES Solution Introduction](https://www.fortune-co.com/Tech/projectDetail/id/64.html)
- [BES2600WM Hardware User Guide (PDF)](https://www.fortune-co.com/Public/Uploads/ueditor/upload/file/20250801/1754019693187058.pdf)
