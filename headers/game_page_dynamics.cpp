// C++ headers
#include <algorithm>
#include <iomanip>
#include <ranges>
#include <sstream>
#include <string>

// Custom headers
#include "game_page.hpp"
#include "game_page_dynamics.hpp"
#include "game_page_process.hpp"
#include "game_page_statics.hpp"

// DEFINES

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//<<<----UTILITIES

int Game::DynamicUnits::getRandomNumber(const int& limit)
{
	// A uniformly-distributed integer random number generator that produces non-deterministic random numbers
	std::random_device device;

	// A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits.
	std::mt19937 generator(device());

	// Produces random integer values i, uniformly distributed on the closed interval[a, b],
	// that is, distributed according to the discrete probability function
	// P(i|a,b)=1/(b-a+1).
	// std::uniform_int_distribution satisfies all requirements of RandomNumberDistribution
	std::uniform_int_distribution<int> distribute_number(0, limit);

	return distribute_number(generator);
}

void Game::DynamicUnits::getRandomPositions(const int& maxUnits, std::vector<int>& donor_positions,
											std::vector<int>& recipient_positions)
{
	// How many units will be randomized?
	int _qty_units{ getRandomNumber(maxUnits) };	// generate TRUE random number from [0, maxUnits]

	// std::cout << "Have been chosen: " << _qty_units << " units.\n";
	// std::cout << "Availables qty: " << donor_positions.size() << '\n';

	if (_qty_units)
	{
		recipient_positions.resize(_qty_units);

		int index{};
		int random_pos{};
		for (int index{}; index < _qty_units; index++)
		{
			// about to_i(donor_positions.size() - 1):
			// Everytime we are creating producer for position in available_positions container
			// So when we are delete some elements from available_positions, we will generate
			// new index of available_positions according to the new size

			// Keep generated position, that is index for available_positions container
			random_pos = getRandomNumber(to_i(donor_positions.size() - 1));

			// Traverse available_positions and find value of position at the generated address
			auto it = std::ranges::find(donor_positions, donor_positions.at(random_pos));
			// Fullfilling emty_positions container with such generated position
			recipient_positions.at(index) = *it;

			// std::cout << "Unit space at position " << *it << ".\n";

			// We need to delete such position at the available_positions container
			// so we don't come along it twice
			donor_positions.erase(it);
		}
	}

	// std::cout << "Availables qty: " << donor_positions.size() << '\n';
}

// UPDATER PLUS_100 ABILITY: for later

// void Game::DynamicUnits::updatePlusHundredAbility(const Game::StaticUnits& utils)
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
// }

