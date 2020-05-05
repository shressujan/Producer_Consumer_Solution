CXX = g++
CXXFLAGS = -Wall -lpthread -lm -lrt -std=gnu++11

part1: part1.o
	$(CXX) $(CXXFLAGS) part1.o -o part1

part1.o: part1.cpp part1.h
	$(CXX) $(CXXFLAGS) -c part1.cpp

clean:
	rm -rf part1 *.o
