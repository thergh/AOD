CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRCDIR = src
SRC = $(SRCDIR)/main.cpp $(SRCDIR)/algo.cpp

TARGET = program

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
