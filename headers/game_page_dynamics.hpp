#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		   THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> DYNAMIC CODE UNITS			//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

// C++ headers
#include <random>
#include <ranges>
#include <vector>

// API

// SFML headers

// Custom headers
#include "game_page.hpp"
#include "util.hpp"

// #include "game_page_statics.hpp"
// #include "game_page_process.hpp"
// #include "game_page_executor.hpp"

// DEFINES

/// FUNCTION POINTER
using executor = void (*)(const int& operand);

// ENUMERATORS

enum t_kinematics
{
	DELTA_X = 0,
	V_X,
	A_X,
	DELTA_Y,
	V_Y,
	A_Y

};

// Forward Game namespace declaration in the 'game_page_dynamics.hpp'
namespace Game
{
	class StaticUnits;	   // forward declaration already declared class (game_page_dynamics.hpp)
	class DynamicUnits;	   // forward declaration already declared class (game_page_dynamics.hpp)
	class Process;		   // forward declaration already declared class (game_page_dynamics.hpp)

	// enum ability_textures;

	// Forward declaration
	struct block_map_variables
	{
		bool block{};	  // Here would be: true, if it is a block; and: false, if it is an ability
		int operand{};	  // Here we are passing operand for executor function: points to add, multiplier for speed,...
		executor function{};	// pointer to function that have to be executed
		std::vector<float> kinematics{ 0.f, 0.f, 0.f, 0.f, 0.f, 0.f };	  // keep kinematic parameters for the abilities
	};

};	  // namespace Game

class Game::DynamicUnits
{
public:
	DynamicUnits() = default;	 // default-constructor declaration
	DynamicUnits(const Game::StaticUnits& statics,
				 const Util::StaticUnits& utils);	 // constructor dependable on 'Game::StaticUnits' object declaration

	// INTERNAL CLASS UTILITIES

	// set one line of the conveyor
	void setLine(const Game::StaticUnits& statics, const bool& first);

	// get random number
	int getRandomNumber(const int& limit);

	// get random postions for game units: empties, abilities
	void getRandomPositions(const int& maxUnits, std::vector<int>& donor_positions,
							std::vector<int>& recipient_positions);

	// Update visibility of every '+100' ability block if there any such
	// void updatePlusHundredAbility(const Game::StaticUnits& utils);

	///<<<---INTERFACE

	// update score status
	void updateScore();

	// blink adder in the interface
	void blinkScoreAdder();

	// Update lifes visibility
	void updateLifeBalls(const Game::StaticUnits& statics);

	// Get initial texture by current state
	int getTextureNumber(const int& p_state);

	// If there was such ability: resize paddle
	void resizePaddle(const Game::StaticUnits& utils);

	// Update paddle texture depending on the time
	void updateElectricPaddle(const Game::StaticUnits& utils);

	// Adjust paddle sprite
	// void adjustPaddle();

	// Move down conveyor array
	void extendConveyor(const Game::StaticUnits& statics);

	// Update awaiting time label
	void updateExtAwaitTimer();

	// Update game time
	void updateGTime() noexcept;

	// update ball/paddle kinematics interface
	void updateParInterface(const std::vector<float>& kinematics, std::vector<sf::Text>& texts);

	///<<<---INTERFACE

	// SIMULATE BALL AWAIT

	// Until we are wait for the user response - we holding the ball
	void holdBall();

	// If ball were lost we are waiting some time and place ball to the paddle
	void waitForBall();

	// FINISH GAME: TO LONG BELT

	// If conveyor belt will touch top of the paddle - the game is over
	void checkLongBelt();

	// PROBABILITIES PATTERNS

