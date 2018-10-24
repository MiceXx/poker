#ifndef Card_h
#define Card_h

#include <iostream>
#include <string>

class Card
{
public:
	Card();
	Card(int rank, char suit);
	~Card();
	
	bool operator>(const Card &card);
	bool operator<(const Card &card);
	bool operator==(const Card &card);
	bool operator!=(const Card &card);

	int getRank();
	char getSuit();
	std::string getCardAsString();
	void printCard();

private:
	int _rank;
	char _suit;
};

#endif