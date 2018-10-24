#include "Board.h"

Board::Board()
{
}

Board::~Board()
{
}

Board::Board(std::vector<Card> cards) {
	_board = cards;
}

/*=================================================
Public Methods
=================================================*/

std::vector<Card> Board::getBoard() {
	return _board;
}

void Board::addCard(Card card) {
	_board.push_back(card);
}

Card Board::getCardByIndex(unsigned int n) {
	if (n >= 0 && n < _board.size()) {
		return _board[n];
	}
	else {
		std::cout << "Board index out of range:" << n << std::endl;
		throw "Tried to access board index out of range";
	}
}

void Board::printBoard() {
	std::cout << "Board: [";
	for (int i = 0; i < _board.size(); i++) {
		std::cout << _board[i].getCardAsString();
		if (i != _board.size() - 1) {
			std::cout << "-";
		}
	}
	std::cout << "]" << std::endl;
}

/*=================================================
Private Methods
=================================================*/