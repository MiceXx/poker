#ifndef Holdem_h
#define Holdem_h

#include <iostream>
#include <vector>
#include <ctime>
#include "../assets/Deck.h"
#include "../assets/Card.h"
#include "../assets/Hand.h"
#include "../assets/Board.h"
#include "../assets/Player.h"

class Holdem
{
public:
	Holdem();
	Holdem(std::vector<Player> players);
	~Holdem();

	void addPlayer(Player player);
	void newGame();

private:
	Deck * _deck;
	Board _board;
	int _pot;
	std::vector<Player> _players;
	int _buttonPosition;

	//deal cards starting at dealer + 1
	void dealCardToAllPlayers();

	//betting round starting at dealer + 3
	void bettingRound();
	void dealFlop();
	void dealTurn();
	void dealRiver();
	std::vector<int> showDown();
	void distributeWinnings(std::vector<int>);
	Hand getbestHand(Player player);

	void printState(); //for debugging purposes
};


#endif