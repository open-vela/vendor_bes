# BEST1700 AOS EVB

[ [English](README.md) | 简体中文 ]

本开发板软件包提供 BEST1700 AOS EVB（AP/APC1 库发布版）的 open-vela 板级支持文件。

> `best1700` 是代码、配置及预编译库中统一使用的平台/SDK 代号；本开发板上实际搭载的芯片为 **BES2800BP**（Cortex-M55 + HiFi4 DSP）。

## 支持的功能

- Wi-Fi
- eMMC
- RM69330 DSI 显示屏
- TMA525C 触摸面板
- USB 串口控制台

## 控制台

串口控制台通过 USB 接口引出。

将开发板通过 USB 连接到主机，使用目标镜像所用的控制台参数打开枚举出的串口设备即可。

## 配置

本发布分支仅支持库模式（library mode）。

可用的板级配置：

- `configs/ap`
- `configs/apc1`

AP 配置启用已发布的 AP 板级封装与 BSP 静态库；APC1 配置启用已发布的 APC1 板级封装与 BSP 静态库。

## 库交付物

板级与芯片的实现主要通过配置目录下的预编译静态库提供：

- `configs/ap/libbesboard_ap.a`
- `configs/ap/libbeschip_ap.a`
- `configs/ap/libnx_bestbsp_ap.a`
- `configs/apc1/libbesboard_apc1.a`
- `configs/apc1/libbeschip_apc1.a`
- `configs/apc1/libnx_bestbsp_apc1.a`

本分支保留的源文件仅限于 AP/APC1 的板级入口封装，以及消费这些库所需的构建胶水代码。

## 第三方声明

发布的静态库中包含第三方组件。本板级软件包的分发应当随附：

- `THIRD_PARTY_NOTICES`

## 编译

使用 open-vela 标准的编译入口编译对应的 AP/APC1 配置。

在 open-vela 仓库根目录编译 AP 的示例：

```bash
./1700_ap.sh
```