	static inline const std::vector<int> ability_probability{
		PLUS_50,	 PLUS_50,	  PLUS_50,	   PLUS_50,		PLUS_50,	 PLUS_50,
		PLUS_50,	 PLUS_50,															 // 8 to 50  16%
		PLUS_100,	 PLUS_100,	  PLUS_100,	   PLUS_100,	PLUS_100,	 PLUS_100,		 // 6 to 50  12%
		PLUS_250,	 PLUS_250,	  PLUS_250,	   PLUS_250,								 // 4 to 50  8%
		PLUS_500,																		 // 1 to 50  2%
		SLOW,		 SLOW,		  SLOW,													 // 3 to 50  6%
		FAST,		 FAST,		  FAST,		   FAST,		FAST,		 FAST,			 // 6 to 50  12%
		THREE_BALLS, THREE_BALLS, THREE_BALLS, THREE_BALLS, THREE_BALLS, THREE_BALLS,	 // 6 to 50  12%
		MAKE_TINY,	 MAKE_TINY,															 // 2 to 50  4%
		MAKE_WIDE,	 MAKE_WIDE,	  MAKE_WIDE,   MAKE_WIDE,	MAKE_WIDE,					 // 5 to 50  10%
		EMPTY,		 EMPTY,		  EMPTY,	   EMPTY,		EMPTY,		 EMPTY,
		EMPTY,		 EMPTY,		  EMPTY	   // 9 to 50  18%
	};

	static inline const std::vector<int> block_probability{
		BLUE,	BLUE,	BLUE,	BLUE,	BLUE,	BLUE,	BLUE,	BLUE,	 // 8 to 50
		SALAD,	SALAD,	SALAD,	SALAD,	SALAD,	SALAD,	SALAD,			 // 7 to 50
		PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,			 // 7 to 50
		RED,	RED,	RED,	RED,	RED,	RED,	RED,			 // 7 to 50
		ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE,					 // 6 to 50
		SKY,	SKY,	SKY,	SKY,	SKY,							 // 5 to 50
		YELLOW, YELLOW, YELLOW, YELLOW,									 // 4 to 50
		GREEN,	GREEN,	GREEN,											 // 3 to 50
		GRAY,	GRAY,													 // 2 to 50
		BROWN															 // 1 to 50
	};

	// SPRITES

	// Conveyor
	std::vector<sf::Sprite> conveyor;

	// To each conveyor unit we will link a map: what to do with it when we destroy
	static inline std::vector<block_map_variables> conveyor_map;

	// Paddle
	std::unique_ptr<sf::Sprite> paddle;

	// Ball
	std::unique_ptr<sf::Sprite> ball;

	// Lifes
	std::vector<std::unique_ptr<sf::Sprite>> lifes_balls;
	static inline bool lost_ball{};

	// TEXT STATUSES

	sf::Text score_label;
	sf::Text score_add_label;

	sf::Text game_timer;

	sf::Text extender_countdown;
	sf::Text extender_await;

	std::vector<sf::Text> ball_parameters;
	std::vector<sf::Text> paddle_parameters;

	// BASEMENT PAINTING

	sf::RectangleShape basement;

	// PAUSE PAINTING

	sf::RectangleShape pause_page;
	sf::Sprite pause_icon;
	sf::Texture pause_texture;

	// PADDLE TEXTURE CHANGE HANDLERS

	static inline int paddle_state{};	 // current state of paddle signalized that it's a basic CAPSULE_1 variant
	static inline int paddle_ext{};		 // container for new state
	static inline const int paddle_max{ 75 };	  // we can extend paddle maximum by 75 pixels
	static inline const int paddle_min{ -75 };	  // we can adjust paddle maximum by 75 pixels

	static inline const std::vector<std::pair<int, int>> paddle_map	   // MAP to the new TEXTURE depending on the
																	   // extension value
		{ { -75, CAPSULE_0 },	  { -50, CAPSULE_1_M200 }, { -25, CAPSULE_1_M100 }, { 0, CAPSULE_1 },
		  { 25, CAPSULE_1_P100 }, { 50, CAPSULE_1_P200 },  { 75, CAPSULE_1_P300 } };

	// VARIABLES PHYSICS

	// BALL
	static inline std::vector<float> ball_kinematics;
	static inline const float bll_friction{ 6.0f };
	static inline float bll_V_step{ 400.0f };
	static inline const float bll_max{ 1200.0f };
	static inline const float bll_min{ 100.0f };
	// static inline const float bll_A_step{ 1800.0f };  //NOT so necessary
	static inline const float bll_bounce{ 0.6f };
	static inline const float bll_mult{ 2.0f };

