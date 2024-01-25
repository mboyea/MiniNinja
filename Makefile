# Created by Matthew Boyea on 2024-01-23
# Last Edited by Matthew Boyea on 2024-01-25

# file extensions
SRC_EXT := cpp
INC_EXT := h
OBJ_EXT := o

# project directories
TARGET_DIR := bin
SRC_DIR := src
INC_DIR := src
LIB_DIR := lib
OBJ_DIR := build
STATIC_DIR := static

# targets
EXE := MiniNinja
TARGET := $(TARGET_DIR)/$(EXE)

# files
SRCS := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
INCS := $(shell find $(INC_DIR) -type f -name *.$(INC_EXT))
LIB_INC_DIRS := $(shell find $(LIB_DIR) -type d -path "*x86_64*/include/SDL2")
OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.$(SRC_EXT)=.$(OBJ_EXT)))
LIB_LIB_DIRS := $(shell find $(LIB_DIR) -type d -path "*x86_64*/lib")
#LIB_DLL_DIRS
#LIB_DLLS

# compilers & flags
CXX := g++
CXXFLAGS := -std=c++17 -g# -Wall
LDFLAGS := $(addprefix -L,$(LIB_LIB_DIRS))
LDLIBS := $(addprefix -l,SDL2 SDL2main SDL2_image SDL2_ttf SDL2_mixer)

all: link

run: $(TARGET)
	@echo "Running..."
	# TODO: launch executable

link: $(OBJS)
	@mkdir -p $(TARGET_DIR)
	@echo "Linking..."; $(CXX) $^ $(LDFLAGS) $(LDLIBS) -o $(TARGET)

$(OBJ_DIR)/%.$(OBJ_EXT) : $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."; $(CXX) $(CXXFLAGS) $(addprefix -I,$(LIB_INC_DIRS)) -c -o $@ $<

clean:
	@echo "Cleaning...";
	$(RM) -r $(OBJ_DIR) $(TARGET_DIR)

.PHONY: clean

# # compilers & flags
# CXX := g++
# CXXFLAGS := -g # -Wall
# LDFLAGS := -L
# # directories
# SRC_DIR := src        # .cpp, .h
# LIB_DIR := lib        # .dll
# OBJ_DIR := build    # .o
# STATIC_DIR := static  # static files
# TARGET_DIR := bin     # .exe, static files
# # file extensions
# SRC_EXT := cpp
# INC_EXT := h
# # files
# SRCS := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
# INCS := -I include
# OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:.$(SRC_EXT)=.o))
# 
# LDLIBS :=
# LIB := -pthread -lmongoclient -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
# 
# $(TARGET_DIR): $(OBJECTS)
# 	@echo " Linking..."
# 	@echo " $(CPP_C) $^ -o $(TARGET_DIR) $(LIB)"; $(CPP_C) $^ -o $(TARGET_DIR) $(LIB)
# 
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
# 	@echo " Compiling..."
# 	@mkdir -p $(OBJ_DIR)
# 	@echo " $(CPP_C) $(CPP_FLAGS) $(INCLUDES) -c -o $@ $<"; $(CPP_C) $(CPP_FLAGS) $(INCLUDES) -c -o $@ $<
# 
# clean:
# 	@echo " Cleaning..."; 
# 	@echo " $(RM) -r $(OBJ_DIR) $(TARGET_DIR)"; $(RM) -r $(OBJ_DIR) $(TARGET_DIR)
# 
# .PHONY: clean
