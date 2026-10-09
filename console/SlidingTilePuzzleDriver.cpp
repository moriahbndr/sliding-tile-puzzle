// Moriah Bender
// Sliding Tile Puzzle Simulator,
// originally only Windows compatible, refactored for cross platform compatibility (see Console files)
// Driver file, console client for the Board engine

#pragma warning(disable:4996)
#pragma warning(disable:6031)

#include <iostream>
#include <iomanip>
#include <limits>
#include <random>

#include "../engine/Board.h"
#include "Console.h"

using namespace std;

void printBoard(const Board& board);		// prints the board, green tiles are in the correct position, red tiles are not
void keyMessage(const Board& board);		// printing key message to user along with current board status and exit code
void startOfGame(Board& board);				// prints the solved board, scrambles it, prints it again
void playGame(Board& board);				// loops until the board is solved, or until the user exits game
int readBoardSize(const char* side);		// prompts until the user enters a value from 2 - 10

int main() {

	int height = 0;
	int width = 0;
	int selection = 0;

	// DISPLAYING DEFAULT BOARD CODE
	Board board;
	printBoard(board);			// printing the board 3x3

	// prompting user to input which board to play or create
	cout << endl << "Please choose from the following" << endl << endl;
	cout << "- Enter 1 to play on the standard board shown above " << endl;
	cout << "- Enter 2 to play on a custom board " << endl;

	// looping to validate input from user
	do {
		cout << endl << "  Selection : ";
		selection = getKeyPress();
		selection = selection - 48;			// converts to the integer the user entered on keyboard
		if (selection != 1 && selection != 2) {
			cout << endl << "  Please enter 1 or 2" << endl;
		}

	} while (selection != 1 && selection != 2);

	// DEFAULT BOARD GAME //
	if (selection == 1) {
		playGame(board);
	}

	// CUSTOM BOARD GAME //
	else if (selection == 2) {

		cout << endl << endl << "CUSTOM BOARD SELECTED" << endl << endl;

		width = readBoardSize("width");
		height = readBoardSize("height");

		cout << endl;
		clearScreen();

		// creating custom board with given values for width and height
		Board customBoard(width, height);
		playGame(customBoard);
	}

	setTextColor(7);
	getKeyPress();
	clearScreen();

	return 0;

}

// ** BOARD SIZE INPUT ** //
int readBoardSize(const char* side) {

	int size = 0;

	cout << "Enter " << side << " of board: ";
	cin >> size;
	cout << endl;

	// fail flag / validating input
	while (cin.fail() || size < 2 || size > 10) {
		cout << "Invalid value entered, please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Please enter a numerical value from 2 - 10 to set the " << side << " of the board : ";
		cin >> size;
		cout << endl;
	}

	// clearing the rest of the line so it is not read as a keypress later
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return size;
}

// ** GAME LOOP ** //
void playGame(Board& board) {

	int key = 0;

	startOfGame(board);

	do {
		setTextColor(7);
		keyMessage(board);

		// movement received by user
		cout << endl << "Enter movement: ";
		key = getKeyPress();

		// moving board tiles
		clearScreen();
		switch (key) {
			case '8': board.move(Direction::Up);    break;
			case '2': board.move(Direction::Down);  break;
			case '4': board.move(Direction::Left);  break;
			case '6': board.move(Direction::Right); break;
		}
		printBoard(board);

		// messages based on board state
		if (board.isSolved()) {
			keyMessage(board);
			setTextColor(2);
			cout << "Board is solved, exiting game" << endl;
			setTextColor(7);

		}
		if (key == '0') {
			setTextColor(7);
			cout << "EXITING GAME" << endl;
		}

	} while (!board.isSolved() && key != '0');
}

// ** START OF GAME MESSAGE ** //
void startOfGame(Board& board) {

	random_device seedSource;

	cout << endl;
	clearScreen();

	// printing the board
	printBoard(board);

	// scrambling the board, again if the scramble happens to end on a solved board
	do {
		board.scramble(seedSource());
	} while (board.isSolved());

	// Printing the scramble board message to user
	cout << endl << "scrambling board..." << endl << endl;
	pauseConsole();
	clearScreen();
	cout << endl << "SCRAMBLING COMPLETE " << endl << endl;
	pauseConsole();
	clearScreen();

	// printing the board
	printBoard(board);
}

// ** KEY MESSAGE ** //
// prints key message to user for board movement and exit game, also prints current status of board solved
void keyMessage(const Board& board) {

	cout << endl << "| 8 UP | 2 DOWN | 4 LEFT | 6 RIGHT | is board solved ? : ";

	if (board.isSolved()) {
		setTextColor(2);
		cout << "YES";
		setTextColor(7);
	}
	else {
		setTextColor(12);
		cout << "NO";
		setTextColor(7);
	}

	cout << endl << "Enter 0 to exit game" << endl;
}

// ** PRINTING BOARD ** //
void printBoard(const Board& board) {

	const vector<int>& tiles = board.tiles();

	cout << endl;

	if (board.width() * board.height() != 9) {
		cout << setw(6) << "   CUSTOM BOARD CREATED" << endl << endl;
	}

	for (int i = 0; i < board.height(); i++) {

		for (int j = 0; j < board.width(); j++) {

			int index = i * board.width() + j;

			// outputs '*' in place of the blank on the board
			if (tiles[index] == 0) {
				setTextColor(7);
				cout << setw(6) << '*';
			}
			else {
				// if the tile is in its winning position, color will be adjusted to green , if not, it will be red
				if (tiles[index] == index + 1) {
					setTextColor(2);
				}
				else {
					setTextColor(4);
				}

				cout << setw(6) << tiles[index];
			}
		}
		cout << endl << endl;
	}
}
