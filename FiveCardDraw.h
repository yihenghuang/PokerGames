#pragma once
#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H

#include "deck.h"
#include "hand.h"
#include "player.h"
#include "game.h"

#include <iostream>
#include <string>
#include <sstream>

#include <memory>
using namespace std;

class FiveCardDraw : public Game{
	friend class Deck;

protected:
	size_t dealer;
	Deck discarded;
	vector<Hand> hands;
	size_t common_bet;
	int highest_bet;
	bool bet = false;


public:
	FiveCardDraw();
	int consec_check= 0;
	int before_turn(Player & a);
	virtual int turn(Player&);
	virtual int after_turn(Player&);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
	int player_check();
	bool check_fold();
	bool check_bet();
	bool betting_phase(Player& a);
	virtual bool call(Player& a);
	virtual bool raise(Player& a, int raise);
	bool check_input(int a);
	static bool poker_rank1(shared_ptr<Player> p2, shared_ptr<Player> p1);
	friend ostream &operator<< (ostream& o, Hand& h);
	virtual int player_size();


	
};


#endif
