#pragma once
#include "Player.h"
#include <iostream>

class HumanPlayer : public Player {
public:
	//Constructors
	HumanPlayer();

	//Main methods
	void place_ships() override;
	void make_turn(Board& opponent_board) override;

private:
	//Main methods
	bool get_direction();
	void manual_placement();
	void auto_placement();
};