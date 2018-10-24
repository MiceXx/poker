#ifndef Board_h
#define Board_h

#include <vector>
#include <sstream>
#include <unordered_map>
#include "Card.h"

class Board
{
public:
	Board();
	Board(std::vector<Card> cards);
	~Board();

	std::vector<Card> getBoard();
	void addCard(Card card);
	Card getCardByIndex(unsigned int n);
	void printBoard();

private:
	std::vector<Card>_board;
};

#endif