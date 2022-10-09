#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		   THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> STATICS CODE UNITS			//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//C++ headers


//API


//SFML headers


//Custom headers
#include "util.hpp"
#include "game_page.hpp"

enum block_textures
{
	BLUE = 0,
	SALAD = 2,
	PURPLE = 4,
	RED = 6,
	ORANGE = 8,
	SKY = 10,
	YELLOW = 12,
	GREEN = 14,
	GRAY = 16,
	BROWN = 18,

	BLK_T_COUNT = 20 //10
};

enum ability_textures
{
	PLUS_50 = 0,
	PLUS_100_1,
	PLUS_100_2,
	PLUS_100_3,
	PLUS_100_4,
	PLUS_100_5,
	PLUS_100_6,
	PLUS_250,
	PLUS_500,
	SLOW,
	FAST,
	THREE_BALLS,
	//RED_FIRE,
	//GREEN_FIRE,
	MAKE_TINY,
	MAKE_WIDE,
	//WITH_TOKEN,
	EMPTY,

	ABILITY_COUNT //15, three textures currently not available NOW
};

enum status_lbls
{
	SCORE_LABEL = 0,
	LIFES_LABEL,
	TIMER_LABEL,
	REV_COUNT_LABEL,
	BALL_LABEL,
	PADDLE_LABEL,

	STAT_LBL_COUNT
};

//Forward Game namespace declaration in the 'game_page_statics.hpp'
namespace Game
{
	class staticUnits;  //forward declaration already declared class (game_page_statics.hpp)

	//forward declaration already declared function
	static void initialize_frame(
		sf::RectangleShape& rect,
		const float& size_x,
		const float& size_y,
		const sf::Color& border_color,			//Black, White, Red, Green, Blue, Yellow, Magenta, Cyan, Transparent
		const sf::Color& fill_color,			//Black, White, Red, Green, Blue, Yellow, Magenta, Cyan, Transparent
		const float& thikness,
		const float& pos_x,
		const float& pos_y
	) noexcept;
};

//class definition
class Game::staticUnits
{
	public:

	staticUnits() = default;								//default-constructor declaration
	staticUnits(const Util::staticUnits& utils);			//constructor dependable on 'Util::staticUnits' object declaration

	//BASIC FRAMES

	sf::RectangleShape legend_frame;
	sf::RectangleShape game_frame;
	sf::RectangleShape status_frame;

	//! REMEMBER: Fonts, Texts, Textures, ContextSettings,...(what else?) - can't be global. They should be someone's property

	//LEGEND LABELS

	sf::Text blocks_label;
	sf::Text abilities_label;

	//BLOCKS DESCRIPTIONS

	std::vector<sf::Text> blocks_descriptions;

	static inline const std::vector<std::string> bd_names
	{
		"2 hit's to break, +5 points",
		"3 hit's to break, +10 points",
		"3 hit's to break, +10 points",
		"3 hit's to break, +10 points",
		"4 hit's to break, +15 points",
		"4 hit's to break, +15 points",
		"4 hit's to break, +15 points",
		"6 hit's to break, +25 points",
		"8 hit's to break, +30 points",
		"10 hit's to break, +40 points"
	};

	//ABILITIES DESCRIPTIONS

	std::vector<sf::Text> abilities_descriptions;

	static inline const std::vector<std::string> ab_names
	{
		"+50 points",
		"+100 points",
		"+250 points",
		"+500 points",
		"Drops blocks slower",
		"Drops blocks faster",
		"Add 3 lifes",
		"Makes paddle tinier",
		"Makes paddle wider",
		"Gives you nothing"
	};

	//STATUS LABELS

	std::vector<sf::Text> status_labels;
	std::vector<sf::Text> ball_parameters;
	std::vector<sf::Text> paddle_parameters;

	static inline const std::vector<std::string> st_names
	{
		"Score:",
		"Lifes:",
		"Timer:",
		"Till the next row:",
		"Ball parameters:",
		"Paddle parameters:"
	};

	static inline const std::vector<float> pos_y_st_labels
	{
		20.f,
		120.f,
		300.f,
		400.f,
		800.f,
		1000.f
	};

	static inline const std::vector<std::string> parameters_names
	{
		"x:",
		"y:",
		"Vx:",
		"Vy:",
		"Ax:",
		"Ay:"
	};

	//STATUS SHAPES

	std::vector<sf::CircleShape> lifes_outline;
	static inline const int MAX_LIFES{ 27 };

	std::vector<sf::RectangleShape> ball_p_frames;
	std::vector<sf::RectangleShape> paddle_p_frames;

	//TEXTURES

	std::vector<sf::Texture> blk_textures;
	std::vector<int> skipped_abl_textures_addresses{ 38, 44, 45, 48 };
	std::vector<sf::Texture> abl_textures;

	//SPRITES

	std::vector<sf::Sprite> blk_sprites;
	std::vector<sf::Sprite> abl_sprites;

	//UTILITIES

	static inline const std::string textures_path{ "data/textures/" };
	static inline const std::string adder_path{ "-Breakout-Tiles.png" };
	static inline const std::string template_message{ " <--- Can't find texture source file in this location...\n" };

};
