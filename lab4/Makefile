CXX = g++

CXXFLAGS = -std=c++17

SRCDIR = src
# SRC = $(SRCDIR)/main.cpp $(SRCDIR)/algo.cpp
SRC = $(SRCDIR)/main.cpp $(SRCDIR)/algo.cpp
# SRC = $(SRCDIR)/test-hyp.cpp $(SRCDIR)/algo.cpp
# SRC = $(SRCDIR)/test-bip-size.cpp $(SRCDIR)/algo.cpp


TARGET = program

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
