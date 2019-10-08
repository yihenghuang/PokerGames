
#include "stdafx.h"
#include "deck.h"
#include "card.h"
#include "hand.h"
#include "player.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <vector>
#include <chrono> 
using namespace std;


Deck::Deck(string file) {
	load(file);
}

//default constructor initializes the deck object to be empty
Deck::Deck() :deck() {
}


const void Deck::add_card(Card c) {
	deck.push_back(c);
}


void Deck::load(string file) {
	ifstream ifs(file);
	string line;
	//vector<Card> cVec;
	if (ifs.is_open()) {
		while (getline(ifs, line)) {//reads one line
			istringstream iss(line);
			string in;
			char tempR;
			char tempS;
			vector<Card> subVec;
			while (iss >> in) {
				//reads one string

				if (in == "//") { break; } //NEED TO BE ADJUSTED

				if (in.length() == 2) {
					tempR = in[0];
					tempS = in[1];
					if (((tempR >= '10') || (tempR <= '1')) && (tempR != 'J') && (tempR != 'j') && (tempR != 'Q') && (tempR != 'q') && (tempR != 'k') && (tempR != 'K') && (tempR != 'A') && (tempR != 'a')) {
						tempR = '\0';
						continue;
					}
					if ((tempS != 'C') && (tempS != 'c') && (tempS != 'D') && (tempS != 'd') && (tempS != 'S') && (tempS != 's') && (tempS != 'H') && (tempS != 'h')) {
						tempS = '\0';
						continue;
					}
				}
				else if (in.length() == 3) {
					if (in[0] == '1' &&  in[1] == '0') {
						tempR = in[0];
						tempS = in[2];
						if ((tempS != 'C') && (tempS != 'c') && (tempS != 'D') && (tempS != 'd') && (tempS != 'S') && (tempS != 's') && (tempS != 'H') && (tempS != 'h')) {
							tempS = '\0';
							continue;
						}
					}
					else {
						continue;
					}
				}
				else {
					continue;
				}

				subVec.push_back(Card(tempR, tempS));
			}
			for (Card c : subVec) {
				deck.push_back(c); // insert back to container member variable
			}
			/*
			if (subVec.size() == 5) {
			//sort(subVec.begin(), subVec.end());
			//check(subVec); // check can return a string which identify the hand
			for (Card c : subVec) {
			deck.push_back(c); // insert back to container member variable
			}
			}
			else if (subVec.size() > 5) {
			cout << "not a hand, too many" << endl;
			}
			else if (subVec.size() < 5 && subVec.size() > 0) {
			cout << "not a hand, too few" << endl;
			}
			else {
			cout << "invalid line" << endl;
			}
			*/
		}
		if (deck.size() < 45) {
			throw deck_size_too_small;
		}
	}
	else {
		throw file_open_error;
	}
	ifs.close();
	return;
}

void Deck::callShuffle() {
	//auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	//shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
	std::random_shuffle(deck.begin(), deck.end());
	//std::random_device rd;
	//std::mt19937 g(rd());
	//std::shuffle(deck.begin(), deck.end(), g);
}

const int Deck::size() {
	return deck.size();
}

ostream &operator<<(ostream & o, const Deck & d)
{
	for (size_t i = 0; i < d.deck.size(); ++i) {
		char rank = d.deck[i].r;
		char suit = d.deck[i].s;
		string str = "";
		switch (rank) {
		case 0: str = "2"; break;
		case 1: str = "3"; break;
		case 2: str = "4"; break;
		case 3: str = "5"; break;
		case 4: str = "6"; break;
		case 5: str = "7"; break;
		case 6: str = "8"; break;
		case 7: str = "9"; break;
		case 8: str = "10"; break;
		case 9: str = "J"; break;
		case 10: str = "Q"; break;
		case 11: str = "K"; break;
		case 12: str = "A"; break;
		}
		switch (suit) {
		case 0: str += "C"; break;
		case 1: str += "D"; break;
		case 2: str += "H"; break;
		case 3: str += "S"; break;
		}
		o << str << " " << flush;
	}
	return o;
}

