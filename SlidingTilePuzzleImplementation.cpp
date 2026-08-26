// Moriah Bender
// Implementation file

#pragma warning(disable:4996)
#pragma warning(disable:6031)

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "SlidingTilePuzzleHeader.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// ** CROSS-PLATFORM CONSOLE HELPERS ** //
void setTextColor(int colorCode) {
#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
#else
	switch (colorCode) {
		case 2:  cout << "\033[32m"; break;	// green
		case 4:  cout << "\033[31m"; break;	// red
		case 12: cout << "\033[91m"; break;	// bright red
		default: cout << "\033[0m";  break;	// reset
	}
#endif
}

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void pauseConsole() {
#ifdef _WIN32
	system("pause");
#else
	cout << "Press Enter to continue..." << endl;
	cin.get();
#endif
}

int getKeyPress() {
#ifdef _WIN32
	return _getche();
#else
	termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	int ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	cout << (char)ch;	// echo manually since terminal echo is disabled
	return ch;
#endif
}

// ** CONSTRUCTOR ** //
SlidingPuzzle::SlidingPuzzle() {
	 
	//default board is 3 * 3
	this-> row = 3;
	this-> column = 3;
	this->theBoard = new(int* [getHeight() * getWidth()]);
	this->winningBoard = new(int* [getHeight() * getWidth()]); // winning game board, this will be an exact copy of theBoard however it will not be manipulated and will remain in the winning state for comparison 

	// creating space for each row
	if (this->theBoard == NULL || this->winningBoard == NULL) {
		return;
	} 

	for (int i = 0; i < getHeight(); i++){
		theBoard[i] = new(int[getWidth()]);
	}

	for (int i = 0; i < getHeight(); i++){
		winningBoard[i] = new(int[getWidth()]);
	}

}

// ** PARAMETERIZED CONSTUCTOR ** //
SlidingPuzzle::SlidingPuzzle(int width, int height) {

	this->setWidth(width);
	this->setHeight(height);

	this->theBoard = new(int* [getHeight() * getWidth()]);
	this->winningBoard = new(int* [getHeight() * getWidth()]);

	// creating space for each row
	if (this->theBoard == NULL || this->winningBoard == NULL) {
		return;
	}

	for (int i = 0; i < getHeight(); i++){
		int x = 0;
		theBoard[i] = new (int[getWidth()]);
	}

	for (int i = 0; i < getHeight(); i++){
		winningBoard[i] = new (int[getWidth()]);
	}
	
	
}

// ** ACCESSORS ** //
int SlidingPuzzle::getHeight() {
	return this->row;
}

int SlidingPuzzle::getWidth() {
	return this->column;
}

// ** MUTATORS ** //
void SlidingPuzzle::setHeight(int height) {
	this->row = height;
}

void SlidingPuzzle::setWidth(int width) {
	this->column = width;
}

