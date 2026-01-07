# Makefile for Abstract Factory Pattern Demo

CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra
TARGET = abstract_factory_demo

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
