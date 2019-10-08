#pragma once
#ifndef HAND_H
#define HAND_H

#include "card.h"
//#include "deck.h"

#include <iostream>
#include <vector>
using namespace std;

enum showHand { StraightFlush, FourOfAKind, FullHouse, Flush, Straight, ThreeOfAKind, TwoPairs, OnePair, NoRank };

class Hand {
	friend struct Card;
	friend struct Player;
	friend class Deck;
	friend class Game;
	friend class FiveCardDraw;
	friend class SevenCardStud;
	friend class TexasHoldEm;

public:
	vector<Card> hand;

	// default constructor
	Hand();

	// copy constructor
	Hand(const Hand& other);

	// size method 
	const int size();

	//assignment op
	void operator=(const Hand& other);

	//const equivalence operator
	const bool operator== (const Hand & other);

	//const less than operator
	const bool operator< ( Hand & other);

	//asString method
	const string asString();
	const string asStringSeven();
	const string asStringTexas();

	static int check(vector<Card>& temp);
	static Hand bestFive(vector<Card>& temp);

	//indexing operator
	const Card operator[](size_t i);
	//remove card
	const void remove_card(size_t i);


	friend bool poker_rank(Hand & h1, Hand & h2);
	friend bool poker_rankSpecial(Hand & h1, Hand & h2);
	friend ostream &operator<< (ostream & o, const Hand & h);
	friend Hand &operator<< (Hand& hand, Deck& deck);
	friend ostream &operator<< (ostream & o, const Deck & d);
	

};
ostream &operator<< (ostream & o, const Hand & h);
Hand &operator<< (Hand& hand, Deck& deck);
bool poker_rank(Hand & h1, Hand & h2);
bool poker_rankSpecial(Hand & h1, Hand & h2);
#endif
