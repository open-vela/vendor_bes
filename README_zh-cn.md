# BES 芯片厂商对 openvela 的支持

[ [English](README.md) | 简体中文 ]

## 简介

本仓库包含恒玄科技（BES Technology）的芯片支持、开发板配置以及为 openvela 操作系统提供的硬件驱动。恒玄科技是无线连接和音频解决方案领域的领先半导体厂商，专注于 AIoT 应用。

本方案由**润欣科技**提供，为可穿戴设备和物联网设备提供完整的软硬件集成方案。

## 仓库结构

```
vendor/bes/
├── chips/           # BES 芯片支持和硬件抽象层
│   ├── bes/        # BES 芯片系列（基于 Cortex-M，如 BES2600）
│   └── besa7/      # BES A7 芯片系列（基于 Cortex-A，暂不涉及）
├── boards/          # 开发板特定配置
│   └── best2003_ep/ # BEST2003 评估平台（对应 BES2600 芯片）
└── drivers/         # BES 专用设备驱动
```

## 支持的硬件

### BES2600WM-AX4F

**BES2600WM-AX4F** 是一款高度集成的 SoC，专为可穿戴设备和物联网设备设计，具备以下特性：

- **处理器**：基于 ARM Cortex-M 架构
- **无线连接**：集成蓝牙支持
- **音频处理**：先进的音频子系统，支持多种接口
- **显示支持**：带 DSI 接口的 LCD 控制器
- **电源管理**：针对可穿戴设备优化的低功耗设计
- **应用领域**：智能手表、运动手环、智能音箱、耳机、智能家居设备及机器人

### 开发板

**BES2600WM MAIN BOARD V1.1**

BES2600WM 官方评估板，提供完整的开发和评估环境。

#### 芯片兼容性

开发板支持多个 BES2600 系列芯片变体，通过跳线帽选择：
- **AX4D & GX6D**：选择 AX4D 跳帽
- **AX4F**：选择 AX4F 跳帽（本仓库支持的型号）

#### 电源系统

- **USB 接口**：
  - Type-C 烧录及供电接口（标准 5V/800mA 以上）
  - 板载 DCDC 转换为 3.6V 供电
  - Type-C USB 接口（5V/800mA 以上）
  
- **电源选择**：
  - 通过跳线帽选择 5V (VBUS) 或 3.6V (3V6) 输入
  - 默认配置：通过 Type-C 供电，跳帽接 3.6V

- **I/O 电平选择**：
  - 可选 3.3V、2.8V 或 1.8V
  - 通过跳线帽配置

- **显示供电**：
  - 可选 VBAT 或 3.6V
  - 默认使用 VBAT

#### 音频系统

- **板载麦克风**：3 个模拟 MIC
- **外接麦克风端子**：P2.54 排针，支持外接模拟麦克和回采电路
- **音频功放**：
  - 型号：纳芯威 NS4150C
  - 额定输出功率：2.8W (5V/4Ω, THD=10%)
  - 输出端子：2pin PH2.0 规格
- **外接功放端子**：P2.54 排针，支持飞线连接外部功放

#### 显示接口

- **MIPI LCD**：30pin FPC 座，下接，0.5mm pitch
- **SPI LCD**：25pin FPC 座，翻盖，0.3mm pitch

#### 摄像头接口

- **MIPI 摄像头**：24pin FPC 座，下接，0.5mm pitch

#### 存储

- **TF 卡槽**：Micro-SD 卡槽，支持插拔检测
- **eMMC**：预留 eMMC 功能

#### 按键

- **SW1**：Power 按键
- **SW2**：Reset 按键
- **SW3-SW6**：按键阵列

#### 其他功能

- **红外收发器**：支持红外通信
- **SPI 转网卡**：网络扩展功能
- **MFi 认证芯片**：支持苹果 MFi 认证
- **ADC 接口**：ADC 接线端子
- **GPIO 扩展**：多组 GPIO 排针，支持杜邦线外接应用

#### 调试接口

- **软件烧录口**：外接烧录接口
- **Debug 口**：调试接口

