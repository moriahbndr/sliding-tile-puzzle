# Sliding Tile Puzzle

Originally created by Moriah Bender in September 2023, this project has since been revisited, refactored, and pushed to GitHub as an ongoing project. 

A console-based sliding tile puzzle (8-puzzle style) written in C++. Play the standard 3x3 board or generate a custom-sized board up to 10x10, then race to slide the tiles back into numerical order.

This is an ongoing project that I plan to expand from a console-based C++ game into a full-stack, real-time puzzle platform. I’ll be refactoring the current game logic into a reusable C++ engine, building a web-based frontend, adding player profiles and race history, and implementing real-time 1 v 1 races where both players compete on the same starting board.

## Features

- Standard 3x3 board, or a custom width/height (1–10) of your choosing
- Board is randomly scrambled with 15,000 legal moves before each game
- Color-coded tiles: green when a tile is in its correct position, red when it isn't
- Live "is board solved?" status after every move
- Cross-platform: builds and runs on macOS, Linux, and Windows

## Requirements

- A C++17-compatible compiler (`clang++`, `g++`, or MSVC)

## Running Instructions

- for MacOS , in the terminal run : `make run`

## How to Play

1. On launch, choose:
   - `1` to play the standard 3x3 board
   - `2` to create a custom board by entering a width and height (1–10)

2. The board scrambles automatically, then gameplay begins.

3. Enter a move using the keypad-style direction codes:

   | Key | Direction |
   |-----|-----------|
   | `8` | Up        |
   | `2` | Down      |
   | `4` | Left      |
   | `6` | Right     |
   | `0` | Exit game |

4. The direction you enter slides the tile adjacent to the blank space (`*`) in that direction.

5. Solve the board by arranging all tiles in ascending order, left to right, top to bottom, with the blank space in the bottom-right corner.

## Project Structure

```
SlidingTilePuzzleDriver.cpp          # main() / program entry point and game loop
SlidingTilePuzzleImplementation.cpp  # SlidingPuzzle class implementation
SlidingTilePuzzleHeader.h            # SlidingPuzzle class declaration
Makefile                             # build via `make` / `make run` / `make clean`
```

## Author

Moriah Bender
2023
Entry-Level Software Engineer
