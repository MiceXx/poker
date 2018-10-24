#include "Game.h"



Game::Game()
{
}

Game::Game(GameType gameType)
{
	switch (gameType) {
	case 1:
		startHoldem;
		break;
	case 2:
		startOmaha;
		break;
	case 3:
		startStud5;
		break;
	}
}

Game::~Game()
{
}

/*=================================================
Public Methods
=================================================*/


/*=================================================
Private Methods
=================================================*/

void startHoldem();
void startOmaha();
void startStud5();