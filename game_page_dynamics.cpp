//C++ headers
#include <iomanip>
#include <sstream>
#include <string>

//Custom headers
#include "game_page.hpp"
#include "game_page_statics.hpp"
#include "game_page_dynamics.hpp"
#include "game_page_process.hpp"

//METHODS

int Game::dynamicUnits::getRandomNumber(const int& limit)
{
	//A uniformly-distributed integer random number generator that produces non-deterministic random numbers
	std::random_device device;

	//A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits.
	std::mt19937 generator(device());

	//Produces random integer values i, uniformly distributed on the closed interval[a, b],
	//that is, distributed according to the discrete probability function
	//P(i|a,b)=1/(b-a+1).
	//std::uniform_int_distribution satisfies all requirements of RandomNumberDistribution
	std::uniform_int_distribution<int> distribute_number(0, limit);

	return distribute_number(generator);
}

void Game::dynamicUnits::getRandomPositions(const int& maxUnits, std::vector<int>& donor_positions, std::vector<int>& recipient_positions)
{

	//How many units will be randomized?
	int _qty_units{ getRandomNumber(maxUnits) }; //generate TRUE random number from [0, maxUnits]

	std::cout << "Have been chosen: " << _qty_units << " units.\n";
	std::cout << "Availables qty: " << donor_positions.size() << '\n';

	if (_qty_units)
	{
		recipient_positions.resize(_qty_units);

		int index{};
		int random_pos{};
		for (int index{}; index < _qty_units; index++)
		{
			//about to_i(donor_positions.size() - 1):
			//Everytime we are creating producer for position in available_positions container
			//So when we are delete some elements from available_positions, we will generate
			//new index of available_positions according to the new size

			//Keep generated position, that is index for available_positions container
			random_pos = getRandomNumber(to_i(donor_positions.size() - 1));

			//Traverse available_positions and find value of position at the generated address
			auto it = std::ranges::find(donor_positions, donor_positions.at(random_pos));
			//Fullfilling emty_positions container with such generated position
			recipient_positions.at(index) = *it;

			std::cout << "Unit space at position " << *it << ".\n";

			//We need to delete such position at the available_positions container
			//so we don't come along it twice
			donor_positions.erase(it);
		}
	}

	std::cout << "Availables qty: " << donor_positions.size() << '\n';
}


//UPDATER PLUS_100 ABILITY: for later

//void Game::dynamicUnits::updatePlusHundredAbility(const Game::staticUnits& utils)
//{
//	if (plus_abl_updater > plus_abl_await)
//	{
//		for (auto& unit : conveyor)
//		{
//			if(
//				(*(*unit).getTexture() == utils.abl_textures.at(PLUS_100_1)
//				||
//				)
//		}
//
//		plus_abl_updater = 0;
//	}
//}

