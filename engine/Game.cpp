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
	this->timerStarted_ = false;
}

// ** ACCESSORS ** //
const Board& Game::board() const {
	return this->board_;
}

int Game::moves() const {
	return this->moves_;
}

// ** ELAPSED TIME ** //
double Game::elapsedSeconds() const {

	if (!timerStarted_) {
		return 0;
	}

	// a solved game is measured up to the solving move, a game in progress is measured up to now
	std::chrono::steady_clock::time_point end = isSolved() ? endTime_ : std::chrono::steady_clock::now();

	std::chrono::duration<double> elapsed = end - startTime_;
	return elapsed.count();
}

// ** STARTING THE TIMER ** //
void Game::startTimer() {
	this->startTime_ = std::chrono::steady_clock::now();
	this->timerStarted_ = true;
}

// ** MOVING AND COUNTING ** //
bool Game::move(Direction dir) {

	// hit a wall, nothing to count
	if (!board_.move(dir)) {
		return false;
	}

	moves_++;

	// stopping the clock on the move that solves the board
	if (board_.isSolved()) {
		endTime_ = std::chrono::steady_clock::now();
	}
	return true;
}

// ** ISSOLVED() ** //
bool Game::isSolved() const {
	return board_.isSolved();
}
