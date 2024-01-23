# Created by Matthew Boyea on 2024-01-23



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
