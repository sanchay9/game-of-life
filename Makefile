# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20
LIBS = -lSDL2

# Source files
SRCS = game.cpp

# Output binary
TARGET = game

# Default rule to build the target
all: $(TARGET)

# Rule to link and compile
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LIBS)
