TARGET=hello
BUILD_DIR=_build
OBJS_DIR=$(BUILD_DIR)/objs


LINKER_SCRIPT=link.ld


# Toolchain

GNU_PREFIX=arm-none-eabi-

CC=$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)gcc
CX=$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)gcc
AS=$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)gcc -x assembler-with-cpp
LD=$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)ld
SZ=$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)size
CP=$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)objcopy

HEX=$(CP) -O ihex
BIN=$(CP) -O binary -S








