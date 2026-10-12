// Moriah Bender
// Game header file
// One game being played : the board plus the move count and timer for it, no console input or output

#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <cstdint>

#include "Board.h"

class Game {

private:
	// ** ATTRIBUTES ** //
	Board board_;
	int moves_;
	bool timerStarted_;
	std::chrono::steady_clock::time_point startTime_;
	std::chrono::steady_clock::time_point endTime_;		// set on the move that solves the board

public:

	// ** CONSTRUCTOR ** //
	Game(int width, int height, std::uint32_t seed);	// builds the board and scrambles it, same seed always gives the same game

	// ** ACCESSORS ** //
	const Board& board() const;
	int moves() const;
	double elapsedSeconds() const;			// time since startTimer(), stops going up once the board is solved, 0 if the timer was never started

	// ** METHODS ** //
	void startTimer();						// starts the clock, called when the player is first shown the scrambled board
	bool move(Direction dir);				// moves the blank and counts it, returns false if it would leave the board
	bool isSolved() const;					// checking if the board is in a solved state

};
#endif
