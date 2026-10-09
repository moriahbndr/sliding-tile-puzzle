// Moriah Bender
// Board header file
// Game engine for the sliding tile puzzle, no console input or output

#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <vector>

enum class Direction { Up, Down, Left, Right };

class Board {

private:
	// ** ATTRIBUTES ** //
	int width_;
	int height_;
	int blank_;								// index of the blank in tiles_
	std::vector<int> tiles_;				// row by row, 0 is the blank

public:

	// ** CONSTRUCTORS ** //
	explicit Board(int width = 3, int height = 3);			// builds a solved board, throws std::invalid_argument if either side is < 2
	Board(int width, int height, std::vector<int> tiles);	// rebuilds a board from saved state, throws std::invalid_argument if the tiles are not valid

	// ** ACCESSORS ** //
	int width() const;
	int height() const;
	const std::vector<int>& tiles() const;

	// ** METHODS ** //
	bool move(Direction dir);				// moves the blank, returns false if it would leave the board
	bool isSolved() const;					// checking if the board is in a solved state
	void scramble(std::uint32_t seed);		// scrambles the board with legal moves, same seed always gives the same board

};
#endif
