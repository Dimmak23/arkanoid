#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		   THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> DYNAMIC CODE UNITS			//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//C++ headers
#include <random>
#include <ranges>


//API


//SFML headers

//Custom headers
#include "util.hpp"
#include "game_page.hpp"
//#include "game_page_statics.hpp"

//Forward Game namespace declaration in the 'game_page_dynamics.hpp'
namespace Game
{
	class staticUnits;  //forward declaration already declared class (game_page_dynamics.hpp)
	class dynamicUnits;  //forward declaration already declared class (game_page_dynamics.hpp)

};

class Game::dynamicUnits
{
	public:
	
	dynamicUnits() = default;								//default-constructor declaration
	dynamicUnits(const Game::staticUnits& utils);			//constructor dependable on 'Util::dynamicUnits' object declaration

	void setLine(std::vector<sf::Sprite>& conveyor, std::vector<int> available_positions);

	//SPRITES

	std::vector<sf::Sprite> conveyor;

	//CONSTS

	std::vector<int> available_positions;
};

inline void Game::dynamicUnits::setLine(std::vector<sf::Sprite>& conveyor, std::vector<int> available_positions)
{
	std::vector<int> empty_positions;
	std::vector<int> ability_positions;

	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> d_empty(0, 3);

	int empty_qty{ d_empty(generator) }; //generate TRUE random number from [0, 3]
	
	std::cout << "Have been chosen: " << empty_qty << " empty spaces.\n";

	std::cout << "Availabels qty: " << available_positions.size() << '\n';

	if (empty_qty)
	{
		empty_positions.resize(empty_qty);

		std::uniform_int_distribution<int> d_empty_pos(0, available_positions.size() - 1);

		int index{};
		auto it = available_positions.begin();
		for (int index{}; index < empty_qty; index++)
		{
			empty_positions.at(index) = available_positions.at(d_empty_pos(generator));
			std::cout << "At position " << empty_positions.at(index) << ".\n";
			auto it = std::ranges::find(available_positions, empty_positions.at(index));
			available_positions.erase(it);
		}
	}

}

	//Colossal class constructor moved here
inline Game::dynamicUnits::dynamicUnits(const Game::staticUnits& utils)
{

//==================================CONVEYOR===============================

	/*
	Conveyor line consist with blocks, abilities and empty spaces... what are we living for.

	So container parsed with different textures from:
		- Game::staticUnits::std::vector<sf::Texture> blk_textures;
		- Game::staticUnits::std::vector<sf::Texture> abl_textures;
	*/

	//Let's get conveyor line by line

	//First line consist only from the blocks or empty spaces

	//there is '12' blocks in the line: Default::maxInLine
	//and Default::maxRows in column

	available_positions.resize(Default::maxInLine);
	int indexer{};
	for (auto& position : available_positions)
		position = indexer++;

	setLine(conveyor, available_positions);

	//randomQty(4, int empty_qty) -> for empty spaces, possible variants: {0, 1, 2, 3}
	//randomPositionsInRow(empty_qty, std::vector<int>empty_positions, std::vector<int> available_positions) -> for empty positions, possible variants: {2, 6, 10}

	//if(NOT first_line)
	//	randomQty(4, int ability_qty) -> for abilities in the line, possible variants: {0, 1, 2, 3}

	//randomPositionsInRow(ability_qty, std::vector<int>ability_positions, std::vector<int> available_positions) -> for abilities positions, possible variants (NOTE: {2, 6, 10} excluded!): {0, 1, 11}

	//ALL other positions will be taked by blocks

	//available_positions passed by value, that we will be delete numbers from there
	
	//==INITALIZE DEFAULT CONVEYOR ARRAY==

	//init blocks with textures

	//set blocks to the specific positions
}
