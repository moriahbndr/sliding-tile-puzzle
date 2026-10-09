// Moriah Bender
// Player header file
// A player in the game, no console input or output and nothing saved between runs

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {

private:
	// ** ATTRIBUTES ** //
	std::string name_;

public:

	static const int MAX_NAME_LENGTH = 20;

	// ** CONSTRUCTOR ** //
	explicit Player(const std::string& name);			// throws std::invalid_argument if the name is not valid

	// ** ACCESSORS ** //
	const std::string& name() const;

	// ** METHODS ** //
	static bool isValidName(const std::string& name);	// valid names are 1 - 20 characters and not only spaces

};
#endif
