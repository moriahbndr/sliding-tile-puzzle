CXX = g++
CXXFLAGS = -std=c++17 -Wall

puzzle: SlidingTilePuzzleDriver.cpp SlidingTilePuzzleImplementation.cpp
	$(CXX) $(CXXFLAGS) SlidingTilePuzzleDriver.cpp SlidingTilePuzzleImplementation.cpp -o puzzle

run: puzzle
	./puzzle

clean:
	rm -f puzzle
