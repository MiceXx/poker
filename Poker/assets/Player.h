#ifndef Player_h
#define Player_h

#include <iostream>
#include <vector>
#include "Hand.h"

class Player : public Hand
{
public:
	Player();
	Player(int n);
	~Player();

	void winChips(int n);
	//return true if resulting chip count is positive
	bool loseChips(int n);

	int getChipCount();

	void setFold();
	void setPlaying();
	int goAllIn();

	bool isPlaying();
	bool isAllin();
	bool isFolded();

private:
	int _chips;
	bool _allIn;
	bool _folded;
	bool _playing;


};

#endif