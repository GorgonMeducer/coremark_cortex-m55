# CoreMark for Cortex-m55(r0p0)
This is a CoreMark project for Cortex-M55 comparing compilers such as gcc, llvm and arm compiler 6.



## Test Environment

### Platform

- Core: **Cortex-M55 (r0p0)**

* System Frequency: **50MHz**

* Memory
  * ITCM: **512 KByte**
  * DTCM: **512 KByte**



### Toolchain

- [Arm Compiler 6.17](https://developer.arm.com/tools-and-software/embedded/arm-compiler/downloads/version-6)
- [Arm GCC 10.3-2021.10](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
- [LLVM Embedded toolchain for Arm (LLVM 13)](https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm/releases)



## Test Results

| Coremark         | AC6.17                    | LLVM | GCC  | Note                                                         |
| ---------------- | ------------------------- | ---- | ---- | ------------------------------------------------------------ |
| Best Performance | 4.51<br />ROM Size: 21136 |      |      | AC6: -Omax +lto;<br />GCC: -Ofast +lto;<br />LLVM uses: -Ofast+lto |
| -Ofast           | 4.06<br />ROM Size: 19748 |      |      |                                                              |
| -Ofast+lto       | 4.01<br />ROM Size: 17256 |      |      |                                                              |
| Best Size        | 2.35<br />ROM Size: 12468 |      |      | AC6: -Omin +lto;<br />GCC: -Oz +lto;<br />LLVM: -Oz+lto      |
| -Oz              | 2.31<br />ROM Size: 13144 |      |      |                                                              |
| -Oz+lto          | 2.35<br />ROM Size: 12468 |      |      |                                                              |
| -Os              | 2.93<br />ROM Size: 13944 |      |      |                                                              |
| -Os+lto          | 2.90<br />ROM Size: 13224 |      |      |                                                              |

