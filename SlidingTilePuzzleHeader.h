// Moriah Bender
// Header file

#pragma warning(disable:4996)
#pragma warning(disable:6031)

#ifndef __SLIDING__TILE__
#define __SLIDING__TILE__
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// ** CROSS-PLATFORM CONSOLE HELPERS ** //
void setTextColor(int colorCode);	// sets console text color (Windows console API or ANSI escape codes)
void clearScreen();					// clears the console (cls on Windows, clear elsewhere)
void pauseConsole();					// waits for user input before continuing (pause on Windows)
int getKeyPress();					// reads a single keypress without waiting for Enter

class SlidingPuzzle {

private:
	// ** ATTRIBUTES ** //
	int row;
	int column;
	int value;
	int** theBoard;
	int** winningBoard;

public:

	// ** CONSTRUCTORS ** //
	SlidingPuzzle();
	SlidingPuzzle(int width, int height);

	// destructor method
	~SlidingPuzzle();

	// ** ACCESSORS ** //
	int getHeight();
	int getWidth();

	// ** MUTATORS ** //
	void setHeight(int height);
	void setWidth(int width);


	// ** METHODS ** //
	bool slideTile(int directionCode);	// takes movement to allow board manipulation
	void InitializeBoard();				// populating the board with the appropriate values based on height and width
	bool isBoardSolved();				// checking if the board is in a solved state
	void scrambleBoard();				// scrambles the board 15,000 times , with legal moves
	void PrintBoard();					// prints the board. Is 3x3 board by default, prints adjusted height and width if applied
	void StartOfGame();
	void keyMessage();					// printing key message to user along with current board status and exit code



};
#endif
