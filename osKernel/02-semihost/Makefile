# direction of outfile and header makefile
TARGET_NAME=semihost
BUILD_DIR=_build
MAKE_COMMON=../Common

ROOT_PROJ:=./

# Linker script 
$(BUILD_DIR)/$(TARGET_NAME).out: \
	LINKER_SCRIPT := $(ROOT_PROJ)/link.ld

# C-Flag
## Configure cortex chip
CPU=-mcpu=cortex-m4 -mthumb -mabi=aapcs
FPU=-mfpu=fpv4-sp-d16 
FLOAT_ABI=-mfloat-abi=hard
OPT=-O3 -g3
MCU=$(CPU) $(FPU) $(FLOAT_ABI) $(OPT)
## Option warning and error 
WA_ERR=-Wall -Werror -Wno-unused-variable
## other option 
OTHER_OPTITON= -ffunction-sections -fdata-sections -fno-strict-aliasing
OTHER_OPTITON+= -fno-builtin
OTHER_OPTITON+= -fshort-enums

CCFLAGS= $(MCU)
CCFLAGS+= $(WA_ERR)
CCFLAGS+= $(OTHER_OPTITON)

# ASM-FLAG
ASMFLAGS=$(MCU)

# LD-Flag
LDFLAGS=$(MCU)
LDFLAGS+=-Wl,--gc-sections,-Map=$(BUILD_DIR)/$(TARGET_NAME).map
LDFLAGS+=--specs=nano.specs
LDFLAGS+=-T$(LINKER_SCRIPT)

# Libarary 
LIBS= -lc -lm -lnosys


# Source code
SRC_FILES=$(wildcard *.c)


# Include folder
# -I$(folder directory)
INC_FOLDER=\

# PHONY
.PHONY: default help


default: $(TARGET_NAME)

include $(MAKE_COMMON)/Makefile.common

$(foreach target, $(TARGET_NAME), $(call define_target, $(target)))

help:
	@echo  help


flash: default
	Jlink.exe -if swd -device nRF52840_xxAA -speed 4000 -CommanderScript CommanderScript/build_windows.jlink

erase:
	Jlink.exe -if swd -device nRF52840_xxAA -speed 4000 -CommanderScript CommanderScript/erase_windows.jlink





