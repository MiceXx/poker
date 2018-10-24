#include "Hand.h"

Hand::Hand()
{
	this->_lo = INT_MAX;
	this->_hi = INT_MIN;
}

Hand::~Hand()
{
}

Hand::Hand(std::vector<Card> cards) {
	_hand = cards;
	this->_lo = INT_MAX;
	this->_hi = INT_MIN;
}

bool Hand::operator>(const Hand &hand) {
	if (_hi > hand._hi) return true;
	if (_hi == hand._hi) {
		for (size_t i = 0; i < _hand.size(); i++) {
			if (_hand[i] > hand._hand[i]) return true;
			else if (_hand[i] < hand._hand[i]) false;
		}
		return false;
	}
	return false;
}

bool Hand::operator<(const Hand &hand) {
	if (_hi < hand._hi) return true;
	if (_hi == hand._hi) {
		for (size_t i = 0; i < _hand.size(); i++) {
			if (_hand[i] < hand._hand[i]) return true;
			else if (_hand[i] > hand._hand[i]) false;
		}
		return false;
	}
	return false;
}

bool Hand::operator==(const Hand &hand) {
	if (_hi != hand._hi) return false;
	for (size_t i = 0; i < _hand.size(); i++) {
		if (_hand[i] != hand._hand[i]) return false;
	}
	return true;
}

/*=================================================
Public Methods
=================================================*/

std::vector<Card> Hand::getHand() {
	return _hand;
}

unsigned int Hand::getHandSize() {
	return _hand.size();
}

int Hand::getHiScore() {
	return _hi;
}
int Hand::getLoScore() {
	return _lo;
}

void Hand::addCard(Card card) {
	_hand.push_back(card);
	std::sort(_hand.begin(), _hand.end());
}

int Hand::computeHiHand() {
	std::sort(_hand.begin(), _hand.end());
	computeHighValue();
	return _hi;
}

int Hand::computeLoHand() {
	std::sort(_hand.begin(), _hand.end());
	computeLowValue();
	return _lo;
}

Card Hand::getCardByIndex(unsigned int n) {
	if (n >= 0 && n < _hand.size()) {
		return _hand[n];
	}
	else {
		std::cout << "Hand index out of range:" << n << std::endl;
		throw "Tried to access hand index out of range";
	}
}

void Hand::printHand() {
	for (int i = 0; i < _hand.size(); i++) {
		std::cout << _hand[i].getCardAsString();
		if (i != _hand.size() - 1) {
			std::cout << "-";
		}
	}
	std::cout << std::endl;
}

std::string Hand::GetHiHandName() {
	std::unordered_map<int, std::string> handRank = {
		{100,"High Card"}, {200, "One Pair"}, {300, "Two Pair"},
		{400, "3-of-a-kind"}, {500, "Straight"}, {600, "Flush"},
		{700, "Full House"}, {800, "4-of-a-Kind"}, {900, "Straight Flush"}
	};

	if (_hi >= 700 && _hi < 800) return "Full House";
	else return handRank[_hi];
}

/*===================================================
Private Methods
=====================================================*/

void Hand::computeHighValue() {

	if (isFlush() && this->isStraight()) _hi = 900;
	else if (isFourOfAKind()) _hi = 800;
	else if (isFullHouse()) _hi = getFullHouseRank();
	else if (isFlush()) _hi = 600;
	else if (isStraight()) _hi = 500;
	else if (isThreeOfAKind()) _hi = 400;
	else if (isTwoPair()) _hi = 300;
	else if (isPair()) _hi = 200;
	else _hi = 100;
}

void Hand::computeLowValue() {
	int tot = 0;
	if (!isPair()) {
		if (_hand[0].getRank() <= 8) {	//NO ACE
			for (size_t i = 0; i < 5; i++) {
				tot = tot * 10 + _hand[i].getRank();
			}

			_lo = tot;
		}
		else if (_hand[0].getRank() == 14 && _hand[1].getRank() <= 8) {	//FIRST CARD IS ACE
			for (size_t i = 1; i < 5; i++) {
				tot = tot * 10 + _hand[i].getRank();
			}
			tot = tot * 10 + 1;
			_lo = tot;
		}
		else {
			_lo = INT_MAX; //NO LOW AVAILABLE
		}
	}
	else _lo = INT_MAX;	//NO LOW AVAILABLE
}

bool Hand::isFourOfAKind() {	// [0==1==2==3] OR [1==2==3==4]
	if ((_hand[0].getRank() == _hand[1].getRank() &&
		_hand[1].getRank() == _hand[2].getRank() &&
		_hand[2].getRank() == _hand[3].getRank()) ||
		_hand[1].getRank() == _hand[2].getRank() &&
		_hand[2].getRank() == _hand[3].getRank() &&
		_hand[3].getRank() == _hand[4].getRank()) return true;
	return false;
}

bool Hand::isFullHouse() {	// [0==1  and 2==3==4] OR [0==1==2 and 3==4]
	if ((_hand[0].getRank() == _hand[1].getRank() &&
		_hand[2].getRank() == _hand[3].getRank() &&
		_hand[3].getRank() == _hand[4].getRank()) ||
		(_hand[0].getRank() == _hand[1].getRank() &&
			_hand[1].getRank() == _hand[2].getRank() &&
			_hand[3].getRank() == _hand[4].getRank())) return true;
	return false;
}

bool Hand::isFlush() {
	for (size_t i = 1; i < 5; i++) {
		if (_hand[i - 1].getSuit() != _hand[i].getSuit()) return false;
	}
	return true;
}

bool Hand::isStraight() {
	if (_hand[0].getRank() == 14 && _hand[1].getRank() == 5) {	//Ace as low card. Only possible straight is A 4 3 2 1
		for (size_t i = 2; i < 5; i++) {	//check 5 4 3 2
			if (_hand[i - 1].getRank() - _hand[i].getRank() != 1) return false;
		}
	}
	else {	//Ace as high card or no Ace
		for (size_t i = 1; i < 5; i++) {
			if (_hand[i - 1].getRank() - _hand[i].getRank() != 1) return false;
		}
	}
	return true;
}

bool Hand::isThreeOfAKind() {
	//// [0==1==2] OR [1==2==3] OR [2==3==4]
	if ((_hand[0].getRank() == _hand[1].getRank() && _hand[1].getRank() == _hand[2].getRank()) ||
		(_hand[1].getRank() == _hand[2].getRank() && _hand[2].getRank() == _hand[3].getRank()) ||
		(_hand[2].getRank() == _hand[3].getRank() && _hand[3].getRank() == _hand[4].getRank())) return true;
	return false;
}

bool Hand::isTwoPair() {
	std::unordered_set<int> set;
	bool firstPair = false;
	for (size_t i = 0; i < 5; i++) {
		int k = _hand[i].getRank();
		if (set.count(k)) {
			if (firstPair) return true;
			else firstPair = true;
		}
		set.insert(k);
	}
	return false;
}

bool Hand::isPair() {
	std::unordered_set<int> set;
	for (size_t i = 0; i < 5; i++) {
		int k = _hand[i].getRank();
		if (set.count(k)) return true;
		set.insert(k);
	}
	return false;
}

int Hand::getFullHouseRank() {	//Base 700
	if (_hand[0].getRank() == _hand[1].getRank() &&
		_hand[2].getRank() == _hand[3].getRank() &&
		_hand[3].getRank() == _hand[4].getRank()) return 700 + _hand[2].getRank();
	return 700 + _hand[0].getRank();
}
