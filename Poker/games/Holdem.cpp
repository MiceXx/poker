#include "Holdem.h"



Holdem::Holdem()
{
}

Holdem::Holdem(std::vector<Player> players) {
	_players = players;
}

Holdem::~Holdem()
{
}

/*=================================================
Public Methods
=================================================*/

void Holdem::addPlayer(Player player) {
	_players.push_back(player);
	std::cout << "Successfully registered Player" << _players.size() << std::endl;
}

void Holdem::newGame() {
	std::srand((unsigned int)std::time(nullptr));
	_buttonPosition = std::rand();
	int nPlayers = _players.size();

	if (nPlayers < 1) {
		std::cout << "Not enough players... Need at least 2" << std::endl;
	}
	else if (nPlayers == 2) {
		std::cout << "~~Starting new game [Holdem] Heads-up" << std::endl;
	}
	else {
		std::cout << "~~Starting new game [Hold-em] with "
			<< nPlayers + 1 << " players" << std::endl;
	}

	//Initialize player's hands
	_pot = 0;
	_deck = new Deck();
	_board = Board();
	_buttonPosition = (_buttonPosition + 1) % nPlayers;
	for (int i = 0; i < nPlayers; i++) {
		_players[i].setPlaying();
	}

	printState(); //debug

	//system("pause");

	dealCardToAllPlayers();
	dealCardToAllPlayers();

	printState(); //debug
	bettingRound();

	dealFlop();
	printState(); //debug

	bettingRound();

	dealTurn();
	printState(); //debug

	bettingRound();

	dealRiver();
	printState(); //debug

	bettingRound();

	std::vector<int> winners = showDown();

	distributeWinnings(winners);
	
}

/*=================================================
Private Methods
=================================================*/

void Holdem::dealCardToAllPlayers() {
	for (size_t i = 0; i < _players.size(); i++) {
		int idx = (i + _buttonPosition) % _players.size();
		if (_players[idx].isPlaying()) {
			Card card = _deck->getNextCard();
			_players[idx].addCard(card);
			std::cout << "Dealing to player " << idx << std::endl;
		}
	}
}

void Holdem::bettingRound() {
	int nPlayers = _players.size();
	int idx = (_buttonPosition + 3) % nPlayers;
	int currentBet = 0;
	std::vector<int> playerBets(nPlayers, 0);
	char move;
	int betAmount;
	int counter = 0;

	std::cout << "Start betting.. " << std::endl;
	while(counter < nPlayers) {
		Player player = _players[idx];
		bool done = false;
		if (!player.isPlaying() || player.isAllin()) {
			counter++;
			continue;
		}
		std::string optionsText = "\nChoose an action:\nb-bet\nc-call\nk-check\nf-fold";
		std::cout << "Player " << idx << "'s turn" << std::endl;
		std::cout << optionsText << std::endl;
		while (!done) {
			std::cin >> move;
			switch (move) {
			case 'b':
				counter = 0;
				std::cout << "Enter your bet amount:" << std::endl;
				std::cin >> betAmount;
				if (betAmount > currentBet && player.loseChips(betAmount)) {
					currentBet = betAmount;
					if (player.isAllin()) {
						std::cout << "Player " << idx << " goes all in for " << betAmount << std::endl;
					}
					else {
						std::cout << "Player " << idx << " bets " << betAmount << std::endl;
					}
					done = true;
				}
				else if (betAmount == currentBet) {
					std::cout << "Player " << idx << " calls " << betAmount << std::endl;
					done = true;
				}
				else {
					std::cout << "==Insufficient Chips==" << optionsText << std::endl;
				}
				break;
			case 'c':
				if (player.loseChips(currentBet)) {
					if (player.isAllin()) {
						std::cout << "Player " << idx << " goes all in for " << betAmount << std::endl;
					}
					else {
						std::cout << "Player " << idx << " calls " << betAmount << std::endl;
					}
					done = true;
				}
				else {
					int allInAmount = player.goAllIn();
					std::cout << "Player " << idx << " goes all in for " << allInAmount << std::endl;
				}
				break;
			case 'k':
				counter++;
				if (currentBet == 0) {
					std::cout << "Player " << idx << " checks" << std::endl;
					done = true;
				}
				else {
					std::cout << "==Unable to check==" << optionsText << std::endl;
				}
				break;
			case 'f':
				player.setFold();
				std::cout << "Player " << idx << " folds" << std::endl;
				done = true;
				break;
			default:
				std::cout << "==Invalid Input==" << optionsText << std::endl;
				break;
			}
			if(!done) idx = (idx+1) % nPlayers;
		}
		if (_players[idx].isPlaying()) {
			Card card = _deck->getNextCard();
			_players[idx].addCard(card);
		}

		//update the pot size
		for (int i = 0; i < nPlayers; i++) {
			_pot += playerBets[i];
		}
	}
}

