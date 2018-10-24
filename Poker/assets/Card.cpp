#include "Card.h"


Card::Card()
{
}

Card::~Card()
{
}

Card::Card(int rank, char suit) {
	_rank = rank;
	_suit = suit;
}


bool Card::operator>(const Card &card) {
	return _rank > card._rank;
}
bool Card::operator<(const Card &card) {
	return _rank < card._rank;
}
bool Card::operator==(const Card &card) {
	return _rank == card._rank;
}
bool Card::operator!=(const Card &card) {
	return _rank != card._rank;
}

int Card::getRank() {
	return _rank;
}

char Card::getSuit() {
	return _suit;
}

std::string Card::getCardAsString() {
	std::string cardAsString = "";
	if (_rank < 10) {
		cardAsString += std::to_string(_rank);
	}
	else if (_rank == 10) {
		cardAsString += 'T';
	}
	else if (_rank == 11) {
		cardAsString += 'J';
	}
	else if (_rank == 12) {
		cardAsString += 'Q';
	}
	else if (_rank == 13) {
		cardAsString += 'K';
	}
	else if (_rank == 14) {
		cardAsString += 'A';
	}
	cardAsString += _suit;
	return cardAsString;
}

void Card::printCard() {
	std::string s = getCardAsString();
	std::cout << s;
}