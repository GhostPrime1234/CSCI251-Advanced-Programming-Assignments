CXX = g++
CXXFLAGS = -c
TARGET = APE

OBJS = main.o Candidate.o ElectoralEntities.o EventManagement.o Issue.o Leader.o People.o PoliticalParty.o Stance.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $<

clean:
	@if exist *.o del *.o
	@if exist $(TARGET) del $(TARGET)
