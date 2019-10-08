#pragma once
#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Game  {
	friend struct Card;
	friend class Hand;
	friend class Deck;
	friend struct Player;

protected:
	//pointer should be initialized to be singular (point to nothing)
	//const static shared_ptr<Game>  a = make_shared<Game>();
	static shared_ptr<Game> pGame;
	
	//default constructed to empty. is this already initialized to empty?
	Deck mainDeck;

	//vector (that is initially empty) of pointers (or even better, of shared_ptrs) to players
	vector<shared_ptr<Player>> vpPlayer;
	

public:
	bool play = true;
	bool all_check = false;
	int silent_players = 0;
	static shared_ptr<Game> instance();
	static void start_game(const string &);
	static void stop_game();
	void add_player(const string & player);
	shared_ptr<Player> find_player(const string& name);
	virtual int before_turn(Player&)=0;
	virtual int turn(Player&) = 0;
	virtual int after_turn(Player&) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
	virtual bool call(Player& a) =0;
	virtual bool raise(Player& a, int raise) = 0;
	virtual int player_size() =0;

	
};

#endif