void Game::DynamicUnits::setLine(const Game::StaticUnits& statics, const bool& first = false)
{
	// std::cout << "Calling Game::DynamicUnits::setLine() method\n";

	std::vector<int> available_positions(Default::maxInLine);
	// available_positions.resize(Default::maxInLine);
	int indexer{};
	for (auto& position : available_positions) position = indexer++;

	std::vector<int> empty_positions;
	std::vector<int> ability_positions;

	// Skip if it's the first line
	if (!first)
	{
		// Generate random positions for empties:
		// std::cout << "\nEmpty spaces:\n";
		// pass available_positions by reference, but it's copy in the setLine() method
		// pass empty_postions by reference
		getRandomPositions(Default::maxEmpties, available_positions, empty_positions);

		// Generate random positions for abilities:
		// std::cout << "\nAbilities spaces:\n";
		// pass available_positions by reference, but it's copy in the setLine() method
		// pass empty_postions by reference
		getRandomPositions(Default::maxAbilities, available_positions, ability_positions);
	}

	float pos_x{ to_f(game_field.origin_x) };
	float pos_y{ to_f(game_field.origin_y) };

	for (int index{}; index < Default::maxInLine; index++)
	{
		// Check if this INDEX is for EMPTY space
		if (!first && (std::ranges::find(empty_positions, index) != empty_positions.end()))
		{
			// here we will not construct anything

			// increment pos_x
			pos_x += to_f(Default::block_width);

			continue;
		}

		// something would be here, block or ability

		// Check if this INDEX is for ABILITY space
		if (!first && (std::ranges::find(ability_positions, index) != ability_positions.end()))
		{
			// construct at the back ABILITY
			conveyor.emplace_back(sf::Sprite());

			// construct a map unit at he back
			conveyor_map.emplace_back();

			// #1. Sprite need texture

			// Here we paste randomized texture from all avalable abilities
			// DON'T FORGET that resetRect helps with

			// HERE not zero SHOULD BE, but randomized from [0, ABILITY_COUNT-1]

			//<---
			//!!! and not all abilities probably should share the same probability to be chosen
			//<---

			// Here we generate random index from the ability_probability container
			int random_ability{ getRandomNumber(to_i(ability_probability.size() - 1)) };
			// int random_ability{getRandomNumber(ABILITY_COUNT -1)};

			///<-
			// Connect needed function from executor by ABILITY_TYPE
			// ABILITY_TYPE from enum is the same number as ability_textures
			int ABILITY_TYPE = ability_probability.at(random_ability);

			// NOPE, it is not a block, it's an ability
			conveyor_map.back().block = false;
			// Operand?
			conveyor_map.back().operand = Util::ability_values.at(ABILITY_TYPE);
			// What we will do with the operand?
			conveyor_map.back().function = abl_function_map.at(ABILITY_TYPE);

			// Now set up initial kinematic parameters
			conveyor_map.back().kinematics.at(V_X) = 0;
			conveyor_map.back().kinematics.at(V_Y) = 0;
			conveyor_map.back().kinematics.at(A_X) = 0;
			conveyor_map.back().kinematics.at(A_Y) = 0;

			///<-

			// Here we are passing NUMBER OF TEXTURE that correspond the number by the ability_probability at random
			// index
			conveyor.back().setTexture(statics.abl_textures.at(ability_probability.at(random_ability)), true);
			//(*conveyor.back()).setTexture(utils.abl_textures.at(random_ability), true);

			// #2. Sprite should be at before organized scale

			conveyor.back().setScale(sf::Vector2f(0.19793f, 0.25f));

			// #3. Sprite will be placed at the appropriate location

			conveyor.back().setPosition(sf::Vector2f(pos_x, pos_y));

			// std::cout << "Ability #" << conveyor.size() << '\n';
		}

		// So if it's not an EMPTY space or ABILITY, it would be BLOCK:
		else
		{
			// construct at the back BLOCK
			conveyor.emplace_back(sf::Sprite());

			// construct a map unit at he back
			conveyor_map.emplace_back();

			// #1. Sprite need texture

			// Here we paste randomized texture from all avalable abilities
			// DON'T FORGET that resetRect helps with

			// HERE not zero, but randomized from [0, BLK_T_COUNT-1],
			// NOTE: odd numbers excluded, only NOT BROKEN: {0,2,4,6,8,10,12,14,16,18}

			//<---
			//!!! and not all blocks probably should share the same probability to be chosen
			//<---

			int random_block{ getRandomNumber(to_i(block_probability.size() - 1)) };
			// int random_block{ getRandomNumber(BLK_T_COUNT/2 - 1) };

			///<-
			// Connect needed function from executor by BLOCK_TYPE
			// BLOCK_TYPE from enum is a twice smaller then enum for Game::StaticUnits::blk_textures
			int BLOCK_TYPE = block_probability.at(random_block) /
							 2;	   // NOTE: There is 20 textures loaded, we are using only every second from them

			// YEP, it is a block
			conveyor_map.back().block = true;
			// How many points to add?
			conveyor_map.back().operand = Util::block_values.at(BLOCK_TYPE);
			// What we will do with the operand?
			conveyor_map.back().function = blk_function_map.at(BLOCK_TYPE);

			///<-

			// Here we are passing NUMBER OF TEXTURE that correspond the number by the block_probability at random index
			conveyor.back().setTexture(statics.blk_textures.at(block_probability.at(random_block)), true);
			//(*conveyor.back()).setTexture(utils.blk_textures.at(2*random_block), true);

			// #2. Sprite should be at before organized scale

			conveyor.back().setScale(sf::Vector2f(0.25f, 0.25f));

			// #3. Sprite will be placed at the appropriate location

			conveyor.back().setPosition(sf::Vector2f(pos_x, pos_y));

			// std::cout << "Block #" << conveyor.size() << '\n';
		}

		// Now we can increment pos_x and go to test the next element in line,
		// what it would be empty, ability or block?

		pos_x += to_f(Default::block_width);
	}
}