**硬件文档**：[BES2600WM 主板硬件用户指南 V1.0 (PDF)](https://www.fortune-co.com/Public/Uploads/ueditor/upload/file/20250801/1754019693187058.pdf)

## 核心特性

### 无线连接
- **蓝牙**：原生 BT/BLE 协议栈支持
- **BLE 桥接模式**：优化的低功耗蓝牙操作

### 音频子系统
- **多种音频接口**：
  - I2S（主/从模式）
  - PCM 接口（CODEC、BTPCM）
  - 音频 DMA（AUDMA）支持
- **智能音频功放支持**：
  - Awinic AW88266A
  - Cirrus Logic CS35L41B
  - Foursemi FS1818U
- **音频处理**：
  - 多声道播放和录音
  - 用于调试的 HCI 音频转储

### 显示与图形
- **LCD 控制器（LCDC）**：
  - 多层支持
  - DSI PHY 接口（可配置单通道/双通道）
  - 颜色格式：RGB565、RGB888、ARGB8888
  - DMA2D 硬件加速
  - TE（撕裂效应）同步
  - ULPS（超低功耗状态）

- **支持的 LCD 控制器**：
  - RM69090、RM69330、GC9503NP
  - ST7703、ST7701S、ST7796U、ST7785M、ST7797
  - HX8394、A064、JD9165A、JT4007

- **触摸面板支持**：
  - TMA525C、CHSC6540、CST3240
  - IST415X、Zinitix、FTS

### 传感器与外设
- **I2C**：多个端口，可配置引脚
- **SPI**：SPI 接口
- **UART**：可配置串行接口
- **GPIO**：丰富的 GPIO（支持中断）
- **ADC**：电池监控、温度传感器
- **加速度计**：LIS2DH 传感器支持
- **PWM**：RGB LED 控制
- **按键**：基于 ADC 的按键支持

### 存储
- **闪存**：NAND/NOR Flash 支持
- **外部存储**：eMMC、SD/MMC（通过 SPI/SDIO）
- **PSRAM**：高速 PSRAM 支持

### 摄像头
- **CAMSPI**：GC032A 传感器
- **CAMCSI**：GC2145 传感器

### 电源管理
- **DVFS**：动态电压频率调节
- **RTC**：带校准的实时时钟
- **电池管理**：充电控制和监控
- **低功耗模式**：针对电池供电设备优化

### 开发与调试
- **JTAG/SWD**：硬件调试支持
- **回溯**：崩溃时的堆栈跟踪
- **崩溃转储**：系统崩溃分析

## 与 openvela 的集成

openvela 操作系统是专为 AIoT（人工智能物联网）领域量身定制的嵌入式操作系统，广泛应用于：
- 智能手表和运动手环
- 智能音箱
- 耳机
- 智能家居设备
- 机器人

openvela 已经在恒玄芯片上完成了完备的适配。

本芯片厂商仓库通过以下方式与 openvela 无缝集成：

1. **Kconfig 集成**：通过 `menuconfig` 访问芯片和开发板配置
2. **构建系统**：与 NuttX/openvela 构建基础设施集成
3. **设备驱动**：标准 NuttX 驱动接口
4. **RTOS 支持**：完全兼容 POSIX

## 配置

配置基于 BES2600WM 的开发板：

```bash
# 示例：为 BEST2003 开发板配置
./build.sh vendor/bes/boards/best2003_ep/aos_evb/<配置名称>

# 或使用 board:config 表示法
./build.sh best2003_ep:aos_evb
```

## 硬件购买和咨询

硬件购买和技术咨询请联系润欣科技：
- **邮箱**：
  - branwang@fortune-co.com
  - petermao@fortune-co.com
  - ivanchen.kj@fortune-co.com

## 许可协议

```
Copyright 2015-2025 BES.
All rights reserved. All unpublished rights reserved.

未经 BES 事先书面许可，不得以任何形式或方式使用或复制本作品的任何
部分，或将其存储在数据库或检索系统中。

本作品的使用受 BES 授予的许可证管辖。
本作品包含 BES 的机密和专有信息。
```

**注意**：本仓库包含恒玄科技的专有代码。有关完整的许可条款，请参阅 LICENSE 文件。

## 贡献

对于芯片厂商特定的更改，请遵循恒玄科技的内部开发流程。对于 openvela 集成问题，请参考主 [openvela 贡献指南](../../docs/CONTRIBUTING_zh-cn.md)。

## 支持

- **润欣科技**（硬件支持）：请使用上述邮箱联系
- **恒玄科技**：请联系您的 BES 代表获取芯片特定支持
- **openvela 集成**：请参阅 [openvela 文档](../../docs/) 或社区论坛

## 相关资源

- [润欣科技 - openvela+BES 方案介绍](https://www.fortune-co.com/Tech/projectDetail/id/64.html)
- [BES2600WM 硬件用户指南 (PDF)](https://www.fortune-co.com/Public/Uploads/ueditor/upload/file/20250801/1754019693187058.pdf)
