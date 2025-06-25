#pragma once
#include <windows.h>
#include <iostream>
#include "Cell.h"


inline void set_color(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

inline void reset_color() {
	set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

inline void print_cell_symbol(CellState state) {
	switch (state) {
	case CellState::Empty:
		set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "🌊";
		break;
	case CellState::Ship:
		set_color(FOREGROUND_INTENSITY); 
		std::cout << "■";
		break;
	case CellState::Hit:
		set_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "🔥";
		break;
	case CellState::Killed:
		set_color(FOREGROUND_RED);
		std::cout << "💀";
		break;
	case CellState::Miss:
		set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "•";
		break;
	default:
		std::cout << "?";
	}
	reset_color();
}