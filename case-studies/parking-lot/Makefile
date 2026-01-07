CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = parking_lot_demo
SOURCES = main.cpp ParkingSpot.cpp ParkingTicket.cpp Payment.cpp ParkingLot.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = ParkingSpot.h Vehicle.h ParkingTicket.h Payment.h PricingStrategy.h DisplayBoard.h ParkingFloor.h ParkingLot.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
