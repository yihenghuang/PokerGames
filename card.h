
#pragma once
#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
using namespace std;


enum Suit { CLUB, DIAMOND, HEART, SPADE };
enum Rank { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };


struct Card {
	friend class Hand;
	friend class Deck;
	friend struct Player;
	friend class Game;
public:
	Suit s;
	Rank r;

	Card(char RankArg, char SuitArg) {
		if (RankArg == '2') {
			r = TWO;
		}
		else if (RankArg == '3') {
			r = THREE;
		}
		else if (RankArg == '4') {
			r = FOUR;
		}
		else if (RankArg == '5') {
			r = FIVE;
		}
		else if (RankArg == '6') {
			r = SIX;
		}
		else if (RankArg == '7') {
			r = SEVEN;
		}
		else if (RankArg == '8') {
			r = EIGHT;
		}
		else if (RankArg == '9') {
			r = NINE;
		}
		else if (RankArg == '1') {
			r = TEN;
		}
		else if (RankArg == 'j' || RankArg == 'J') {
			r = JACK;
		}
		else if (RankArg == 'q' || RankArg == 'Q') {
			r = QUEEN;
		}
		else if (RankArg == 'k' || RankArg == 'K') {
			r = KING;
		}
		else if (RankArg == 'a' || RankArg == 'A') {
			r = ACE;
		}

		if (SuitArg == 'c' || SuitArg == 'C') {
			s = CLUB;
		}
		else if (SuitArg == 'd' || SuitArg == 'D') {
			s = DIAMOND;
		}
		else if (SuitArg == 'h' || SuitArg == 'H') {
			s = HEART;
		}
		else if (SuitArg == 's' || SuitArg == 'S') {
			s = SPADE;
		}

	}

	Card( int RankArg,  int SuitArg) {
		if (RankArg == 0) {
			r = TWO;
		}
		else if (RankArg == 1) {
			r = THREE;
		}
		else if (RankArg == 2) {
			r = FOUR;
		}
		else if (RankArg == 3) {
			r = FIVE;
		}
		else if (RankArg == 4) {
			r = SIX;
		}
		else if (RankArg == 5) {
			r = SEVEN;
		}
		else if (RankArg == 6) {
			r = EIGHT;
		}
		else if (RankArg == 7) {
			r = NINE;
		}
		else if (RankArg == 8) {
			r = TEN;
		}
		else if (RankArg == 9) {
			r = JACK;
		}
		else if (RankArg == 10) {
			r = QUEEN;
		}
		else if (RankArg == 11) {
			r = KING;
		}
		else if (RankArg == 12) {
			r = ACE;
		}

		if (SuitArg == 0) {
			s = CLUB;
		}
		else if (SuitArg == 1) {
			s = DIAMOND;
		}
		else if (SuitArg == 2) {
			s = HEART;
		}
		else if (SuitArg == 3) {
			s = SPADE;
		}

	}

	bool operator< (Card &);
	bool operator> (Card &);
	
};



#endif