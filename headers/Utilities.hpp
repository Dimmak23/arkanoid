#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		THIS THE STORAGE FOR UTILITIES USABLE IN THE ALL CODE UNITS (INTRO, GAME, OUTRO)	//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//* WinAPI
#include <Windows.h>

//* C++ STD
#include <iostream>
#include <memory>
#include <stdexcept>

//* SFML
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

//* Custom
#include "outline.hpp"

// Tired to write long hard readeble code
#define to_f(lvalue) static_cast<float>(lvalue)
#define to_i(lvalue) static_cast<int>(lvalue)

// Abilities textures enumerator from 'util.hpp'
enum ability_textures
{
	PLUS_50 = 0,
	// PLUS_100_1,
	// PLUS_100_2,
	// PLUS_100_3,
	// PLUS_100_4,
	// PLUS_100_5,
	// PLUS_100_6,
	PLUS_100,
	PLUS_250,
	PLUS_500,
	SLOW,
	FAST,
	THREE_BALLS,
	// RED_FIRE,
	// GREEN_FIRE,
	MAKE_TINY,
	MAKE_WIDE,
	// WITH_TOKEN,
	EMPTY,

	ABILITY_COUNT	 // 10, 9 textures currently not available NOW
};

// Blocks textures enumerator from 'util.hpp'
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

	BLK_T_COUNT = 20	// 10
};

enum paddle_textures
{
	CAPSULE_0 = 0,
	CAPSULE_1_M200,
	CAPSULE_2_M200,
	CAPSULE_3_M200,
	CAPSULE_1_M100,
	CAPSULE_2_M100,
	CAPSULE_3_M100,
	CAPSULE_1,
	CAPSULE_2,
	CAPSULE_3,
	CAPSULE_1_P100,
	CAPSULE_2_P100,
	CAPSULE_3_P100,
	CAPSULE_1_P200,
	CAPSULE_2_P200,
	CAPSULE_3_P200,
	CAPSULE_1_P300,
	CAPSULE_2_P300,
	CAPSULE_3_P300,
	// CONNECTOR_1,
	// CONNECTOR_2,
	// CONNECTOR_3,
	// WIDE,			//NO NEED
	// TINY,			//NO NEED

	PADDLE_COUNT	// 3: three not available now, 2 not needed
};

namespace Utilities
{
	class StaticUnits;

	class Process;

	template <typename Parsable>
	static void safe_parse(Parsable& destination, const std::string& path, const char* message) noexcept;

	static void initialize_text(sf::Text& label,			  // destination
								const std::string& value,	  // value that would be written
								const sf::Font& font,		  // what font
								const int& char_s,			  // characters size
								const bool& self_centered,	  // should it be self-centered
								const float& pos_x,			  // position by x
								const float& pos_y,			  // position by y
								const uint32_t& style,		  // Regular, Bold, Italic, Underlined, StrikeThrough
								const sf::Color& color		  // Black, White, Red, Green, Blue, Yellow, Magenta, Cyan,
															  // Transparent

								) noexcept;

	static inline const std::vector<int> block_values{ // points to add
													   1, 2, 5, 10, 15, 20, 25, 30, 35, 40
	};

	static inline const std::vector<int> ability_values{
		// points to add
		50, 100, 250, 500,
		// decrease/increase ball speed by 100 pix/sec from current speed
		-100, 100,
		// add 3 lifes
		3,
		// substract/add paddle width by 25 pix from inital width
		-25, 25,
		// empty ability
		0
	};

};	  // namespace Utilities

//? This could be a template for Fonts and texture parse
template <typename Parsable>
inline void Utilities::safe_parse(Parsable& destination, const std::string& path, const char* message) noexcept
{
	bool parsing_result = destination.loadFromFile(path);
	try
	{
		if (!(parsing_result)) throw std::invalid_argument(message);
		// else std::cout << "Parsed: " << path << "\n";
	}
	catch (const std::invalid_argument& logo_font_error)
	{
		std::cout << logo_font_error.what() << '\n';
	}
}

