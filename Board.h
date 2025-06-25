#pragma once
#include "Cell.h"
#include "Ship.h"
#include <iostream>
using namespace std;


class Board {
private:
	Cell* grid[10][10];
	Ship* ships[10];
	int ship_count;
public:
	//Constructors && Destructor
	Board();
	~Board();

	//Main class methods
	bool place_ship(int x, int y, int size, bool horizontal);
	bool can_place_ship(int x, int y, int size, bool horizontal) const;
	CellState shoot(int x, int y);
	bool all_ships_killed() const;
	void mark_surrounding(const Ship& ship);

	void draw(bool hide_ships = false) const;

	//Getters
	Cell* get_cell(int x, int y) const;
};