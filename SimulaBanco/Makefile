CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Name of the final executable
TARGET = simula_banco

# Automatically find all .cpp files in the directory
SRCS = $(wildcard *.cpp)

# Generate the corresponding object (.o) file names
OBJS = $(SRCS:.cpp=.o)

# Default rule when you just type 'make'
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile individual .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the compiled files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
