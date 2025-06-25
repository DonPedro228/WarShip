#include "BotPlayer.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
using namespace std;

//Constructors
BotPlayer::BotPlayer() {
	srand(time(nullptr));
}

//Main methods
void BotPlayer::place_ships() {
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

	cout << "🤖 Bot has placed its ships." << endl;
}

void BotPlayer::make_turn(Board& opponent_board) {
	while (true) {
		int x = -1, y = -1;

		if (!targeting_queue.empty()) {
			auto target = targeting_queue.back();
			targeting_queue.pop_back();
			x = target.first;
			y = target.second;
		}
		else {
			do {
				x = rand() % 10;
				y = rand() % 10;
			} while (!is_valid_target(x, y));
		}

		if (!is_valid_target(x, y)) continue;  
		shots_made.push_back({ x, y });

		try {
			cout << "🤖 Bot shoots at (" << x << ", " << y << "): ";
			CellState result = opponent_board.shoot(x, y);

			if (result == CellState::Killed) {
				cout << "Killed!" << endl;
				hunt_state = HuntState::Searching;
				targeting_queue.clear();
				break;
			}
			else if (result == CellState::Hit) {
				cout << "Hit!" << endl;

				if (hunt_state == HuntState::Searching) {
					first_hit = { x, y };
					queue_adjacent(x, y);
					hunt_state = HuntState::Hunting;
				}
				else if (hunt_state == HuntState::Hunting) {
					second_hit = { x, y };
					calculate_direction();
					hunt_state = HuntState::Targeting;

					int dx = direction.first;
					int dy = direction.second;

					for (int step = 1; step < 4; ++step) {
						int tx = second_hit.first + step * dx;
						int ty = second_hit.second + step * dy;
						if (is_valid_target(tx, ty)) targeting_queue.push_back({ tx, ty });
						else break;
					}

					for (int step = 1; step < 4; ++step) {
						int tx = first_hit.first - step * dx;
						int ty = first_hit.second - step * dy;
						if (is_valid_target(tx, ty)) targeting_queue.push_back({ tx, ty });
						else break;
					}
				}
				else if (hunt_state == HuntState::Targeting) {
					int dx = direction.first;
					int dy = direction.second;

					int tx = x + dx;
					int ty = y + dy;

					if (is_valid_target(tx, ty)) {
						targeting_queue.push_back({ tx, ty });
					}
					else {
						for (int step = 1; step < 4; ++step) {
							int back_x = first_hit.first - step * dx;
							int back_y = first_hit.second - step * dy;
							if (is_valid_target(back_x, back_y)) {
								targeting_queue.push_back({ back_x, back_y });
							}
							else break;
						}
					}
				}
			}
			else if (result == CellState::Miss) {
				cout << "Miss." << endl;
			}
			break;

		}
		catch (const std::exception& e) {
			continue;
		}
	}
}

void BotPlayer::queue_adjacent(int x, int y) {
	pair<int, int> directions[4] = {
		{0, -1}, {0, 1}, {-1, 0}, {1, 0}
	};

	for (auto& dir : directions) {
		int nx = x + dir.first;
		int ny = y + dir.second;

		if (is_valid_target(nx, ny)) {
			targeting_queue.push_back({ nx, ny });
		}
	}

	random_shuffle(targeting_queue.begin(), targeting_queue.end());
}

void BotPlayer::calculate_direction() {
	int dx = second_hit.first - first_hit.first;
	int dy = second_hit.second - first_hit.second;

	if (dx != 0) { dx /= abs(dx); }
	if (dy != 0) { dy /= abs(dy); }

	direction = { dx, dy };
}

bool BotPlayer::is_valid_target(int x, int y) {
	if (x < 0 || x >= 10 || y < 0 || y >= 10) {
		return false;
	}
	return find(shots_made.begin(), shots_made.end(), make_pair(x, y)) == shots_made.end();
}