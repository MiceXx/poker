#ifndef Ranker_h
#define Ranker_h

#include <iostream>
#include "../assets/Hand.h"
#include "../assets/Board.h"


/*
==========
Hi Ranking
==========
Each hand will be given a 'hi' score. We determine this score by first checking all possible hand rankings, starting with the top (Straight flush).
The rankings are provided as follows:
	HIGHCARD, 100
	ONEPAIR, 200
	TWOPAIR, 300
	THREEOFAKIND, 400
	STRAIGHT, 500
	FLUSH, 600
	FULLHOUSE, 700
	FOUROFAKIND, 800
	STRAIGHTFLUSH 900
To compare two hands on the 'hi' score, we must first check the ranking.
If they are the same, then we can check each individual card (in sorted order) to find the highest 'kicker'

==========
Lo Ranking
==========
Each hand will be given a 'lo' score. This score is initialized to infinity.
If a hand does not have a 'lo' hand, this score is also set to infinity. If a low hand is available, we create a 5 digit score for the hand.
The highest possible 'lo' hand will be scored 87654. The lowest possible 'lo' hand will be scored 54321. To compare two low hands, we must simply compare this score.

*/

class Omaha
{
public:
	Omaha();
	Omaha(Hand hand1, Hand hand2, Board board);
	~Omaha();

	std::string Solve();

private:
	Board _board;
	Hand _handA;
	Hand _handB;

	/*
	highHand:
		Finds the highest possible hand that can be made from the current hand and the board
		RETURNS the highest hand and the rank
*/
	Hand hiHand(Hand hand);

	/*
		lowHand:
			Finds the lowest possible hand that can be made from the current hand and the board
			RETURNS the lowest hand and the rank
	*/
	Hand loHand(Hand hand);

	/*
	compareHi:
		Returns 1 if hand 1 is bigger
		Returns 2 if hand 2 is bigger
		Returns 0 if both hands are equal
		ONLY COMPARES Hi VAL
	*/
	int compareHi(Hand hand1, Hand hand2);

	/*
	compareLo:
		Returns 1 if hand 1 is bigger
		Returns 2 if hand 2 is bigger
		Returns 0 if both hands are equal
		ONLY COMPARES LO VAL
	*/
	int compareLo(Hand hand1, Hand hand2);

};

#endif