void Holdem::dealFlop() {
	_deck->burnCard();
	Card card1 = _deck->getNextCard();
	Card card2 = _deck->getNextCard();
	Card card3 = _deck->getNextCard();
	_board.addCard(card1);
	_board.addCard(card2);
	_board.addCard(card3);
	std::cout << "Dealing Flop:" << card1.getCardAsString() << " "
								<< card2.getCardAsString() << " "
								<< card3.getCardAsString() << std::endl;
}

void Holdem::dealTurn() {
	_deck->burnCard();
	Card card = _deck->getNextCard();
	_board.addCard(card);
	std::cout << "Dealing Turn:" << card.getCardAsString() << std::endl;
}

void Holdem::dealRiver() {
	_deck->burnCard();
	Card card = _deck->getNextCard();
	_board.addCard(card);
	std::cout << "Dealing River:" << card.getCardAsString() << std::endl;
}

//Return vector of winners' player index
std::vector<int> Holdem::showDown() {
	std::vector<int> splitIndices;
	std::vector<Hand> bestHands(_players.size());

	for (size_t i = 0; i < _players.size(); i++) {
		if (_players[i].isFolded()) bestHands[i] = Hand();
		else {
			Hand h = getbestHand(_players[i]);
			h.computeHiHand();
			bestHands[i] = h;
			std::cout << "Player " << i << " best hand: ";
			h.printHand();
		}
	}

	int winnerPos = 0;
	int winnerVal = -2;
	bool split = false;
	for (size_t i = 0; i < bestHands.size(); i++) {
		if (bestHands[i].getHiScore() > winnerVal) {
			winnerPos = i;
			winnerVal = bestHands[i].getHiScore();
			split = false;
		}
		else if (bestHands[i].getHiScore() == winnerVal) {
			split = true;
		}
	}
	if (split) {
		for (size_t i = 0; i < bestHands.size(); i++) {
			if (bestHands[i].getHiScore() == winnerVal) {
				splitIndices.push_back(i);
			}
		}
		std::cout << "***Split pot between players ";
		for (size_t i = 0; i < splitIndices.size() - 1; i++) {
			std::cout << splitIndices[i] << " ";
		}
		std::cout << "and " << splitIndices.back()
			<< " with "
			<< bestHands[winnerPos].GetHiHandName() << std::endl;
	}
	else {
		_players[winnerPos].winChips(_pot);
		splitIndices.push_back(winnerPos);
		std::cout << "***Winner is Player "
			<< winnerPos << " with "
			<< bestHands[winnerPos].GetHiHandName() << std::endl;
	}
	return splitIndices;

}

Hand Holdem::getbestHand(Player player) {
	Hand maxHand = Hand({ player.getCardByIndex(0),
			 player.getCardByIndex(1),
			_board.getCardByIndex(0),
			_board.getCardByIndex(1),
			_board.getCardByIndex(2) });
	for (size_t i = 0; i < 5; i++) {
		for (size_t j = i+1; j < 5; j++) {
			for (size_t k = j+1; k < 5; k++) {
				Hand h = Hand({ player.getCardByIndex(0),
					player.getCardByIndex(1),
					_board.getCardByIndex(i),
					_board.getCardByIndex(j),
					_board.getCardByIndex(k) });
				if (h > maxHand) maxHand = h;
			}
		}
	}
	return maxHand;
}

void Holdem::distributeWinnings(std::vector<int> winnersArray) {
	unsigned int n = winnersArray.size();
	for (size_t i = 0; i <n; i++) {
		int idx = winnersArray[i];
		_players[idx].winChips(_pot / n);
	}
	_pot = 0;
}

void Holdem::printState() { //for debugging purposes
	std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
	_board.printBoard();
	std::cout << "------------------------------------------" << std::endl;
	for (size_t i = 0; i < _players.size(); i++) {
		std::cout << "Player " << i << ":";
		_players[i].printHand();
	}
	std::cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << std::endl;
}