//<<<----UTILITIES

//<<<----INTERFACE

// When we score have been changed we are sill not have been erase adder
// we pop him up to the interface
// and wait some time
void Game::DynamicUnits::blinkScoreAdder()
{
	if (score_add_timer > score_adder_appear_await)
	{
		score_add_label.setFillColor(sf::Color::Black);
		score_add_label.setPosition(
			sf::Vector2f(score_label.getGlobalBounds().left + score_label.getGlobalBounds().width + 10.f,
						 score_label.getGlobalBounds().top));

		score_add_timer = 0;
		score_adder = 0;
	}
}

// So when score have neen changed it is visible on the label
// and we also see adder poping up
void Game::DynamicUnits::updateScore()
{
	if (score > score_max)
	{
		score = score_max;
		return;
	}
	else if (std::to_string(score) == score_label.getString())
	{
		return;
	}
	else
	{
		score_label.setString(std::to_string(score));

		std::string to_s_adder = std::to_string(score_adder);
		to_s_adder.insert(to_s_adder.begin(), '+');

		score_add_label.setString(to_s_adder);
		score_add_label.setFillColor(sf::Color::Yellow);
		score_add_label.setPosition(
			sf::Vector2f(score_label.getGlobalBounds().left + score_label.getGlobalBounds().width + 10.f,
						 score_label.getPosition().y /*+ score_label.getGlobalBounds().height*/
						 ));
	}
}

// So when life variable have been changed - update life status
void Game::DynamicUnits::updateLifeBalls(const Game::StaticUnits& statics)
{
	if (lifes > lifes_max)
	{
		lifes = lifes_max;
		return;
	}
	else if (lifes < 0)
	{
		lifes = 0;
		return;
	}
	else
	{
		if (lifes > lifes_balls.size())
		{
			int adder = to_i(lifes - lifes_balls.size());

			while (adder-- > 0)
			{
				int new_index{ to_i(lifes_balls.size()) };

				lifes_balls.emplace_back(std::make_unique<sf::Sprite>());

				(*lifes_balls.back()).setTexture(statics.bll_texture, true);
				(*lifes_balls.back()).setScale(sf::Vector2f(0.5f, 0.5f));
				(*lifes_balls.back())
					.setPosition(sf::Vector2f(
						statics.lifes_outline.at(lifes_indexer.at(new_index)).getGlobalBounds().left + 2.5f,
						statics.lifes_outline.at(lifes_indexer.at(new_index)).getGlobalBounds().top + 2.6f));
			}
		}
		else if (lifes < lifes_balls.size())
		{
			lifes_balls.pop_back();
		}
		else
			return;
	}
}

// Adjust paddle if paddle level were changed
// void Game::DynamicUnits::adjustPaddle()
//{
//	if (paddle_scale_x >= paddle_scale_x_max)
//	{
//		paddle_scale_x = paddle_scale_x_max;
//		return;
//	}
//	else if (paddle_scale_x <= paddle_scale_x_min)
//	{
//		paddle_scale_x = paddle_scale_x_min;
//		return;
//	}
//	else if ((*paddle).getScale().x == paddle_scale_x)
//		return;
//	else
//	{
//		(*paddle).setScale(sf::Vector2f(paddle_scale_x, 0.25f));
//		(*paddle).setOrigin(sf::Vector2f((*paddle).getLocalBounds().width/2, 0.f));
//	}
// }

