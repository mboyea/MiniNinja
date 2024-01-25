# Created by Matthew Boyea on 2024-01-23
# Last Edited by Matthew Boyea on 2024-01-25

# file extensions
SRC_EXT := cpp
INC_EXT := h
OBJ_EXT := o
DLL_EXT := dll

# project directories
SRC_DIR := src
OBJ_DIR := build
LIB_DIR := lib
TARGET_DIR := bin
STATIC_DIR := static

# targets
EXE_NAME := MiniNinja
EXE_PATH := $(TARGET_DIR)/$(EXE_NAME)

# files
SRCS := $(shell find $(SRC_DIR) -type f -name "*.$(SRC_EXT)")
LIB_INC_DIRS := $(shell find $(LIB_DIR) -type d -path "*x86_64*/include/SDL2")
OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.$(SRC_EXT)=.$(OBJ_EXT)))
LIB_LIB_DIRS := $(shell find $(LIB_DIR) -type d -path "*x86_64*/lib")
LIB_DLL_DIRS := $(shell find $(LIB_DIR) -type d -path "*x86_64*/bin")
LIB_DLLS := $(shell find $(LIB_DLL_DIRS) -type f -name "*.$(DLL_EXT)")
DLLS := $(addprefix $(TARGET_DIR)/,$(notdir $(LIB_DLLS)))
#STATICS := $(shell find $(STATIC_DIR) -type f)
# /%.dll

# compilers & flags
CXX := g++
CXXFLAGS := -std=c++17 -g# -Wall
LDFLAGS := $(addprefix -L,$(LIB_LIB_DIRS))
LDLIBS := $(addprefix -l,mingw32 SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)

all : run

run : $(EXE_PATH).exe $(DLLS)
	$(shell exec "$(EXE_PATH).exe")

$(TARGET_DIR)/%: $(STATIC_DIR)/%
	@mkdir -p $(TARGET_DIR)
	@echo "Copying $<..."; cp -r $< $@

define COPY_DLL_template
$(TARGET_DIR)/%.$(DLL_EXT) : $(1)/%.$(DLL_EXT)
	@mkdir -p $(TARGET_DIR)
	@echo "Copying $$(<) into $$(@) ..."; cp $$(<) $$(@)
endef
$(foreach LIB_DLL_DIR,$(LIB_DLL_DIRS),$(eval $(call COPY_DLL_template,$(LIB_DLL_DIR))))

$(TARGET_DIR)/%.$(DLL_EXT) : $(LIB_DLL_DIRS)%.$(DLL_EXT)
	@mkdir -p $(TARGET_DIR)
	@echo "Copying DLL $^ into $@ ...";

$(EXE_PATH).exe : $(OBJS)
	@mkdir -p $(TARGET_DIR)
	@echo "Linking..."; $(CXX) $^ $(LDFLAGS) $(LDLIBS) -o $(EXE_PATH)

$(OBJ_DIR)/%.$(OBJ_EXT) : $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."; $(CXX) $(CXXFLAGS) $(addprefix -I,$(LIB_INC_DIRS)) -c -o $@ $<

clean :
	@echo "Cleaning...";
	$(RM) -r $(OBJ_DIR) $(TARGET_DIR)

.PHONY : all clean