void Game::dynamicUnits::setLine(const Game::staticUnits& statics, const bool& first = false)
{
	std::cout << "Calling Game::dynamicUnits::setLine() method\n";
	
	std::vector<int> available_positions(Default::maxInLine);
	//available_positions.resize(Default::maxInLine);
	int indexer{};
	for (auto& position : available_positions)
		position = indexer++;

	std::vector<int> empty_positions;
	std::vector<int> ability_positions;

	//Skip if it's the first line
	if(!first)
	{
		//Generate random positions for empties:
		std::cout << "\nEmpty spaces:\n";
		//pass available_positions by reference, but it's copy in the setLine() method
		//pass empty_postions by reference
		getRandomPositions(Default::maxEmpties, available_positions, empty_positions);

		//Generate random positions for abilities:
		std::cout << "\nAbilities spaces:\n";
		//pass available_positions by reference, but it's copy in the setLine() method
		//pass empty_postions by reference
		getRandomPositions(Default::maxAbilities, available_positions, ability_positions);
	}

	float pos_x{ to_f(game_field.origin_x) };
	float pos_y{ to_f(game_field.origin_y) };

	for (int index{}; index < Default::maxInLine; index++)
	{

		//Check if this INDEX is for EMPTY space
		if (!first && (std::ranges::find(empty_positions, index) != empty_positions.end()) )
		{
			//here we will not construct anything

			//increment pos_x
			pos_x += to_f(Default::block_width);

			continue;
		}

		//something would be here, block or ability

		//Check if this INDEX is for ABILITY space
		if ( !first && (std::ranges::find(ability_positions, index) != ability_positions.end()) )
		{
			//construct at the back ABILITY
			conveyor.emplace_back(std::make_unique<sf::Sprite>());

			//#1. Sprite need texture

			//Here we paste randomized texture from all avalable abilities
			//DON'T FORGET that resetRect helps with

			//HERE not zero SHOULD BE, but randomized from [0, ABILITY_COUNT-1]

			//<---
			//!!! and not all abilities probably should share the same probability to be chosen
			//<---

			//Here we generate random index from the ability_probability container
			int random_ability{getRandomNumber(to_i(ability_probability.size()-1))};
			//int random_ability{getRandomNumber(ABILITY_COUNT -1)};

			//Here we are passing NUMBER OF TEXTURE that correspond the number by the ability_probability at random index
			(*conveyor.back()).setTexture(statics.abl_textures.at(ability_probability.at(random_ability)), true);
			//(*conveyor.back()).setTexture(utils.abl_textures.at(random_ability), true);

			//#2. Sprite should be at before organized scale

			(*conveyor.back()).setScale(sf::Vector2f(0.19793f, 0.25f));

			//#3. Sprite will be placed at the appropriate location

			(*conveyor.back()).setPosition(sf::Vector2f(pos_x, pos_y));

		}

		//So if it's not an EMPTY space or ABILITY, it would be BLOCK:
		else
		{
			//construct at the back BLOCK
			conveyor.emplace_back(std::make_unique<sf::Sprite>());

			//#1. Sprite need texture

			//Here we paste randomized texture from all avalable abilities
			//DON'T FORGET that resetRect helps with

			//HERE not zero, but randomized from [0, BLK_T_COUNT-1],
			//NOTE: odd numbers excluded, only NOT BROKEN: {0,2,4,6,8,10,12,14,16,18}
			
			//<---
			//!!! and not all blocks probably should share the same probability to be chosen
			//<---

			int random_block{ getRandomNumber(to_i(block_probability.size() - 1)) };
			//int random_block{ getRandomNumber(BLK_T_COUNT/2 - 1) };

			//Here we are passing NUMBER OF TEXTURE that correspond the number by the block_probability at random index
			(*conveyor.back()).setTexture(statics.blk_textures.at(block_probability.at(random_block)), true);
			//(*conveyor.back()).setTexture(utils.blk_textures.at(2*random_block), true);

			//#2. Sprite should be at before organized scale

			(*conveyor.back()).setScale(sf::Vector2f(0.25f, 0.25f));

			//#3. Sprite will be placed at the appropriate location

			(*conveyor.back()).setPosition(sf::Vector2f(pos_x, pos_y));

		}


		//Now we can increment pos_x and go to test the next element in line,
		//what it would be empty, ability or block?

		pos_x += to_f(Default::block_width);

	}

}

//Move down conveyor array

void Game::dynamicUnits::extendConveyor(const Game::staticUnits& statics)
{
	std::cout << "Calling Game::dynamicUnits::extendConveyor() method\n";
	
	std::stringstream streamer;

	//if ((extender_timer > 10) && (extender_timer < 100))
	//	streamer << "0" << std::fixed << std::setprecision(1) << extender_timer;
	//else if (extender_timer < 10)
	//	streamer << "00" << std::fixed << std::setprecision(1) << extender_timer;
	//else
	//	streamer << std::fixed << std::setprecision(1) << extender_timer;

	if (extender_timer < 10)
		streamer << "0" << std::fixed << std::setprecision(1) << extender_timer;
	else 
		streamer << std::fixed << std::setprecision(1) << extender_timer;

	//Update status_field timer for the countdown
	extender_countdown.setString(streamer.str());
	
	//Check if it's time to extend the conveyor line
	if (extender_timer < 0.1f)  //set accurancy
	{
		//First of all move all the other units
		for (auto& unit : conveyor)
		{
			(*unit).move(sf::Vector2f(0, to_f(Default::block_height)));
		}

		//Now we are emplacing at the conveyor back new line
		setLine(statics);

		extender_timer = to_extend_await;
	}
}

