#pragma once
#ifndef SEVENCARDSTUD_H
#define SEVENCARDSTUD_H
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "game.h"

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

class SevenCardStud : public Game {
	friend class Deck;

protected:
	size_t dealer;
	vector<Hand> hands;
	int common_bet;
	unsigned int highest_bet = 0;
	bool oneleft = false;
	string foldname;

public:
	SevenCardStud();

	virtual int before_turn(Player & a);
	virtual int turn(Player&);
	virtual int after_turn(Player&);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
	static bool poker_rankSeven(shared_ptr<Player> p2, shared_ptr<Player> p1);
	friend ostream &operator<< (ostream& o, Hand& h);

	virtual bool call(Player& a);
	virtual bool raise(Player& a, int raise) ;
	virtual int player_size() ;
};
#endif
