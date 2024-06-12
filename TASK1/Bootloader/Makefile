TARGET_NAME:=boot
BUILD_DIR:=_build
INC_MAKE_DIR:=../Common
OBJECT_DIR:=$(BUILD_DIR)/objs

ROOT_PROJ:=./

# flag
CCFLAGS+=


CXFLAGS+=


LDFLAGS+=


LIBS+=

ASMFLAG=


SRC_FILES +=\
	$(ROOT_PROJ)/main.c\

INC_FOLDER +=\
	$(ROOT_PROJ)


.PHONY: default help


default: $(TARGET_NAME)

include $(INC_MAKE_DIR)/Makefile.common

#  foreach   $(variable), $(list), $(text)
$(foreach target, $(TARGET_NAME), $(call define_target, $(target)))

help:
	echo "help"





