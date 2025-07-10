# Makefile created library project
TARGET_NAME:=ace
BUILD_DIR:=_build
MAKE_COMMON:=../../Common
LIB_OUTPUT_PATH = $(BUILD_DIR)/$(TARGET_NAME).a
# This is the root project directory and the core directory
ROOT_PROJ:=./
# Core directory for the project
COMMON=./common/
CORE=./ports/cortex-m4/


# This is the Flags for the compiler
CPU=-mcpu=cortex-m4 -mthumb -mabi=aapcs
FPU=-mfloat-abi=hard -mfpu=fpv4-sp-d16
OPT=-O0 -g3
CCFLAGS+= $(CPU) $(FPU) $(FLOAT) $(OPT)

ASMFLAG=$(CCFLAGS)

SRC_EXCLUDE=\

SRC_INCLUDE+=$(wildcard $(COMMON)/src/thread/*.c)
SRC_INCLUDE+=$(wildcard $(COMMON)/src/*.c)
SRC_INCLUDE+=$(wildcard $(CORE)/src/*.c)
SRC_INCLUDE+=$(wildcard $(CORE)/src/*.S)

SRC_FILES:=$(filter-out $(SRC_EXCLUDE), $(SRC_INCLUDE))

INC_FOLDERS=\
	$(COMMON)/inc\
	$(CORE)/inc\


.PHONY:	default help

default: $(TARGET_NAME)

# Include common makefile. File contains TOOLCHAIN directory and rules for building targets
include $(MAKE_COMMON)/Makefile.common

# Call function to define targets 
$(call define_library, $(TARGET_NAME), $(LIB_OUTPUT_PATH))

define create_library
@echo Creating library: $($@)
$(NO_ECHO)$(AR) $($@) $^
@echo Done
endef
ace:
	$(create_library)

# Help target
help:
	@echo  help


