CXX = g++
CXXFLAGS = -std=c++17 -Wall

SOURCES = console/SlidingTilePuzzleDriver.cpp console/Console.cpp engine/Board.cpp
HEADERS = console/Console.h engine/Board.h

puzzle: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o puzzle

run: puzzle
	./puzzle

clean:
	rm -f puzzle
