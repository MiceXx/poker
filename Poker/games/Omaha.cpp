#include "Omaha.h"

/*
	HIGHCARD, 100
	ONEPAIR, 200
	TWOPAIR, 300
	THREEOFAKIND, 400
	STRAIGHT, 500
	FLUSH, 600
	FULLHOUSE, 700
	FOUROFAKIND, 800
	STRAIGHTFLUSH 900
*/

Omaha::Omaha()
{
}

Omaha::Omaha(Hand handA, Hand handB, Board board)
{
	this->_handA = handA;
	this->_handB = handB;
	this->_board = board;
}

Omaha::~Omaha()
{
}

/*=================================================
Public Methods
=================================================*/

/*=================================================
Private Methods
=================================================*/
Hand Omaha::hiHand(Hand hand) {	//Using brute force with all possible combination of hands (60 total)... Not the best method, but easiest given the time constraint
	Hand maxHand = Hand({ hand.getCardByIndex(0),
							hand.getCardByIndex(1),
							_board.getCardByIndex(0),
							_board.getCardByIndex(1),
							_board.getCardByIndex(2) });
	for (size_t i = 0; i < 4; i++) {	//Loop hand
		for (size_t j = i + 1; j < 4; j++) {
			for (size_t ii = 0; ii < 5; ii++) {	//Loop Board
				for (size_t jj = ii + 1; jj < 5; jj++) {
					for (size_t kk = jj + 1; kk < 5; kk++) {
						Hand h = Hand({ hand.getCardByIndex(i),
							hand.getCardByIndex(j),
							_board.getCardByIndex(ii),
							_board.getCardByIndex(jj),
							_board.getCardByIndex(kk) });
						int k = compareHi(h, maxHand);
						if (k == 1) maxHand = h;
					}
				}
			}
		}
	}
	return maxHand;
}

Hand Omaha::loHand(Hand hand) {
	Hand minHand = Hand({ hand.getCardByIndex(0),
							hand.getCardByIndex(1),
							_board.getCardByIndex(0),
							_board.getCardByIndex(1),
							_board.getCardByIndex(2) });
	for (size_t i = 0; i < 4; i++) {	//Loop hand
		for (size_t j = i + 1; j < 4; j++) {
			for (size_t ii = 0; ii < 5; ii++) {	//Loop Board
				for (size_t jj = ii + 1; jj < 5; jj++) {
					for (size_t kk = jj + 1; kk < 5; kk++) {
						Hand h = Hand({ hand.getCardByIndex(i),
							hand.getCardByIndex(j),
							_board.getCardByIndex(ii),
							_board.getCardByIndex(jj),
							_board.getCardByIndex(kk) });
						if (h.getLoScore() != INT_MAX) {
							int k = compareLo(h, minHand);
							if (k == 2) minHand = h;
						}
					}
				}
			}
		}
	}
	return minHand;
}

std::string Omaha::Solve() {
	std::unordered_map<int, std::string> handRank = {
		{100,"High Card"}, {200, "One Pair"}, {300, "Two Pair"},
		{400, "3-of-a-kind"}, {500, "Straight"}, {600, "Flush"},
		{700, "Full House"}, {800, "4-of-a-Kind"}, {900, "Straight Flush"}
	};
	std::string answer = "";

	/****************************FIND THE HI WINNER**************************/
	Hand hiA = hiHand(_handA);
	Hand hiB = hiHand(_handB);
	int m = compareHi(hiA, hiB);
	Hand hiWinner;
	if (m == 1) {
		int k = hiA.computeHiHand();
		std::string handName;
		if (k >= 700 && k < 800) handName = "Full House";
		else handName = handRank[k];
		answer = answer + "HandA Wins Hi (" + handName + ") ; ";
		hiWinner = hiA;
	}
	else if (m == 2) {
		int k = hiB.computeHiHand();
		std::string handName;
		if (k >= 700 && k < 800) handName = "Full House";
		else handName = handRank[k];
		answer = answer + "HandB Wins Hi (" + handName + ") ; ";
		hiWinner = hiB;
	}
	else {
		int k = hiA.computeHiHand();
		std::string handName;
		if (k >= 700 && k < 800) handName = "Full House";
		else handName = handRank[k];
		answer = answer + "Split Pot Hi (" + handName + ") ; ";
		hiWinner = hiA;
	}

	/***************************FIND THE Lo WINNER**************************/
	Hand loA = loHand(_handA);
	Hand loB = loHand(_handB);
	int n = compareLo(loA, loB);
	if (loB.computeLoHand() == INT_MAX && loA.computeLoHand() == INT_MAX)
		answer = answer + "No hand qualified for Low";
	else if ((loB.computeLoHand() == INT_MAX && loA.computeLoHand() != INT_MAX && compareHi(hiWinner, loA) == 0) || n == 2)
		answer = answer + "HandA Wins Lo";
	else if ((loA.computeLoHand() == INT_MAX && loB.computeLoHand() != INT_MAX && compareHi(hiWinner, loB) == 0) || n == 1)
		answer = answer + "HandB Wins Lo";
	else
		answer = answer + "Split Pot Lo";
	return answer;
}


/*
	compareHi:
		Returns 1 if hand 1 is bigger
		Returns 2 if hand 2 is bigger
		Returns 0 if both hands are equal
		ONLY COMPARES HI VAL
*/
int Omaha::compareHi(Hand hand1, Hand hand2) {
	if (hand1.getHandSize() != 5) {
		throw "hand1 does not have 5 cards";
	}
	if (hand2.getHandSize() != 5) {
		throw "hand2 does not have 5 cards";
	}
	if (hand1.computeHiHand() > hand2.computeHiHand()) {
		return 1;
	}
	else if (hand2.computeHiHand() > hand1.computeHiHand()) {
		return 2;
	}
	else { //Hand Hi values are same

		for (size_t i = 0; i < 5; i++) {
			if (hand1.getCardByIndex(i).getRank() > hand2.getCardByIndex(i).getRank()) {
				return 1;
			}
			else if (hand2.getCardByIndex(i).getRank() > hand1.getCardByIndex(i).getRank()) {
				return 2;
			}
		}
		return 0;
	}
}

/*
	compareLo:
		Returns 1 if hand 1 is bigger
		Returns 2 if hand 2 is bigger
		Returns 0 if both hands are equal
		ONLY COMPARES LO VAL
*/
int Omaha::compareLo(Hand hand1, Hand hand2) {
	if (hand1.computeLoHand() > hand2.computeLoHand()) {
		return 1;
	}
	else if (hand2.computeLoHand() > hand1.computeLoHand()) {
		return 2;
	}
	else { //Hand Hi values are same

		for (size_t i = 0; i < 5; i++) {
			if (hand1.getCardByIndex(i).getRank() > hand2.getCardByIndex(i).getRank()) {
				return 1;
			}
			else if (hand2.getCardByIndex(i).getRank() > hand1.getCardByIndex(i).getRank()) {
				return 2;
			}
		}
		return 0;
	}
}