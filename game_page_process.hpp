#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		   THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> PROCESS CODE UNITS			//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//C++ headers


//API


//SFML headers


//Custom headers
#include "util.hpp"
#include "game_page.hpp"
//#include "game_page_statics.hpp"
//#include "game_page_dynamics.hpp"


//Forward Game namespace declaration in the 'game_page_process.hpp'
namespace Game
{
	class staticUnits;		//forward declaration already declared class (game_page_process.hpp)
	class dynamicUnits;		//forward declaration already declared class (game_page_process.hpp)
	class Process;			//forward declaration already declared class (game_page_process.hpp)

};

class Game::Process
{
	public:

	Process() = default;										//default-constructor declaration

	static inline bool running{ true };

	void render(sf::RenderWindow& window, const Game::staticUnits& utils, const Game::dynamicUnits& dynamo);
	void interact(sf::RenderWindow& window);

	private:

	sf::Event event{};  //!NOT SURE IF I NEED ANY NON-STATIC MEMBERS
};
