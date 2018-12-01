CXX = g++
CXXARGS = -Wall

all: mazemaker

mazemaker: main.cpp CompleteMaze.cpp Grid.cpp CartesianPoint.h CompleteMaze.h Grid.h Wall.h
	$(CXX) $(CXXARGS) -o $@ *.cpp

clean:
	rm -f mazemaker
