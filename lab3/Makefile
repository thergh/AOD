# Variables
SRC_DIR = src
BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)/program
CXX = g++
# CXXFLAGS = -O2 -Wall -std=c++20
CXXFLAGS = -g -Wall -std=c++20
SRC_FILES = $(SRC_DIR)/algo.cpp $(SRC_DIR)/main.cpp
# SRC_FILES = $(SRC_DIR)/algo.cpp $(SRC_DIR)/main-test.cpp
# SRC_FILES = $(SRC_DIR)/algo.cpp $(SRC_DIR)/main-tech.cpp
HEADERS = $(SRC_DIR)/algo.hpp

# Default target
all: $(EXECUTABLE)

# Build target
$(EXECUTABLE): $(SRC_FILES) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(EXECUTABLE)

# Clean target
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean
