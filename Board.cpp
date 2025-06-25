#include "Board.h"
#include "ColorUtils.h"

//Constructors && Destructors
Board::Board() : ship_count(0) {
	for (int y = 0; y < 10; ++y) {
		for (int x = 0; x < 10; ++x) {
			grid[y][x] = new Cell();
			grid[y][x]->set_x(x);
			grid[y][x]->set_y(y);
			grid[y][x]->set_state(CellState::Empty);
		}
	}

	for (int i = 0; i < 10; ++i) {
		ships[i] = nullptr;
	}
}

Board::~Board() {
	for (int y = 0; y < 10; ++y) {
		for (int x = 0; x < 10; ++x) {
			delete grid[y][x];
		}
	}
	for (int i = 0; i < ship_count; ++i) {
		delete ships[i];
	}
}

//Main methods 

Cell* Board::get_cell(int x, int y) const {
	if (x >= 0 && x < 10 && y >= 0 && y < 10) {
		return grid[y][x];
	}
	return nullptr;
}

bool Board::can_place_ship(int x, int y, int size, bool horizontal) const {
	if (horizontal && x + size > 10) return false;
	if (!horizontal && y + size > 10) return false;

	for (int i = 0; i < size; ++i) {
		int cx = x + (horizontal ? i : 0);
		int cy = y + (horizontal ? 0 : i);

		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				int nx = cx + dx;
				int ny = cy + dy;
				
				if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10) {
					if (grid[ny][nx]->get_state() == CellState::Ship) {
						return false;
					}
				}
			}
		}
	}

	return true;
}

bool Board::place_ship(int x, int y, int size, bool horizontal) {
	if (!can_place_ship(x, y, size, horizontal) || ship_count >= 10) {
		return false;
	}

	Ship* ship = new Ship(size);
	if (!ship->place(grid, x, y, horizontal)) {
		delete ship;
		return false;
	}

	ships[ship_count++] = ship;
	return true;
}

CellState Board::shoot(int x, int y) {
	Cell* cell = get_cell(x, y);
	if (!cell) {
		throw std::invalid_argument("Invalid coordinates.");
	}

	CellState current = cell->get_state();
	if (current == CellState::Hit || current == CellState::Miss || current == CellState::Killed) {
		throw std::invalid_argument("This cell was already shot at.");
	}

	if (current == CellState::Ship) {
		cell->set_state(CellState::Hit);
		for (int i = 0; i < ship_count; ++i) {
			if (ships[i]->is_hit(x, y)) {
				if (ships[i]->check_killed()) {
					mark_surrounding(*ships[i]);
					return CellState::Killed;
				}
				return CellState::Hit;
			}
		}
	}

	cell->set_state(CellState::Miss);
	return CellState::Miss;
}

void Board::mark_surrounding(const Ship& ship) {
	for (int i = 0; i < ship.get_size(); ++i) {
		int cx = ship.get_cell(i)->get_x();
		int cy = ship.get_cell(i)->get_y();
		
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				int nx = cx + dx;
				int ny = cy + dy;

				if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10) {
					if (dx == 0 && dy == 0) {
						continue;
					}
					Cell* neigbor = grid[ny][nx];
					if (neigbor->get_state() == CellState::Empty) {
						neigbor->set_state(CellState::Miss);
					}
				}
			}
		}
	}
}

bool Board::all_ships_killed() const {
	for (int i = 0; i < ship_count; ++i) {
		if (!ships[i]->get_killed()) return false;
	}
	return true;
}


void Board::draw(bool hide_ships) const {
	cout << "  ";
	for (int x = 0; x < 10; ++x) {
		cout << x << " ";
	}
	cout << endl;

	for (int y = 0; y < 10; ++y) {
		cout << y << " |";
		for (int x = 0; x < 10; ++x) {
			CellState state = grid[y][x]->get_state();

			switch (state) {
			case CellState::Empty:
				set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "~";
				break;

			case CellState::Ship:
				if (hide_ships) {
					set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					cout << "~";
				}
				else {
					set_color(FOREGROUND_INTENSITY);
					cout << "■";
				}
				break;

			case CellState::Hit:
				set_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "X";
				break;

			case CellState::Miss:
				set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "o";
				break;

			case CellState::Killed:
				set_color(FOREGROUND_RED);
				cout << "#";
				break;
			}

			reset_color();
			cout << " ";
		}
		cout << endl;
	}
}
