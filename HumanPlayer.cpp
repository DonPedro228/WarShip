#include "HumanPlayer.h"
#include <cstdlib>
#include <ctime>
using namespace std;

//Constructors
HumanPlayer::HumanPlayer() {
	srand(time(nullptr));
}


//Main methods
void HumanPlayer::place_ships() {
	int choice;
	cout << "Choose ship placement method: " << endl;
	cout << "1. Manual" << endl;
	cout << "2. Automatic" << endl;
	cout << "Your choice:" << endl;
	cin >> choice;

	if (choice == 1) {
		manual_placement();
	}
	else if (choice == 2) {
		auto_placement();
	}
	else {
		cout << "Choose method 1 or 2! " << endl;
		exit(1);
	}
}

void HumanPlayer::manual_placement() {
	int sizes[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

	for (int i = 0; i < 10; ++i) {
		int x, y;
		bool horizontal = get_direction();

		cout << "Placing ship of size " << sizes[i] << endl;

		while (true) {
			cout << "Enter X (0-9): "; cin >> x;
			cout << "Enter Y (0-9): "; cin >> y;

			if (board.place_ship(x, y, sizes[i], horizontal)) {
				board.draw(false);
				break;
			}
			else {
				cout << "❌ Can't place ship here. Try again." << endl;
			}
		}
	}
}

void HumanPlayer::auto_placement() {
	int sizes[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

	for (int i = 0; i < 10; ++i) {
		int x, y;
		bool horizontal;
		while (true) {
			x = rand() % 10;
			y = rand() % 10;
			horizontal = rand() % 2;

			if (board.place_ship(x, y, sizes[i], horizontal)) {
				break;
			}
		}
	}

	cout << "Ships placed automatically." << endl;
	board.draw(false);
}

bool HumanPlayer::get_direction() {
	char dir;
	while (true) {
		cout << "Direction (h/v): "; cin >> dir;
		if (dir == 'h' || dir == 'H') return true;
		if (dir == 'v' || dir == 'V') return false;
		cout << "Invalid direction! Try correct direction." << endl;
	}
}

void HumanPlayer::make_turn(Board& opponent_board) {
	while (true) {
		int x, y;
		cout << ">> Enter target X (0-9): ";
		cin >> x;
		cout << "Enter target Y (0-9): ";
		cin >> y;

		try {
			CellState result = opponent_board.shoot(x, y);
			switch (result) {
			case CellState::Hit:
				cout << "🎯 Hit!" << endl;
				break;
			case CellState::Killed:
				cout << "💥 Killed!" << endl;
				break;
			case CellState::Miss:
				cout << "💦 Miss." << endl;
				break;
			}
			break; \
		}
		catch (const std::exception& e) {
			cout << "⚠️  Error: " << e.what() << " Try again." << endl;
		}
	}
}