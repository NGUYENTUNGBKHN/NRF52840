TARGET_NAME:=boot
BUILD_DIR:=_build
MAKE_COMMON:=../Common


ROOT_PROJ:=./

$(BUILD_DIR)/$(TARGET_NAME).out: \
	LINKER_SCRIPT := $(ROOT_PROJ)/boot.ld

CPU=-mcpu=cortex-m4 -mthumb -mabi=aapcs
FPU=-mfloat-abi=hard -mfpu=fpv4-sp-d16
OPT=-O3 -g3
CCFLAGS+=$(CPU) $(FPU) $(OPT)
CCFLAGS+=-ffunction-sections -fdata-sections -fno-strict-aliasing
CCFLAGS+=-fno-builtin -fshort-enums
CCFLAGS+=-Wall -Wno-unused-variable

ASMFLAG+=$(CPU) $(FPU) $(OPT)

LDFLAGS+=$(CPU) $(FPU) $(OPT)
LDFLAGS+=-Wl,--gc-sections
LDFLAGS+=--specs=nano.specs
LDFLAGS+=-T$(LINKER_SCRIPT) -mthumb -mabi=aapcs


SRC_FILES=\
	$(ROOT_PROJ)/main.c\
	$(ROOT_PROJ)/boot_startup.c\

INC_FOLDER=\

LIBS+=-lc -lm



.PHONY:	default help

default: $(TARGET_NAME)


include $(MAKE_COMMON)/Makefile.common


$(foreach target, $(TARGET_NAME), $(call define_target, $(target)))



help:
	@echo  help


flash: default
	Jlink.exe -if swd -device nRF52840_xxAA -speed 4000 -CommanderScript CommanderScript/build_windows.jlink

erase:
	Jlink.exe -if swd -device nRF52840_xxAA -speed 4000 -CommanderScript CommanderScript/erase_windows.jlink


