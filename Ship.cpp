#include "Ship.h"

//Constructors && destructors
Ship::Ship(int s) : size(s), is_killed(false) {
	for (int i = 0; i < size; ++i) {
		cells[i] = nullptr;
	}
}

Ship::~Ship() {}


//Main methods

//Place ship on the place
bool Ship::place(Cell* grid[10][10], int start_x, int start_y, bool horizontal) {
	if (horizontal) {
		if (start_x + size > 10) {
			return false;
		}
	}
	else {
		if (start_y + size > 10) {
			return false;
		}
	}

	//Check, that cells are empty
	for (int i = 0; i < size; ++i) {
		int x = start_x + (horizontal ? i : 0);
		int y = start_y + (horizontal ? 0 : i);

		if (grid[y][x]->get_state() != CellState::Empty) {
			return false;
		}
	}

	//Set ship
	for (int i = 0; i < size; ++i) {
		int x = start_x + (horizontal ? i : 0);
		int y = start_y + (horizontal ? 0 : i);

		grid[y][x]->set_state(CellState::Ship);
		cells[i] = grid[y][x];
	}

	return true;
}

//Hiting ship?
bool Ship::is_hit(int x, int y) {
	for (int i = 0; i < size; ++i) {
		if (cells[i]->get_x() == x && cells[i]->get_y() == y) {
			cells[i]->set_state(CellState::Hit);
			return true;
		}
	}
	return false;
}

//Check if killed ship or no
bool Ship::check_killed() {
	for (int i = 0; i < size; ++i) {
		if (cells[i]->get_state() != CellState::Hit && cells[i]->get_state() != CellState::Killed) {
			return false;
		}
	}
	is_killed = true;

	for (int i = 0; i < size; ++i) {
		cells[i]->set_state(CellState::Killed);
	}
	return true;
}