	// PADDLE
	static inline std::vector<float> paddle_kinematics;
	static inline const float pdl_friction{ 5.f };	  // 7.f
	static inline const float pdl_V_step{ 1000.0f };
	static inline const float pdl_A_step{ 5000.0f };	// 180000.f
	static inline const float pdl_bounce{ -0.2f };

	// ABILITIES
	static inline const float abl_friction{ .0f };
	static inline const float abl_V_step{ 300.0f };
	static inline const float abl_bounce{ 0.15f };
	static inline const float abl_mult{ 8.0f };

	// VARIABLES TIMERS

	// static inline float plus_abl_updater{};

	//___Belt extender
	static inline float to_extend_await{};
	static inline float extender_timer{};

	//___Score adder blink
	static inline const float score_adder_appear_await{ 1.f };
	static inline float score_add_timer{};

	//___
	static inline float game_time{};

	//___Paddle
	static inline const float paddle_upd_await{ 0.05f };
	static inline float pdl_upd_timer{};

	static inline float paddle_scale_x{ 0.25f };
	static inline float paddle_scale_y{ 0.25f };
	// static inline const float paddle_scale_x_max{0.9f};
	// static inline const float paddle_scale_x_min{0.1f};
	// static inline const float paddle_scale_step{0.05f};

	//___Lost ball awaiting
	static inline const float to_new_ball_await{ 2.f };
	static inline float ball_timer{};

	// VARIABLES STATUSES

	static inline int score{};
	static inline int score_adder{};
	static inline const int score_max{ 999999 };

	static inline int lifes{ 9 };
	static inline const int lifes_max{ 27 };

	static inline const std::vector<int> lifes_indexer{ 0,	9, 18, 1,  10, 19, 2,  11, 20, 3,  12, 21, 4, 13,
														22, 5, 14, 23, 6,  15, 24, 7,  16, 25, 8,  17, 26 };

	// Are we hold ball on the paddle?
	static inline bool catched_ball{ true };

	// static inline const float plus_abl_await{0.5f};

	// UTILITIES
	static inline const std::string pictures_path{ "assets/pictures/" };
};

static inline void increaseScore(const int& operand)
{
	Game::DynamicUnits::score += operand;
	Game::DynamicUnits::score_adder = operand;
}

static inline void chageBallSpeed(const int& operand)
{
	Game::DynamicUnits::bll_V_step += to_f(operand);

	if (Game::DynamicUnits::bll_V_step > Game::DynamicUnits::bll_max)
		Game::DynamicUnits::bll_V_step = Game::DynamicUnits::bll_max;

	if (Game::DynamicUnits::bll_V_step < Game::DynamicUnits::bll_min)
		Game::DynamicUnits::bll_V_step = Game::DynamicUnits::bll_min;
}

static inline void increaseLifes(const int& operand) { Game::DynamicUnits::lifes += operand; }

static inline void adjustPaddleSize(const int& operand)
{
	Game::DynamicUnits::paddle_ext += operand;

	if ((Game::DynamicUnits::paddle_ext > Game::DynamicUnits::paddle_max))
	{
		Game::DynamicUnits::paddle_ext = Game::DynamicUnits::paddle_max;
		return;
	}
	else if ((Game::DynamicUnits::paddle_ext < Game::DynamicUnits::paddle_min))
	{
		Game::DynamicUnits::paddle_ext = Game::DynamicUnits::paddle_min;
		return;
	}
}

static inline void emptyFunc(const int& operand) { return; }

static inline std::vector<executor> abl_function_map{ increaseScore,	increaseScore,	increaseScore, increaseScore,
													  chageBallSpeed,	chageBallSpeed, increaseLifes, adjustPaddleSize,
													  adjustPaddleSize, emptyFunc

};

static inline std::vector<executor> blk_function_map{ increaseScore, increaseScore, increaseScore, increaseScore,
													  increaseScore, increaseScore, increaseScore, increaseScore,
													  increaseScore, increaseScore

};
