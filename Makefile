# Compiler
CXX := g++

# Directories
BUILD_DIR := build
LIB_DIR := $(BUILD_DIR)/lib
BIN_DIR := $(BUILD_DIR)/bin
OBJ_DIR := $(BUILD_DIR)/obj
TEST_EXE := $(BIN_DIR)/test

# Library Name
LIB_NAME := gfx
SHARED_LIB := $(LIB_DIR)/lib$(LIB_NAME).dylib

# Source & Headers
SRC := $(wildcard src/*.cpp)
INCLUDE_PATHS := include
OBJ := $(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Test File
TEST_SRC := tests/test.cpp

# Compiler & Linker Flags
CXXFLAGS := -std=c++20 -Wall -Wextra -I$(INCLUDE_PATHS) -fPIC
LDFLAGS := -L$(LIB_DIR) -lgfx -Wl,-rpath,$(LIB_DIR)

# Dependency files
DEPS := $(OBJ:.o=.d)

# Default target
all: $(SHARED_LIB)

# Compile object files
$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -MMD -MF $(OBJ_DIR)/$*.d -c $< -o $@

# Build shared library
$(SHARED_LIB): $(OBJ) | $(LIB_DIR)
	@$(CXX) -dynamiclib -o $@ $^

# Compile test program (dynamically links libgfx)
$(TEST_EXE): $(TEST_SRC) $(SHARED_LIB) | $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Run tests
test: $(TEST_EXE)
	@$(TEST_EXE)

# Create necessary directories
$(BUILD_DIR) $(LIB_DIR) $(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@

# Clean rule
clean:
	@rm -rf $(BUILD_DIR)

# Include dependency files
-include $(DEPS)

.PHONY: all clean test
