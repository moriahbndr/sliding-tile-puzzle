// Moriah Bender
// Console implementation file

#pragma warning(disable:4996)
#pragma warning(disable:6031)

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Console.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

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
	int ch = _getche();

	// arrow keys arrive as two values on Windows : 0 or 224, then a code for the key
	if (ch == 0 || ch == 224) {
		switch (_getch()) {
			case 72: return KEY_ARROW_UP;
			case 80: return KEY_ARROW_DOWN;
			case 75: return KEY_ARROW_LEFT;
			case 77: return KEY_ARROW_RIGHT;
		}
	}
	return ch;
#else
	termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	int ch = getchar();

	// arrow keys arrive as three characters : Escape, then '[' (or 'O'), then a letter
	if (ch == 27) {

		// waiting at most a tenth of a second for the rest, so pressing Escape on its own does not hang
		newt.c_cc[VMIN] = 0;
		newt.c_cc[VTIME] = 1;
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);

		int next = getchar();
		if (next == '[' || next == 'O') {
			switch (getchar()) {
				case 'A': ch = KEY_ARROW_UP;    break;
				case 'B': ch = KEY_ARROW_DOWN;  break;
				case 'D': ch = KEY_ARROW_LEFT;  break;
				case 'C': ch = KEY_ARROW_RIGHT; break;
			}
		}
		clearerr(stdin);	// a timed out read leaves stdin marked as ended, this resets it
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	// echo manually since terminal echo is disabled, arrow keys and Escape have nothing to print
	if (ch != 27 && ch < KEY_ARROW_UP) {
		cout << (char)ch;
	}
	return ch;
#endif
}