// Get initial texture by current state
int Game::DynamicUnits::getTextureNumber(const int& p_state)
{
	// Get true when current paddle state suit mapped paddle state
	auto first_in_pair = [&](const std::pair<int, int>& unit) { return (unit.first == p_state); };

	// Connect to the initial texture number by current paddle state
	auto new_texture_it = std::find_if(paddle_map.begin(), paddle_map.end(), first_in_pair);

	if (new_texture_it != paddle_map.end())
		return ((*new_texture_it).second);
	else
		return CAPSULE_1;
}

// If there was such ability: resize paddle
void Game::DynamicUnits::resizePaddle(const Game::StaticUnits& utils)
{
	// Check if paddle have been adjusted
	if (paddle_state != paddle_ext)
	{
		// Change texture because of resize
		paddle_state = paddle_ext;

		(*paddle).setTexture(utils.pdl_textures.at(getTextureNumber(paddle_state)), true);

		(*paddle).setOrigin(sf::Vector2f((*paddle).getLocalBounds().width / 2, 0.f));
	}
}

// Update electric visibility paddle
void Game::DynamicUnits::updateElectricPaddle(const Game::StaticUnits& utils)
{
	if (pdl_upd_timer > paddle_upd_await)
	{
		int init_texture{ getTextureNumber(paddle_state) };

		// If it's zero size texture we can reset timer and go back
		if (init_texture == CAPSULE_0)
		{
			pdl_upd_timer = 0;
			return;
		}
		// BUT! If it's something else, we have to update paddle
		else if ((*paddle).getTexture() == &(utils.pdl_textures.at(init_texture)))
		{
			(*paddle).setTexture(utils.pdl_textures.at(init_texture + 1), true);
		}
		else if ((*paddle).getTexture() == &(utils.pdl_textures.at(init_texture + 1)))
		{
			(*paddle).setTexture(utils.pdl_textures.at(init_texture + 2), true);
		}
		else if ((*paddle).getTexture() == &(utils.pdl_textures.at(init_texture + 2)))
		{
			(*paddle).setTexture(utils.pdl_textures.at(init_texture), true);
		}

		pdl_upd_timer = 0;
	}
}

// Move down conveyor array
// Also update await extender label
void Game::DynamicUnits::extendConveyor(const Game::StaticUnits& statics)
{
	std::stringstream streamer;

	if (extender_timer < 10)
		streamer << "0" << std::fixed << std::setprecision(1) << extender_timer;
	else
		streamer << std::fixed << std::setprecision(1) << extender_timer;

	streamer << " sec";

	// Update status_field timer for the countdown
	extender_countdown.setString(streamer.str());

	// Check if it's time to extend the conveyor line
	if (extender_timer < 0.1f)	  // set accurancy
	{
		// First of all move all the other units
		for (auto& unit : conveyor)
		{
			unit.move(sf::Vector2f(0, to_f(Default::block_height)));
		}

		// Now we are emplacing at the conveyor back new line
		setLine(statics);

		extender_timer = to_extend_await;
	}
}

