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
//#include "game_page_process.hpp"


//DEFINES
#define to_i(lvalue) static_cast<int>(lvalue)


//Forward Game namespace declaration in the 'game_page_dynamics.hpp'
namespace Game
{
	class staticUnits;  //forward declaration already declared class (game_page_dynamics.hpp)
	class dynamicUnits;  //forward declaration already declared class (game_page_dynamics.hpp)
	class Process;  //forward declaration already declared class (game_page_dynamics.hpp)
	
	enum ability_textures;

};

class Game::dynamicUnits
{
	public:
	
	dynamicUnits() = default;																//default-constructor declaration
	dynamicUnits(const Game::staticUnits& statics, const Util::staticUnits& utils);			//constructor dependable on 'Game::staticUnits' object declaration

	//set one line of the conveyor
	void setLine(const Game::staticUnits& statics, const bool& first);

	//get random number
	int getRandomNumber(const int& limit);

	//get random postions for game units: empties, abilities
	void getRandomPositions(const int& maxUnits, std::vector<int>& donor_positions, std::vector<int>& recipient_positions);

	//Update visibility of every '+100' ability block if there any such
	//void updatePlusHundredAbility(const Game::staticUnits& utils);

	//Update paddle texture depending on the time
	void updateElectricPaddle(const Game::staticUnits& utils);

	//Adjust paddle sprite
	void adjustPaddle();

	//Move down conveyor array
	void extendConveyor(const Game::staticUnits& statics);

	//Update game time
	void updateGTime() noexcept;

	//PROBABILITIES PATTERNS

	std::vector<int> ability_probability
	{
		PLUS_50,PLUS_50,PLUS_50,PLUS_50,PLUS_50,PLUS_50,PLUS_50,PLUS_50,				//8 to 50  16%
		PLUS_100,PLUS_100,PLUS_100,PLUS_100,PLUS_100,PLUS_100,							//6 to 50  12%
		PLUS_250,PLUS_250,PLUS_250,PLUS_250,											//4 to 50  8%
		PLUS_500,																		//1 to 50  2%
		SLOW,SLOW,SLOW,																	//3 to 50  6%
		FAST,FAST,FAST,FAST,FAST,FAST,													//6 to 50  12%
		THREE_BALLS,THREE_BALLS,THREE_BALLS,THREE_BALLS,THREE_BALLS,THREE_BALLS,		//6 to 50  12%
		MAKE_TINY,MAKE_TINY,															//2 to 50  4%
		MAKE_WIDE,MAKE_WIDE,MAKE_WIDE,MAKE_WIDE,MAKE_WIDE,								//5 to 50  10%
		EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY							//9 to 50  18%
	};

	std::vector<int> block_probability
	{
		BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,			//8 to 50
		SALAD,SALAD,SALAD,SALAD,SALAD,SALAD,SALAD,			//7 to 50
		PURPLE,PURPLE,PURPLE,PURPLE,PURPLE,PURPLE,PURPLE,	//7 to 50
		RED,RED,RED,RED,RED,RED,RED,						//7 to 50
		ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,			//6 to 50
		SKY,SKY,SKY,SKY,SKY,								//5 to 50
		YELLOW,YELLOW,YELLOW,YELLOW,						//4 to 50
		GREEN,GREEN,GREEN,									//3 to 50
		GRAY,GRAY,											//2 to 50
		BROWN												//1 to 50
	};

	//SPRITES

	//Conveyor
	std::vector<std::unique_ptr<sf::Sprite>> conveyor;

	//Paddle
	std::unique_ptr<sf::Sprite> paddle;

	//Ball
	std::unique_ptr<sf::Sprite> ball;

	//Lifes
	std::vector<std::unique_ptr<sf::Sprite>> lifes_balls;

	//TEXT PARAMETERS

	sf::Text game_timer;
	sf::Text extender_countdown;

	//VARIABLES

	//Timers

	//static inline float plus_abl_updater{};
	
	//___Belt extender
	static inline const float to_extend_await{ 15.f };
	static inline float extender_timer{ to_extend_await };

	//___
	static inline float game_time{};

	//___Paddle
	static inline const float paddle_upd_await{ 0.05f };
	static inline float pdl_upd_timer{};

	static inline float paddle_scale_x{0.25f};
	static inline const float paddle_scale_x_max{0.9f};
	static inline const float paddle_scale_x_min{0.1f};
	static inline const float paddle_scale_step{0.05f};

	//Lifes
	static inline int lifes{9};
	static inline const int lifes_max{27};
	
	//static inline const float plus_abl_await{0.5f};

};
