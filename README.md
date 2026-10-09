# Sliding Tile Puzzle

Originally created by Moriah Bender in September 2023, this project has since been revisited, refactored, and pushed to GitHub as an ongoing project. 

A console-based sliding tile puzzle (8-puzzle style) written in C++. Play the standard 3x3 board or generate a custom-sized board up to 10x10, then race to slide the tiles back into numerical order.

This is an ongoing project that I plan to expand from a console-based C++ game into a full-stack, real-time puzzle platform. I’ll be refactoring the current game logic into a reusable C++ engine, building a web-based frontend, adding player profiles and race history, and implementing real-time 1 v 1 races where both players compete on the same starting board.

## Features

- Standard 3x3 board, or a custom width/height (2–10) of your choosing
- Board is randomly scrambled with 15,000 legal moves before each game
- Color-coded tiles: green when a tile is in its correct position, red when it isn't
- Live "is board solved?" status after every move
- Cross-platform: builds and runs on macOS, Linux, and Windows

## Requirements

- A C++17-compatible compiler (`clang++`, `g++`, or MSVC)

## Running Instructions

- for MacOS , in the terminal run : `make run`

## How to Play

1. On launch, enter your name (1–20 characters). No account is created and nothing is saved.

2. Then choose:
   - `1` to play the standard 3x3 board
   - `2` to create a custom board by entering a width and height (2–10)

3. The board scrambles automatically, then gameplay begins.

4. Enter a move using the arrow keys:

   | Key | Direction |
   |-----|-----------|
   | `↑` | Up        |
   | `↓` | Down      |
   | `←` | Left      |
   | `→` | Right     |
   | `0` | Exit game |

5. The direction you enter slides the tile adjacent to the blank space (`*`) in that direction.

6. Solve the board by arranging all tiles in ascending order, left to right, top to bottom, with the blank space in the bottom-right corner.

## Project Structure

```
engine/
  Board.cpp                          # Board class implementation (game engine, no console I/O)
  Board.h                            # Board class declaration
  Player.cpp                         # Player class implementation (name entered on start up, nothing saved)
  Player.h                           # Player class declaration
console/
  SlidingTilePuzzleDriver.cpp        # main() / program entry point, game loop and board printing
  Console.cpp                        # cross-platform console helpers (color, clear, keypress)
  Console.h                          # console helper declarations
Makefile                             # build via `make` / `make run` / `make clean`
```

## Author

Moriah Bender
2023
Entry-Level Software Engineer
