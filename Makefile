# Created by Matthew Boyea on 2024-01-23

# targets
EXE := MiniNinja
TARGET := $(TARGET_DIR)/$(EXE)

# compilers & flags
CXX := g++
CXXFLAGS := -g# -Wall
LDFLAGS := -L# flags or names given to compilers whenever they invoke the linker
LDLIBS :=# -lfoo # names (flags) given to compilers to invoke the linker to support loading libs

# directories
TARGET_DIR := bin
SRC_DIR := src
INC_DIR := src
LIB_DIR := lib
OBJ_DIR := build
STATIC_DIR := static

# # file extensions
SRC_EXT := cpp
INC_EXT := h
LIB_EXT := dll
OBJ_EXT := o

# files
SRCS := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
INCS := $(shell find $(INC_DIR) -type f -name *.$(INC_EXT))
LIBS := $(shell find $(LIB_DIR) -type f -name *.$(LIB_EXT))
OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.$(SRC_EXT)=.$(OBJ_EXT)))

all: link

run: $(TARGET)
	@echo "Running..."
	# TODO: launch executable

link: $(OBJS)
	@echo "Linking..."
	@mkdir -p $(TARGET_DIR)
	# TODO: link objects into executable

$(OBJ_DIR)/%.$(OBJ_EXT) : $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."; $(CXX) $(CXXFLAGS) -c -o $@ $< # TODO: pass LIB libraries

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
