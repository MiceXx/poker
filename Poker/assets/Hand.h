#ifndef Hand_h
#define Hand_h

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include "Card.h"

class Hand
{
public:
	Hand();
	Hand(std::vector<Card> cards);
	~Hand();

	bool operator>(const Hand &hand);
	bool operator<(const Hand &hand);
	bool operator==(const Hand &hand);

	std::vector<Card> getHand();
	unsigned int getHandSize();
	int getHiScore();
	int getLoScore();
	void addCard(Card card);
	int computeHiHand();
	int computeLoHand();
	Card getCardByIndex(unsigned int n);
	void printHand();
	std::string GetHiHandName();

protected:
	std::vector<Card>_hand;
	int _hi;
	int _lo;

private:
	void computeHighValue();
	void computeLowValue();
	bool isFourOfAKind();
	bool isFullHouse();
	bool isFlush();
	bool isStraight();
	bool isThreeOfAKind();
	bool isTwoPair();
	bool isPair();
	int getFullHouseRank();
};

/*================================================
UNUSED ENUM REFERENCES BELOW
================================================*/

enum HandType
{
	HIGHCARD,		//100
	ONEPAIR,		//200
	TWOPAIR,		//300
	THREEOFAKIND,	//400
	STRAIGHT,		//500
	FLUSH,			//600
	FULLHOUSE,		//700
	FOUROFAKIND,	//800
	STRAIGHTFLUSH	//900
};

enum CardSuit
{
	INVALIDSUIT,
	CLUB,
	SPADE,
	HEART,
	DIAMOND
};

enum CardRank
{
	INVALIDNUMBER,
	TWO = 2,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
};

#endif