// when blocks at the bottom go to the specific line we will change extender waiting timer
// Wait for the new line:
//	- Longer, if there a lot of blocks;
//	- less, if there is a few blocks.
void Game::DynamicUnits::updateExtAwaitTimer()
{
	std::stringstream streamer;

	int block_index{};
	bool running{ true };

	for (int indexer{}; indexer < Default::time_belt_ext_mapping.size(); indexer++)
	{
		while (!(conveyor_map.at(block_index).block))
		{
			block_index++;
			if (block_index == conveyor_map.size())
			{
				running = false;
				return;
			}
			continue;
		}

		if (running && (conveyor.at(block_index).getGlobalBounds().top + Default::block_height) >=
						   to_f(Default::conveyor_mapping.at(indexer)))
		{
			to_extend_await = Default::time_belt_ext_mapping.at(indexer);

			streamer.str("");
			streamer << "(";

			// if (to_extend_await < 10)
			//	streamer << "0" << std::fixed << std::setprecision(1) << to_extend_await;
			// else
			//	streamer << std::fixed << std::setprecision(1) << to_extend_await;

			streamer << std::fixed << std::setprecision(1) << to_extend_await;

			streamer << ")";

			extender_await.setString(streamer.str());

			return;
		}
	}
}

// Time

void Game::DynamicUnits::updateGTime() noexcept
{
	std::stringstream streamer;

	if ((game_time > 10) && (game_time < 100))
		streamer << "0" << std::fixed << std::setprecision(1) << game_time;
	else if (game_time < 10)
		streamer << "00" << std::fixed << std::setprecision(1) << game_time;
	else
		streamer << std::fixed << std::setprecision(1) << game_time;

	streamer << " sec";

	// Update status_field timer for the countdown
	game_timer.setString(streamer.str());
}

// so when ball kinematics have been changed, they would be updated here
// and when paddle kinematics have been changed, they would be updated here
void Game::DynamicUnits::updateParInterface(const std::vector<float>& kinematics, std::vector<sf::Text>& texts)
{
	std::stringstream streamer;
	float buffer{};

	int precision{};

	// go thru all text parameters
	int indexer{};
	for (auto& text : texts)
	{
		buffer = kinematics.at(indexer);
		streamer.str("");

		if (std::abs(buffer) >= 100000)
			precision = 0;
		else if (std::abs(buffer) >= 10000)
			precision = 1;
		else if (std::abs(buffer) >= 1000)
			precision = 2;
		else
			precision = 3;

		if ((std::abs(buffer) > 10) && (std::abs(buffer) < 100))
			streamer << ((buffer < 0) ? "-0" : " 0") << std::fixed << std::setprecision(precision)
					 << ((buffer < 0) ? -buffer : buffer);
		else if (std::abs(buffer) < 10)
			streamer << ((buffer < 0) ? "-00" : " 00") << std::fixed << std::setprecision(precision)
					 << ((buffer < 0) ? -buffer : buffer);
		else
			streamer << ((buffer < 0) ? "-" : " ") << std::fixed << std::setprecision(precision)
					 << ((buffer < 0) ? -buffer : buffer);

		if (text.getString() == streamer.str())
		{
			indexer++;
			continue;
		}
		else
		{
			text.setString(streamer.str());
		}

		indexer++;
	}
}

//<<<----INTERFACE

//<<<----SIMULATE

// Until user released ball - hold it
void Game::DynamicUnits::holdBall()
{
	if (catched_ball)
	{
		// reset ball position
		(*ball).setPosition(sf::Vector2f((*paddle).getGlobalBounds().left + (*paddle).getGlobalBounds().width / 2,
										 (*paddle).getGlobalBounds().top - (*ball).getGlobalBounds().height / 2));
	}
}

// Wait some time before placing ball to the paddle
void Game::DynamicUnits::waitForBall()
{
	if (ball_timer > to_new_ball_await)
	{
		// reset ball position
		(*ball).setPosition(sf::Vector2f((*paddle).getGlobalBounds().left + (*paddle).getGlobalBounds().width / 2,
										 (*paddle).getGlobalBounds().top - (*ball).getGlobalBounds().height / 2));

		// reset ball kinematics
		bll(DELTA_X) = 0;
		bll(DELTA_Y) = 0;
		bll(V_X) = 0;
		bll(V_Y) = 0;
		bll(A_X) = 0;
		bll(A_Y) = 0;

		// reset paddle position
		//(*paddle).setPosition(
		//				sf::Vector2f(
		//										to_f(game_field.origin_x + game_field.overall_width / 2),
		//										to_f(game_field.origin_y + game_field.overall_height -
		// Default::block_height)
		//									)
		//);

		// reset paddle kinematics
		// pdl(DELTA_X) = 0;
		// pdl(V_X) = 0;
		// pdl(A_X) = 0;

		// reset timer
		ball_timer = 0;

		// we are not loosing ball anymore here
		lost_ball = false;

		// we hold ball on the paddle
		catched_ball = true;
	}
}

