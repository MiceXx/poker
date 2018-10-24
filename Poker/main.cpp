#include <string>
#include <sstream>
#include <fstream>

#include "assets/Hand.h"
#include "assets/Board.h"
#include "assets/Card.h"
#include "assets/Player.h"
#include "games/Omaha.h"
#include "games/Holdem.h"

int main(int argc, char **argv) {
	Hand hand1 = Hand({ Card(14,'c') ,Card(13,'d') ,Card(11,'d') ,Card(3,'d') });
	Hand hand2 = Hand({ Card(5,'c') ,Card(5,'d') ,Card(6,'c') ,Card(7,'d') });
	Board board = Board({ Card(14,'h') ,Card(13,'h') ,Card(5,'s') ,Card(2,'s'),Card(12,'d') });
	Omaha omaha = Omaha(hand1, hand2, board);
	std::string answer = omaha.Solve();
	std::cout << answer << std::endl;

	int startingStack = 1500;
	Player p1 = Player(startingStack);
	Player p2 = Player(startingStack);

	Holdem holdem = Holdem();
	holdem.addPlayer(p1);
	holdem.addPlayer(p2);
	holdem.newGame();

	std::cin.get();
	return 0;
	
}