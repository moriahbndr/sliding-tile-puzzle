// Moriah Bender
// Console header file

#ifndef CONSOLE_H
#define CONSOLE_H

// ** CROSS-PLATFORM CONSOLE HELPERS ** //
void setTextColor(int colorCode);	// sets console text color (Windows console API or ANSI escape codes)
void clearScreen();					// clears the console (cls on Windows, clear elsewhere)
void pauseConsole();				// waits for user input before continuing (pause on Windows)
int getKeyPress();					// reads a single keypress without waiting for Enter, arrow keys come back as the codes below

// ** ARROW KEY CODES ** //
// values returned by getKeyPress() for the arrow keys, chosen to be outside the range of normal characters
const int KEY_ARROW_UP = 1000;
const int KEY_ARROW_DOWN = 1001;
const int KEY_ARROW_LEFT = 1002;
const int KEY_ARROW_RIGHT = 1003;

#endif
