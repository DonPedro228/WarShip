#pragma once
#include "Player.h"
#include <vector>
using namespace std;

enum class HuntState {
	Searching,
	Hunting,    
	Targeting   
};


class BotPlayer : public Player {
private:
	vector<pair<int, int>> shots_made;

	HuntState hunt_state = HuntState::Searching;
	pair<int, int> first_hit;
	pair<int, int> second_hit;
	pair<int, int> direction;
	vector<pair<int, int>> targeting_queue;
public:
	//Constructors
	BotPlayer();

	//Main methods
	void place_ships() override;
	bool make_turn(Board& opponent_board) override;

private:
	void queue_adjacent(int x, int y);
	void calculate_direction();
	bool is_valid_target(int x, int y);
};
