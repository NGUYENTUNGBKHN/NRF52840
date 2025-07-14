TARGET_NAME=win_tool
BUILD_DIR=_build
OBJ_DIR=$(BUILD_DIR)/obj

PROJ_DIR=./

CC=gcc
CX=g++
SZ=size
$(if $(shell $(CC) --version),,$(info Cannot find $(CC)))

CCFLAG:=\


SRC_INCLUDE+=$(wildcard *.cpp)
SRC_INCLUDE+=$(wildcard $(PROJ_DIR)/operation/*.cpp)
SRC_INCLUDE+=$(wildcard $(PROJ_DIR)/parseArg/*.cpp)
SRC_EXCLUDE=\

SRC_FILES=$(filter-out $(SRC_EXCLUDE), $(SRC_INCLUDE))


INC_FOLDERS=\
	-I$(PROJ_DIR)/inc\
	-I$(PROJ_DIR)/operation\
	-I$(PROJ_DIR)/parseArg\

OBJECT:=$(foreach obj, $(SRC_FILES), $(OBJ_DIR)/$(obj:%.cpp=%.opp))


.PHONY: all clean

all: $(BUILD_DIR)/$(TARGET_NAME)

$(OBJ_DIR)/%.opp: %.cpp
	@echo "Compiling $(notdir $<)"
	@mkdir -p $(shell dirname $@)
	@$(CX) -c $< $(CCFLAG) $(INC_FOLDERS) -o $@

$(BUILD_DIR)/$(TARGET_NAME): $(OBJECT)
	@echo "LINK $@"
	@mkdir -p $(shell dirname $@)
	@$(CX) $(OBJECT) $(CCFLAG) $(INC_FOLDERS) -o $@
	@echo "Done."

clean: 
	rm -r $(BUILD_DIR)

