#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//		THIS THE STORAGE FOR UTILITIES USABLE IN THE ALL CODE UNITS (INTRO, GAME, OUTRO)	//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//C++ headers
//#include <stdint.h>
#include <Windows.h>
#include <iostream>
#include <memory>

//API


//SFML headers
//#include <SFML/System/Vector2.hpp>//???
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

//Custom headers
#include "outline.hpp"

//Tired to write long hard readeble code
#define to_f(lvalue) static_cast<float>(lvalue)

//static sf::Vector2f individual_nscale(const float& nscale, sf::Vector2f indi_sprite)//???
//{
//	indi_sprite *= nscale;
//	return indi_sprite;
//}

namespace Util
{
	class staticUnits;
	
	class Process;

	template <typename Parsable>
	static void safe_parse(Parsable& destination, const std::string& path, const char* message) noexcept;
	
	static void initialize_text(
		sf::Text& label,				//destination
		const std::string& value,		//value that would be written
		const sf::Font& font,			//what font
		const int& char_s,				//characters size
		const bool& self_centered,		//should it be self-centered
		const float& pos_x,				//position by x
		const float& pos_y,				//position by y
		const uint32_t& style,			//Regular, Bold, Italic, Underlined, StrikeThrough
		const sf::Color& color			//Black, White, Red, Green, Blue, Yellow, Magenta, Cyan, Transparent

	) noexcept;

};

//This could be a template for Fonts and texture parse
template <typename Parsable>
inline void Util::safe_parse(Parsable& destination, const std::string& path, const char* message) noexcept
{
	bool parsing_result = destination.loadFromFile(path);
	try
	{
		if (!(parsing_result)) throw std::exception(message);
		else std::cout << "Parsed: " << path << "\n";

	}
	catch (const std::exception& logo_font_error)
	{
		std::cout << logo_font_error.what() << '\n';
	}
}

//This could be used for other Texts in other namespaces
inline void Util::initialize_text(
	sf::Text& label,				//destination
	const std::string& value,		//value that would be written
	const sf::Font& font,			//what font
	const int& char_s,				//characters size
	const bool& self_centered,		//should it be self-centered
	const float& pos_x,				//position by x
	const float& pos_y,				//position by y
	const uint32_t& style,			//Regular, Bold, Italic, Underlined, StrikeThrough
	const sf::Color& color			//Black, White, Red, Green, Blue, Yellow, Magenta, Cyan, Transparent

) noexcept
{
	label.setString(value);
	label.setFont(font);
	label.setCharacterSize(char_s);
	
	if (self_centered)
	{	
		//Now as we have changed font and character size: we have approved width and height
		//on wheich we can orient
		label.setOrigin(sf::Vector2f
		(
			label.getGlobalBounds().width / 2,
			label.getGlobalBounds().height / 2)
		);
	}
	//otherwise center is sf::Vector2f(0, 0)

	//Position depend on the one that we have set up in the outline
	label.setPosition(sf::Vector2f(pos_x, pos_y));
	
	label.setStyle(style);
	label.setFillColor(color);
}

class Util::staticUnits
{
	public:

		staticUnits();  //constructor declaration

	public:

		//! REMEMBER: Fonts, Texts, Textures, ContextSettings,...(what else?) - can't be global. They should be someone's property
		sf::Font logo_font;
		sf::Font main_font;

		//Sharable event
		//static inline sf::Event event{};

	private:

		//Be sure that here we parse independently on the Debug, Release, and USAGE
		//<-
		static inline const std::string logoFontPath{ "data/fonts/70-Breakout-Tiles.ttf" };
		static inline const std::string mainFontPath{ "data/fonts/71-Breakout-Tiles.ttf" };
		//<-

		static inline const char* logoFontParseError{ "_____logo font parse error...\n" };
		static inline const char* mainFontParseError{ "_____main font parse error...\n" };

};

//Constructor definition
inline Util::staticUnits::staticUnits()
{
	safe_parse(logo_font, logoFontPath, logoFontParseError);
	safe_parse(main_font, mainFontPath, mainFontParseError);

}

class Util::Process
{
	public:
	
		static void resetStartPoint();

		static void updateDelta();
	
		static inline LARGE_INTEGER frame_begin_time{};		//main timer clock start point

		static inline float perfomance_frequancy{};			//main frequancy: how mane cycles(frames) in one second

		static inline LARGE_INTEGER frame_end_time{};		//main timer clock end point

		static inline float delta_time { 0.016666f };

};

inline void Util::Process::resetStartPoint()
{
	//Get CPU time
	QueryPerformanceCounter(&frame_begin_time); // here we start to calculate time in the CPU units
	
	//Cycles(frames) in one second
	LARGE_INTEGER perf{};
	QueryPerformanceFrequency(&perf);
	perfomance_frequancy = to_f(perf.QuadPart); // this return how mane cycles(frames) in one second
}

inline void Util::Process::updateDelta()
{
	// here we finish to calculate time in the CPU units
	QueryPerformanceCounter(&frame_end_time);

	//static_cast<float>(frame_end_time.QuadPart - frame_begin_time.QuadPart) - this gives you how many cycles were spent on the current frame
	delta_time = to_f(frame_end_time.QuadPart - frame_begin_time.QuadPart) / perfomance_frequancy; // time in seconds
	frame_begin_time = frame_end_time; // here we start to measure delta_time of the new frame
}
