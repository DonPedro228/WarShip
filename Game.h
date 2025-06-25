#pragma once
#include "HumanPlayer.h"
#include "BotPlayer.h"


class Game {
private:
	HumanPlayer human;
	BotPlayer bot;
	bool human_turn;

public:
	//Constructors
	Game();

	//Main methods
	void start();
	void loop();
	void draw_fields();
	void end_game(bool human_won);
};