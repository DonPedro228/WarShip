#pragma once
#include <iostream>
using namespace std;

enum class CellState{ Empty, Ship, Hit, Miss, Killed};


class Cell {
private:
	int x, y;
	CellState state;
public:
	//Constructors
	Cell();
	Cell(int x, int y, CellState s = CellState::Empty);
	~Cell();

	//Getters
	int get_x() const { return x; }
	int get_y() const { return y; }
	CellState get_state() const { return state; }

	//Setters
	void set_x(int _x) { x = _x; }
	void set_y(int _y) { y = _y; }
	void set_state(CellState _state) { state = _state; }
};