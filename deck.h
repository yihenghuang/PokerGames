#pragma once
#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "hand.h"
#include <iostream>
#include <vector>
#include <random>
using namespace std;


class Deck {

	friend struct Card;
	friend class Hand;
	friend struct Player;
	friend class Game;
	friend class FiveCardDraw;
	friend class SevenCardStud;
	friend class TexasHoldEm;
	vector<Card> deck;
public:

	//default constructor initializes the deck object to be empty
	Deck();

	// takes a Card as its only parameter, and adds it to the deck.
	const void add_card(Card c);

	//constructor
	Deck(string file);

	//load method
	void load(string file);

	//shuffle method
	void callShuffle();

	//size method
	const int size();

	friend ostream &operator<< (ostream & o, const Deck & d);
	friend Hand &operator<< (Hand& hand, Deck& deck);

	friend const string Hand::asString();
	friend int Hand::check(vector<Card>& temp);

	friend bool Card::operator< ( Card &);
	friend bool Card::operator> ( Card &);

	friend bool poker_rank(Hand & h1, Hand & h2);
	friend bool poker_rankSpecial(Hand & h1, Hand & h2);
};

//non member insertion operator<<
ostream &operator<< (ostream & o, const Deck & d);


#endif