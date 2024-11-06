# Compiler to be used (g++ is the C++ compiler)
CXX = g++

# Compiler flags (in this case, ensuring C++17 standard is used)
CXXFLAGS = -std=c++17

# Object files to be created from the source files
TARGETS = main.o header.o

# Name of the final program (executable)
PROGRAM = main

# Default target, builds the final program
all: $(PROGRAM)

# Rule to build the final executable 'main' from the object files
# $@ refers to the target (main), $^ refers to all dependencies (main.o header.o)
$(PROGRAM): $(TARGETS)
	$(CXX) $(TARGETS) -o $(PROGRAM) $(CXXFLAGS)

# Rule to compile any .cpp file into a corresponding .o (object) file
# $< refers to the first prerequisite (the .cpp file), $@ refers to the target (the .o file)
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean target: removes object files and the executable
clean:
	@if exist *.o del *.o               # Remove all object (.o) files
	@if exist $(PROGRAM).exe del $(PROGRAM).exe  # Remove the executable (main.exe)
