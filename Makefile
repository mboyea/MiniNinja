# Created by Matthew Boyea on 2024-01-23

# targets
EXE := MiniNinja
TARGET := $(TARGET_DIR)/$(EXE)

# compilers & flags
CXX := g++
CXXFLAGS := -g # -Wall

# directories
TARGET_DIR := bin     # executable output
SRC_DIR := src        # c++ source files
INC_DIR := src        # c++ header files
BUILD_DIR := build    # c++ object files
LIB_DIR := lib        # c++ library files
STATIC_DIR := static  # static files

# # file extensions
SRC_EXT := cpp        # c++ source files
INC_EXT := h          # c++ header files

# files
SRCS := 

all: run

run: link
	@echo " Running..."

link: compile
	@echo " Linking..."

compile:
	@echo " Compiling..."

clean:
	@echo " Cleaning...";

.PHONY: clean

# # compilers & flags
# CXX := g++
# CXXFLAGS := -g # -Wall
# LDFLAGS := -L
# # directories
# SRC_DIR := src        # .cpp, .h
# LIB_DIR := lib        # .dll
# BUILD_DIR := build    # .o
# STATIC_DIR := static  # static files
# TARGET_DIR := bin     # .exe, static files
# # file extensions
# SRC_EXT := cpp
# INC_EXT := h
# # files
# SRCS := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
# INCS := -I include
# OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SRC_EXT)=.o))
# 
# LDLIBS :=
# LIB := -pthread -lmongoclient -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
# 
# all: static
# 
# static: 
# 
# $(TARGET_DIR): $(OBJECTS)
# 	@echo " Linking..."
# 	@echo " $(CPP_C) $^ -o $(TARGET_DIR) $(LIB)"; $(CPP_C) $^ -o $(TARGET_DIR) $(LIB)
# 
# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
# 	@echo " Compiling..."
# 	@mkdir -p $(BUILD_DIR)
# 	@echo " $(CPP_C) $(CPP_FLAGS) $(INCLUDES) -c -o $@ $<"; $(CPP_C) $(CPP_FLAGS) $(INCLUDES) -c -o $@ $<
# 
# clean:
# 	@echo " Cleaning..."; 
# 	@echo " $(RM) -r $(BUILD_DIR) $(TARGET_DIR)"; $(RM) -r $(BUILD_DIR) $(TARGET_DIR)
# 
# .PHONY: clean
