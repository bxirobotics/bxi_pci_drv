# bxi_pci_drv

同一个 main 分支保存 PCI 测试工具源码、公共头和两种架构的闭源 SDK。SDK 无源码；make 编译 drv_test、motor_test，不重编 libbxi_pci_drv.a。

| 文件 | 架构 | SHA256 |
| --- | --- | --- |
| lib/libbxi_pci_drv.a | x86_64 | `553205d540c90206fab7e6cebf039b42c757ce1741600f2510faff4b17e59d65` |
| lib/libbxi_pci_drv_arm.a | aarch64 | `daac39670682c324193e52417cea8ad3aa24d6df9e88a1a37a2fd278d65291c9` |
| lib/bxi_pci_drv.h | 共用头 | `ba19a5dca54c84748777f70a813c92499e2c214da3da9a1835151c83caee5f2f` |

2026-11-19 整理来源：x86 SDK 沿用 pkg_src f3aef6b 内置版本（hw a06d5be 固定的官方 2a8ee9669d2bf9f9b32a7705e7223383264a089e）；ARM SDK 沿用 pkg_src f3aef6b（来自 simon_dev 2cc8f2f），头逐字一致。不声称两架构来自相同上游提交；未修改 SDK 的轮询实现。

在上一级 hardware_packge 执行 `make`、`make x86` 或 `make arm`，统一生成最终 ROS 安装包。独立在本目录 `make` 仅用本机编译器构建测试程序，缓存默认 ~/.cache/bxi-build/pci-native，交叉工具链通过 FLAGS_USER 传给 CMake。

**drv_test、motor_test 会操作 PCI、电源和电机，不能直接执行作为普通编译验收。** 统一构建只检查其目标架构，不运行它们。

升级 SDK 时需同步核对公共头及目标架构，更新本表和 pkg_src/hardware_elf3 的固定 SHA256 校验后重建，避免误混两个架构。
