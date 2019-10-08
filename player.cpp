
#include "stdafx.h"
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 

#include <vector>
using namespace std;

Player::Player(const char* s) {
	string str(s);


	playersname = str;
	fold = false;
	numWin = 0;
	numLost = 0; // set the chips to be 20 at the beginning
	string txt = playersname + ".txt";
	ifstream file;
	file.open(txt);
	string input;
	//cout << playersname + ".txt" << endl;
	if (file.is_open()) {
		getline(file, input);

		istringstream ss1(input);
		string spliced;

		int count = 0;
		while (ss1 >> spliced) {
			if (count == 0) {
				//making sure it's the correct format
				//cout << "in name extracting" << endl;
				count++;
				continue;
			}
			if (spliced == " ") {
				continue;
			}
			if (count == 1) {
				//cout << "extracting wins" << endl;
				numWin = stoi(spliced);
				count++;
				continue;
			}
			if (count == 2) {
				//cout << "extracting losses" << endl;
				numLost = stoi(spliced);
				count++;
				continue;
			}
			if (count == 3) {
				chips = stoi(spliced);
				if (chips == 0) {
					bool reset = true;
					string resp;
					string ans1="yes";
					while (reset) {
						cout << "do you want to reset your chips to 20" << endl;
						cout << "please type 'yes'" << endl;
						getline(cin, resp);
						if (resp == ans1) {
							chips = 20;
							reset = false;
							break;
						}
						else continue;
					}
					break;
				}
				//cout << "inside" << endl;


			}
			//else { throw file_open_error; }
		}
	}
	else {
		fold = false;
		numWin = 0;
		numLost = 0; // set the chips to be 20 at the beginning
		chips = 20;
	}
}





//use the ostream to print out the player's name, number of wins, and number of losses with spaces between them 
ostream & operator<<(ostream & o, const Player& p) {
	o << p.playersname << " " << p.numWin << " " << p.numLost << flush;
	return o;
}

