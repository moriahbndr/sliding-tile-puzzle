// Moriah Bender
// Console implementation file

#pragma warning(disable:4996)
#pragma warning(disable:6031)

#include <iostream>
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
