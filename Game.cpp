#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

//Constructors
Game::Game() : human_turn(true) {}


//Main methods
void Game::start() {
	cout << "=========== SEA BATTLE ===========" << endl;
	cout << "Prepare for war, commander!" << endl << endl;

	cout << "== Your fleet setup ==" << endl;
	human.place_ships();

	cout << endl;

	cout << "== Bot fleet setup ==" << endl;
	bot.place_ships();

	cout << "Let the battle begin!" << endl << endl;

	loop();
}

void Game::loop() {
	while (true) {
		draw_fields();

		bool hit;

		if (human_turn) {
			do {
				cout << ">> Your turn: " << endl;
				hit = human.make_turn(bot.get_board());
			} while (hit && !bot.get_board().all_ships_killed());
		}
		else {
			do {
				cout << ">> Bot's turn: " << endl;
				this_thread::sleep_for(chrono::milliseconds(800));
				hit = bot.make_turn(human.get_board());
			} while (hit && !human.get_board().all_ships_killed());
		}

		if (bot.get_board().all_ships_killed()) {
			end_game(true);
			break;
		}
		else if (human.get_board().all_ships_killed()) {
			end_game(false);
			break;
		}

		human_turn = !human_turn;
	}
}

void Game::draw_fields() {
	system("cls");
	cout << "=========== SEA BATTLE ===========" << endl;
	cout << "Your Field:" << endl;
	human.get_board().draw(false);

	cout << "Enemy Field: " << endl;
	bot.get_board().draw(true);
}

void Game::end_game(bool human_won) {
	draw_fields();

	cout << endl;
	cout << "========== GAME OVER ==========" << endl;

	if (human_won) {
		cout << "🎉 You win! Well played!" << endl;
	}
	else {
		cout << "💀 Bot wins... Better luck next time." << endl;
	}

	cout << "Press any key to exit..." << endl;
	cin.ignore();
	cin.get();
}