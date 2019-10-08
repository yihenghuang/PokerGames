#include "stdafx.h"
#include "SevenCardStud.h"
#include "player.h"
#include "game.h"
#include "deck.h"
#include "hand.h"
#include "card.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <memory>
using namespace std;

SevenCardStud::SevenCardStud() : dealer(0), common_bet(0), highest_bet(0), oneleft(false) { //static definition
	for (int i = 0; i < 13; ++i) {
		for (int j = 0; j < 4; ++j) {
			mainDeck.add_card(Card(i, j));
		}
	}
}


// same as the poker_rank1 in FiveCardDraw. comparing totally different hands within a deck
bool SevenCardStud::poker_rankSeven(shared_ptr<Player> p1, shared_ptr<Player> p2)
{
	
	//p1 higher -> return true;
	//swapped from last project, p1 is now rhs
	Player player1 = *p1;
	Player player2 = *p2;
	int p1reseult = Hand::check(player1.get_hand().hand);
	int p2reseult = Hand::check(player2.get_hand().hand);
	vector <Card> vec1 = player1.get_hand().hand;
	vector<Card> vec2 = player2.get_hand().hand;
	//getting variables out 
	if (p2 == nullptr) {
		return false;
	}
	else if (p1 == nullptr) {
		return true;
	}

	else if (p2reseult > p1reseult) {
		return true;
	}
	else if (p1reseult > p2reseult) {
		return false;
	}
	else {
		//straight flush
		if (p1reseult == 0) {
			if (vec1[4].r > vec2[4].r) {
				return true;
			}
			else {
				return false;
			} //straight flush, compare highest rank
		}
		else if (p1reseult == 4) { //straight
			if (vec2[4].r < vec1[4].r) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (p1reseult == 3) { //flush
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
		else if (p1reseult == 1) {//four of a kind
			int num_rhs = vec1[2].r;
			int num_lhs = vec2[2].r;
			if (num_rhs > num_lhs) {
				return true;
			}
			else return false;
		}
		else if (p1reseult == 2) {  //full house
			if (vec1[2].r > vec2[2].r) {
				return true;
			}
			else return false;
		}
		else if (p1reseult == 5) {
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
		else if (p1reseult == 6) {
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

		else if (p1reseult == 7) {
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




//not implemennted
bool SevenCardStud::call(Player& a) {
	return 0;
}
//not implemennted
bool SevenCardStud::raise(Player& a, int raise) {
	return 0;
}
//not implemennted
int SevenCardStud::before_turn(Player & a) {
	return 0;
}








// fill the hand with 5 cards if it has less than 5
//new: ask about bet
int SevenCardStud ::turn(Player & a)
{
	int player_size = vpPlayer.size();


	std::cout << "------------------PLAYER " << a.playersname<<"-------------------" << endl;
	std::cout << "MY HAND: " << a.playersCards.asString() << endl;
	int pos;
	for (size_t i = 0; i < vpPlayer.size(); ++i) {
		if (vpPlayer[i]->playersname == a.playersname) {pos = i;}
	}
	int i = (pos + 1)%player_size;
	while (i != pos) {
		std::cout << "Player Name: " << vpPlayer[i]->playersname << flush;
		std::cout << " Hand: " << vpPlayer[i]->playersCards.asStringSeven() << flush;// only prints those visible
		std::cout << " Current Bet: " << vpPlayer[i]->betweight << endl;
		i = (i + 1) % player_size;
	}
	cout << "You has won previously:" << a.get_wins() << endl;
	cout << "You has lost previously:" << a.get_loss() << endl;
	cout << "Your remaining chips :" << a.chips << endl;
	cout << "Your bet is: " << a.betweight << endl;
	cout << "The highest bet: " << highest_bet << endl;


	
	bool tof = true;
	while (tof) {
		if (a.chips == 0) {
			cout << "you have no remaining chips, but still in the game." << endl;
			tof = false;
		}
		else if (a.betweight == highest_bet) {
			cout << "-> Do you want to check or raise 1 or 2? "  <<endl;
			string input;
			getline(cin, input);
			if (input == "1") {//raise one
				size_t diff = 1;
				/*
				if (a.chips < diff) {
					cout << "Not enought chips. All in" << endl;
					diff = a.chips;
				}
				*/
				a.chips = a.chips - diff;
				a.betweight = a.betweight + diff;
				common_bet = common_bet + diff;
				highest_bet = highest_bet + 1;
				tof = false;
			}
			else if (input == "2") {// raise two
				int diff =   2;
				if (a.chips < diff) {
					cout << "Not enought chips. All in" << endl;
					diff = a.chips;
				}
				a.chips = a.chips - diff;
				a.betweight = a.betweight + diff;
				common_bet = common_bet + diff;
				highest_bet = highest_bet + 2;
				tof = false;
			}
			else if (input == "check") { // check 
				tof = false;
			}
			else {
				continue;
			}
		}
		else {
			cout << "-> Do you want to fold, call, or raise 1 or 2? Your bet is lower than the highest." << endl;
			string input;
			getline(cin, input);
			if (input == "1") {//raise one
				int diff = highest_bet - a.betweight + 1;
				if (a.chips < diff) {
					cout << "Not enought chips. All in" << endl;
					diff = a.chips;
				}
				a.chips = a.chips - diff;
				a.betweight = a.betweight + diff;
				common_bet = common_bet + diff;
				highest_bet = highest_bet + 1;
				tof = false;
			}
			else if (input == "2") {// raise two
				int diff = highest_bet - a.betweight + 2;
				if (a.chips < diff) {
					cout << "Not enought chips. All in" << endl;
					diff = a.chips;
				}
				a.chips = a.chips - diff;
				a.betweight = a.betweight + diff;
				common_bet = common_bet + diff;
				highest_bet = highest_bet + 2;
				tof = false;
			}
			else if (input == "call") {//call
				int diff = highest_bet - a.betweight;
				if (a.chips < diff) {
					cout << "Not enought chips. All in" << endl;
					diff = a.chips;
				}
				a.chips = a.chips - diff;
				a.betweight = a.betweight + diff;
				common_bet = common_bet + diff;
				tof = false;
			}
			
			else if (input == "fold") {//fold /////**************ISSUE********************************
				tof = false;
				a.fold = true;
				int card_cnt = 0;
				while (card_cnt < a.playersCards.size()) {
					mainDeck.add_card(a.get_hand()[0]);
					a.playersCards.remove_card(0);
					card_cnt++;
				}
				a.numLost++;
				ofstream myfile;
				foldname = foldname+a.playersname+" ";
				myfile.open(a.playersname + ".txt");
				myfile << a.playersname << " " << a.numWin << " " << a.numLost << " " << a.chips << endl;
				myfile.close();
				vpPlayer.erase(vpPlayer.begin() + pos);
				if (vpPlayer.size() < 2) {
					oneleft = true;
					vpPlayer[0]->numWin++;
					vpPlayer[0]->chips = vpPlayer[0]->chips+common_bet;
					cout << "=====>>>Game over. all other players folded<<<======" << endl;
					cout << foldname << "have fold ***************" << endl;
					cout << "*******************" << vpPlayer[0]->playersname << " won the game!**************" << endl;
					std::cout << "Player's highest five cards: " << vpPlayer[0]->playersCards.asString() << endl;
					cout << "Player has wins previously:" << vpPlayer[0]->get_wins() << endl;
					cout << "Player has losses previously:" << vpPlayer[0]->get_loss() << endl;
					cout << "remaining chips " << vpPlayer[0]->chips << endl;
					int cardcnt = 0;
					while (cardcnt <vpPlayer[0]->playersCards.size()) {
						mainDeck.add_card(vpPlayer[0]->get_hand()[0]);
						vpPlayer[0]->playersCards.remove_card(0);
						cardcnt++;
					}
					ofstream file;
					string name = vpPlayer[0]->playersname;
					file.open(vpPlayer[0]->playersname + ".txt");
					file << vpPlayer[0]->playersname << " " << vpPlayer[0]->numWin << " " << vpPlayer[0]->numLost << " " << vpPlayer[0]->chips << endl;
					file.close();
					
				}
			}
			else {
				continue;
			}
		}
	}
	
	return 0;
}

//print out players name and hand after turn
// new: print player out with secret cards hiden
int SevenCardStud::after_turn(Player & a)
{
	//Hand ahand = Hand::bestFive(a.get_hand().hand);
	//sort(ahand.hand.begin(), ahand.hand.end());
	std::cout << "---------------PLAYER STATUS AFTER TURN--------------" << endl;
	std::cout << "Player name: " << a.get_name() << endl;
	std::cout << "Player's highest five cards: " << a.playersCards.asString()<< endl;
	cout << "Player has wins previously:" << a.get_wins() << endl;
	cout << "Player has losses previously:" << a.get_loss() << endl;
	cout << "remaining chips " << a.chips << endl;
	return 0;
}

//deal cards to players can call before_turn to ask for removal
int SevenCardStud::before_round()
{
	mainDeck.callShuffle();
	for (size_t i = 0; i < vpPlayer.size();++i) {
		if (vpPlayer[i]->chips == 0) {
			cout << vpPlayer[i]->playersname << " have no chips. Respond Yes to reset chip count to 20" << endl;
			string res;
			getline(cin, res);
			if (res == "Yes") {
				vpPlayer[i]->chips = 20;
				cout << "Chips set to 20 " << endl;
			}
			// kick out
			else {
				cout << vpPlayer[i]->playersname << " is out of the game" << endl;
				vpPlayer.erase(vpPlayer.begin() + i);
			}
		}
	}
	int player_size = vpPlayer.size();
	
	for (int a = 0; a < player_size; ++a) {
		vpPlayer[a]->chips--; // each player paying 1 chip
		vpPlayer[a]->betweight++;
		common_bet++;
		Hand temp = Hand(); // construct empty hand
		hands.push_back(temp); //empty hand pushed to hands vec???
	}

	highest_bet = 1;

	mainDeck.callShuffle();
	
	int pos = (dealer + 1) % player_size;
	int rcd = (dealer + 1) % player_size;

	for (int i = 0; i < 3; ++i) { // deal first 3 cards to all players
		do {
			vpPlayer[pos]->playersCards << mainDeck;
			pos = (pos + 1) % player_size;
		} while (pos != rcd);
	}
	mainDeck.callShuffle();

	return 0;
}
//call turn and after_turn to refill to 5 cards and print out players name and hand
//return error code if there is any in turn and after_turn
int SevenCardStud::round()
{
	int player_size = vpPlayer.size();
	int pos = (dealer + 1) % player_size;
	int rcd = (dealer + 1) % player_size;

	bool goodturn = false;
	//dealing 4 cards and conducting 5 bets
	for (int i = 0; i <= 4;++i) {
		if (oneleft == false) {
		cout << "################# This is the " << i + 1 << " turn ############### " << endl;
		}

		player_size = vpPlayer.size();
		pos = (dealer + 1) % player_size;
		rcd = (dealer + 1) % player_size;
		goodturn = false;
		
		while (!goodturn && oneleft == false) {
			// complete one circle of betting ************* might cause problem during folding
			do {
				player_size = vpPlayer.size();
				int rcd1 = turn(*vpPlayer[pos]);
				if (rcd1 != 0) {
					return rcd1;
				}

				if (vpPlayer.size() == player_size - 1) {
					pos--;
				}
				pos = (pos + 1) % vpPlayer.size();
			} while (pos != rcd && oneleft==false);
			
			if (oneleft == true) {
				break;
			}

			if (oneleft == false) {
				//a for-loop to check if all cards are equal
				for (size_t i = 0; i < vpPlayer.size(); ++i) {
					goodturn = true;
					if (vpPlayer[i]->betweight != highest_bet) {
						goodturn = false;
						break;
					}
				}
			}
			
		}
		
		//deal one more card to players if less than 7
		if (oneleft == false) {
			mainDeck.callShuffle();
			player_size = vpPlayer.size();
			if (vpPlayer[dealer]->get_hand().size() < 7) {
				pos = (dealer + 1) % player_size;
				rcd = (dealer + 1) % player_size;
				do {
					vpPlayer[pos]->playersCards << mainDeck;
					pos = (pos + 1) % player_size;
				} while (pos != rcd);
			}
		}
		if (oneleft == true) {
			break;
		}

	}
	
	for (size_t i = 0; i < vpPlayer.size(); ++i) { // clear all bet weight
		vpPlayer[i]->betweight = 0;
	}
	
	return 0;
}


int SevenCardStud::player_size() {
	return vpPlayer.size();
}

int SevenCardStud::after_round()
{
	if (oneleft == false) {

		// copy the cards back to mainDeck
		for (size_t count = 0; count < vpPlayer.size();++count) {
			for (int i = 0; i < vpPlayer[count]->get_hand().size(); ++i) {
				mainDeck.add_card(vpPlayer[count]->get_hand()[i]);
			}
		}



		mainDeck.callShuffle();



		for (size_t i = 0; i < vpPlayer.size(); ++i) {
			Hand t = Hand::bestFive(vpPlayer[i]->playersCards.hand);
			vpPlayer[i]->playersCards.hand.clear();
			vpPlayer[i]->playersCards.hand = t.hand;

			t.hand.clear();
		}

		std::sort(vpPlayer.begin(), vpPlayer.end(), SevenCardStud::poker_rankSeven);

		//determine memhers of co-winning
		int winnersNum = 1;
		vector<shared_ptr<Player>> t1;
		vector<shared_ptr<Player>> t2;
		for (size_t i = 1; i < vpPlayer.size(); ++i) {
			t1.push_back(vpPlayer[i - 1]);
			t1.push_back(vpPlayer[i]);
			std::sort(t1.begin(), t1.end(), SevenCardStud::poker_rankSeven);
			t2.push_back(vpPlayer[i]);
			t2.push_back(vpPlayer[i - 1]);
			std::sort(t2.begin(), t2.end(), SevenCardStud::poker_rankSeven);
			if (t1[0]->get_hand() == t2[1]->get_hand()) {
				t1.clear();
				t2.clear();
				winnersNum++;
			}
			else {
				break;
			}
		}


		//give all winners credit
		for (int i = 0; i < winnersNum;++i) {
			cout << "**************" << vpPlayer[i]->playersname << " won the game!" << "*************" << endl;
			cout << endl;
			vpPlayer[i]->numWin++; // winner record ++
			vpPlayer[i]->chips = vpPlayer[i]->chips + common_bet / winnersNum;
		}

		//losers add to their lost
		for (size_t i = winnersNum; i < vpPlayer.size(); ++i) {
			vpPlayer[i]->numLost++;
		}

		//call after_turn to print out all results

		for (size_t i = 0; i < vpPlayer.size(); ++i) {
			after_turn(*vpPlayer[i]);
			
		}

	}

	oneleft = false;
	common_bet = 0;
	highest_bet = 0;
	if (foldname.size()>0) {
		cout << "********" << foldname << " have fold without showing hands*************" << endl;
	}
	for (size_t i = 0; i < vpPlayer.size(); ++i) {
		vpPlayer[i]->get_hand().hand.clear();
	}

	std::cout << "Main deck now has " << mainDeck.size() << "cards" << endl;
	std::cout << mainDeck << endl;

	

	string ans = "No";
	string res;
	bool prompt_ = true;
	while (prompt_) {
		std::cout << "Please type in the player name you want to exit the game.. if none please type in 'No' .." << endl;
		getline(cin, res);
		if (res == "No" || res == "no" || res == "NO") {
			break;
		}
		istringstream iss(res);
		string word;
		while (iss >> word) {
			if (word == " ") {
				continue;
			}
			else {
				for (size_t i = 0; i < vpPlayer.size(); ++i) {
					if (word == vpPlayer[i]->playersname) {
						ofstream myfile;
						myfile.open(res + ".txt");
						myfile << vpPlayer[i]->playersname << " " << vpPlayer[i]->numWin << " " << vpPlayer[i]->numLost << " " << vpPlayer[i]->chips<< endl;
						myfile.close();
						vpPlayer.erase(vpPlayer.begin() + i);
						prompt_ = false;
					}
					else {
						continue;
					}//process ones that are valid
				}

			}
		}
	}


	string new_player;
	bool join = true;
	while (join) {
		std::cout << "any new player to join the game? please type in the name separated by a black space.. " << endl;
		std::cout << "if none new players you want to add, just type in 'No' " << endl;
		std::cout << "\n" << endl;
		string input;
		//cin >> input;
		getline(cin, input);
		if (input == ans || input == "no" || input == "no") {
			break;
		}
		istringstream iss(input);
		string word;
		while (iss >> word) {
			if (word == " ") {
				continue;

			}
			try {
				Game::add_player(word.c_str());
				join = false;
			}
			catch (string a) {
				std::cout << a;
			}
		}
	}

	// if ingame or rejoin player have zero, ask for refill or kick out
	for (size_t i = 0; i < vpPlayer.size();++i) {
		if (vpPlayer[i]->chips == 0) {
			cout << vpPlayer[i]->playersname << " have no chips. Respond Yes to reset chip count to 20" << endl;
			string res;
			getline(cin, res);
			if (res == "Yes") {
				vpPlayer[i]->chips = 20;
			}
			else {// kick out
				cout << vpPlayer[i]->playersname << " is out of the game" << endl;
				ofstream myfile;
				myfile.open(vpPlayer[i]->playersname + ".txt");
				myfile << vpPlayer[i]->playersname << " " << vpPlayer[i]->numWin << " " << vpPlayer[i]->numLost << " " << vpPlayer[i]->chips << endl;
				myfile.close();
				vpPlayer.erase(vpPlayer.begin()+i);
			}
		}
	}

	if (vpPlayer.size() < 2) {
		Game::stop_game();
		vpPlayer.clear();
		play = false;
		cout << "The Game was stopped. Too Few Players" << endl;
		//throw too_few_players;
		//too less people
	}
	else {
		dealer++;
	}
	return 0;
}

