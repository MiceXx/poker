#include "Player.h"

Player::Player()
{
}

Player::Player(int n) {
	_chips = n;
	_allIn = false;
	_folded = false;
	_playing = true;
}

Player::~Player()
{
}

void Player::winChips(int n) {
	_chips+= n;
}

bool Player::loseChips(int n) {
	if(_chips > n){
		_chips -= n;
		return true;
	}
	else if (_chips == n) {
		_chips = 0;
		_allIn = true;
	}
	return false;
}

int Player::getChipCount() {
	return _chips;
}

void Player::setFold() {
	_folded = true;
	_playing = false;
	_allIn = false;
}
void Player::setPlaying() {
	if (_chips > 0) {
		_playing = true;
	}
	_folded = false;
	_allIn = false;
}

int Player::goAllIn() {
	int n = _chips;
	_chips = 0;
	_folded = false;
	_playing = true;
	_allIn = true;
	return n;
}

bool Player::isPlaying() {
	return _playing;
}
bool Player::isAllin() {
	return _allIn;
}
bool Player::isFolded() {
	return _folded;
}