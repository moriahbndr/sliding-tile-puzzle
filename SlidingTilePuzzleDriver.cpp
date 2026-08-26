// Moriah Bender
// Sliding Tile Puzzle Simulator, 
// originally only Windows compatible, refactored for cross platform compatibility (also in Imp file)
// Driver file

#pragma warning(disable:4996)
#pragma warning(disable:6031)

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include "SlidingTilePuzzleHeader.h"

using namespace std;

int main() {

	int height = 0;
	int width = 0;
	int direction = 0;
	int selection = 0;

	// seeding random number generator
	srand((unsigned int)time(NULL));

	// DISPLAYING DEFAULT BOARD CODE
	SlidingPuzzle board;
	board.InitializeBoard();	// populating the board
	board.PrintBoard();			// printing the board 3x3

	// prompting user to input which board to play or create
	cout << endl << "Please choose from the following" << endl << endl;
	cout << "- Enter 1 to play on the standard board shown above " << endl;
	cout << "- Enter 2 to play on a custom board " << endl;

	// looping to validate input from user
	do {
		cout << endl << "  Selection : ";
		selection = getKeyPress();
		selection = selection - 48;			// converts to the integer the user entered on keyboard
		//cin >> selection;
		if (selection != 1 && selection != 2) {
			cout << endl << "  Please enter 1 or 2" << endl;
		}
	
	} while (selection != 1 && selection != 2);

	// DEFAULT BOARD GAME //
	if (selection == 1) {

		board.StartOfGame();

		// loops until the board is solved, or until the user exits game //
		do {
			setTextColor(7);
			board.keyMessage();

			// movement received by user
			cout << endl << "Enter movement: ";
			direction = getKeyPress();
			direction = direction - 48;

			// moving board tiles
			clearScreen();
			board.slideTile(direction);
			board.PrintBoard();

			// messages based on board state
			if (board.isBoardSolved()) {
				board.keyMessage();
				setTextColor(2);
				cout << "Board is solved, exiting game" << endl;
				setTextColor(7);

			}
			if (direction == 0) {
				//clearScreen();
				setTextColor(7);
				cout << "EXITING GAME" << endl;
			}

		} while (!board.isBoardSolved() && direction != 0);

	}

	// CUSTOM BOARD GAME //
	else if (selection == 2) {

		cout << endl << endl << "CUSTOM BOARD SELECTED" << endl;

		// prompting user to input width
		cout << endl << "Enter width of board: ";
		cin >> width;
		cout << endl;

		// fail flag / validating input
		while (cin.fail() || width < 0 || width > 10) {
			cout << "Invalid value entered, please try again." << endl;
			cin.clear();
			rewind(stdin);

			cout << "Please enter a numerical value from 1 - 10 to set the width of the board : ";
			cin >> width;
			cout << endl;
		}

		// prompting user to enter height
		cout << "Enter height of board: ";
		cin >> height;

		// fail flag / validating input
		while (cin.fail() || height < 0 || height > 10) {
			cout << "Invalid value entered, please try again." << endl;
			cin.clear();
			rewind(stdin);

			cout << "Please enter a numerical value from 1 - 10 to set the height of the board : ";
			cin >> height;
			cout << endl;
		}

		cout << endl;
		clearScreen();

		// creating custom board with given values for width and height
		SlidingPuzzle customBoard = SlidingPuzzle(width, height);
		customBoard.StartOfGame();

		// loops until the board is solved, or until the user exits game
		do {
			setTextColor(7);
			customBoard.keyMessage();

			// movement received by user
			cout << endl << "Enter movement: ";
			direction = getKeyPress();
			direction = direction - 48;

			// moving the board tiles
			clearScreen();
			customBoard.slideTile(direction);
			customBoard.PrintBoard();

			// messages based on board state
			if (customBoard.isBoardSolved()) {
				customBoard.keyMessage();
				setTextColor(2);
				cout << "Board is solved, exiting game" << endl;
				setTextColor(7);

			}
			if (direction == 0) {
				//clearScreen();
				setTextColor(7);
				cout << "EXITING GAME" << endl;
			}

		} while (!customBoard.isBoardSolved() && direction != 0);

	}
		setTextColor(7);
		getKeyPress();
		clearScreen();

	return 0;

}


