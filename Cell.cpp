#include "Cell.h"

Cell::Cell() : x(0), y(0), state(CellState::Empty) {}

Cell::Cell(int x, int y, CellState s) : x(x), y(y), state(s) {}

Cell::~Cell() {}