CXX = g++
CXXFLAGS = -g -Wall -lpthread -lm -lrt -std=gnu++11 -pedantic

part2: monitor.o part2.o
	$(CXX) $(CXXFLAGS) monitor.o part2.o -o part2

part2.o: part2.cpp part2.h monitor.h
	$(CXX) $(CXXFLAGS) -c part2.cpp monitor.cpp

monitor.o: monitor.cpp monitor.h
	$(CXX) $(CXXFLAGS) -c monitor.cpp

clean:
	rm -rf part2 *.o
