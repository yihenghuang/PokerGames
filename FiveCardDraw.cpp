#include "stdafx.h"
#include "FiveCardDraw.h"
#include "player.h"
#include "game.h"
#include "FiveCardDraw.h"
#include "deck.h"
#include "hand.h"
#include "card.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <memory>
using namespace std;


FiveCardDraw::FiveCardDraw() : dealer(0), bet(false), common_bet(0), highest_bet(1) { //static definition
	for ( int i = 0; i < 13; ++i) {
		for ( int j = 0; j < 4; ++j) {
			mainDeck.add_card(Card(i, j));
		}
	}
}





bool FiveCardDraw::poker_rank1(shared_ptr<Player> p1, shared_ptr<Player> p2)
{
	//p1 higher -> return true;
	//swapped from last project, p1 is now rhs
	Player r_player = *p1;
	Player l_player = *p2;
	int rhs_type_reseult = Hand::check(r_player.get_hand().hand);
	int lhs_type_reseult = Hand::check(l_player.get_hand().hand);
	vector <Card> rhs_vec = r_player.get_hand().hand;
	vector<Card> lhs_vec = l_player.get_hand().hand;
	//getting variables out 
	if (p2 == nullptr) {
		return false;
	}
	else if (p1 == nullptr) {
		return true;
	}

	else if (lhs_type_reseult < rhs_type_reseult) {
		return true;
	}
	else if (rhs_type_reseult < lhs_type_reseult) {
		return false;
	}
	else {
		//straight flush
		if (rhs_type_reseult == 0) {
			if (rhs_vec[4].r > lhs_vec[4].r) {
				return true;
			}
			else {
				return false;
			} //straight flush, compare highest rank
		}
		else if (rhs_type_reseult == 4) { //straight
			if (lhs_vec[4].r < rhs_vec[4].r) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (rhs_type_reseult == 3) { //flush
			int i = 4;
			while (i > -1) {
				if (lhs_vec[i].r < rhs_vec[i].r) { return true; }
				else if (rhs_vec[i].r < lhs_vec[i].r) { return false; }
				else {
					//do nothing
				}
				--i;
			}
			return false;
		}
		else if (rhs_type_reseult == 1) {//four of a kind
			int num_rhs = rhs_vec[2].r;
			int num_lhs = lhs_vec[2].r;
			if (num_rhs > num_lhs) {
				return true;
			}
			else return false;
		}
		else if (rhs_type_reseult == 2) {  //full house
			if (rhs_vec[2].r > lhs_vec[2].r) {
				return true;
			}
			else return false;
		}
		else if (rhs_type_reseult == 5) {
			int i = 0;
			int j = 0;
			int three1 = 0;
			int three2 = 0;
			while (i < 3) {
				if ((rhs_vec[i].r == rhs_vec[i + 1].r) && (rhs_vec[i + 1].r == rhs_vec[i + 2].r))
				{
					three1 = rhs_vec[i].r;
				}
				i++;
			}
			while (j < 3) {
				if ((lhs_vec[j].r == lhs_vec[j + 1].r) && (lhs_vec[j + 1].r == lhs_vec[j + 2].r))
				{
					three2 = lhs_vec[j].r;
				}
				j++;
			}
			if (three1 > three2) {
				return true;
			}
			else return false;
		}
		else if (rhs_type_reseult == 6) {

			int i = 0;
			int j = 0;
			int p1_rhs = 0;
			int p2_rhs = 0;
			int p1_lhs = 0;
			int p2_lhs = 0;
			int fifthr = 0;
			int fifthl = 0;
			while (i < 4) {
				if (rhs_vec[i].r == rhs_vec[i + 1].r)// if right 0=1, 1 =2, 2=3
				{
					if (i == 0) {
						p1_rhs = rhs_vec[0].r;
					}
					else if (i == 1) {
						p1_rhs = rhs_vec[1].r;
						fifthr = rhs_vec[0].r;
					}
					else if (i == 2) {
						fifthr = rhs_vec[4].r;
					}
					else fifthr = rhs_vec[2].r;

					p2_rhs = rhs_vec[j].r; // second entry set its value
				}
				++i;
			}
			while (j < 4) {
				if (rhs_vec[j].r == rhs_vec[j + 1].r)
				{
					if (j == 0) {
						p1_lhs = lhs_vec[0].r;
					}
					else if (j == 1) {
						p1_lhs = lhs_vec[1].r;
						fifthl = lhs_vec[0].r;
					}
					else if (j == 2) {
						fifthl = lhs_vec[4].r;
					}
					else fifthl = lhs_vec[2].r;

					p2_lhs = lhs_vec[j].r; // second entry set its value
				}
				++j;
			}
			if (p2_rhs > p2_lhs) {
				return true;
			}
			else if (p2_lhs > p2_rhs) {
				return false;
			}
			else {
				if (p1_rhs > p1_lhs) {
					return true;
				}
				else if (p1_lhs > p1_rhs) {
					return false;
				}
				else {
					if (fifthr > fifthl) {
						return true;
					}
					else {
						return false;
					}
				}
			}
		}

		else if (rhs_type_reseult == 7) {
			//one pair
			int i = 0;
			int j = 0;
			int p1_rhs = 0;
			int p1_lhs = 0;
			int comp1_rhs, comp2_rhs, comp3_rhs;
			int comp1_lhs, comp2_lhs, comp3_lhs;
			while (i < 4) {
				if (rhs_vec[i].r == rhs_vec[i + 1].r)
				{
					p1_rhs = rhs_vec[i].r;
					if (i == 3) {
						comp1_rhs = rhs_vec[0].r;
						comp2_rhs = rhs_vec[1].r;
						comp3_rhs = rhs_vec[2].r;
					}
					else if (i == 2) {
						comp1_rhs = rhs_vec[0].r;
						comp2_rhs = rhs_vec[1].r;
						comp3_rhs = rhs_vec[4].r;
					}
					else if (i == 1) {
						comp1_rhs = rhs_vec[0].r;
						comp2_rhs = rhs_vec[3].r;
						comp3_rhs = rhs_vec[4].r;
					}
					else if (i == 0) {
						comp1_rhs = rhs_vec[2].r;
						comp2_rhs = rhs_vec[3].r;
						comp3_rhs = rhs_vec[4].r;
					}

				}
				++i;
			}//now i have the rank when they are equal
			while (j < 4) {
				if (lhs_vec[j].r == lhs_vec[j + 1].r)
				{
					p1_lhs = lhs_vec[j].r;
					if (j == 3) {
						comp1_lhs = lhs_vec[0].r;
						comp2_lhs = lhs_vec[1].r;
						comp3_lhs = lhs_vec[2].r;
					}
					else if (j == 2) {
						comp1_lhs = lhs_vec[0].r;
						comp2_lhs = lhs_vec[1].r;
						comp3_lhs = lhs_vec[4].r;
					}
					else if (j == 1) {
						comp1_lhs = lhs_vec[0].r;
						comp2_lhs = lhs_vec[3].r;
						comp3_lhs = lhs_vec[4].r;
					}
					else if (j == 0) {
						comp1_lhs = lhs_vec[2].r;
						comp2_lhs = lhs_vec[3].r;
						comp3_lhs = lhs_vec[4].r;
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
				if (lhs_vec[i].r < rhs_vec[i].r) { return true; }
				else if (rhs_vec[i].r < lhs_vec[i].r) { return false; }
				else {
					//do nothing
				}
				--i;
			}
			return false;
		}
	}
}


int FiveCardDraw::before_turn(Player& a) {
	std::cout << "------------------PLAYER STATUS-------------------" << endl;
	std::cout << "Player Name: " << a.get_name() << endl;

	std::cout << "Player Hand: " << a.playersCards.asString() << endl;
	cout << "Player has wins previously:" << a.get_wins() << endl;
	cout << "Player has losses previously:" << a.get_loss() << endl;
	cout << "player has chips previously: " << a.chips << endl;
	cout << "now the highest bet is: " << highest_bet << endl;
	cout << "your bet now is: " << a.betweight5 << endl;
	cout << "pot has money: " << common_bet << endl;

	betting_phase(a);

	string input;
	if (a.fold == false) {
		//cout << "count: " << a.enter << endl;
		if (play == true) {
			if (a.enter == 0) {
				a.enter = 1;
				bool flag = true;
				while (flag) {
					std::cout << "Do you want to discard any of the card? please give the position of the card in the hand. Each position separated by a blank space" << endl;
					std::getline(cin, input);
					istringstream iss(input);
					int pos_discard;
					vector<size_t> rcd;
					//CHECK INPUT HERE
					if (input.length() > 9) {
						continue;
					}
					else if (input.length() == 0) {
						flag = false;
						return 0;
						break;
						//no cards to discard 
					}
					else {
						//cout << "valid input length inside" << endl;
						while (iss >> pos_discard) {
							if (pos_discard > 4 || pos_discard < 0) {
								continue;
							}
							if (pos_discard == ' ') {
								continue;
							}
							/*
							if (sstream.peek() == ' ') {
							sstream.ignore();
							}
							*/
							if (std::find(rcd.begin(), rcd.end(), pos_discard) != rcd.end()) {
								continue;
							}
							rcd.push_back(pos_discard);


						}
						int comp = (input.length() + 1) / 2;
						//cout << comp;
						if (rcd.size() == comp) {
							flag = false;
							size_t pos;
							//vector< Card> rcd_card;
							//vector<int> rcd_pos;
							std::cout << "discard card at : " << input << endl;

							for (size_t i = 0; i < rcd.size(); ++i) {
								pos = rcd[i];
								discarded.add_card(a.get_hand()[pos]);
								a.get_hand().remove_card(pos);
								for (size_t j = 0; j < rcd.size(); ++j) {
									if (rcd[j] > pos) {
										rcd[j]--;
									}
								}//update pointer location	
							}
							std::cout << "card discarded by all players: " << discarded << endl;

						}

					}
				}

			}

		}
	}

	return 0;
}

int FiveCardDraw::turn(Player & b)
{
	int curr_cards = b.get_hand().size();

	while (curr_cards < 5) { //**update curr_cards
		int card_index = mainDeck.size();
		//std::cout <<"card in main"<< card_index;
		if (card_index != 0) {
			mainDeck.callShuffle();
			Card push_back = mainDeck.deck[card_index-1];
			mainDeck.deck.pop_back();//push back last card 
			b.get_hand().hand.push_back(push_back);
		//	hands.push_back(push_back);
			curr_cards++;
		}
		else { //when main deck is out 

			int card_index_dsc = discarded.size();
			if (card_index_dsc == 0) {
				return no_cards_in_deck; //no cards in either deck, failure
			}
			discarded.callShuffle();
			Card push_back = discarded.deck[card_index_dsc-1]; //push back last card 
			discarded.deck.pop_back();
			b.get_hand().hand.push_back(push_back);
			curr_cards++;

		}
	}

	return 0;
}

int FiveCardDraw::after_turn(Player & a)
{
	sort(a.get_hand().hand.begin(), a.get_hand().hand.end());
	std::cout << "---------------PLAYER STATUS AFTER TURN--------------" << endl;
	std::cout << "Player name: " << a.get_name() << endl;
	std::cout << "Player hand: " << a.get_hand().asString() << endl;
	cout << "now the highest bet is: " << highest_bet << endl;
	cout << "pot has money: " << common_bet << endl;
	cout << "now you have bet: " << a.betweight5 << endl;

	betting_phase(a);
	return 0;
}

int FiveCardDraw::before_round()
{
	
	mainDeck.callShuffle();
	// dealer is default at last position ;
	bool reset = true;
	string resp;
	string ans1 = "yes";
	for (size_t i = 1; i < vpPlayer.size(); ++i) {
		if (vpPlayer[i]->chips == 0) {
			while (reset) {
				cout << "do you want to reset your chips to 20" << endl;
				std::getline(cin, resp);
				if (resp == ans1) {
					vpPlayer[i]->chips = 20;
					reset = false;
					break;
				}
				else continue;
			}

		}
	}
	
	if (play == true && all_check==false) {
		int player_size = vpPlayer.size();
		//std::cout << "player size: "<< player_size;
		common_bet = player_size; // initialize bet with player size
		for (int a = 0; a < player_size; ++a) {
			Hand temp = Hand();
			hands.push_back(temp);
			vpPlayer[a]->chips--; //deduct 1 chip from each player
		}
		mainDeck.callShuffle();
		//instantiate new hands 
		//std::cout << mainDeck;
		int pos = (dealer + 1) % player_size;
		int rcd = (dealer + 1) % player_size;

		for (int i = 0; i < 5; ++i) {
			//starting position
			do {
				//hands[j] << mainDeck;
				vpPlayer[pos]->playersCards << mainDeck;
				pos = (pos + 1) % player_size;
			} while (pos != rcd);
		} //dealing cards





		pos = (dealer + 1) % player_size;
		
		do {
			before_turn(*vpPlayer[pos]);
			pos = (pos + 1) % player_size;
		} while (pos != rcd);

		vector<shared_ptr<Player>> temp = vpPlayer;
		for (size_t i = 0; i < temp.size(); ++i) {
			if (temp[i]->fold == true) {
				temp.erase(temp.begin() + i);
			}
		}
		int player_size1 = temp.size();

			pos = (dealer + 1) % player_size1;
			if (play == true) {
				while (check_bet() != true) {

					do {
						//cout << "checking bet" << endl;
						//cout << silent_players << endl;
						//cout << temp.size() << endl;
						if ((temp.size() - silent_players) ==1) {
							after_round();
						}
						before_turn(*temp[pos]);
						if (play == false) {
							break;
						}
						pos = (pos + 1) % player_size1;
					} while ((pos != rcd));
				}
			}
			
			bet = false;
		

	}
	return 0;
}

int FiveCardDraw::round()
{
	if (play == true && all_check==false) {
		int player_size = vpPlayer.size();
		int pos = (dealer + 1) % player_size;
		int rcd = (dealer + 1) % player_size;

		do {
			int rcd1 = turn(*vpPlayer[pos]);
			int rcd2 = after_turn(*vpPlayer[pos]);
			if (rcd1 != 0) {
				return rcd1;
			}
			if (rcd2 != 0) {
				return rcd2;
			}
			pos = (pos + 1) % player_size;
		} while (pos != rcd);

			vector<shared_ptr<Player>> temp = vpPlayer;
			for (size_t i = 0; i < temp.size(); ++i) {
				if (temp[i]->fold == true) {
					temp.erase(temp.begin() + i);
				}
			}
			int player_size1 = temp.size();
			//cout << "temp size" << temp.size();
			int pos1 = (dealer + 1) % player_size1;
			int temp1 = (dealer + 1) % player_size1;
			while (check_bet() != true) {
				cout << check_bet() << endl;
				do {
					cout << "checking bet" << endl;
					after_turn(*temp[pos1]);
					pos1 = (pos1 + 1) % player_size1;
				} while (pos1 != temp1);
			}
			bet = false;
		}

	return 0;
}

int FiveCardDraw::after_round()
{
	if (play == true) {
		
		vector<shared_ptr<Player>> temp = vpPlayer;
		for (size_t i = 0; i < temp.size(); ++i) {
			if (temp[i]->fold == true) {
				temp.erase(temp.begin() + i); //remove players folded. only rank those who are still on board
			}
		}
		sort(temp.begin(), temp.end(), poker_rank1);

		for (size_t i = 0; i < vpPlayer.size(); ++i) {
			if (vpPlayer[i] == temp[0]) {
				vpPlayer[i]->numWin++;
				vpPlayer[i]->chips = vpPlayer[i]->chips+ common_bet;
			}
			else {
				vpPlayer[i]->numLost++;
			}
		}
	
		//cout << vpPlayer.size();

		for (size_t i = 0; i < vpPlayer.size(); ++i) {
			std::cout << "------------------PLAYER STATUS AT THE END-------------------" << endl;
			std::cout << "Player Name: " << vpPlayer[i]->get_name() << endl;
			if (vpPlayer[i]->fold == false) {
				std::cout << "Player Hand: " << vpPlayer[i]->playersCards.asString() << endl;
			}
			cout << "Player has wins: " << vpPlayer[i]->get_wins() << endl;
			cout << "Player has losses: " << vpPlayer[i]->get_loss() << endl;
			cout << "player has chips: " << vpPlayer[i]->chips << endl;
		}
		for (int i = discarded.size() - 1; i > -1; --i) {
			mainDeck.add_card(discarded.deck[i]);
			discarded.deck.pop_back();
		}

		int player_count = vpPlayer.size();

		int count = 0;
		while (count < player_count) {
			int card_cnt = 0;
			while (card_cnt < 5) {
				mainDeck.add_card(vpPlayer[count]->get_hand()[0]);
				vpPlayer[count]->playersCards.remove_card(0);
				card_cnt++;
			}
			count++;
		}

		string ans = "No";
		string res;
		bool prompt_ = true;
		while (prompt_) {
			std::cout << "Please type in the player name you want to exit the game.. if none please type in 'No' .." << endl;
			//	cin >> res;
			std::getline(cin, res);
			if (res == "No" || res =="no" || res == "NO") {
				//start_game("fivecarddraw");
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
							myfile.open(word + ".txt");
							myfile << vpPlayer[i]->playersname << " " << vpPlayer[i]->numWin << " " << vpPlayer[i]->numLost << " " << vpPlayer[i]->chips << endl;
							//myfile << "She/He has " << vpPlayer[i]->numWin << " number of wins" << endl;
							//myfile << "She/He has " << vpPlayer[i]->numLost << " number of losses" << endl;
							myfile.close();
							//cout << "erasing: " << endl;
							vpPlayer.erase(vpPlayer.begin() + i);
							//cout << "vp player size" << vpPlayer.size() << endl;
							prompt_ = false;

						}
						else {
							continue;
						}//process ones that are valid ;
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
			std::getline(cin, input);
			if (input == ans || input == "no" || res == "NO") {
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
			bet = false;
			for (size_t a = 0; a < vpPlayer.size(); ++a) {
				vpPlayer[a]->fold = false;
				vpPlayer[a]->betweight5 = 1;
				vpPlayer[a]->silent = false;
			}
			highest_bet = 1;
			common_bet = 0;
			cout << "............new round starting soon..........." << endl;
			
		}
	}
	else {
		for (size_t i = 0; i < vpPlayer.size(); ++i) {
			if (vpPlayer[i]->fold == false) {
				std::cout << "------------------WINNER STATUS AT THE END-------------------" << endl;
				std::cout << "Player Name: " << vpPlayer[i]->get_name() << endl;
				std::cout << "Player Hand: " << vpPlayer[i]->playersCards.asString() << endl;
				cout << "Player has wins: " << vpPlayer[i]->get_wins() << endl;
				cout << "Player has losses: " << vpPlayer[i]->get_loss() << endl;
				cout << "player has chips: " << vpPlayer[i]->chips << endl;
			}
		}

		bet = false;
		for (size_t a = 0; a < vpPlayer.size(); ++a) {
			vpPlayer[a]->fold = false;
			vpPlayer[a]->betweight5 = 1;
			vpPlayer[a]->silent = false;
		}
		highest_bet = 1;
		common_bet = 0;

		for (int i = discarded.size() - 1; i > -1; --i) {
			mainDeck.add_card(discarded.deck[i]);
			discarded.deck.pop_back();
		}

		int player_count = vpPlayer.size();

		int count = 0;
		while (count < player_count) {
			int card_cnt = 0;
			while (card_cnt < 5) {
				mainDeck.add_card(vpPlayer[count]->get_hand()[0]);
				vpPlayer[count]->playersCards.remove_card(0);
				card_cnt++;
			}
			count++;
		}
		//std::cout << "-----------Main Deck contains cards as follow: ------------" << endl;
		//std::cout << "The deck now has " << mainDeck.size() << "cards" << endl;
		//std::cout << mainDeck << endl;
		
	}
	return 0;
}

bool FiveCardDraw::check_bet() {
	vector<shared_ptr<Player>> temp = vpPlayer;
	for (size_t i = 0; i < temp.size(); ++i) {
		if (temp[i]->fold == true) {
			temp.erase(temp.begin() + i);
		}
		else if (temp[i]->silent == true) {
			temp.erase(temp.begin() + i);
			silent_players++;
		}
	}
	//cout << "temp size" << temp.size();
	int count = temp.size();
	int start = 0;

		while (start < count) {
			if (temp[start]->betweight5 == highest_bet) {
				//cout << "here " << temp[start]->playersname << endl;
				start++;
			}
			else {
				return false;
			}
		}
	

		return true;
	
}


bool FiveCardDraw::call(Player& a) {
	if (highest_bet > a.chips) {
		if (a.chips > 0) {
			cout << "too few chips. all in. please wait until end of the round"<<endl;

			common_bet = common_bet + a.chips;
			a.betweight5 = highest_bet;
			a.chips = 0;
			a.silent = true;
		}
	}
	a.chips = a.chips - highest_bet;
	a.betweight5 = highest_bet;
	common_bet = common_bet + highest_bet;
	if (a.betweight5 > highest_bet) {
		highest_bet = a.betweight5;
	}
	return true;
}

int FiveCardDraw::player_check() {
	vector<shared_ptr<Player>> temp = vpPlayer;

	for (size_t i = 0; i < temp.size(); ++i) {
		if (temp[i]->fold == true) {
			//cout<<temp[i]->playersname;
			temp.erase(temp.begin() + i);
		}
		else if (temp[i]->silent == true) {
			temp.erase(temp.begin() + i);
		}
	}
	return temp.size();
}

bool FiveCardDraw::raise(Player& a, int raise) {
	int raised_amount = highest_bet + raise;
	if (raised_amount > a.chips) {
		cout << "you have too few chips to raise. all in. but you will be remain in the game" << endl;
		common_bet = common_bet + a.chips;
		a.betweight5 = raised_amount;
		a.chips = 0;
		a.silent = true;
	}
	else {
		a.chips = a.chips - raised_amount;
		a.betweight5 = raised_amount;
		common_bet = common_bet + raised_amount;
		if (a.betweight5 > highest_bet) {
			highest_bet = a.betweight5;
			//cout << "highest bet now:" << highest_bet << endl;
		}
	}
	return true;
}

bool FiveCardDraw::betting_phase(Player& a) {
	if (a.fold == false) {//not folded 
		if (a.chips == 0) {
			cout << "you don't have any chips. but you will remain in the game" << endl;
			a.silent = true;
		}
		
		else {
			if (a.silent == false) {
				if (bet == false) { // no bet given
					//cout << "before" << consec_check << endl;

					if (consec_check == player_check()) {
						//cout << "player_check" << player_check() << endl;
						//cout << consec_check << endl;
						all_check = true;
						a.enter = 0;
						consec_check = 0;
						after_round();


					}
					else {
						bool ask = true;
						string ans = "check";
						while (ask) {
							std::cout << "do you want to CHECK or BET 1 or 2 chips?" << endl;
							std::cout << "please type in 'check' or '1' or '2'" << endl;
							string input;
							std::getline(cin, input);
							if (input == ans) {
								a.betweight5 = 1; // if check , then just 1 chip
								consec_check++;
								ask = false;
							}
							else if (input == "1") {
								a.chips--;
								//cout << a.betweight5 << endl;
								a.betweight5 =a.betweight5+ 1;
								common_bet += 1;
								//cout << a.betweight5 << endl;
								if (a.betweight5 > highest_bet) {
									highest_bet = a.betweight5;
								}
								bet = true;
								ask = false;
							}
							else if (input == "2") {
								a.chips = a.chips - 2;
								a.betweight5 = a.betweight5 + 2;
								common_bet = common_bet + 2;
								if (a.betweight5 > highest_bet) {
									highest_bet = a.betweight5;
								}
								bet = true;
								//cout << bet;
								ask = false;
							}
							else {

								std::cout << "invalid input." << endl;
								//throw invalid_input;//will be reprompted 
								continue;
							}

						}
					}
				}
				else {
					//if (a.betweight5 != highest_bet) {
					consec_check = 0;
					bool ask = true;
					string ans = "fold";
					string call = "call";

					while (ask) {
						std::cout << "do you want to FOLD or CALL or RAISE 1 or 2 chips?" << endl;
						std::cout << "please type in 'fold' or 'call' or '1' or '2' " << endl;
						string input;
						std::getline(cin, input);
						if (input == ans) {
							a.fold = true;
							if (check_fold() == false) {
								cout << "game over. all other players folded." << endl;
								play = false;
								ask = false; //edit, making the last player the winner

							}
							ask = false;
						}
						else if (input == call) {
							if (FiveCardDraw::call(a) == true) {
								ask = false;
							}
							else continue;
						}
						else if (input == "1" || input == "2") {
							if (FiveCardDraw::raise(a, stoi(input)) == true) {
								ask = false;
							}
							else continue;

						}

						else {
							cout << "invalid input. please reenter.." << endl;
							continue;
						}
						//continue;
							//cout<<"invalid input strings"; //will be reprompted


					}
				}
			}
		}
	}

	return bet;

}

bool FiveCardDraw::check_input(int a) {
	if (a == 1) {
		return true;
	}
	else if (a == 2) {
		return true;
	}
	cout << "input not 1 or 2. please reenter" << endl;
	return false;
}


bool FiveCardDraw::check_fold() {
	int count = 0;
	for (size_t i = 0; i < vpPlayer.size(); ++i) {
		if (vpPlayer[i]->fold == true) {
			count++;
		}
	}

	if (count == vpPlayer.size() - 1) {
		for (size_t i = 0; i < vpPlayer.size(); ++i) {
			if (vpPlayer[i]->fold == false) {
				vpPlayer[i]->numWin++;
				vpPlayer[i]->chips = vpPlayer[i]->chips+ common_bet;
				vpPlayer[i]->betweight5 = 1;
			}
			else {
				vpPlayer[i]->numLost++;
				vpPlayer[i]->betweight5 = 1;
			}
		}
		highest_bet = 1;
		common_bet = 0;
		return false;
	}
	return true;
}

int FiveCardDraw::player_size() {
	return vpPlayer.size();
}
