#ifndef Deck_h
#define Deck_h

#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include "Card.h"

class Deck
{
public:
	Deck();
	~Deck();
	
	int cardsRemaining();
	Card getNextCard();
	void shuffle();
	void burnCard();

private:
	std::vector<Card> _deck;
	int _index;
};

#endif
