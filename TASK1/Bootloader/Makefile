TARGET_NAME:=boot
BUILD_DIR:=_build
INC_MAKE_DIR:=../Common
OBJECT_DIR:=$(BUILD_DIR)/objs

ROOT_PROJ:=./
DRV_DIR:=./driver

$(BUILD_DIR)/$(TARGET_NAME).out:\
	LINKER_SCRIPT := boot.ld

CPU=-mcpu=cortex-m4 -mthumb -mabi=aapcs
FPU=-mfloat-abi=hard -mfpu=fpv4-sp-d16
OPT=-O3 -g3

# flag
CCFLAGS+=$(CPU) $(FPU) $(OPT)
CCFLAGS+=-ffunction-sections -fdata-sections -fno-strict-aliasing
CCFLAGS+=-fno-builtin -fshort-enums
CCFLAGS+=-Wall -Werror

LDFLAGS+=$(CPU) $(FPU) $(OPT)
LDFLAGS+=-Wl,--gc-sections
LDFLAGS+=--specs=nano.specs
LDFLAGS+=-T$(LINKER_SCRIPT) -mthumb -mabi=aapcs

LIBS+=-lc -lm

ASMFLAG+=$(CPU) $(FPU) $(OPT)


SRC_FILES +=\
	$(ROOT_PROJ)/main.c\
	$(ROOT_PROJ)/boot_startup.c\
	$(DRV_DIR)/Uart/drv_uart.c\


INC_FOLDER +=\
	$(ROOT_PROJ)\
	$(DRV_DIR)/Common\
	$(DRV_DIR)/Uart\


.PHONY: default help


default: $(TARGET_NAME)

include $(INC_MAKE_DIR)/Makefile.common

#  foreach   $(variable), $(list), $(text)
$(foreach target, $(TARGET_NAME), $(call define_target, $(target)))

help:
	echo "help"


flash:
	echo "flash"


