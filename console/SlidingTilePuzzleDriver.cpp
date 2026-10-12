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
#include <string>

#include "../engine/Board.h"
#include "../engine/Game.h"
#include "../engine/Player.h"
#include "Console.h"

using namespace std;

void printBoard(const Board& board);						// prints the board, green tiles are in the correct position, red tiles are not
void keyMessage(const Game& game, const Player& player);	// printing key message to user along with player name, move count, time, current board status and exit code
void startOfGame(const Game& game);							// prints the solved board, the scramble messages, then the scrambled board
void playGame(int width, int height, const Player& player);	// loops until the board is solved, or until the user exits game
int readBoardSize(const char* side);						// prompts until the user enters a value from 2 - 10
Player readPlayer();						// prompts until the user enters a valid name

int main() {

	int height = 0;
	int width = 0;
	int selection = 0;

	// player enters their name once on start up, nothing is saved after the game closes
	Player player = readPlayer();
	clearScreen();
	cout << endl << "Welcome, " << player.name() << endl;

	// DISPLAYING DEFAULT BOARD CODE
	Board board;
	printBoard(board);			

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
		playGame(board.width(), board.height(), player);

	} else if (selection == 2) {		// CUSTOM BOARD GAME //

		cout << endl << endl << "CUSTOM BOARD SELECTED" << endl << endl;

		width = readBoardSize("width");
		height = readBoardSize("height");

		cout << endl;
		clearScreen();

		// playing on a custom board with given values for width and height
		playGame(width, height, player);
	}

	setTextColor(7);
	getKeyPress();
	clearScreen();

	return 0;

}

// ** PLAYER NAME INPUT ** //
Player readPlayer() {

	string name;

	cout << endl << "Enter your name: ";

	// looping to validate input from user
	while (true) {

		// input has ended, so there is nobody to ask again
		if (!getline(cin, name)) {
			name = "Player";
			break;
		}
		if (Player::isValidName(name)) {
			break;
		}
		cout << "Please enter a name from 1 - " << Player::MAX_NAME_LENGTH << " characters : ";
	}

	return Player(name);
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
void playGame(int width, int height, const Player& player) {

	int key = 0;
	random_device seedSource;

	// creating the game, the board is scrambled and the move count starts at 0
	Game game(width, height, seedSource());

	startOfGame(game);

	// the player can see the scrambled board now, so the clock starts
	game.startTimer();

	do {
		setTextColor(7);
		keyMessage(game, player);

		// movement received by user
		cout << endl << "Enter movement: ";
		key = getKeyPress();

		// moving board tiles
		clearScreen();
		switch (key) {
			case KEY_ARROW_UP:    game.move(Direction::Up);    break;
			case KEY_ARROW_DOWN:  game.move(Direction::Down);  break;
			case KEY_ARROW_LEFT:  game.move(Direction::Left);  break;
			case KEY_ARROW_RIGHT: game.move(Direction::Right); break;
		}
		printBoard(game.board());

		// messages based on board state
		if (game.isSolved()) {
			keyMessage(game, player);
			setTextColor(2);
			cout << "Board is solved, exiting game" << endl;
			setTextColor(7);

		}
		if (key == '0') {
			keyMessage(game, player);
			setTextColor(7);
			cout << "EXITING GAME" << endl;
		}

	} while (!game.isSolved() && key != '0');
}

// ** START OF GAME MESSAGE ** //
void startOfGame(const Game& game) {

	cout << endl;
	clearScreen();

	// printing the solved board
	printBoard(Board(game.board().width(), game.board().height()));

	// Printing the scramble board message to user
	cout << endl << "scrambling board..." << endl << endl;
	pauseConsole();
	clearScreen();
	cout << endl << "SCRAMBLING COMPLETE " << endl << endl;
	pauseConsole();
	clearScreen();

	// printing the scrambled board
	printBoard(game.board());
}

// ** KEY MESSAGE ** //
// prints player name, move count, time and key message to user for exit game, also prints current status of board solved
void keyMessage(const Game& game, const Player& player) {

	// whole seconds played so far, shown as minutes:seconds
	int seconds = (int)game.elapsedSeconds();

	cout << endl << "Player : " << player.name() << /* random generated emoji/character here*/" | Moves : " << game.moves();
	cout << " | Time : " << seconds / 60 << ":" << setfill('0') << setw(2) << seconds % 60 << setfill(' ');
	cout << " | is board solved ? : ";

	if (game.isSolved()) {
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
