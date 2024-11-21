# Variables
SRC_DIR = src
BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)/program
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Default target
all: $(EXECUTABLE)

# Build target
$(EXECUTABLE): $(SRC_FILES)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(EXECUTABLE)

# Clean target
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean
