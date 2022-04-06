SET PATH=C:\Program Files (x86)\LLVMEmbeddedToolchainForArm\13.0.0\bin
SET CPU_TYPE=SSE-300-MPS3
SET CPU_VENDOR=ARM
SET UV2_TARGET=Cortex-M55_MPS3
SET CPU_CLOCK=0x017D7840
clang.exe @".\llvm_build\build.__i"
ld.lld.exe @".\llvm_build\lv_template.lnp"
llvm-size.exe ./Objects/lv_template.axf
@echo # "C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2021.10\arm-none-eabi\lib\thumb\v8.1-m.main+mve\hard\crt0.o"