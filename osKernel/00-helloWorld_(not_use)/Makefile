TARGET=hello
BUILD_DIR=_build
OBJS_DIR=$(BUILD_DIR)/objs


LINKER_SCRIPT=link.ld


# Toolchain

GNU_PREFIX=arm-none-eabi-

CC='$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)gcc'
CX='$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)gcc'
AS='$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)gcc' -x assembler-with-cpp
LD='$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)ld'
SZ='$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)size'
CP='$(TOOLCHAIN_TUNG)/$(GNU_PREFIX)objcopy'

HEX=$(CP) -O ihex
BIN=$(CP) -O binary -S

# Configure CPU, compiler 
CPU=-mcpu=cortex-m4
FPU=-mfpu=fpv4-sp-d16
FLOAT_ABI=-mfloat-abi=hard
MCU= $(CPU) $(FPU) $(FLOAT_ABI)
OPT= -O3 -g3


# C Flag
CCFLAGS += $(MCU) $(OPT)
CCFLAGS += -Wall -Werror -ffunction-sections -fdata-sections -fno-strict-aliasing
CCFLAGS += -fno-builtin -fshort-enums 
CCFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

ASMFLAG= $(MCU)
ASMFLAG+= -g3

LDFLAG = $(MCU) $(OPT) 
LDFLAG += -T$(LINKER_SCRIPT) --specs=nano.specs
LDFLAG += -Wl,--gc-sections,-Map=$(BUILD_DIR)/$(TARGET).map

LIBS += -lc -lm -lnosys

# Source 

SRC_FILE=$(wildcard *.c)

INC_FOLDER=\

ASM_FILE=$(wildcard *.s)


OBJECTS=$(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC_FILE))
OBJECTS+=$(patsubst %.s,$(OBJS_DIR)/%.s.o,$(ASM_FILE))


.PHONY: all clean default

default: all
 
all: $(BUILD_DIR)/$(TARGET).out $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin



$(OBJS_DIR)/%.o: %.c
	@echo "Compiling $<"
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CCFLAGS) $(INC_FOLDER) -c $< -o $@

$(OBJS_DIR)/%.s.o: %.s
	@echo "Assembling $<"
	@mkdir -p $(shell dirname $@)
	@$(CC) $(ASMFLAG) $(INC_FOLDER) -c $< -o $@

$(BUILD_DIR)/$(TARGET).out: $(OBJECTS)
	@echo "LINK $@"
	@$(CC) $(LDFLAG) $(INC_FOLDER) $(LIBS) $(OBJECTS) -o $@
	@$(SZ) $@


$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).out
	@echo "HEX $@"
	@$(HEX) $< $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).out
	@echo "BIN $@"
	@$(BIN) $< $@


clean:
	@echo "Remove project"
	@rm -r $(BUILD_DIR)


flash: default
	Jlink.exe -if swd -device nRF52840_xxAA -speed 4000 -CommanderScript CommanderScript/build_windows.jlink

erase:
	Jlink.exe -if swd -device nRF52840_xxAA -speed 4000 -CommanderScript CommanderScript/erase_windows.jlink






