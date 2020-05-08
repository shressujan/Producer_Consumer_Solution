CXX = g++
CXXFLAGS = -g -Wall -lpthread -lm -lrt -std=gnu++11 -pedantic

part2: condition.o monitor.o part2.o
	$(CXX) $(CXXFLAGS) condition.o monitor.o part2.o -o part2

part2.o: part2.cpp part2.h monitor.h
	$(CXX) $(CXXFLAGS) -c part2.cpp monitor.cpp condition.cpp

monitor.o: monitor.cpp monitor.h
	$(CXX) $(CXXFLAGS) -c monitor.cpp condition.cpp

condition.o: condition.cpp
	$(CXX) $(CXXFLAGS) -c condition.cpp

clean:
	rm -rf part2 *.o
