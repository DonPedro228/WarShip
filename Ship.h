#pragma once
#include "Cell.h"
#include <iostream>
using namespace std;



class Ship {
private:
	int size;
	Cell* cells[4];
	bool is_killed;
public:
	//Constructors
	Ship(int size);
	~Ship();

	//Getters
	int get_size() const { return size; }
	int get_killed() const { return is_killed; }
	Cell** get_cells() { return cells;  }
	Cell* get_cell(int i) const { return cells[i]; }

	//Main class methods
	bool place(Cell* grid[10][10], int start_x, int start_y, bool horizontal);
	bool is_hit(int x, int y);
	bool check_killed();
};