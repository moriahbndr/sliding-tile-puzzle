// Moriah Bender
// Game implementation file

#include "Game.h"

// ** CONSTRUCTOR ** //
Game::Game(int width, int height, std::uint32_t seed) : board_(width, height) {

	// scrambling the board, with the next seed if the scramble happens to end on a solved board
	do {
		board_.scramble(seed);
		seed++;
	} while (board_.isSolved());

	// the scramble moves the board directly, so none of it is counted
	this->moves_ = 0;
}

// ** ACCESSORS ** //
const Board& Game::board() const {
	return this->board_;
}

int Game::moves() const {
	return this->moves_;
}

// ** MOVING AND COUNTING ** //
bool Game::move(Direction dir) {

	// hit a wall, nothing to count
	if (!board_.move(dir)) {
		return false;
	}

	moves_++;
	return true;
}

// ** ISSOLVED() ** //
bool Game::isSolved() const {
	return board_.isSolved();
}
