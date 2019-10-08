
#include "stdafx.h"
#include "hand.h"
#include "player.h"
#include "card.h"
#include "deck.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
using namespace std;

Hand::Hand() {
	hand = {};
}

Hand::Hand(const Hand& other) {
	this->hand = other.hand;
}

void Hand::operator=(const Hand& other) {
	if (hand.size() != other.hand.size()) {
	}
	else {
		this->hand = other.hand;
	}
}

const int Hand::size() {
	return hand.size();
}

const bool Hand::operator== (const Hand & other) {
	if (hand.size() != other.hand.size()) {
		return false;
	}

	for (size_t i = 0;i < hand.size();++i) {
		if (hand[i].r != other.hand[i].r) {
			return false;
		}
	}
	return true;
}

const bool Hand::operator< ( Hand & other) {

	for (unsigned int i = 0; i < hand.size(); ++i) {
		if (hand[i] < other.hand[i]) {
			return true;
		}
		else if (hand[i] > other.hand[i]) {
			return false;
		}
	}
	if (hand.back() < other.hand.back()) {
		return true;
	}
	else {
		return false;
	}
}

const string Hand::asString() {
	string s;
	for (size_t i = 0; i < hand.size(); ++i) {
		switch (hand[i].r) {
		case TWO: s += "2"; break;
		case THREE: s += "3"; break;
		case FOUR: s += "4"; break;
		case FIVE: s += "5"; break;
		case SIX: s += "6"; break;
		case SEVEN: s += "7"; break;
		case EIGHT: s += "8"; break;
		case NINE: s += "9"; break;
		case TEN: s += "10"; break;
		case JACK: s += "J"; break;
		case QUEEN: s += "Q"; break;
		case KING: s += "K"; break;
		case ACE: s += "A"; break;
		}
		switch (hand[i].s) {
		case CLUB: s += "C"; break;
		case DIAMOND: s += "D"; break;
		case HEART: s += "H"; break;
		case SPADE: s += "S"; break;
		}
		s += " ";
	}
	return s;
}

const string Hand::asStringSeven() {
	string s;
	for (size_t i = 0; i < hand.size(); ++i) {
		if (i == 0 || i == 1 || i == 6) {
			s += "*";
		}
		else {
			switch (hand[i].r) {
			case TWO: s += "2"; break;
			case THREE: s += "3"; break;
			case FOUR: s += "4"; break;
			case FIVE: s += "5"; break;
			case SIX: s += "6"; break;
			case SEVEN: s += "7"; break;
			case EIGHT: s += "8"; break;
			case NINE: s += "9"; break;
			case TEN: s += "10"; break;
			case JACK: s += "J"; break;
			case QUEEN: s += "Q"; break;
			case KING: s += "K"; break;
			case ACE: s += "A"; break;
			}
			switch (hand[i].s) {
			case CLUB: s += "C"; break;
			case DIAMOND: s += "D"; break;
			case HEART: s += "H"; break;
			case SPADE: s += "S"; break;
			}
		}
		s += " ";
	}
	return s;
}

const string Hand::asStringTexas() {
	string s;
	for (size_t i = 0; i < hand.size(); ++i) {
		if (i == 0 || i == 1 ) {
			s += "**";
		}
		else {
			switch (hand[i].r) {
			case TWO: s += "2"; break;
			case THREE: s += "3"; break;
			case FOUR: s += "4"; break;
			case FIVE: s += "5"; break;
			case SIX: s += "6"; break;
			case SEVEN: s += "7"; break;
			case EIGHT: s += "8"; break;
			case NINE: s += "9"; break;
			case TEN: s += "10"; break;
			case JACK: s += "J"; break;
			case QUEEN: s += "Q"; break;
			case KING: s += "K"; break;
			case ACE: s += "A"; break;
			}
			switch (hand[i].s) {
			case CLUB: s += "C"; break;
			case DIAMOND: s += "D"; break;
			case HEART: s += "H"; break;
			case SPADE: s += "S"; break;
			}
		}
		s += " ";
	}
	return s;
}

