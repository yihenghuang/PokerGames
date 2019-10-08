#include "stdafx.h"
#include "game.h"
#include "player.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
#include "TexasHoldEm.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// = nullptr // make_shared<Game>();
shared_ptr<Game> Game::pGame = 0;


shared_ptr<Game> Game::instance() {
	if (pGame.use_count() == 0) {
		throw instance_not_available; //issue
	}
	else {
	
		shared_ptr<Game> pGameCopy = pGame;
		return pGameCopy;
	}
}


void Game::start_game(const string &s) {
	if (pGame.use_count() != 0) {
		throw game_already_started;
	}
	if (s.compare("fivecarddraw") == 0) {

		pGame = make_shared<FiveCardDraw>();
		pGame->vpPlayer.clear();

	}
	else if (s.compare("sevencardstud") == 0) {
		pGame = make_shared<SevenCardStud>();
		pGame->vpPlayer.clear();
	}

	else if (s.compare("texasholdem") == 0) {
		pGame = make_shared<TexasHoldEm>();
		pGame->vpPlayer.clear();
	}
	else {
		throw unknown_game;
	}

}

void Game::stop_game() {
	if (pGame.use_count() == 0) {
		throw stop_game_when_no_game_in_progres;
	}
	//cout << "stoping" << endl;
	pGame->vpPlayer.clear();
	//cout << "size: " << pGame->vpPlayer.size() << endl;
	pGame = nullptr;

	//pGame.use_count() = 0;//set to singular
}

/*A public (non-static) add_player method that takes a reference to a const C++ style string as its only parameter.
If there is already a player in the game whose name is the same as the passed C++ style string,
the method should throw an already_playing exception.
Otherwise the method should dynamically allocate a Player with that name, and then push a pointer (or shared_ptr) to the object
back into the game's vector of pointers to players.*/

void Game::add_player(const string & player) {
	
	if (find_player(player) == nullptr) {
		
		vpPlayer.push_back(make_shared<Player>(Player(player.c_str())));
	}
	else {
		throw player_already_playing;
	}
	// call find. if return a player pointer, throw
	// if return nullptr, get pointer,
	//open file, if exist, update data, vector
}

/*A public (non-static) find_player method that takes a reference to a const C++ style string as its only parameter, 
and either returns a pointer (or shared_ptr) to the matching Player object or returns a singular pointer (or shared_ptr) 
if there is no player in the game with that name.*/

shared_ptr<Player> Game::find_player(const string& player) {

	for (size_t i = 0; i < vpPlayer.size(); ++i) {
		if (vpPlayer[i]->playersname == player) {
			return vpPlayer[i];
		}
	}
	return nullptr;
}

/*A public virtual destructor. 
If (and only if - do not do this if the vector contains shared_ptrs) the vector contains native C++ pointers (e.g., of type Player *), 
the destructor should iterate through the vector of pointers to players and call delete on each one.*/

