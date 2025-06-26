#pragma once
#include "Board.h"


class Player {
protected:
	Board board;
public:
	//Constructors && destructors
	virtual ~Player() {}

	virtual void place_ships() = 0;
	virtual bool make_turn(Board& opponent_board) = 0;


	//Getters
	Board& get_board() { return board; }
};