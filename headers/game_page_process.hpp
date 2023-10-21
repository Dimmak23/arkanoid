#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		   THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> PROCESS CODE UNITS			//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//* C++ std

//* SFML

//* Custom
#include "game_page.hpp"
#include "util.hpp"

// Forward Game namespace declaration in the 'game_page_process.hpp'
namespace Game
{
	class StaticUnits;	   // forward declaration already declared class (game_page_process.hpp)
	class DynamicUnits;	   // forward declaration already declared class (game_page_process.hpp)
	class Process;		   // forward declaration already declared class (game_page_process.hpp)

};	  // namespace Game

class Game::Process
{
public:
	Process();
	~Process() = default;

	static inline bool running{ false };
	static inline bool on_pause{ false };

	void render(sf::RenderWindow& window, const Game::StaticUnits& utils, const Game::DynamicUnits& dynamo);

	void interact(sf::RenderWindow& window, Game::DynamicUnits& dynamo, const float& d_time);

public:
	sf::Event event{};	  //! NOT SURE IF I NEED ANY NON-STATIC MEMBERS
};

inline Game::Process::Process()
{
	// IMPLEMENT STRATEGY FOR REPLAY
	running = true;
	on_pause = false;
}