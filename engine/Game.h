// Moriah Bender
// Game header file
// One game being played : the board plus the score for it, no console input or output

#ifndef GAME_H
#define GAME_H

#include <cstdint>

#include "Board.h"

class Game {

private:
	// ** ATTRIBUTES ** //
	Board board_;
	int moves_;

public:

	// ** CONSTRUCTOR ** //
	Game(int width, int height, std::uint32_t seed);	// builds the board and scrambles it, same seed always gives the same game

	// ** ACCESSORS ** //
	const Board& board() const;
	int moves() const;

	// ** METHODS ** //
	bool move(Direction dir);				// moves the blank and counts it, returns false if it would leave the board
	bool isSolved() const;					// checking if the board is in a solved state

};
#endif
