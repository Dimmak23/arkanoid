#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		   THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME -> STATICS CODE UNITS			//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//* C++ std

//* SFML
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>

//* Custom
#include "game_page.hpp"
#include "util.hpp"

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

// Forward Game namespace declaration in the 'game_page_statics.hpp'
namespace Game
{
	class StaticUnits;	   // forward declaration already declared class (game_page_statics.hpp)
	class DynamicUnits;	   // forward declaration already declared class (game_page_statics.hpp)

	// forward declaration already declared function
	static void initialize_frame(sf::RectangleShape& rect, const float& size_x, const float& size_y,
								 const sf::Color& border_color,	   // Black, White, Red, Green, Blue, Yellow, Magenta,
																   // Cyan, Transparent
								 const sf::Color& fill_color,	   // Black, White, Red, Green, Blue, Yellow, Magenta,
																   // Cyan, Transparent
								 const float& thikness, const float& pos_x, const float& pos_y) noexcept;

};	  // namespace Game

// class definition
class Game::StaticUnits
{
public:
	StaticUnits() = default;						// default-constructor declaration
	StaticUnits(const Util::StaticUnits& utils);	// constructor dependable on 'Util::StaticUnits' object declaration

	// BASIC FRAMES

	sf::RectangleShape legend_frame;
	sf::RectangleShape game_frame;
	sf::RectangleShape status_frame;

	// CONVEYOR EXTENSION LABEL LINES

	std::vector<sf::RectangleShape> extension_lines;

	//! REMEMBER: Fonts, Texts, Textures, ContextSettings,...(what else?) - can't be global. They should be someone's
	//! property

	// LEGEND LABELS

	sf::Text blocks_label;
	sf::Text abilities_label;

	// BLOCKS DESCRIPTIONS

	std::vector<sf::Text> blocks_descriptions;

	// ABILITIES DESCRIPTIONS

	std::vector<sf::Text> abilities_descriptions;

	static inline const std::vector<std::string> ab_names{ "+50 points",
														   "+100 points",
														   "+250 points",
														   "+500 points",
														   "Makes ball slower by 100 px/sec",
														   "Makes ball faster by 100 px/sec",
														   "Add 3 lifes",
														   "Makes paddle tinier by 25 px",
														   "Makes paddle wider by 25 px",
														   "Gives you nothing" };

	// STATUS LABELS

	std::vector<sf::Text> status_labels;
	std::vector<sf::Text> ball_parameters;
	std::vector<sf::Text> paddle_parameters;

	// sf::Text timer_adder;
	// sf::Text countdown_adder;

	static inline const std::vector<std::string> st_names{
		"Score:", "Lifes:", "Timer:", "Till the next row:", "Ball parameters:", "Paddle parameters:"
	};

	// static inline const std::string sec{ "sec" };

	static inline const std::vector<float> pos_y_st_labels{ 20.f, 120.f, 300.f, 400.f, 800.f, 1000.f };

	static inline const std::vector<std::string> parameters_names{ "dx:", "Vx:", "Ax:", "dy:", "Vy:", "Ay:" };

	// STATUS SHAPES

	std::vector<sf::CircleShape> lifes_outline;
	static inline const int MAX_LIFES{ 27 };

	std::vector<sf::RectangleShape> ball_p_frames;
	std::vector<sf::RectangleShape> paddle_p_frames;

	// TEXTURES

	//___BLOCKS
	std::vector<sf::Texture> blk_textures;

	//___ABILITY
	std::vector<int> skipped_abl_textures_addresses{ 32, 33, 34, 35, 36, 37, 44, 45, 48 };
	std::vector<sf::Texture> abl_textures;

	//___BALL
	sf::Texture bll_texture;

	//___PADDLES
	std::vector<int> skipped_pdl_textures_addresses{ 53, 54, 55 };
	std::vector<sf::Texture> pdl_textures;

	// SPRITES

	std::vector<sf::Sprite> blk_sprites;
	std::vector<sf::Sprite> abl_sprites;

	// UTILITIES

	static inline const std::string textures_path{ "assets/textures/" };
	static inline const std::string adder_path{ "-Breakout-Tiles.png" };
	static inline const std::string template_message{ " <--- Can't find texture source file in this location...\n" };
};