ostream &operator<< (ostream & o, Hand & h) {
	for (size_t i = 0; i < h.hand.size(); ++i) {
		char rank = h.hand[i].r;
		char suit = h.hand[i].s;
		string str = " ";
		switch (rank) {
		case 0: str = "TWO"; break;
		case 1: str = "THREE"; break;
		case 2: str = "FOUR"; break;
		case 3: str = "FIVE"; break;
		case 4: str = "SIX"; break;
		case 5: str = "SEVEN"; break;
		case 6: str = "EIGHT"; break;
		case 7: str = "NINE"; break;
		case 8: str = "TEN"; break;
		case 9: str = "JACK"; break;
		case 10: str = "QUEEN"; break;
		case 11: str = "KING"; break;
		case 12: str = "ACE"; break;
		};
		switch (suit) {
		case 0: str += "_CLUB "; break;
		case 1: str += "_DIAMOND "; break;
		case 2: str += "_HEART "; break;
		case 3: str += "_SPADE "; break;
		};
		o << str << flush;
	}

	return o;
}

Hand &operator<< (Hand& hand, Deck& deck) {
	hand.hand.push_back(deck.deck[deck.deck.size() - 1]);
	deck.deck.pop_back();
	sort(hand.hand.begin(), hand.hand.end());
	return hand;
}



int Hand::check(vector<Card>& temp) {
	int same_suit = 0;
	int seq_rank = 0;
	int eq_count = 0;
	int eq_rank[4] = { 0,0,0,0 };
	for (int i = 0; i < 4; ++i) {
		if (temp[i].s == temp[i + 1].s) {
			same_suit++;
		}
		if (temp[i].r == (temp[i + 1].r - 1)) {
			seq_rank++;
		}
		if (temp[i].r == temp[i + 1].r) {
			eq_count++;
			eq_rank[i] = 1;
		}
	}
	if (same_suit == 4) {
		if (seq_rank == 4) {
			return StraightFlush;
		}
		else {
			return Flush;
		}
	}
	else {
		if (seq_rank == 4) {
			return Straight;
		}
	}
	if (eq_count == 3) {
		if ((eq_rank[0] == 0) || (eq_rank[3] == 0)) {
			return FourOfAKind;
		}
		else {
			return FullHouse;
		}
	}
	else if (eq_count == 2) {
		
		if ((eq_rank[0] == eq_rank[1]) || (eq_rank[2] == eq_rank[3])) {
			return ThreeOfAKind;
		}
		else if (eq_rank[1] == eq_rank[2]) {
			if (eq_rank[1] == 1) {
				return ThreeOfAKind;
			}
			else {
				return TwoPairs;
			}
		}
		else {
			return TwoPairs;
		}
	}
	else if (eq_count == 1) {
		//cout << "enter one pair?&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
		return OnePair;
	}
	else {
		return NoRank;
	}
}



//special version just to compare different combination of five cards out of seven

// { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
//{ StraightFlush, FourOfAKind, FullHouse, Flush, Straight, ThreeOfAKind, TwoPairs, OnePair, NoRank };
bool poker_rankSpecial(Hand& h1, Hand& h2){
	
	int h1reseult = Hand::check(h1.hand);
	int h2reseult = Hand::check(h2.hand);
	vector <Card> vec1 = h1.hand;
	vector<Card> vec2 = h2.hand;

	
	if (h2reseult < h1reseult) {
		//cout << "enter different hand comparing in special+++++++++++++++++++++++++" << endl;
		return false;
	}
	else if (h1reseult < h2reseult) {
		//cout << "enter different hand comparing in specia--------------------------" << endl;
		return true;
	}
	else {
		//straight flush
		if (h1reseult == 0) {
			int i = 4;
			while (i > -1) {
				if (vec2[i].r < vec1[i].r) { return true; }
				else if (vec1[i].r < vec2[i].r) { return false; }
				else {
					//do nothing
				}
				--i;
			}
			return false;
		}
		//straight
		else if (h1reseult == 4) {
			int i = 4;
			while (i > -1) {
				if (vec2[i].r < vec1[i].r) { return true; }
				else if (vec1[i].r < vec2[i].r) { return false; }
				else {
					//do nothing
				}
				--i;
			}

			i = 4;
			while (i > -1) {
				if (vec2[i].s < vec1[i].s) { return true; }
				else if (vec1[i].s < vec2[i].s) { return false; }
				else {
					//do nothing
				}
				--i;
			}
			return false;
		}
		//flush
		else if (h1reseult == 3) {
			int i = 4;
			while (i > -1) {
				if (vec2[i].r < vec1[i].r) { return true; }
				else if (vec1[i].r < vec2[i].r) { return false; }
				else {
					//do nothing
				}
				--i;
			}
			return false;
		}
		//four of a kind
		else if (h1reseult == 1) {
			int num_rhs = vec1[2].r;
			int num_lhs = vec2[2].r;
			int dr;
			int dl;
			if (vec1[0].r != vec1[2].r) { dr = 0; }
			else { dr = 4; }
			if (vec2[0].r != vec2[2].r) { dl = 0; }
			else { dl = 4; }
			if (num_rhs > num_lhs) {
				return true;
			}
			else if (num_rhs < num_lhs) {
				return false;
			}
			else {//if the four cards equal
				if (vec1[dr].r > vec2[dl].r) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		//full house
		else if (h1reseult == 2) {
			int dr;
			int dl;
			if (vec1[0].r != vec1[2].r) { dr = 0; }
			else { dr = 4; }
			if (vec2[0].r != vec2[2].r) { dl = 0; }
			else { dl = 4; }

			if (vec1[2].r > vec2[2].r) {
				return true;
			}
			else if (vec1[2].r < vec2[2].r) {
				return false;
			}
			else {
				if (vec1[dr].r > vec2[dl].r) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		// three of a kind
		else if (h1reseult == 5) {
			int i = 0;
			int j = 0;
			int threer = 0;
			int threel = 0;
			int r1;
			int r2;
			int l1;
			int l2;
			while (i < 3) {
				if ((vec1[i].r == vec1[i + 1].r) && (vec1[i + 1].r == vec1[i + 2].r))
				{
					threer = vec1[i].r;
					if (i == 0) { r1 = 3;r2 = 4; }
					else if (i == 1) { r1 = 0;r2 = 4; }
					else { r1 = 0; r2 = 1; }
				}
				i++;
			}
			while (j < 3) {
				if ((vec2[j].r == vec2[j + 1].r) && (vec2[j + 1].r == vec2[j + 2].r))
				{
					threel = vec2[j].r;
					if (j == 0) { l1 = 3;l2 = 4; }
					else if (j == 1) { l1 = 0;l2 = 4; }
					else { l1 = 0; l2 = 1; }
				}
				j++;
			}
			if (threer > threel) {
				return true;
			}
			else if (threer < threel) {
				return false;
			}
			else {
				if (vec1[r2].r > vec2[l2].r) {
					return true;
				}
				else if (vec1[r2].r < vec2[l2].r) {
					return false;
				}
				else {
					if (vec1[r1].r > vec2[l1].r) {
						return true;
					}
					else if (vec1[r1].r < vec2[l1].r) {
						return false;
					}
					else {
						return false;
					}
				}
			}
		}
		// two pairs
		else if (h1reseult == 6) {
			if (vec2[3].r < vec1[3].r) {
				return true;
			}
			else if (vec1[3].r < vec2[3].r) {
				return false;
			}
			else {
				if (vec2[1].r < vec1[1].r) {
					return true;
				}
				else if (vec1[1].r < vec2[1].r) {
					return false;
				}
				else {
					int fifth1 = 0;
					int fifth2 = 0;
					if (vec1[0].r != vec1[1].r) { fifth1 = vec1[0].r; }// pos 0
					if (vec2[0].r != vec2[1].r) { fifth2 = vec2[0].r; }//pos 0
					if (vec1[4].r != vec1[3].r) { fifth1 = vec1[4].r; }//pos 4
					if (vec2[4].r != vec2[3].r) { fifth2 = vec2[4].r; }//pos 4
					if ((vec1[2].r != vec1[3].r) && (vec1[2].r != vec1[1].r)) { fifth1 = vec1[2].r; }//pos 2
					if ((vec2[2].r != vec2[3].r) && (vec2[2].r != vec2[1].r)) { fifth2 = vec2[2].r; }

					if (fifth1 > fifth2) {
						return true;
					}
					else {
						return false;
					}
				}
			}
		}
		// one pair
		else if (h1reseult == 7) {
			int i = 0;
			int j = 0;
			int p1_rhs = 0;
			int p1_lhs = 0;
			int comp1_rhs, comp2_rhs, comp3_rhs;
			int comp1_lhs, comp2_lhs, comp3_lhs;
			while (i < 4) {
				if (vec1[i].r == vec1[i + 1].r)
				{
					p1_rhs = vec1[i].r;
					if (i == 3) {
						comp1_rhs = vec1[0].r;
						comp2_rhs = vec1[1].r;
						comp3_rhs = vec1[2].r;
					}
					else if (i == 2) {
						comp1_rhs = vec1[0].r;
						comp2_rhs = vec1[1].r;
						comp3_rhs = vec1[4].r;
					}
					else if (i == 1) {
						comp1_rhs = vec1[0].r;
						comp2_rhs = vec1[3].r;
						comp3_rhs = vec1[4].r;
					}
					else if (i == 0) {
						comp1_rhs = vec1[2].r;
						comp2_rhs = vec1[3].r;
						comp3_rhs = vec1[4].r;
					}

				}
				++i;
			}//now i have the rank when they are equal
			while (j < 4) {
				if (vec2[j].r == vec2[j + 1].r)
				{
					p1_lhs = vec2[j].r;
					if (j == 3) {
						comp1_lhs = vec2[0].r;
						comp2_lhs = vec2[1].r;
						comp3_lhs = vec2[2].r;
					}
					else if (j == 2) {
						comp1_lhs = vec2[0].r;
						comp2_lhs = vec2[1].r;
						comp3_lhs = vec2[4].r;
					}
					else if (j == 1) {
						comp1_lhs = vec2[0].r;
						comp2_lhs = vec2[3].r;
						comp3_lhs = vec2[4].r;
					}
					else if (j == 0) {
						comp1_lhs = vec2[2].r;
						comp2_lhs = vec2[3].r;
						comp3_lhs = vec2[4].r;
					}
				}
				++j;
			}

			if (p1_rhs > p1_lhs) { return true; }
			else if (p1_rhs < p1_lhs) { return false; }
			else {
				if (comp3_rhs > comp3_lhs) { return true; }
				else if (comp3_lhs > comp3_rhs) { return false; }
				else {
					if (comp2_rhs > comp2_lhs) { return true; }
					else if (comp2_lhs > comp2_rhs) { return false; }
					else {
						if (comp1_rhs > comp1_lhs) { return true; }
						else if (comp1_lhs > comp1_rhs) { return false; }
						else { return false; }
					}
				}
			}
		}
		// no rank
		else { 
			int i = 4;
			while (i > -1) {
				if (vec2[i].r < vec1[i].r) { return true; }
				else if (vec1[i].r < vec2[i].r) { return false; }
				else {
					//do nothing
				}
				--i;
			}
			return false;
		}
	}
}


// same as the poker_rank1 in FiveCardDraw and SevenCardStude. comparing totally different hands within a deck
// but take in hands directly instead of players
bool poker_rank(Hand& h1, Hand& h2){
	//p1 higher -> return true;
	//swapped from last project, p1 is now rhs
	int h1reseult = Hand::check(h1.hand);
	int h2reseult = Hand::check(h2.hand);
	vector <Card> vec1 = h1.hand;
	vector<Card> vec2 = h2.hand;

	if (h2reseult > h1reseult) {
		return true;
	}
	else if (h1reseult > h2reseult) {
		return false;
	}
	else {
		//straight flush
		if (h1reseult == 0) {
			if (vec1[4].r > vec2[4].r) {
				return true;
			}
			else {
				return false;
			} //straight flush, compare highest rank
		}
		else if (h1reseult == 4) { //straight
			if (vec2[4].r < vec1[4].r) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (h1reseult == 3) { //flush
			int i = 4;
			while (i > -1) {
				if (vec2[i].r < vec1[i].r) { return true; }
				else if (vec1[i].r < vec2[i].r) { return false; }
				else {
					//do nothing
				}
				--i;
			}
			return false;
		}
		else if (h1reseult == 1) {//four of a kind
			int num_rhs = vec1[2].r;
			int num_lhs = vec2[2].r;
			if (num_rhs > num_lhs) {
				return true;
			}
			else return false;
		}
		else if (h1reseult == 2) {  //full house
			if (vec1[2].r > vec2[2].r) {
				return true;
			}
			else return false;
		}
		else if (h1reseult == 5) {
			int i = 0;
			int j = 0;
			int three1 = 0;
			int three2 = 0;
			while (i < 3) {
				if ((vec1[i].r == vec1[i + 1].r) && (vec1[i + 1].r == vec1[i + 2].r))
				{
					three1 = vec1[i].r;
				}
				i++;
			}
			while (j < 3) {
				if ((vec2[j].r == vec2[j + 1].r) && (vec2[j + 1].r == vec2[j + 2].r))
				{
					three2 = vec2[j].r;
				}
				j++;
			}
			if (three1 > three2) {
				return true;
			}
			else return false;
		}
		else if (h1reseult == 6) {

			if (vec2[3].r < vec1[3].r) {
				return true;
			}
			else if (vec1[3].r < vec2[3].r) {
				return false;
			}
			else {
				if (vec2[1].r < vec1[1].r) {
					return true;
				}
				else if (vec1[1].r < vec2[1].r) {
					return false;
				}
				else {
					int fifth1 = 0;
					int fifth2 = 0;
					if (vec1[0].r != vec1[1].r) { fifth1 = vec1[0].r; }// pos 0
					if (vec2[0].r != vec2[1].r) { fifth2 = vec2[0].r; }//pos 0
					if (vec1[4].r != vec1[3].r) { fifth1 = vec1[4].r; }//pos 4
					if (vec2[4].r != vec2[3].r) { fifth2 = vec2[4].r; }//pos 4
					if ((vec1[2].r != vec1[3].r) && (vec1[2].r != vec1[1].r)) { fifth1 = vec1[2].r; }//pos 2
					if ((vec2[2].r != vec2[3].r) && (vec2[2].r != vec2[1].r)) { fifth2 = vec2[2].r; }

					if (fifth1 > fifth2) {
						return true;
					}
					else {
						return false;
					}
				}
			}
		}

		else if (h1reseult == 7) {
			//one pair
			int i = 0;
			int j = 0;
			int p1_rhs = 0;
			int p1_lhs = 0;
			int comp1_rhs, comp2_rhs, comp3_rhs;
			int comp1_lhs, comp2_lhs, comp3_lhs;
			while (i < 4) {
				if (vec1[i].r == vec1[i + 1].r)
				{
					p1_rhs = vec1[i].r;
					if (i == 3) {
						comp1_rhs = vec1[0].r;
						comp2_rhs = vec1[1].r;
						comp3_rhs = vec1[2].r;
					}
					else if (i == 2) {
						comp1_rhs = vec1[0].r;
						comp2_rhs = vec1[1].r;
						comp3_rhs = vec1[4].r;
					}
					else if (i == 1) {
						comp1_rhs = vec1[0].r;
						comp2_rhs = vec1[3].r;
						comp3_rhs = vec1[4].r;
					}
					else if (i == 0) {
						comp1_rhs = vec1[2].r;
						comp2_rhs = vec1[3].r;
						comp3_rhs = vec1[4].r;
					}

				}
				++i;
			}//now i have the rank when they are equal
			while (j < 4) {
				if (vec2[j].r == vec2[j + 1].r)
				{
					p1_lhs = vec2[j].r;
					if (j == 3) {
						comp1_lhs = vec2[0].r;
						comp2_lhs = vec2[1].r;
						comp3_lhs = vec2[2].r;
					}
					else if (j == 2) {
						comp1_lhs = vec2[0].r;
						comp2_lhs = vec2[1].r;
						comp3_lhs = vec2[4].r;
					}
					else if (j == 1) {
						comp1_lhs = vec2[0].r;
						comp2_lhs = vec2[3].r;
						comp3_lhs = vec2[4].r;
					}
					else if (j == 0) {
						comp1_lhs = vec2[2].r;
						comp2_lhs = vec2[3].r;
						comp3_lhs = vec2[4].r;
					}
				}
				++j;
			}
			if (p1_rhs > p1_lhs) { return true; }
			else if (p1_rhs < p1_lhs) { return false; }
			else {
				if (comp3_rhs > comp3_lhs) { return true; }
				else if (comp3_lhs > comp3_rhs) { return false; }
				else {
					if (comp2_rhs > comp2_lhs) { return true; }
					else if (comp2_lhs > comp2_rhs) { return false; }
					else {
						if (comp1_rhs > comp1_lhs) { return true; }
						else if (comp1_lhs > comp1_rhs) { return false; }
						else { return false; }
					}
				}
			}

		}

		else { //no rank
			int i = 4;
			while (i > -1) {
				if (vec2[i].r < vec1[i].r) { return true; }
				else if (vec1[i].r < vec2[i].r) { return false; }
				else {
					//do nothing
				}
				--i;
			}
			return false;
		}
	}
}





const Card Hand::operator[](size_t i) {
	if (i < hand.size()) {
		return hand[i];
	}
	else {
		throw index_out_of_bound;
	}
}

const void Hand::remove_card(size_t i) {
	if (i< hand.size()) {
		hand.erase(hand.begin()+i);
	}
	else {
		throw removal_out_of_bound;
	}
}

//takes in a vector of seven card hands, return the best five card Hand

Hand Hand::bestFive(vector<Card>& temp) {
	vector<Hand> hands21;
	Hand t;
	for (int i = 0; i <= 5;++i) {
		for (int j = i + 1; j <= 6;++j) {
			for (int k = 0; k <= 6; ++k) {
				t.hand.push_back(temp[k]);
				if (k == i || k == j) {
					t.hand.pop_back();
				}
			}
			hands21.push_back(t);
			t.hand.clear();
		}
	}
	std::sort(hands21.begin(), hands21.end(), poker_rankSpecial);

	return hands21[0]; // could be 0 if the poker_rank was misunderstood
}


