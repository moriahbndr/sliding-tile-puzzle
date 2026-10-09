// Moriah Bender
// Console header file

#ifndef CONSOLE_H
#define CONSOLE_H

// ** CROSS-PLATFORM CONSOLE HELPERS ** //
void setTextColor(int colorCode);	// sets console text color (Windows console API or ANSI escape codes)
void clearScreen();					// clears the console (cls on Windows, clear elsewhere)
void pauseConsole();				// waits for user input before continuing (pause on Windows)
int getKeyPress();					// reads a single keypress without waiting for Enter

#endif
