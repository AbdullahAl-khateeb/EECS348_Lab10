# Build the Lab 10 matrix program.
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = lab10

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

# Remove the compiled program.
clean:
	rm -f $(TARGET)

.PHONY: all clean
