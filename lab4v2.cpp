// lab3_submitted.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "deck.h"
#include "hand.h"
#include "card.h"
#include "player.h"
#include "game.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
#include "TexasHoldEm.h"


#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <cstring>
using namespace std;



bool Card :: operator< (Card & cVec) {
	if (r < cVec.r) {
		return true;
	}
	else if ((r == cVec.r) && (s<cVec.s)) {
		return true;
	}
	else {
		return false;
	}
}

bool Card :: operator> (Card & cVec) {
	if (r > cVec.r) {
		return true;
	}
	else if ((r == cVec.r) && (s>cVec.s)) {
		return true;
	}
	else {
		return false;
	}
}

enum arguments { game_type = 1, min_arguments = 4, base_arguments = 2, max_argument = 13 };


void usagemessage() {
	std::cout << "should enter name of a game followed by the names of two or more, but less than 11 players." << endl;
	std::cout << "program ended" << endl;
}


int main(int argc, char* argv[])
{

	bool playing = true;
	vector<string> promp_rst = {};
	//std::cout << "here" << endl;
	for (int i = 0; i < argc; ++i) {
		promp_rst.push_back(argv[i]);
	}

	if (promp_rst.size() < min_arguments) {
		usagemessage();
		return too_few_arguments;// return non-zero
	}
	else if (promp_rst.size()> max_argument) { //assume 52 cards 
		usagemessage();
		return too_few_arguments;
	}

	while (playing) {
		try {
			
			const string gameName = promp_rst[game_type];
			std::cout << gameName;
			
			Game::start_game(gameName);
			shared_ptr<Game> newGame = Game::instance();

			for (size_t i = base_arguments; i < promp_rst.size(); ++i) {
				
				try {
					newGame->Game::add_player(promp_rst[i]);
				}

				catch (exceptions e) {
					if (e == player_already_playing) {
						throw duplicate_player;
					}
				}
			}


			int numPlayers = promp_rst.size() - base_arguments;
			bool ingame = true;
			while (newGame->player_size() >= base_arguments) {//base_argument == 2
				std::cout << "  " << endl;
				std::cout << "==========STARTING NEW GAME=======" << endl;
				std::cout << "  " << endl;
				while (newGame->play == true)
				{
					newGame->before_round();
					newGame->round();
					newGame->after_round();
				}
				newGame->play = true;
				continue;
			}
			
			cout << "game stopped" << endl;

			std::cout << "game is stopped, do you wish to switch to a different game, or quit the program?" << endl;
			std::cout << "available games are: 'fivecarddraw' , 'sevencardstud', 'texasholdem'. please type in the name as given followed by two players separated by blank space." << endl;
			std::cout << "if you wish to quit, simply type in 'quit'. " << endl;

			

			bool reprompt = true;
			while (reprompt) {
				string ans;
				getline(cin, ans);
				istringstream iss(ans);
				string input;
				promp_rst.clear();
				promp_rst.push_back("lab4v1.exe");

				while (iss >> input) {
					promp_rst.push_back(input);
				}
				if (promp_rst.size() < min_arguments) {
					
					if (promp_rst[game_type] == "quit") { //if 2 arguments, see if its "quit"
						cout << "game now ended!" << endl;
						return 0;
					}
					else {
						std::cout << "not enough arguments. correct format will be a gamename, as listed above, followed by at least two players." << endl;
						continue;
					}
				}
				else if (promp_rst[game_type] != "fivecarddraw" && promp_rst[game_type] != "sevencardstud"
					&& promp_rst[game_type] != "texasholdem") {
					std::cout << "game name not correct, please reenter as instruction given." << endl;
					continue;
				}
				else {
					std::cout << "starting new game!" << endl;

					reprompt = false;
				}
			}
			
		}


		catch (exceptions e) {
			if (e == usage_message) {
				usagemessage();
				return usage_message;
			}

			else if (e == player_already_playing) {
				std::cout << "cannot add duplicate players, player already playing" << endl;
				return player_already_playing;
			}
			else if (e == unknown_game) {
				std::cout << "the game name is unknown" << endl;
				return unknown_game;
			}
			else if (e == index_out_of_bound) {
				std::cout << "index out of bound" << endl;
				return index_out_of_bound;
			}
			else if (e == removal_out_of_bound) {
				std::cout << "removal out of bound" << endl;
				return removal_out_of_bound;
			}
			else if (e == duplicate_player) {
				std::cout << "cannot have duplicate player. please reenter player names." << endl;
				return duplicate_player;
			}
			else if (e == game_already_started) {
				std::cout << "game already started" << endl;
				return game_already_started;
			}
			else if (e == no_cards_in_deck) {
				std::cout << "no cards in deck" << endl;
				return no_cards_in_deck;
			}

			else if (e == instance_not_available) {
				std::cout << "instance not available" << endl;
				return instance_not_available;
			}
			/*
			else if (e == too_few_players) {
				std::cout << "less than 2 players. game stopped." << endl;
				return too_few_players;
			}
			*/
			else if (e == deck_size_too_small) {
				std::cout << "less than 45 cards, deck size too small. " << endl;
				return deck_size_too_small;
			}
			else if (e == file_open_error) {
				std::cout << "cannot load the file. check the player name input " << endl;
				return file_open_error;
			}


			else if (e == stop_game_when_no_game_in_progres) {
				std::cout << "stop game when no game is in progress" << endl;
				return stop_game_when_no_game_in_progres;
			}
			else if (e == too_few_chips) {
				std::cout << "trying to bet with too few chips" << endl;
				return too_few_chips;
			}
		}
		catch (...) {
			std::cout << "unexpected error" << endl;
			return failure;
		}
	}
}
