#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////
//										    												//
//										    												//
//				THIS THE STORAGE FOR FUNCTIONAL USABLE IN THE GAME CODE UNITS				//
//										    												//
//										    												//
//////////////////////////////////////////////////////////////////////////////////////////////

//C++ headers
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>

//API


//SFML headers
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

//Custom headers
#include "util.hpp"

//dependable headers with some class definitions
#include "game_page_statics.hpp"
#include "game_page_dynamics.hpp"

//First Game namespace declaration
namespace Game
{
	class staticUnits;
	class dynamicUnits;
	class Process;

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

void Game::initialize_frame(
	sf::RectangleShape& rect,
	const float& size_x,
	const float& size_y,
	const sf::Color& border_color,			//Black, White, Red, Green, Blue, Yellow, Magenta, Cyan, Transparent
	const sf::Color& fill_color,			//Black, White, Red, Green, Blue, Yellow, Magenta, Cyan, Transparent
	const float& thikness,
	const float& pos_x,
	const float& pos_y
) noexcept
{
	rect.setSize(sf::Vector2f(size_x, size_y));					//Size it
	rect.setOutlineColor(border_color);							//Color it border
	rect.setFillColor(fill_color);								//Color background
	rect.setOutlineThickness(thikness);		//Set thikness, -<value>: outline inside, +<value>: outline outside
	rect.setPosition(sf::Vector2f(pos_x, pos_y));
}
