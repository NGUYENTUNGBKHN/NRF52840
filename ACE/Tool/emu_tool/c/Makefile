TARGET_NAME=emu_tool_c
BUILD_DIR=_build
OBJ_DIR=$(BUILD_DIR)/obj

PROJ_DIR=./

CC=gcc

CCFLAG=\

SRC_INCLUDE+=$(wildcard *.c)
SCR_EXCLUDE=\

SRC_FILES=$(filter-out $(SCR_EXCLUDE), $(SRC_INCLUDE))


INC_FOLDERS=\


OBJECT:=$(foreach obj, $(SRC_FILES), $(OBJ_DIR)/$(obj:%.c=%.o))


.PHONY:	all clean


all: $(BUILD_DIR)/$(TARGET_NAME)

$(OBJ_DIR)/%.o: %.c
	@echo "Compiling $(notdir $<)"
	@mkdir -p $(shell dirname $@)
	@$(CC) -c $< $(CCFLAG) $(INC_FOLDERS) -o $@

$(BUILD_DIR)/$(TARGET_NAME): $(OBJECT)
	@echo "Link $(notdir $@)"
	@mkdir -p $(shell dirname $@)
	@$(CC) $(OBJECT) $(CCFLAG) $(INC_FOLDERS) -o $@
	@echo "Done." 

clean:
	rm -r $(BUILD_DIR)