// ** KEY MESSAGE ** //
// prints key message to user for board movement and exit game, also prints current status of board solved
void SlidingPuzzle::keyMessage() {

	cout << endl << "| 8 UP | 2 DOWN | 4 LEFT | 6 RIGHT | is board solved ? : ";

	if (isBoardSolved()) {
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
// prints the board, default board until user passes values
void SlidingPuzzle::PrintBoard() {

	cout << endl;

	if (getWidth() * getHeight() != 9) {
		cout << setw(6) << "   CUSTOM BOARD CREATED" << endl << endl;
	}

	for (int i = 0; i < getHeight(); i++){

		for (int j = 0; j < getWidth(); j++){

			if (theBoard[i][j] != NULL) {		// locating '*' character on the board

				// if the tiles on the board matches the winning tiles, color will be adjusted to green , if not, they will be red
				if (theBoard[i][j] == winningBoard[i][j]) {
					setTextColor(2);
				}
				else {
					setTextColor(4);
				}

				cout << setw(6) << theBoard[i][j];

			}
			// outputs '*' in place of nulll placement on board
			if (theBoard[i][j] == NULL) {
				setTextColor(7);
				cout << setw(6) << '*';
			}
		}
		cout << endl << endl;
	}
}

// ** INITIALIZE BOARD ** //
// assigning values to board
void SlidingPuzzle::InitializeBoard() {

	for (int i = 0; i < getHeight(); i++){

		int x = 0; 

		for (int j = 0; j < (getWidth()); j++){

			// if same width and height
			// assigning values to both winning board and the board
			if (getHeight() == getWidth()) {
				this->theBoard[j][i] = ((j + 1) + (i * 1)) + x;
				this->winningBoard[j][i] = ((j + 1) + (i * 1)) + x;

				// value increments as i increases
				x = x + (getHeight() - 1);

				// locating last element in board and assigning it to Null, this will used for the '*' character
				if (i == (getHeight() - 1) && j == (getWidth() - 1)) {
					this->theBoard[j][i] = NULL;
					this->winningBoard[j][i] = NULL;

				}
			}
			// all other boards getting populated with appropriate values
			else {
				this->theBoard[i][j] = (   (   i * getWidth() + (j + 1)  )   );
				this->winningBoard[i][j] = ((i * getWidth() + (j + 1)));

				// locating last element in board and assigning it to Null, this will used for the '*' character
				if (i == (getHeight() - 1) && j == (getWidth() - 1)) {

					this->theBoard[i][j] = NULL;
					this->winningBoard[i][j] = NULL;

				}
			}
		}
	}
}

// ** ISBOARDSOLVED() ** //
// determining if the board is in a solved state or not
// ran into issues when comparing it to the winning board so did not use that for comparison here
bool SlidingPuzzle::isBoardSolved() {

	int value = 0;
	int yes = 0;
	bool analyzeBoard = false;

	// if '*' is in the correct position, analyzeBoard = true
	if (theBoard[getHeight() - 1][getWidth() - 1] == NULL) {
		analyzeBoard = true;
	}
	else {
		analyzeBoard = false;
	}

	// if the '*' is in the correct position, analyze the board for correct values in correct positions 
	if (analyzeBoard) {

		for (int i = 0; i < getHeight(); i++){

			int x = 0;

			for (int j = 0; j < (getWidth()); j++){

				//** if it is a 3x3 / 5x5 / 7x7 , etc board **
				if (getHeight() == getWidth()) {	
					value = ((j + 1) + (i * 1)) + x;	// value = the correct value that should be in each spot (by calculations)
					x = x + (getHeight() - 1);			// increment and add to x value as each column increments
				
					// if the spot on the board has the correct value, increment yes, if not, it will not be changed
					if (theBoard[j][i] == value) {
						yes++;
					}
				}

				//** if it is any other board **
				else {
					value = ((j + 1) + (i * getWidth()));
					if (theBoard[i][j] == value) {
						yes++;
					}
				}
			}
		}

		// if yes totals (height * width) -1, the board is solved
		if (yes == ( (getHeight() * getWidth()) -1 ) ) {
			return true;
		}
		else {
			return false;
		}
		return 0;
	}
	return 0;
}

// ** SLIDING TILES ** //
bool SlidingPuzzle::slideTile(int directionCode) {

	// UP	8
	// DOWN	2
	// LEFT 4
	// RIGHT 6

	int* star = NULL;
	int rowPosition = 0;
	int columnPosition = 0;

	// first searching for the special character on the board
	// assigning the row and column positions of the * as well
	for (int i = 0; i < getHeight(); i++) {
	
		for (int j = 0; j < getWidth(); j++) {

			if (theBoard[i][j] == NULL) {

				star = &theBoard[i][j];		// int* star points to whatever address the star is located in
				rowPosition = i;
				columnPosition = j;

			}
		}
	}	

	switch (directionCode) {

		// UP
		case 8:
			if (rowPosition > 0) {
				int* up = &theBoard[rowPosition - 1][columnPosition];	// *up  points to whatver address is above the Star char
				int temp = *up;											// assigning the value in up to temp
				*up = *star;											// address of up now holds star char
				*star = temp;											// address of star now holds temp
				return true;
			}
			else {
				return false;
			}
			break;

		// DOWN
		case 2:
			if (rowPosition < (getHeight() - 1)) {
				int* down = &theBoard[rowPosition + 1][columnPosition];
				int temp = *down;

				if (star) {
					*down = *star;
					*star = temp;
				}
				return true;
			}
			else {
				return false;
			}
			break;

		// LEFT
		case 4:
			if (columnPosition > 0) {
				int* left = &theBoard[rowPosition][columnPosition - 1];
				int temp = *left;
				*left = *star;
				*star = temp;
				return true;
			}
			else {
				return false;
			}
			break;

		// RIGHT
		case 6:
			if (columnPosition < (getWidth() - 1)) {

				if (star) {
					int* right = &theBoard[rowPosition][columnPosition + 1];
					int temp = *right;
					*right = *star;
					*star = temp;
				}
				return true;
				
			}
			else {
				return false;
			}
			break;
			
		default:
			return false;

	}

}



// ** SCRAMBLING THE BOARD ** //
void SlidingPuzzle::scrambleBoard() {

	// seeding of the random number taking place in main() driver
	for (int i = 1; i < 15000; i++) {
		int randomNum = (rand() % 4 + 1) * 2;	// random numbers 2,4,6,8 which correspond with the user input for movement of board being generated
		slideTile(randomNum);					// passing the random numbers, 2,4,6,8 , into slideTile() function
	}

	// Printing the scramble board message to user
	cout << endl << "scrambling board..." << endl << endl;
	pauseConsole();
	clearScreen();
	cout << endl << "SCRAMBLING COMPLETE " << endl << endl;
	pauseConsole();
	clearScreen();
}



// ** DESTRUCTOR CODE ** //
SlidingPuzzle::~SlidingPuzzle() {

	// deallocating memory

	for (int i = 0; i < getHeight(); i++) {
		delete[] theBoard[i];
		delete[] winningBoard[i];
	}
	delete[] theBoard;
	delete[] winningBoard;


}

// ** START OF GAME MESSAGE ** // 
void SlidingPuzzle::StartOfGame() {

	cout << endl;
	clearScreen();

	// creating board
	InitializeBoard();

	// printing the board
	PrintBoard();

	// scrambling the board
	scrambleBoard();

	// printing the board
	PrintBoard();
}


