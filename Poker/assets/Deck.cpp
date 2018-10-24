#include "Deck.h"

Deck::Deck()
{
	std::cout << "Initializing Deck..." << std::endl;
	_index = 0;
	std::srand((unsigned int)std::time(0));
	char suits[4] = { 's','h','d','c' };
	for (int r = 2; r < 15; r++) {
		for (int s = 0; s < 4; s++) {
			_deck.push_back(Card(r, suits[s]));
		}
	}
	std::cout << "Shuffling Deck..." << std::endl;
	random_shuffle(std::begin(_deck), std::end(_deck));
}

Deck::~Deck()
{
}

/*=================================================
Public Methods
=================================================*/

int Deck::cardsRemaining() {
	return 52 - _index;
}

Card Deck::getNextCard() {
	return _deck[_index++];
	throw "Ran out of cards!";
}

void Deck::burnCard() {
	std::cout << "Burning card..." << std::endl;
	_index++;
}

void Deck::shuffle() {
	std::cout << "Shuffling Deck..." << std::endl;
	std::srand((unsigned int)std::time(0));
	random_shuffle(std::begin(_deck), std::end(_deck));
}