//Time

void Game::dynamicUnits::updateGTime() noexcept
{
	std::cout << "Calling Game::dynamicUnits::updateGTime() method\n";

	std::stringstream streamer;

	if ((game_time > 10) && (game_time < 100))
		streamer << "0" << std::fixed << std::setprecision(1) << game_time;
	else if (game_time < 10)
		streamer << "00" << std::fixed << std::setprecision(1) << game_time;
	else
		streamer << std::fixed << std::setprecision(1) << game_time;

	//Update status_field timer for the countdown
	game_timer.setString(streamer.str());
}

//CONSTRUCTOR

//Colossal class constructor moved here

Game::dynamicUnits::dynamicUnits(const Game::staticUnits& statics, const Util::staticUnits& utils)
{
	std::cout << "Games::dynamicUnits construction\n";
//==================================CONVEYOR===============================

	/*
	Conveyor line consist with blocks, abilities and empty spaces... what are we living for.

	So container parsed with different textures from:
		- Game::staticUnits::std::vector<sf::Texture> blk_textures;
		- Game::staticUnits::std::vector<sf::Texture> abl_textures;
	*/

	//==INITALIZE DEFAULT CONVEYOR ARRAY==
	
	//Let's get conveyor line by line

	//First line consist only from the blocks!
	setLine(statics, true);

	//we start from second row
	for (int row{ 1 }; row < Default::maxRows; row++)
	{
		//there is '12' blocks in the line: Default::maxInLine
		//and Default::maxRows in column

		//First of all, let's move all the previously existing units
		for (auto& unit : conveyor)
		{
			(*unit).move(sf::Vector2f(0, to_f(Default::block_height)));
		}

		//<---
		//Instead of moving lines all the time
		//here we can start constructing from the bottom to top
		//<---

		//Now call to construct new line at the above
		//All others lines consists from empties, abilities and blocks
		setLine(statics);
	}

	std::cout << "Conveyor units were created: " << conveyor.size() << '\n';

//==================================DYNAMIC STATUSES===============================

	//==INITALIZE GAME TIMER TEXT==

	Util::initialize_text(
		game_timer,
		"000.0",
		utils.main_font,
		10,
		false,
		statics.status_labels.at(TIMER_LABEL).getGlobalBounds().left,
		statics.status_labels.at(TIMER_LABEL).getGlobalBounds().top
		+ statics.status_labels.at(TIMER_LABEL).getGlobalBounds().height
		+ 20.f,
		sf::Text::Regular,
		sf::Color::Red
	);


	//==INITALIZE EXTENDER COUNTDOWN TEXT==

	std::stringstream streamer;

	//if ((to_extend_await > 10) && (to_extend_await < 100) )
	//	streamer << "0" << std::fixed << std::setprecision(1) << to_extend_await;
	//else if (to_extend_await < 10)
	//	streamer << "00" << std::fixed << std::setprecision(1) << to_extend_await;
	//else
	//	streamer << std::fixed << std::setprecision(1) << to_extend_await;

	if (to_extend_await < 10)
		streamer << "0" << std::fixed << std::setprecision(1) << to_extend_await;
	else
		streamer << std::fixed << std::setprecision(1) << to_extend_await;

	//Update status_field timer for the countdown
	extender_countdown.setString(streamer.str());

	Util::initialize_text(
		extender_countdown,
		streamer.str(),
		utils.main_font,
		10,
		false,
		statics.status_labels.at(REV_COUNT_LABEL).getGlobalBounds().left,
		statics.status_labels.at(REV_COUNT_LABEL).getGlobalBounds().top
			+ statics.status_labels.at(REV_COUNT_LABEL).getGlobalBounds().height
			+ 20.f,
		sf::Text::Regular,
		sf::Color::Red
	);

}
