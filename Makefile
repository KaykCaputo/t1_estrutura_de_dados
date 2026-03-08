CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -I src

SRC := src/main.cpp
TARGET := build/main

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(dir $(TARGET))
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build
