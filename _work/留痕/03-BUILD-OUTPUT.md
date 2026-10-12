# 03 构建产物记录

## 首次源码构建（round 1）

- 时间：2026-10-11 16:21:27 起，增量构建耗时 264 秒（全量阶段为 rom-build-2 的 1497 秒）
- 命令：make TOOLCHAIN=/ucrt64 -j12（PATH 含 /ucrt64/bin），工作目录 E:\es
- 工具链：arm-none-eabi-gcc 16.1.0 (ucrt64)、GNU Make 4.4.1
- 产物：E:\es\pokeemerald.gba，33554432 字节（32 MiB）
- 已用容量：ROM 27495828 B（81.94%）、EWRAM 231240 B（88.21%）、IWRAM 28388 B（32 KB 的 86.63%）
- 尾部填充：最后一个非 0xFF 字节位于 0x1A38D93，其后全 0xFF

| 校验 | 值 |
| --- | --- |
| SHA1 | B526D5A36D589ED14B9238AE32C416C8DAC25B89 |
| SHA256 | 6FF9EE5BC9F9C976A37D2A6C7B3ADEA2DCFB51967992B1C0CEE5E7AA702B952F |
| 备份位置 | _work\artifacts\EmeraldStory-源码构建-20261011-1625.gba |
| 链接 map | _work\artifacts\pokeemerald.map |

## 对比证据

| 对比 | 差异字节 | 区域数 | 说明 |
| --- | --- | --- | --- |
| 现用 ROM vs 基线 ROM | 602 (0.0018%) | 10 | 精确对应 Codex 报告的定点补丁（4×5B 脚本指针 + 4×4B + 0x1B00000 区 458B + 0x1B00400 区 122B）→ 校核了对比方法 |
| 新构建 vs 基线 ROM | 25794337 (76.87%) | 10850 | 跨工具链构建（GCC 16.1 vs 原 WSL 工具链），代码与引用地址整体位移 |

## 数据完整性锚点

三个 multiboot 二进制（不经过编译器的嵌入数据）在三个 ROM 中均**完整命中**，仅偏移不同：

| 数据 | 新构建 | 现用/基线 |
| --- | --- | --- |
| mb_ereader.gba (12512B) | 0x0F6A0D0 | 0x0F8AF5C |
| mb_colosseum.gba (163840B) | 0x0F6D1B0 | 0x0F8E03C |
| mb_berry_fix.gba (15348B) | 0x0F664DC | 0x0F87368 |