// This could be used for other Texts in other namespaces
inline void Utilities::initialize_text(sf::Text& label,				 // destination
									   const std::string& value,	 // value that would be written
									   const sf::Font& font,		 // what font
									   const int& char_s,			 // characters size
									   const bool& self_centered,	 // should it be self-centered
									   const float& pos_x,			 // position by x
									   const float& pos_y,			 // position by y
									   const uint32_t& style,		 // Regular, Bold, Italic, Underlined, StrikeThrough
									   const sf::Color& color		 // Black, White, Red, Green, Blue, Yellow, Magenta,
																	 // Cyan, Transparent

									   ) noexcept
{
	label.setString(value);
	label.setFont(font);
	label.setCharacterSize(char_s);

	if (self_centered)
	{
		// Now as we have changed font and character size: we have approved width and height
		// on wheich we can orient
		label.setOrigin(sf::Vector2f(label.getGlobalBounds().width / 2, label.getGlobalBounds().height / 2));
	}
	// otherwise center is sf::Vector2f(0, 0)

	// Position depend on the one that we have set up in the outline
	label.setPosition(sf::Vector2f(pos_x, pos_y));

	label.setStyle(style);
	label.setFillColor(color);
}

class Utilities::StaticUnits
{
public:
	StaticUnits();	  // constructor declaration

public:
	//! REMEMBER: Fonts, Texts, Textures, ContextSettings,...(what else?) - can't be global. They should be someone's
	//! property
	sf::Font logo_font;
	sf::Font main_font;
	sf::Font score_font;

	// Sharable event
	// static inline sf::Event event{};

private:
	// Be sure that here we parse independently on the Debug, Release, and USAGE
	//<-
	static inline const std::string logoFontPath{ "assets/fonts/70-Breakout-Tiles.ttf" };
	static inline const std::string mainFontPath{ "assets/fonts/71-Breakout-Tiles.ttf" };
	static inline const std::string scoreFontPath{ "assets/fonts/73-Breakout-Tiles.ttf" };
	//<-

	static inline const char* logoFontParseError{ "_____logo font parse error...\n" };
	static inline const char* mainFontParseError{ "_____main font parse error...\n" };
	static inline const char* scoreFontParseError{ "_____score font parse error...\n" };
};

// Constructor definition
inline Utilities::StaticUnits::StaticUnits()
{
	// std::cout << "Utilities::StaticUnits construction\n";

	safe_parse(logo_font, logoFontPath, logoFontParseError);
	safe_parse(main_font, mainFontPath, mainFontParseError);
	safe_parse(score_font, scoreFontPath, scoreFontParseError);
}

class Utilities::Process
{
public:
	static void resetStartPoint();

	static void updateDelta();

	static inline LARGE_INTEGER frame_begin_time{};	   // main timer clock start point

	static inline float perfomance_frequancy{};	   // main frequancy: how mane cycles(frames) in one second

	static inline LARGE_INTEGER frame_end_time{};	 // main timer clock end point

	static inline float delta_time{ 0.016666f };

	// Running status of the Game
	static inline bool running{ true };
};

inline void Utilities::Process::resetStartPoint()
{
	// Get CPU time
	QueryPerformanceCounter(&frame_begin_time);	   // here we start to calculate time in the CPU units

	// Cycles(frames) in one second
	LARGE_INTEGER perf{};
	QueryPerformanceFrequency(&perf);
	perfomance_frequancy = to_f(perf.QuadPart);	   // this return how mane cycles(frames) in one second
}

inline void Utilities::Process::updateDelta()
{
	// here we finish to calculate time in the CPU units
	QueryPerformanceCounter(&frame_end_time);

	// static_cast<float>(frame_end_time.QuadPart - frame_begin_time.QuadPart) - this gives you how many cycles were
	// spent on the current frame
	delta_time = to_f(frame_end_time.QuadPart - frame_begin_time.QuadPart) / perfomance_frequancy;	  // time in seconds
	frame_begin_time = frame_end_time;	  // here we start to measure delta_time of the new frame
}
