// Moriah Bender
// Player implementation file

#include <stdexcept>

#include "Player.h"

// ** CONSTRUCTOR ** //
Player::Player(const std::string& name) {

	if (!isValidName(name)) {
		throw std::invalid_argument("name must be 1 - 20 characters and not only spaces");
	}

	this->name_ = name;
}

// ** ACCESSORS ** //
const std::string& Player::name() const {
	return this->name_;
}

// ** ISVALIDNAME() ** //
bool Player::isValidName(const std::string& name) {

	if (name.empty() || (int)name.length() > MAX_NAME_LENGTH) {
		return false;
	}

	// looking for at least one character that is not a space
	return name.find_first_not_of(' ') != std::string::npos;
}