// maybe we need to finish game because of to long belt
void Game::DynamicUnits::checkLongBelt()
{
	int index{};

	while (!(conveyor_map.at(index).block))
	{
		index++;
	}

	if (conveyor.at(index).getGlobalBounds().top >=
		(game_field.origin_y + game_field.overall_height - 2 * Default::block_height))
		Game::Process::running = false;
}

//<<<----SIMULATE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR

// Colossal class constructor moved here

Game::DynamicUnits::DynamicUnits(const Game::StaticUnits& statics, const Util::StaticUnits& utils)
{
	//==================================RESET STATIC NON-CONSTS===============================

	conveyor_map.clear();

	lost_ball = false;

	// PADDLE TEXTURE CHANGE HANDLERS
	paddle_state = 0;
	paddle_ext = 0;

	// VARIABLES PHYSICS

	// BALL
	ball_kinematics.clear();
	bll_V_step = 400.0f;

	// PADDLE
	paddle_kinematics.clear();

	// VARIABLES TIMERS

	//___Belt extender
	to_extend_await = 0;
	extender_timer = 0;

	//___Score adder blink
	score_add_timer = 0;

	//___
	game_time = 0;

	//___Paddle
	pdl_upd_timer = 0;

	paddle_scale_x = 0.25f;
	paddle_scale_y = 0.25f;

	//___Lost ball awaiting
	ball_timer = 0;

	// VARIABLES STATUSES

	score = 0;
	score_adder = 0;

	lifes = 9;

	// Are we hold ball on the paddle?
	catched_ball = true;

	//==================================CONVEYOR===============================

	/*
	Conveyor line consist with blocks, abilities and empty spaces... what are we living for.

	So container parsed with different textures from:
		- Game::StaticUnits::std::vector<sf::Texture> blk_textures;
		- Game::StaticUnits::std::vector<sf::Texture> abl_textures;
	*/

	//==INITALIZE DEFAULT CONVEYOR ARRAY==

	// Let's get conveyor line by line

	// First line consist only from the blocks!
	setLine(statics, true);

	// we start from second row
	for (int row{ 1 }; row < Default::maxRows; row++)
	{
		// there is '12' blocks in the line: Default::maxInLine
		// and Default::maxRows in column

		// First of all, let's move all the previously existing units
		for (auto& unit : conveyor)
		{
			unit.move(sf::Vector2f(0, to_f(Default::block_height)));
		}

		//<---
		// Instead of moving lines all the time
		// here we can start constructing from the bottom to top
		//<---

		// Now call to construct new line at the above
		// All others lines consists from empties, abilities and blocks
		setLine(statics);
	}

	// std::cout << "Conveyor units were created: " << conveyor.size() << '\n';

	//==================================DYNAMIC STATUSES===============================

	//==INITALIZE GAME SCORE STATUS TEXT==

	Util::initialize_text(score_label, std::to_string(score), utils.score_font, 35, false,
						  statics.status_labels.at(SCORE_LABEL).getGlobalBounds().left,
						  statics.status_labels.at(SCORE_LABEL).getGlobalBounds().top +
							  statics.status_labels.at(SCORE_LABEL).getGlobalBounds().height + 10.f,
						  sf::Text::Regular, sf::Color::Red);

	//==INITALIZE GAME SCORE ADDER TEXT==

	Util::initialize_text(score_add_label, std::to_string(score_adder), utils.score_font, 35, false,
						  statics.status_labels.at(SCORE_LABEL).getGlobalBounds().left +
							  statics.status_labels.at(SCORE_LABEL).getGlobalBounds().width + 10.f,
						  statics.status_labels.at(SCORE_LABEL).getGlobalBounds().top, sf::Text::Regular,
						  sf::Color::Black);

	//==INITALIZE GAME TIMER TEXT==

	Util::initialize_text(game_timer, "000.0", utils.main_font, 10, false,
						  statics.status_labels.at(TIMER_LABEL).getGlobalBounds().left,
						  statics.status_labels.at(TIMER_LABEL).getGlobalBounds().top +
							  statics.status_labels.at(TIMER_LABEL).getGlobalBounds().height + 20.f,
						  sf::Text::Regular, sf::Color::Red);

	//==INITIALIZE EXTENDER COUNTDOWN TEXT==

	std::stringstream streamer;

	if (to_extend_await < 10)
		streamer << "0" << std::fixed << std::setprecision(1) << to_extend_await;
	else
		streamer << std::fixed << std::setprecision(1) << to_extend_await;

	streamer << " sec";

	Util::initialize_text(extender_countdown, streamer.str(), utils.main_font, 10, false,
						  statics.status_labels.at(REV_COUNT_LABEL).getGlobalBounds().left,
						  statics.status_labels.at(REV_COUNT_LABEL).getGlobalBounds().top +
							  statics.status_labels.at(REV_COUNT_LABEL).getGlobalBounds().height + 20.f,
						  sf::Text::Regular, sf::Color::Red);

	//==INITIALIZE EXTENDER AWAITER TEXT==

	streamer.str("(");

	if (to_extend_await < 10)
		streamer << "0" << std::fixed << std::setprecision(1) << to_extend_await;
	else
		streamer << std::fixed << std::setprecision(1) << to_extend_await;

	streamer << ")";

	Util::initialize_text(extender_await, streamer.str(), utils.main_font, 10, false,
						  extender_countdown.getGlobalBounds().left + extender_countdown.getGlobalBounds().width + 10.f,
						  statics.status_labels.at(REV_COUNT_LABEL).getGlobalBounds().top +
							  statics.status_labels.at(REV_COUNT_LABEL).getGlobalBounds().height + 20.f,
						  sf::Text::Regular, sf::Color::Red);

	// std::cout << "Timers were instatiated." << '\n';

	//==INITIAL LIFES BALLS==

	for (int index{}; index < lifes;)
	{
		lifes_balls.emplace_back(std::make_unique<sf::Sprite>());

		(*lifes_balls.back()).setTexture(statics.bll_texture, true);
		(*lifes_balls.back()).setScale(sf::Vector2f(0.5f, 0.5f));
		(*lifes_balls.back())
			.setPosition(sf::Vector2f(statics.lifes_outline.at(lifes_indexer.at(index)).getGlobalBounds().left + 2.5f,
									  statics.lifes_outline.at(lifes_indexer.at(index)).getGlobalBounds().top + 2.6f));

		index++;
	}

	// std::cout << "Lifes balls were drawn." << '\n';

	//==INITALIZE BALL KINEMATICS==

	ball_kinematics.resize(statics.ball_parameters.size());

	// Initial velocities for the ball
	// ball_kinematics.at(V_X) = -bll_V_step;
	// ball_kinematics.at(V_Y) = -bll_V_step;

	//==INITALIZE BALL PARAMETERS STATUS TEXTS==

	ball_parameters.resize(statics.ball_parameters.size());

	int index{};
	for (auto& parameter : ball_parameters)
	{
		Util::initialize_text(parameter, "000.000", utils.main_font, 10, false,
							  statics.ball_parameters.at(index).getPosition().x + 35.f,
							  statics.ball_parameters.at(index).getPosition().y, sf::Text::Regular, sf::Color::Red);

		index++;
	}

	//==INITALIZE BALL KINEMATICS==

	paddle_kinematics.resize(statics.paddle_parameters.size());
	// all values goes to '0'

	//==INITALIZE PADDLE PARAMETERS STATUS TEXTS==

	paddle_parameters.resize(statics.paddle_parameters.size());

	index = 0;
	for (auto& parameter : paddle_parameters)
	{
		Util::initialize_text(parameter, "000.000", utils.main_font, 10, false,
							  statics.paddle_parameters.at(index).getPosition().x + 35.f,
							  statics.paddle_parameters.at(index).getPosition().y, sf::Text::Regular, sf::Color::Red);

		index++;
	}

	//==================================TOOLS===============================

	//==PADDLE SPRITE==

	// Defined new paddle
	paddle = std::make_unique<sf::Sprite>();

	(*paddle).setTexture(statics.pdl_textures.at(CAPSULE_1), true);
	(*paddle).setScale(sf::Vector2f(paddle_scale_x, paddle_scale_y));
	(*paddle).setOrigin(sf::Vector2f(((*paddle).getLocalBounds().width / 2), 0.f));
	(*paddle).setPosition(sf::Vector2f(to_f(game_field.origin_x + game_field.overall_width / 2),
									   to_f(game_field.origin_y + game_field.overall_height - Default::block_height)));

	// std::cout << "Paddle drawn." << '\n';

	//==INIT BALL==

	// Defined new ball
	ball = std::make_unique<sf::Sprite>();

	(*ball).setTexture(statics.bll_texture, true);
	(*ball).setScale(sf::Vector2f(1.f, 1.f));
	(*ball).setOrigin(sf::Vector2f(((*ball).getLocalBounds().width / 2), ((*ball).getLocalBounds().height / 2)));
	(*ball).setPosition(sf::Vector2f(to_f(game_field.origin_x + game_field.overall_width / 2),
									 (to_f(game_field.origin_y + game_field.overall_height - Default::block_height) -
									  ((*ball).getLocalBounds().height / 2))));

	// std::cout << "Ball drawn." << '\n';

	//==================================BASEMENT===============================

	basement.setSize(sf::Vector2f(to_f(game_field.overall_width), to_f(game_field.overall_height)));
	basement.setFillColor(sf::Color::Black);
	basement.setPosition(sf::Vector2f(to_f(game_field.origin_x),
									  to_f(game_field.origin_y + game_field.overall_height + game_field.outside_thk)));

	//=================================PAUSE PAGE===============================

	pause_page.setSize(sf::Vector2f(to_f(outline.overall_width - 2 * outline.empty_thk),
									to_f(outline.overall_height - 2 * outline.empty_thk)));
	pause_page.setFillColor(sf::Color(255, 255, 255, to_i(0.6f * 255)));
	pause_page.setPosition(sf::Vector2f(to_f(outline.empty_thk), to_f(outline.empty_thk)));

	int picture_address{ 66 };
	Util::safe_parse(pause_texture, (pictures_path + std::to_string(picture_address) + Game::StaticUnits::adder_path),
					 (pictures_path + std::to_string(picture_address) + Game::StaticUnits::adder_path +
					  Game::StaticUnits::template_message)
						 .c_str());

	pause_icon.setTexture(pause_texture, true);
	pause_icon.setColor(sf::Color(255, 255, 255, to_i(0.8f * 255)));
	pause_icon.setOrigin(sf::Vector2f(pause_icon.getGlobalBounds().width / 2, pause_icon.getGlobalBounds().height / 2));
	pause_icon.setScale(sf::Vector2f(0.5f, 0.5f));
	pause_icon.setPosition(sf::Vector2f(to_f(outline.overall_width) / 2, to_f(outline.overall_height) / 2));
}
