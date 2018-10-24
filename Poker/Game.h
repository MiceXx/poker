#pragma once
class Game
{
public:
	enum GameType {
		Holdem,	//1
		Omaha,	//2
		Stud5,	//3
	};

	Game();
	Game(GameType gameType);
	~Game();

private:
	void startHoldem();
	void startOmaha();
	void startStud5();
};

