// Moriah Bender
// Board implementation file

#include <random>
#include <stdexcept>
#include <utility>

#include "Board.h"

// ** CONSTRUCTOR ** //
// builds a solved board, 3 * 3 by default
Board::Board(int width, int height) {

	if (width < 2 || height < 2) {
		throw std::invalid_argument("board must be at least 2 x 2");
	}

	this->width_ = width;
	this->height_ = height;
	this->tiles_.resize(width * height);

	// tiles count up from 1, the last spot is the blank
	for (int i = 0; i < width * height - 1; i++) {
		tiles_[i] = i + 1;
	}
	this->blank_ = width * height - 1;
	tiles_[blank_] = 0;
}

// ** SAVED STATE CONSTRUCTOR ** //
// rebuilds a board from tiles listed row by row, 0 is the blank
Board::Board(int width, int height, std::vector<int> tiles) {

	if (width < 2 || height < 2) {
		throw std::invalid_argument("board must be at least 2 x 2");
	}

	int count = width * height;
	if ((int)tiles.size() != count) {
		throw std::invalid_argument("tile count does not match board size");
	}

	// every value from 0 to count - 1 must appear exactly once
	std::vector<bool> seen(count, false);
	for (int i = 0; i < count; i++) {
		int tile = tiles[i];
		if (tile < 0 || tile >= count || seen[tile]) {
			throw std::invalid_argument("tiles must be the values 0 to (width * height) - 1 with no repeats");
		}
		seen[tile] = true;

		if (tile == 0) {
			this->blank_ = i;
		}
	}

	this->width_ = width;
	this->height_ = height;
	this->tiles_ = std::move(tiles);
}

// ** ACCESSORS ** //
int Board::width() const {
	return this->width_;
}

int Board::height() const {
	return this->height_;
}

const std::vector<int>& Board::tiles() const {
	return this->tiles_;
}

// ** MOVING THE BLANK ** //
bool Board::move(Direction dir) {

	int row = blank_ / width_;
	int col = blank_ % width_;

	switch (dir) {
		case Direction::Up:    if (row == 0)           return false; row--; break;
		case Direction::Down:  if (row == height_ - 1) return false; row++; break;
		case Direction::Left:  if (col == 0)           return false; col--; break;
		case Direction::Right: if (col == width_ - 1)  return false; col++; break;
		default: return false;
	}

	// swapping the blank with the tile it is moving onto
	int target = row * width_ + col;
	std::swap(tiles_[blank_], tiles_[target]);
	blank_ = target;
	return true;
}

// ** ISSOLVED() ** //
// solved when the tiles count up from 1 and the blank is in the last spot
bool Board::isSolved() const {

	int last = width_ * height_ - 1;

	for (int i = 0; i < last; i++) {
		if (tiles_[i] != i + 1) {
			return false;
		}
	}
	return tiles_[last] == 0;
}

// ** SCRAMBLING THE BOARD ** //
// random legal moves keep the board solvable
// rng() % 4 is used instead of a distribution class so every compiler gives the same board for the same seed
void Board::scramble(std::uint32_t seed) {

	std::mt19937 rng(seed);

	for (int i = 0; i < 15000; i++) {
		move(static_cast<Direction>(rng() % 4));
	}
}
