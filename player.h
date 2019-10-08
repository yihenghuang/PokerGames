#pragma once
#ifndef PLAYER_H
#define PLAYER_H


#include "hand.h"

#include <iostream>
#include <string>
using namespace std;


enum exceptions
{
	stop_game_when_no_game_in_progres, game_already_started, unknown_game, instance_not_available, player_already_playing,
	index_out_of_bound, removal_out_of_bound, too_few_players, deck_size_too_small, file_open_error, usage_message, success,failure, duplicate_player,
	no_cards_in_deck, too_few_chips, invalid_input, too_few_arguments
};


struct Player {

	friend struct Card;
	friend class Hand;
	friend class Deck;
	friend class Game;

public:
	string playersname;
	Hand playersCards;
	Hand playersHighFive;//highest five cards out of seven
	size_t numWin;
	size_t numLost;
	int chips =20;
	bool fold=false;
	int betweight = 0;
	int betweight5 = 1;
	int enter = 0;
	bool silent = false;

	string& get_name() {
		return playersname;
	}
	Hand& get_hand() {
		return playersCards;
	}
	unsigned int& get_wins() {
		return numWin;
	}
	unsigned int& get_loss() {
		return numLost;
	}
	Player(const char* s);
	friend Hand &operator<< (Hand& hand, Deck& deck);
};

//use the ostream to print out the player's name, number of wins, and number of losses with spaces between them 
ostream & operator<<(ostream & o, const Player& p);


#endif