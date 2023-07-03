# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Files
SOURCES := $(shell find $(SRC_DIR) -name "*.cpp")
SOURCES += main.cpp
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BIN_DIR)/myproject

# Build rule
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony targets
.PHONY: all clean

all: $(EXECUTABLE)

clean:
	rm -rf $(OBJ_DIR)/ $(BIN_DIR)/

run:
	./$(EXECUTABLE)

$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))